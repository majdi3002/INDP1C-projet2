#include <bits/stdc++.h>


using namespace std;


class Istorage {
protected:
    string fileName = "dataset.txt";

public:
    virtual void addUser(const string&, const string&, const string&) = 0;
    virtual vector<tuple<string, string, string>> getAlldata() = 0;
    virtual bool userExists(const string& Username)=0;
    virtual tuple<bool, string, string> getUserInfo(const string& Username)=0;
    virtual ~Istorage() {}
};


class FileManager : public Istorage {
public:
    void addUser(const string& Username, const string& HashedPassword, const string& salt) override {
        if (userExists(Username)) {
            cout << "Error: Username '" << Username << "' already exists. Choose another username.\n";
            return;
        }
        else{
        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            outFile << Username << "," << HashedPassword << "," << salt << endl;
            outFile.close();
            cout << "User " << Username << " added successfully!\n";
        } else {
            cerr << "ERROR WHILE ADDING USER" << endl;
        }}
    }

    vector<tuple<string, string, string>> getAlldata() override {
        vector<tuple<string, string, string>> users;
        ifstream inFile(fileName);

        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string Username, HashedPassword, salt;

                if (getline(ss, Username, ',') &&
                    getline(ss, HashedPassword, ',') &&
                    getline(ss, salt, ',')) {
                    users.emplace_back(Username, HashedPassword, salt);
                }
            }
            inFile.close();
        } else {
            cerr << "Unable to get user DATA" << endl;
        }
        return users;
    }

    bool userExists(const string& Username) {
        vector<tuple<string, string, string>> users = getAlldata();
        for (const auto& [uname, pass, s] : users) {
            if (uname == Username) {
                return true;
            }
        }
        return false;
    }

    tuple<bool, string, string> getUserInfo(const string& Username) {
        vector<tuple<string, string, string>> users = getAlldata();
        for (const auto& [uname, pass, s] : users) {
            if (uname == Username) {
                return {true,pass, s}; // Return found user info
            }
        }
        return {false, "", ""}; // User not found
    }
};


class SaltGenerator {
public:
    static string generateSalt(int length = 8) {
        string salt;
        const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        int charSize = sizeof(characters) - 1;
        srand(time(0));

        for (int i = 0; i < length; ++i) {
            salt += characters[rand() % charSize];
        }

        return salt;
    }
};


class IHash {
    protected:
        string password;
        string salt;
    public:
        IHash(){}
        virtual string hashPassword() = 0;
        virtual ~IHash() = default;
    };
    
    class Hasher : public IHash {
    public:
        Hasher(const string& pass,const string& sal){
            password=pass;
            salt=sal;
        }
        string hashPassword() override {
            string alternated = alternate_characters(password, salt);
            string hashed = to_hex(alternated);
            return hashed;
        }
    
    private:
        string alternate_characters(const string& password, const string& salt) {
            string result;
            size_t max_length = max(password.length(), salt.length());
            for (size_t i = 0; i < max_length; i++) {
                if (i < password.length()) {
                    result += password[i];
                }
                if (i < salt.length()) {
                    result += salt[i];
                }
            }
            return result;
        }
    
        string to_hex(const string& input) {
            stringstream ss;
            for (char c : input) {
                ss << hex << setw(2) << setfill('0') << (int)c;
            }
            return ss.str();
        }
    };

    class IValidator {
        public:
            virtual ~IValidator() = default;
            virtual bool validate(const string& input) const = 0;
        };
        
        class PasswordValidator : public IValidator {
        public:
            bool validate(const string& password) const override {
                if (password.length() < 8) return false;
        
                bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
                string specialChars = "@#$%^&*()_+!~";
        
                for (char ch : password) {
                    if (isupper(ch)) hasUpper = true;
                    else if (islower(ch)) hasLower = true;
                    else if (isdigit(ch)) hasDigit = true;
                    else if (specialChars.find(ch) != string::npos) hasSpecial = true;
                }
        
                return hasUpper && hasLower && hasDigit && hasSpecial;
            }
        };


class IuserService {
protected:
    FileManager fileManager;
public:
    virtual void RegisterUser(const string& username, const string& password) = 0;
    virtual bool LoginUser(const string& username, const string& password) = 0;
};


class UserService : protected IuserService {

public:
    void RegisterUser(const string& username, const string& password) override {
        
        string salt = SaltGenerator::generateSalt(8);
        Hasher hasher(password,salt);
        string hashedPassword=hasher.hashPassword();
        fileManager.addUser(username, hashedPassword, salt);
    }

    bool LoginUser(const string& username, const string& password) override {
        auto [exists, storedHashedPassword, salt] = fileManager.getUserInfo(username);

        if (!exists) {
            cout << "Login Failed: Username does not exist.\n";
            return false;
        }
        Hasher hasher(password,salt);
        string enteredHashedPassword = hasher.hashPassword();
        if (enteredHashedPassword == storedHashedPassword) {
            cout << "Login Successful! Welcome, " << username << "!\n";
            return true;
        } else {
            cout << "Login Failed: Incorrect password.\n";
            return false;
        }
    }
};

int main() {
    UserService userService;
    FileManager fileManager;
    
    int choice;
    string username, password;

    while (true) {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue;
        }

        if (choice == 1) {
            cout << "Enter username: ";
            cin >> username;
            bool test=true;
            while(test){
            cout << "Enter password: ";
            cin >> password;
            PasswordValidator v;
            if(v.validate(password)){test=false;}
        }
            userService.RegisterUser(username, password);
            }
            
        else if (choice == 2) {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            userService.LoginUser(username, password);
        } 
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } 
        else {
            cout << "Invalid choice, try again!\n";
        }
    }

    return 0;
}
