#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
//principe: takes a password ,generates a salt than merges them into one string taking a caracter from each one alternatively ,converts each caracter into ASCII code and finally converts the resulting string into hexadecimal//
using namespace std;

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
    Hasher(string pass,string sal){
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

int main() {
    string password = "khison";
    string salt = "since3456in";
    Hasher hasher(password,salt);
    string hashed_password=hasher.hashPassword();
    cout<<hashed_password;
    return 0;
}
