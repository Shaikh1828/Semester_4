#include<bits/stdc++.h>
using namespace std;

void generate_table( vector<vector<char>> &table, string key_word, map<char,pair<int,int>> &loc );
void generate_diagram( vector<vector<char>> &diagram, string text );
string encryption( vector<vector<char>> table, vector<vector<char>> diagram, map<char,pair<int,int>> loc );
string decryption( vector<vector<char>> table, map<char, pair<int,int>> loc, string encrypted_text );

int main()
{
    char left, right;
    vector<vector<char>> table;
    vector<vector<char>> diagram;
    map<char, pair<int,int>> loc; 
    string key_word, text, encrypted_string, decrypted_string;

    cout<<"Enter keyword: ";
    cin >> key_word;
    getchar();
    cout << "Enter text: ";
    getline( cin, text );
    generate_table( table, key_word, loc );
    generate_diagram( diagram, text );
    cout << "Table:" << endl;
    for( auto r : table )
    {
        for(auto c:r)
        {
            cout << c << " " ;
        }
        cout << endl;
    }
    cout << "Diagram:" << endl;
    for( auto d : diagram )
    {
        cout << d[0] << d[1] << " " ;
    }
    cout << endl;
    //cout<<"Location of e is: "<<loc['e'].first<<" "<<loc['e'].second<<endl;
    encrypted_string = encryption( table, diagram, loc );
    decrypted_string = decryption( table, loc, encrypted_string );
    cout << "Encrypted text: " << encrypted_string << endl;
    cout << "Decrypted text: " << decrypted_string << endl;
    return 0;

}

void generate_table( vector<vector<char>> &table, string key_word, map<char, pair<int,int>> &loc )
{
    table.resize( 5, vector<char>(5) );
    vector<bool> is_used(25);
    int row = 0, col = 0, i, curr;
    for( auto key : key_word )
    {
        if( col == 5 )
        {
            col = 0;
            row ++ ;
        }
        if( !is_used[key-'a'] )
        {
            table[row][col] = key;
            loc[key] = {row,col};
            col ++ ;
            is_used[key-'a'] = true;
        }
    }
    for( i = 'a'; i <= 'z'; i++ )
    {
        if( i == 'j' )
        {
            continue;
        }
        if( col == 5 )
        {
            col = 0;
            row ++;
        }
        if( !is_used[i-'a'] )
        {
            table[row][col] = i;
            loc[i] = {row, col};
            col ++;
            is_used[i-'a'] = true;
        }
    }
}

void generate_diagram( vector<vector<char>> &diagram, string text )
{
    int curr;
    char left, right;
    for( curr = 0; curr < text.size(); curr+=2 )
    {
        if( curr < text.size()-1 )
        {
            left = text[curr];
            right = text[curr+1];
            if( left == right )
            {
                right='x';
                curr--;
            }
            diagram.push_back({left, right});
        }
        else
        {
            left = text[curr];
            right = 'x';
            diagram.push_back({left,right});
        }
    }
}

string encryption( vector<vector<char>> table, vector<vector<char>> diagram, map<char,pair<int,int>> loc )
{
    string encrypted_string = "";
    char left, right, l, r;
    int r1, r2, c1, c2;
    for( auto d : diagram )
    {
        left = d[0];
        right = d[1];
        r1 = loc[left].first;
        r2 = loc[right].first;
        c1 = loc[left].second;
        c2 = loc[right].second;
        //cout << "Left: " << left << " Right: " << right << " r1=" <<r1 << " r2=" <<r2 << " c1=" <<c1 << " c2=" <<c2;
        if( r1 == r2 )
        {
            encrypted_string += (table[r1][(c1+1)%5]);
            encrypted_string += (table[r1][(c2+1)%5]);
        }
        else if( c1 == c2 )
        {
            //cout << table[(r1+1)%5][c1] << " " << table[(r2+1)%5][c1] << '\n';
            encrypted_string += (table[(r1+1)%5][c1]);
            encrypted_string += (table[(r2+1)%5][c2]);
        }
        else
        {
            encrypted_string += (table[r1][c2]);
            encrypted_string += (table[r2][c1]);
        }
    }
    return encrypted_string;
}

string decryption( vector<vector<char>> table, map<char,pair<int,int>> loc, string encrypted_text )
{
    string decrypted_string = "";
    char left, right, curr;
    int r1, r2, c1, c2, i;
    for( i = 0; i < encrypted_text.size(); i += 2 )
    {
        left = encrypted_text[i];
        right = encrypted_text[i+1];
        r1 = loc[left].first;
        c1 = loc[left].second;
        r2 = loc[right].first;
        c2 = loc[right].second;
        if( r1 == r2 )
        {
            if( c1 == 0 )
            {
                c1 = 4;
            }
            else
            {
                c1 -- ;
            }
            if( c2 == 0 )
            {
                c2 = 4;
            }
            else
            {
                c2 -- ;
            }
            curr = table[r1][c1];
            if( curr != 'x' )
            {
                decrypted_string += curr;
            }
            curr = table[r2][c2];
            if(curr != 'x')
            {
                decrypted_string += curr;
            }
        }
        else if( c1 == c2 )
        {
            if(r1==0)
            {
                r1 = 4;
            }
            else
            {
                r1--;
            }
            if( r2 == 0 )
            {
                r2 = 4;
            }
            else
            {
                r2--;
            }
            curr = table[r1][c1];
            if( curr != 'x' )
            {
                decrypted_string += curr;
            }
            curr = table[r2][c2];
            if( curr != 'x' )
            {
                decrypted_string += curr;
            }
        }
        else
        {
            curr=table[r1][c2];
            if( curr != 'x' )
            {
                decrypted_string += curr;
            }
            curr = table[r2][c1];
            if( curr != 'x' )
            {
                decrypted_string += curr;
            }
        }
    }
    return decrypted_string;
}
