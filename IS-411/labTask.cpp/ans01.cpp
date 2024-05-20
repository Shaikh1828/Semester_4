#include"aes_cbc.hpp"
using namespace std;

int main()
{
    string inpt, encr ;
    cout << "Input from file : " ;
    //getline( cin, inpt );
    inpt  = read_file_string();
    encr = cbc_encryption( inpt ) ;
    write_file(encr);
    string decr;
     decr= getDecryptedText( encr ) ;
     write_dec_file(decr, inpt.size());
    cout<<decr<<endl;
}