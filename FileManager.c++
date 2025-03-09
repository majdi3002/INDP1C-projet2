#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class FileManager {
private:
    string fileName="projet2.txt";

public:
    void addUser(const string& Username, const string& Password, const string& salt) {
    ofstream outFile(fileName, std::ios::app);

    if (outFile.is_open()) {
        outFile << Username << "," << Password << "," << salt << std::endl;
        outFile.close();
    } else {
        std::cerr << "ERROR WHILE ADDING USER" << std::endl;
    }
}

   
    void getdata(string& Username, string& Password, string& salt) {
        ifstream inFile(fileName);

        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                getline(ss, Username, ','); 
                getline(ss, Password, ',');
                getline(ss, salt, ','); 
            }
            inFile.close();
        } else {
            cout << "Unable to get userDATA" << endl;
        }
    }


};

int main() {
   
    return 0;
}
