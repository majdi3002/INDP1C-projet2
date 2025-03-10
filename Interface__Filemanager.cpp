#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class IFileManager {
public:
    virtual ~IFileManager() = default;
    virtual void addUser(const string& Username, const string& Password, const string& salt) = 0;
    virtual void getdata(string& Username, string& Password, string& salt) = 0;
};
