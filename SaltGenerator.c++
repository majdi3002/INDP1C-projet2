#include <bits/stdc++.h>
using namespace std;

class ISaltGenerator {
    public:
        virtual string generateSalt(int length = 8) = 0;  
        virtual ~ISaltGenerator() = default;  
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
    