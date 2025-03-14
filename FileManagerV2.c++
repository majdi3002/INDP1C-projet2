#include <bits/stdc++.h>

using namespace std;


class Istorage {
protected:
    string fileName = "projet2.txt";

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

        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            outFile << Username << "," << HashedPassword << "," << salt << endl;
            outFile.close();
            cout << "User " << Username << " added successfully!\n";
        } else {
            cerr << "ERROR WHILE ADDING USER" << endl;
        }
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
