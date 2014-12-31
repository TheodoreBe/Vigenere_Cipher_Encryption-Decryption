/** CS515 Assignment File: crypto_cracker.cpp
Name: Theodore Belanger
Date: 9/24/2014
*/
#include <iostream>
#include <fstream> 
#include <sstream>
using namespace std;

//------------Functions------------
int alphaIndex( char c )
{
        int position = (int)c - 97;  
        return position;
}
//-----------------------------------
char indexAlpha( int t )
{
        char position = (char)( t + 97);  
        return position;
}
//------------MAIN------------------
int main(int argc, char *argv[]) 
{
    //-------------Main Global Variables-------------
    int keyLength; 
    int inputLength = 0;
    //---------------------------------------------
    
    if( argc == 3 ) // Checks that program gets 3 parameters [ ./mybreak ] [ length of key ] [ file to decrypt ]  
    {
        //---------Checking if keylength is valid------------------------------
        
        int t = *argv[1] - '0'; // extracting t = key length  out of args
        
        if(  t > 0 && t < 10 )// will ony do words of length 1-9 because of char to int 
        {
           keyLength = t; 
        }
        
        else// getts glagged if input index 1 isnt a digit > 0 
        {
            cout << "Key must be greater than 0 and less than 10!" << endl; 
        }
        
        //---------------Key length is valid and now must check file ----------
        
        //ifstream in( argv[ 3 ] ); // supposed to open file to decrypt 
        
        //------------------ Known letter frequencies  ----------------------    
            
        float A [26] = {0.0821, 0.0150, 0.0230, 0.0479, 0.1237, 0.0225, 0.0208, 0.0645,
         0.0676, 0.0018, 0.0087, 0.0393, 0.0254, 0.0705, 0.0767, 0.0163, 0.0009, 0.0550,
         0.0617, 0.0921, 0.0291, 0.0087, 0.0254, 0.0013, 0.0195, 0.0006};

        /**=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-TOP-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-  
        *                        
        *                        -Alpha shift 2D array
        *                    
        *      The purpose of this section is to take the A[], that is fill
        *      of frequencies of characters being used, and create a 2D array
        *      where each new like is the frequency A[] array shifted right with
        *      its roll over being place on its left-most side.  
        */
        //-=-=----=-=-===-=-=-=-=-=--=- Variable -=-=----=-=-===-=-=-=-=-=--=-
        
        double AN [26][26]; 
        
        //-=-=----=-=-===-=-=-=-=-=--=-=-Start=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-=-=-=

        for(int i=0; i<26; i++)
        {
            for(int j=0; j<26; j++)
            {
                AN[i][j] = A[(j-i+26)%26]; 
            }
        }
        
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-TEST=-=-=-=-=-=-=-=-=-=-=--==-=-==-==-=-
//        cout << AN[0][0] <<  " : AN[0][0]" <<endl;
//        cout << AN[0][1] <<  " : AN[0][1]" <<endl;
//        cout << AN[0][2] <<  " : AN[0][2]" <<endl;
//        cout << AN[1][0] <<  " : AN[1][0]" <<endl;
//        cout << AN[1][1] <<  " : AN[1][1]" <<endl;
//        cout << AN[24][24] <<  " : AN[24][24]" <<endl;
//        cout << AN[25][25] <<  " : AN[25][25]" <<endl;
        //-=-=-=-=-=-=-=-=-=-=--=-=-=-END=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-
          
        /**=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-TOP-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-  
        *        
        *                     Getting Number of Char in File         
        *
        *        All this does is help return a count of chars in the file.. these
        *        Math Methods that will follow will use this to divide 
        *        the length of the file by the size of the key.... this information
        *        will then be used to calculate  the 
        */
        //-=-=----=-=-===-=-=-=-=-=--=-=-=Variables-=-=-=-=-=--=-=--=-=--=-=-=-=
        
        ifstream in( argv[ 2 ] ); // open file that i am attempting to decrypt
        int place = 0;
        
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Start=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        while( in.good() )
        {
            char c = in.get( );
            if( !( c == 32 ) || ( c <= 90 && c >= 65 ) || ( c <= 90 && c >= 65 ) )
            {
                inputLength = inputLength + 1;
            }
        }
        in.close();
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-Test-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=
        
        // cout<< inputLength << "inputLength" << endl;   //test print 

        //-=-=-=-=-=-=-=-=-=-=-=-=-=--=-END=-=-=-=-=-=-=-=-=-=-=--=-=-==-=-=-=-=--

        //-=-=----=-=-===-=-=-=-=-=--=-=-TOP=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-=-=-=
        /**     
        *               Math Calculations for w[][] creation  While loop         
        *
        *        These are the small math functions that will be used to controlee  
        *        the following while and for loops.
        *         
        */
        //-=-=----=-=-===-=-=-=-=-=--=-=-Start=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-=-=-
        
        int keyRepNum = inputLength / keyLength;
        int extraCouple = inputLength - ((keyRepNum)*(keyLength));

        
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-TEST-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        
//        cout << "int  keyRepNum-->" <<  keyRepNum <<endl;
//        cout << "int extraCouple -->" << extraCouple << endl;
//        cout << "end of math" << endl;
           
        //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-END-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        
        //-=-=----=-=-===-=-=-=-=-=--=-=-TOP=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-=-=-=
        /**     
        *        This serves to keep track of the accounts that are  
        *        recorded in the input at the indexes of the key.
        *         
        */
        //-=-=----=-=-===-=-=-=-=-=--=-=-Start=-=-=-=-=-=-=-=-=-=--=-=-=-=--=-=-=-

        double counted [keyLength][26];
        for( int h = 0; h < keyLength; h++)
        {
            for( int u = 0; u < 26; u++ )
            {
                counted[h][u] = 0;
            }
        }
        
        ifstream in1( argv[ 2 ] ); // open file that I am attempting to decrypt
        //int setIncrementDist;
        int v = 0;
        for( int i = 0; i < keyRepNum; i++  )
        {
            for( int n = 0; n < keyLength; n ++ )
            {
                v++;
                char e = in1.get();
                int index = alphaIndex( e );
                ///cout << counted[n][index] << " Before adding 1!"<< endl;

                counted[n][index] += 1; 
 //               cout << "Key Index:" << n << ":Letter:" << e << ":Index current sum:" << counted[n][index] << endl;
 //               cout << v << " :Iteration#"<< endl;
            }
        }
        
        ///------------^^^WORKS WELL AND LOGGS ALL CHAR IN FILE 

            for( int y = 0; y < extraCouple -1; y++ )
            {
                char e = in1.get();
                //cout << e  << "last couple letters" <<  extraCouple << " extraCouple" << endl;
                int index = alphaIndex( e );
               //cout << counted[y][index] << " Before adding 1!"<< endl;
                counted[y][index] += 1;
 //              cout << "Key Index:" << y << ":Letter:" << e << ":Index  sum:" << counted[y][index] << endl;
 //               cout << v << " :Iteration#"<< endl;
            }
        
        //
       // cout << "Done calcing file" <<endl;

        //-=-=-Finding sum of key indexes and dot value=-=-=-=-==-
        float w[keyLength][26];
        //--------------Populating array to empy-------
        for( int h = 0; h < keyLength; h++)
        {
            for( int u = 0; u < 26; u++ )
            {
                w[h][u] = 0;
            }
        }
        //-------------        -----------------------
        float tempCal = 0;
        float lineSumA[keyLength];
        float lineSum = 0;
        //--initializing linesum to be full of zeros--
        for( int i = 0; i < keyLength; i++ )
        {
            lineSumA[i] = 0;
        }
        //----------Finding lineSumA[]------------
        for( int h = 0; h < keyLength; h++)
        {
            lineSum = 0;
            for( int t = 0; t < 26; t++ )
            {
               lineSum += counted[h][t];
            }
            lineSumA[ h ] = lineSum;
 //           cout << lineSum << "Line sum" << endl;
        }
        for( int h = 0; h < keyLength; h++)
        {
            //----------after linesum[] is found-----
            for( int u = 0; u < 26; u++ )
            {
               tempCal = ( (counted[h][u]) / ( lineSumA[ h ] ) );
               w[h][u] = tempCal;
//               cout << w[h][u] << endl;
            }
            
//            cout << "end key index" << endl;
        }
        //-----------Dot product time----------------
        //--------making array to save answers in-----
        int answers[ keyLength ];
        for( int k = 0; k < keyLength; k++ )
        {
            answers[k] = 0;
        }
        //--------Key index check ------------
        float cMax = 0;
        float current = 0;
        int cMaxIndex = 0;
        for(int i = 0; i < keyLength ; i++ )
        {
            cMax = 0;
            cMaxIndex = 0;
            for( int j = 0; j < 26; j++)
            {
                for( int h= 0; h <26 ; h++ )
                {
                    current += w[i][h] * A[(h-j+26)%26];                     
                }
                if( current > cMax )
                {
                    cMax = current;
                    cMaxIndex = j;
                } 
                current = 0;
            }
            answers[ i ] = cMaxIndex ; 
//            cout << cMaxIndex << "cMaxIndex" << endl;
        }
        //---Finding the letters at indexes saved in answers[]-----
        char correctLetter;
        string answer = "";
        for( int a = 0; a < keyLength ; a++)
        {
            correctLetter = indexAlpha( answers[a] );
            answer += correctLetter ;
        }
        //cout << answer << " <-- This is the decription key" << endl;
        cout << answer << endl;
    }
}
