#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class PasswordManager
{
private:
    string user;
    string pass;
    string encrypt( string & );
    bool meetsCriteria( string );

public:
    void setUsername(string);
    string getUsername(string &);
    void setEncryptedPassword(string);
    string getEncryptedPassword(string &);
    bool setNewPassword(string);
    bool authenticate(string);
};


