#include <iostream>
#include <string.h>
#include <stdio.h>

//#define DEBUG
using namespace std;

void promptUser(string&, string&);
string int2str(int);
string reverse(string);
int main()
{
    string inputString = "";
    string searchString = "0000";    // Search for 3 zeros

    int maxNum = 1024;  // 2^10 = 1024 combinations
    maxNum--;         // 0 to 1023
    int alpha = 0;      // Number of strings that contain
                        // the substring "000"
    int found = 0;      // return result from function find()
                        // -1 = substring was not found

    for(int i=0 ; i <= maxNum ; i++)
    {
        inputString = int2str(i);
        found = inputString.find(searchString);

        if(found != string::npos)
        {
            alpha++;    // The string has "000" in it
            cout << alpha << ": " << inputString << " contains " << searchString << endl;
        }
        else
        {
            //cout << inputString << endl;
        }
    }

    cout << "\nResults: " << endl;
    cout << "---------------------------" << endl;
    cout << "alpha = " << alpha << endl;

    if(alpha > 512)
        cout << "9B to 10B mapping is IMPOSSIBLE" << endl;
    else
        cout << "9B to 10B mapping is POSSIBLE" << endl;

    return 0;
}

void promptUser(string& inString, string& searchString)
{
   inString = "hello";
   searchString = "world";

   cout << "instring = " << inString << "   searchString = " << searchString << endl;
}

string int2str(int num)
{
// Input "num" is only valid from 0 to 1024
// int2str function takes in an integer
// argument and returns the binary form of
// that integer as a string.

    string result = "";
    int iterations = 10; // To get a full 10-bit number

    while(iterations > 0)
    {
        if(num%2 == 0)
            result = result + "0";
        else
            result = result + "1";

        num = num/2;
        iterations--;
    }

    result = reverse(result);
    #ifdef DEBUG
    cout << "int2str = " << result << endl;
    #endif

    return result;
}

string reverse(string s)
{
// input string "s" is reversed and the
// resulting string is returned to caller
    string result = "";
    for(int i=0 ; i < s.length(); i++)
        result = s[i] + result;

    return result;
}
