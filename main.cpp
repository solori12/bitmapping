#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>

//#define DEBUG
using namespace std;

void promptUser(string&);
int calculateThreshold(int&, int&, int&);
int calculateAlpha(int,string&);
string int2str(int);
string reverseString(string);
void cls();
int main()
{
    string searchString = "";
    int maxNum = 0;
    int x = 0, y = 0;
    int threshold = 0;
    int alpha = 0;
    bool quit = false;

    while(quit == false)
    {
        promptUser(searchString);
        threshold = calculateThreshold(maxNum,x,y);
        alpha = calculateAlpha(maxNum,searchString);

        cout << "\n\nResults: " << endl;
        cout << "---------------------------" << endl;
        cout << "alpha = " << alpha << endl;
        cout << "threshold = " << threshold << endl;

        if(alpha > threshold)
        {
            cout << "alpha is GREATER then the threshold" << endl;
            cout << x <<  "B to " << y << "B mapping is IMPOSSIBLE" << endl << endl;
        }
        else
        {
            cout << "alpha is LESS THAN OR EQUAL to the threshold" << endl;
            cout << x <<  "B to " << y << "B mapping is POSSIBLE" << endl << endl;
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
   cout << "Enter the string to avoid: ";
   cin >> searchString;
   cout << "string entered = " << searchString << endl;
}

int calculateAlpha(int maxNum, string& searchString)
{
    string inputString = "";
    int found = 0;
    int alpha = 0;

    for(int i=0 ; i <= maxNum ; i++)
    {
        inputString = int2str(i);
        found = inputString.find(searchString);

        if(found != string::npos)
        {
            alpha++;    // The string has "000" in it
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

int calculateThreshold(int& maxNum, int& x, int &y)
{
    int threshold;

    cout << "Please input the bit mapping values for x and y " << endl;
    cout << "Ex.) For a 9bit to 10 bit mapping; x = 9, y = 10" << endl;
    cout << "\tx = "; cin >> x;
    cout << "\ty = "; cin >> y;

    // Alpha is calculated as such:  2^y - alpha >= 2^x    --- 1024 - alpha >= 512
    // alpha <= 2^y - 2^x
    // threshold = 2^y - 2^x
    maxNum = pow(2,y) - 1;
    threshold = pow(2,y) - pow(2,x);

    #ifdef DEBUG
        cout << "maxNum = " << maxNum << endl;
        cout << "threshold = " << threshold << endl;
    #endif
    return threshold;
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
