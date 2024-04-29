#include<bits/stdc++.h>
using namespace std;

int main()
{
    int t, flag, length; 
    int cr[26];
    string str;  
    char ch, prev ;

    cin >> t ;
    while ( t-- )
    {
        for( int i = 0; i < 26; i++ ) cr[i] = 0;
        cin >> length ;
        flag = 0 ;
        prev = 'a';
        cin >> str;

        for ( int i=0; i<length; i++ )
        {
            ch = str[i];
            if( ch == prev ) ;
            else if ( cr[ch-65] == 0 )
            {
                prev = ch ;
                cr[ch-65] = 1 ;
            }
            else if( cr[ch-65] == 1 )
            {
                flag = 1 ;
                break;
            }
            
        }
        
        if( flag )
            cout << "NO" << endl ;
        else
            cout << "YES" << endl ;
    }
    
}