// #include"aes_ecb.hpp"
// #include"aes_ctr.hpp"
#include"aes_cbc.hpp"
using namespace std;

int main()
{
    string inpt, encr ;
    cout << "Input : " ;
    getline( cin, inpt );
    encr = cbc_encryption( inpt ) ;
    write_file(encr);
    string decr;
     decr= getDecryptedText( encr ) ;
     write_dec_file(decr, inpt.size());
    cout<<decr<<endl;
}

string read_file()
{
   FILE *fp;
    string encr = "";
    // encr.resize();
    int i;
    // unsigned char encrypted[extendedLen];
    fp=fopen("encrypted_text.txt","r+");
    for( i=0;i<extendedLen;i++)
    {
        char character;
        fscanf(fp,"%c",&character);
        encr += character ;
        // unsigned int concatenated_value;
   
        // // Convert characters to their respective hexadecimal values
        // int digit1 = (character1 >= 'A' && character1 <= 'F') ? character1 - 'A' + 10 : character1 - '0';
        // int digit2 = (character2 >= 'A' && character2 <= 'F') ? character2 - 'A' + 10 : character2 - '0';

        // Combine the hexadecimal digits
        // concatenated_value = ((unsigned int)digit1 << 4) | (unsigned int)digit2;
        // encrypted[i]=concatenated_value;
        // cout<<encrypted[i]<<" ";
    }
    cout<<endl;
    // cout<<"hello"<<endl;
    fclose(fp);
    // for( i=0;i<extendedLen;i++)encr[i]=encrypted[i];
    // encr[i]='\0';
    return encr;
}