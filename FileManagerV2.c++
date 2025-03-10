#include <bits/stdc++.h>

using namespace std;


class Istorage {
    protected:
        string fileName = "projet2.txt";
    
    public:
        virtual void addUser(const string&, const string&, const string&) = 0;
        virtual vector<tuple<string, string, string>> getdata() = 0;
        virtual ~Istorage() {}
    };
    
    
    class FileManager : public Istorage {
    public:
        void addUser(const string& Username, const string& Password, const string& salt) override {
            ofstream outFile(fileName, ios::app);
            if (outFile.is_open()) {
                outFile << Username << "," << Password << "," << salt << endl;
                outFile.close();
                cout << "User " << Username << " added successfully!\n";
            } else {
                cerr << "ERROR WHILE ADDING USER" << endl;
            }
        }
    
        vector<tuple<string, string, string>> getdata() override {
            vector<tuple<string, string, string>> users;
            ifstream inFile(fileName);
    
            if (inFile.is_open()) {
                string line;
                while (getline(inFile, line)) {
                    stringstream ss(line);
                    string Username, Password, salt;
    
                    if (getline(ss, Username, ',') &&
                        getline(ss, Password, ',') &&
                        getline(ss, salt, ',')) {
                        users.emplace_back(Username, Password, salt);
                    }
                }
                inFile.close();
            } else {
                cerr << "Unable to get user DATA" << endl;
            }
            return users;
        }
    
        bool userExists(const string& Username) {
            vector<tuple<string, string, string>> users = getdata();
            for (const auto& [uname, pass, s] : users) {
                if (uname == Username) {
                    return true;
                }
            }
            return false;
        }
    };