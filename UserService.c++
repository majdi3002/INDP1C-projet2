#include <bits/stdc++.h>

using namespace std;


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
            if (fileManager.userExists(username)) {
                cout << "Error: Username already exists!\n";
                return;
            }
            string salt = SaltGenerator::generateSalt(8);
            string hashedPassword = Hasher::hashPassword(password, salt);
            fileManager.addUser(username, hashedPassword, salt);
        }
    
        bool LoginUser(const string& username, const string& password) override {
            auto [exists, storedHashedPassword, salt] = fileManager.getUserInfo(username);
    
            if (!exists) {
                cout << "Login Failed: Username does not exist.\n";
                return false;
            }
         
            string enteredHashedPassword = Hasher::hashPassword(password, salt);
            if (enteredHashedPassword == storedHashedPassword) {
                cout << "Login Successful! Welcome, " << username << "!\n";
                return true;
            } else {
                cout << "Login Failed: Incorrect password.\n";
                return false;
            }
        }
    };