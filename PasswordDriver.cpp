// File Name: assign4_g_d100.cpp
// 
// Author: Gregory Duke
// Date: 3/25/19
// Assignment Number: 4
// CS 2308.255 Spring 2019
// Instructor: Jill Seaman
// 
// Program operates as password change utility; accepts three forms of user input, 
// username, password, and new password. If all three are correct, program will
// change password on file. If not, will output specific error message and quit.

#include <iostream>
#include <string>
#include <fstream>
#include "PasswordManager.h"

using namespace std;

int main()
{
    PasswordManager passwords[3];

    int flag = 0;

    bool arr[3];

    string x, y;

    //Sets strings to null because some fxns above pass by reference
    string username = "", identif_onfile = "", old_pass = "", new_pass = "";

    ifstream fin;
    fin.open( "passwords.txt" );
    if ( !fin )
    {
        cout << "Couldn't open file. Please examine contents." << endl;
    }

    //Generates username and password from input file, saves them 3 instances
    //of password class
    for ( int i = 0; i < 3; i++ )
    {
        fin >> x >> y;
        passwords[i].setEncryptedPassword(y);
        passwords[i].setUsername(x);
    }

    fin.close();

    cout << "Password Criteria: " << endl
         << "1. Must contain at least 8 characters." << endl
         << "2. Must contain an upper and lowercase letter." << endl
         << "3. Must contain a digit." << endl << endl
         << "Please enter your username: ";
    cin >> username;
    cout << endl << "Please enter your old password: ";
    cin >> old_pass;
    cout << endl << "Please enter your new password: ";
    cin >> new_pass;
    cout << endl;


    /* ----------------------------------------------------------------------
      Loop below cycles through username characters and compares each to
      characters in username from file. If there are any inconsistencies,
      the if statement will flag the loop and break it.
     -----------------------------------------------------------------------*/

    for ( int i = 0; i < 3; i++ )
    {
        passwords[i].getUsername( identif_onfile );
        for ( int k = 0; k < username.length(); k++)
        {
            if ( identif_onfile[k] != username[k] )
            {
                arr[i] = false;
                break;
            }
            else
                arr[i] = true;
        }
    }
    //If no usernames match, if statement outputs error message and raises flag
    if ( arr[0] == false && arr[1] == false && arr[2] == false )
    {
        cout << "Username entered does not match any on file." << endl;
        flag = 0;
    }
    // Else, checks for true value to proceed with reset, sets flag to indicate
    else if ( arr[0] == true )
        flag = 1;
    else if ( arr[1] == true )
        flag = 2;
    else if ( arr[2] == true )
        flag = 3;

    //If no issues, proceeds to compare old passwords
    if ( flag != 0 )
    {
        if ( passwords[flag-1].authenticate(old_pass) == false )
        {
            cout << "Old password is incorrect." << endl;
            flag = 0;
        }
    }

    // If no issues with old pass, determine if new pass meets criteria
    if ( flag != 0 )
    {
        if ( passwords[flag-1].setNewPassword(new_pass) == false )
        {
            cout << "New password does not meet criteria." << endl;
        }
        else
        {
            cout << "Password has been changed for netID: ";
            passwords[flag-1].getUsername( identif_onfile );
            cout << identif_onfile;
        }

    }

    return 0;
}
