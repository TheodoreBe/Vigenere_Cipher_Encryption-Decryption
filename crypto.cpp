/** CS515 Assignment File: crypto.cpp
Name: Theodore Belanger
Date: 9/24/2014
*/
#include <iostream>
#include <fstream> 
#include <sstream>

using namespace std;
//---------global Variables-------
string key = ""; 
int keyLength;
char mode;
//------------------keyCheck-----------------
bool keyCheck( string key1 )
{
    bool correct = false;
    key = key1;
    //cout << key1 << "<--key Function found!" << endl;
    int length =  key1.length(); 
    if( length < 10 &&  length > 0 )
    {
        for( int i = 0; i < length; i++ )
        {
            if( key1[i]  < 97 && key1[i] > 64 )
            {
                key1[i] += 32; 
                cout << "---------- Error: ----------" << endl;   
                cout << "key must have less than 10 all lower case letters" <<endl;
            }
        }
        key = key1;
        keyLength = key.length();
        correct = true;
    }
    return correct; 
}


//------------------Main------------------
int main(int argc, char *argv[] ) 
{
    string keyString = "";
    char task;
    //----------- Checks to see if there is the correct amount of arguments--------
    if( argc == 5 ) 
    {
        string indexOne( argv[ 1 ] );
        //----------- If index 1 is equal to either just e or just d-------------
        if( ( *argv[ 1 ] == 'e' || *argv[ 1 ] == 'd' ) && ( indexOne.length() == 1 ) ) 
        {
			    //----------------------- Setting mode E or D -------------------------
            if( *argv[ 1 ] == 'e' )
            {
                task = 'e';
            }
            if ( *argv[ 1 ] == 'd' )
            {
	            task = 'd';
            }
            //--------------if the key inside index 2 is valid -----------------
            keyString = argv[ 2 ];
            if( keyCheck( keyString ) )
            {
                //cout << "Key works" << endl;
            }
            else
            {
                cout << "---------- Error: ----------" << endl;
                cout << "Key must have less than 10 all lower case letters" << endl;
                return 0;
            }
            // ----------------file in.. ifstream...file out ofstream--------------
            switch ( task )
            {
                case 'e' : 
                {
                    ifstream in( argv[ 3 ] ); // supposed to open file 
                    ofstream fileOut( argv[ 4 ] );
                    int place = 0;
                    while( in.good() )// while has more.. applies something to each thing...
                    {				    
                        char c = in.get( );
                        //int tempVal = c;
                          if ( c == EOF )
                        {
                            break;
                        }
                        //int tempVal = c;
                        if( (c <= 90 && c >= 65) || (c >= 97 && c <= 122 ) )
                        {
                            // checks if character is uppercase 
                            if( c <= 90 && c >= 65 )
                            {
                                c = c + 32;
                            }
                            //encrypts character
                            c = (c - 'a' + key[ place % keyLength ] - 'a' ) % 26 + 'A';
                            if( c <= 90 && c >= 65 )
                            {
                                c = c + 32;
                            }	
                            fileOut.put( c ); 
                            place++;
                        }	
                        else 
                        {
                            fileOut.put( c );
                        }
                    }
                    in.close();
                    fileOut.close();
                    break;
                }
                
                case 'd' : 
                {
                    ifstream in( argv[ 3 ] ); // supposed to open file 
                    ofstream fileOut( argv[ 4 ] );
                    int place = 0;
                    while( in.good() )// while has more.. applies something to each thing...
                    {
                         char c = in.get( );
                        //int tempVal = c;
                          if ( c == EOF )
                        {
                            break;
                        }
                        if( (c <= 90 && c >= 65) || (c >= 97 && c <= 122 ) )
                        {
                            // checks if character is uppercase 
                            if( c <= 90 && c >= 65 )
                            {
                                c = c + 32;
                            }
                            //encrypts character
                            c = (c - key[ place % keyLength ] + 26 ) % 26 + 'A';
                            if( c <= 90 && c >= 65 )
                            {
                                c = c + 32;
                            }
                            fileOut.put( c ); 
                            place++;
                        }	
                        else 
                        {
                            fileOut.put( c ); 
                        }
                    }// ends while( in.good ) 
                    in.close();
                    fileOut.close();
			        break;
                }
            }// end of switch		
        }
        else // if( ( *argv[ 1 ] == 'e' || *argv[ 1 ] == 'd' ) && ( indexOne.length() == 1 ) ) 
        {
            cout << "---------- Error: ----------" << endl;
            cout << "must enter e for encryption or d for decryption" << endl; 
            return 0;
        } 
    }
    else //for if input is wrong. 
    {
        cout << "---------- Error: ----------" << endl;
        cout << "Wrong number of arguments!" << endl;
        cout << "Argument format: " <<endl;
        cout << "./encryption < e/d > < encription phrase > < in file > < out file >"<< endl;
    }
}