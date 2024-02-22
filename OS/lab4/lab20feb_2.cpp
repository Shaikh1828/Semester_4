#include<bits/stdc++.h>
using namespace std;

#include<unistd.h>

int main()
{
    int row1=3, col1=2, row2=2, col2=2 ;
    int mat1[][col1] = { {2, 2}, { 2, 2}, {2, 2} }, mat2[][col2] = { {2, 2}, {2, 2} };
    int mult[row1][col2];
    
    for ( int i = 0; i < row1; i++ )
    {
        for ( int j = 0; j < col2; j++ )
        {
            mult[i][j] = 0 ;    
        }
    }    


    for ( int i = 0; i < row1; i++ )                                         
    { 
    	int pid1 ;  
    	if( pid1 = fork() )
		{                                                                        
        	 for (int j = 0; j < col2; j++ )                                     
        	{
		        for ( int k = 0; k < col1; k++ )
		        {
		            mult[i][j] += mat1[i][k]*mat2[k][j];
            	}
            	cout << mult[i][j] << " ";	
            }
            cout << endl;
            break;
        }
    }
    

    /*for ( int i = 0; i < row1; i++ )
    {
        for ( int j = 0; j < col2; j++ )
        {
            cout << mult[i][j] << " ";
        }
        cout << endl ;
    } */   

}
