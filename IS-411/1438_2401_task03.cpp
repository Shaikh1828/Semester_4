#include<bits/stdc++.h>
using namespace std;

int main()
{
    string plain_text, encrypted_text = "", decrypted_text = "", key_word, new_key_word ;
    int key_size, text_size, curr_key, curr_text, i, new_text ;

    cout << "Enter plain text: " ;
    cin >> plain_text ;
    text_size = plain_text.size() ;
    
    cout << "Enter keyword: " ;
    cin >> key_word;
    new_key_word = key_word;
    key_size = key_word.size();
    
    if( key_size < text_size )
    {
        int remaining = text_size-key_size ;
        while( remaining )
        {
            if( remaining >= key_size )
            {
                new_key_word += key_word;
            }
            else
            {
                new_key_word += key_word.substr(0,remaining);
            }
            remaining = text_size-new_key_word.size();
        }
    }
    // cout<<"Keyword: "<<new_key_word<<endl;
    for( i = 0; i < text_size; i++ )
    {
        curr_key = new_key_word[i]-'a';
        curr_text = plain_text[i]-'a';
        new_text = (curr_key+curr_text)%26;
        encrypted_text.push_back('a'+new_text-32);
    }
    cout << "Encrypted text: " << encrypted_text << endl;
    for( i = 0; i < text_size; i++ )
    {
        curr_key = new_key_word[i]-'a';
        curr_text = encrypted_text[i]-'A';
        new_text = curr_text-curr_key;
        if( new_text < 0 )
        {
            new_text += 26 ;
        }
        else
        {
            new_text %= 26 ;
        }
        decrypted_text.push_back('a'+new_text) ;
    }
    cout << "Decrypted text: " << decrypted_text << endl ;
    return 0 ;
}