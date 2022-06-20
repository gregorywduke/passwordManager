#include <string>
#include "PasswordManager.h"

string PasswordManager::encrypt( string &text )
{
    string encrypted;
    encrypted = text;

    for ( int i = 0; i < text.length(); i++ )
    {
        text[i] = ((encrypted[i] - 65 ) + 25 ) %94 + 65;
        //text[i] = ((encrypted[i] - 33 ) + 25 ) %94 + 33;
    }

    return text;
}

bool PasswordManager::meetsCriteria( string text )
{
    bool validate = false, up = false, low = false, digit = false;
    int total = 0;

    for ( int i = 0; i < text.length(); i++ )
    {
        total += 1;
        if ( isupper(text[i]) )
            up = true;
        if ( islower(text[i]) )
            low = true;
        if ( isdigit(text[i]) )
            digit = true;
    }

    if ( up == true && low == true && digit == true && total >= 8 )
        validate = true;

    return validate;
}

void PasswordManager::setUsername( string text )
{
    user = text;
}

string PasswordManager::getUsername( string &text )
{
    text = user;
    return text;
}

void PasswordManager::setEncryptedPassword( string text )
{
    pass = text;
}

string PasswordManager::getEncryptedPassword( string &text )
{
    text = pass;
    return text;
}

bool PasswordManager::setNewPassword( string text )
{
    bool validate;

    if ( meetsCriteria(text) == true )
    {
        encrypt( text );
        pass = text;
        validate = true;
    }
    else
        validate = false;

    return validate;
}

bool PasswordManager::authenticate( string text )
{
    encrypt(text);
    bool validate;

    for ( int i = 0; i < text.length(); i++ )
    {
        if ( text[i] != pass[i] )
        {
            validate = false;
            break;
        }
        else
            validate = true;
    }
    return validate;
}
