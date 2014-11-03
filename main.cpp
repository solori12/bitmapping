#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <time.h>

//#define DEBUG
  #define ULL  unsigned long long
  #define LL   long long
using namespace std;

void promptUser(string&);
LL calculateThreshold(ULL&, int&, int&);
ULL calculateAlpha(ULL,string&);
string int2str(ULL,int);
string reverseString(string);
void cls();
void PrintDataSizes();

int main()
{
    string searchString = "";
    ULL maxNum = 0;
    int x = 0, y = 0;
    LL threshold = 0;
    ULL alpha = 0;
    clock_t start;   // Timing variables for program execution
    clock_t stop;
    double elapsed_Time;
    bool quit = false;


    while(quit == false)
    {
        promptUser(searchString);
        threshold = calculateThreshold(maxNum,x,y);

        if(threshold > 0)
        {
            start = clock();
            alpha = calculateAlpha(maxNum,searchString);
            stop = clock();
            elapsed_Time = static_cast<double>((static_cast<double>(stop-start) / CLOCKS_PER_SEC));

            cout << "\n\nResults: " << endl;
            cout << "---------------------------" << endl;
            cout << "alpha = " << alpha << endl;
            cout << "threshold = " << threshold << endl;
            cout << "avoid string = \"" << searchString << "\"" << endl;
            cout << "Exeuction Time = " << elapsed_Time << " seconds" << endl << endl;

            if(alpha > threshold)
            {
                cout << "\t" << x <<  "B to " << y << "B mapping is IMPOSSIBLE" << endl;
                cout << "\tSince alpha > threshold" << endl << endl;
            }
            else
            {
                cout << "\t" << x <<  "B to " << y << "B mapping is POSSIBLE" << endl;
                cout << "\tSince alpha <= threshold" << endl << endl;
            }
            cout << "---------------------------" << endl;
        }
        else
        {
            cout << endl;
            cout << "\tERROR:" << endl;
            cout << "\tX must be less than Y" << endl;
            cout << "\tPlease try again!" << endl << endl;
        }

        char response;
        cout << "Would you like to conduct another test run? (Y/N)" << endl;
        cout << "Response: ";
        cin >> response;
        cout << "--------------------------";
        if(response == 'y' || response == 'Y')
            quit = false;
        else
            quit = true;

        cls();
    }
    return 0;
}

void promptUser(string& searchString)
{
   cout << "Enter the string to avoid" << endl;
   cout << "Ex.) 0000 or 1111" << endl;
   cout << "\n\tavoid string = ";
   cin >> searchString;
   cout << endl;
   //cout << "\tstring entered = " << searchString << endl << endl;
}

ULL calculateAlpha(ULL maxNum, string& searchString)
{
    string inputString = "";
    int found = 0;
    ULL alpha = 0;
    ULL i = 0 ;
    int numOfBits = static_cast<int>(log2(maxNum+1));

    for(i = 0; i <= maxNum ; i++)
    {
        inputString = int2str(i,numOfBits);
        found = inputString.find(searchString);

        if(found != string::npos)
        {
            alpha++;    // The current combination contains the string to avoid (searchString).
            //cout << alpha << ": " << inputString << " contains " << searchString << endl;
        }
        else
        {
            //cout << inputString << endl;
        }
    }

    #ifdef DEBUG
        cout << "alpha = " << alpha << endl;
    #endif // DEBUG

    return alpha;
}

LL calculateThreshold(ULL& maxNum, int& x, int &y)
{
    LL threshold;

    cout << "Please input the bit mapping values for x and y " << endl;
    cout << "Ex.) For a 9bit to 10 bit mapping; x = 9, y = 10" << endl << endl;
    cout << "\tx = "; cin >> x;
    cout << "\ty = "; cin >> y;

    // Alpha is calculated as such:  2^y - alpha >= 2^x    --- 1024 - alpha >= 512
    // alpha <= 2^y - 2^x
    // threshold = 2^y - 2^x
    // Alpha represents the number of combinations in the Y-bit domain that contain
    // the string to avoid. In other words, alpha represents the number of combinations
    // that cannot be used!

    if( x > y)
        return -1;  // throw back an error

    maxNum = pow(2,y) - 1;
    threshold = pow(2,y) - pow(2,x);

    return threshold;
}

string int2str(ULL num, int numOfBits)
{
// Input "num" is only valid from 0 to 1024
// int2str function takes in an integer
// argument and returns the binary form of
// that integer as a string.

    string result = "";

    while(numOfBits > 0)
    {
        if(num%2 == 0)
            result = result + "0";
        else
            result = result + "1";

        num = num/2;
        numOfBits--;
    }

    result = reverseString(result);
    #ifdef DEBUG
        //00cout << "int2str = " << result << endl;
    #endif

    return result;
}

string reverseString(string s)
{
// input string "s" is reversed and the
// resulting string is returned to caller
    string result = "";
    for(int i=0 ; i < s.length(); i++)
        result = s[i] + result;

    return result;
}

void cls()
{
    system("CLS");
}

void PrintDataSizes()
{
    cout << "Size is in BYTES" << endl;
    cout << "Size of " << "char                   " << sizeof(char) << endl;
    cout << "Size of " << "signed short int       " << sizeof(signed short int) << endl;
    cout << "Size of " << "signed int             " << sizeof(signed int) << endl;
    cout << "Size of " << "signed long int        " << sizeof(signed long int) << endl;
    cout << "Size of " << "signed long long int   " << sizeof(signed long long int) << endl;
    cout << "Size of " << "unsigned int           " << sizeof(unsigned int) << endl;
    cout << "Size of " << "unsigned long int      " << sizeof(unsigned long int) << endl;
    cout << "Size of " << "unsigned long long int " << sizeof(unsigned long long int) << endl;
}
