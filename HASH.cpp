#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;
//principe: takes a password ,generates a salt than merges them into one string taking a caracter from each one alternatively ,converts each caracter into ASCII code and finally converts the resulting string into hexadecimal//

class IHash {
public:
    virtual string hash_function(const string& password, const string& salt) = 0;
    virtual ~IHash() = default;
};

class Hasher : public IHash {
public:
    string hash_function(const string& password, const string& salt) override {
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

void process_hash(IHash& hasher, const string& password, const string& salt) {
    string hashed_password = hasher.hash_function(password, salt);
    cout << "Hashed Password: " << hashed_password << endl;
}

int main() {
    string password = "password";
    string salt = "SALT123";

    Hasher hasher;

    process_hash(hasher, password, salt);

    return 0;
}
