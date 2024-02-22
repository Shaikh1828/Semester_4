#include<bits/stdc++.h>
using namespace std;

string encryption( string message , int key );
string decryption( string message , int key );

int main()
{
    int key ;
    string input, encryptedMessage, decryptedMessage ;
    cout << "Enter the String :" ;
    cin >> input ;
    cout << "Cypher key:";
    cin >> key;
    cout << "Input Message : " << input << endl ;
    encryptedMessage = encryption(input, key ) ;
    cout << encryptedMessage << endl ;
    decryptedMessage = decryption(encryptedMessage, key ) ;
    cout << decryptedMessage << endl ;
}


string encryption( string message , int key )
{
    string encrTxt = message;
    int ch ;
    for( int i=0; i<message.length(); i++ )
    {
        ch = message[i] - 97 ;
        encrTxt[i] = 65 + (ch+key)%26 ;
    }
    return encrTxt ;
}

string decryption( string message , int key )
{
    string decrTxt = message;
    int ch ;
    for( int i=0; i<message.length(); i++ )
    {
        ch = message[i] - 65 ;
        if( ch >= key ) decrTxt[i] = 97 + (ch-key)%26 ;
        else decrTxt[i] = 97 + (ch-key)%26 + 26 ;
    }
    return decrTxt ;
}