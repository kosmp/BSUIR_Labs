#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int main()
{
    cout << "In a given string consisting of letters, numbers and other symbols, the program finds the sum of the sum of all numbers." << endl;
    string str = "";
    cout << "Let's fill line." << endl;
    getline(cin, str);
    int wordSize = 0;   // last index in a number
    int startWordSize = 0;  // counter of first index in a number
    bool check = false;     // will be completed algorithm for checking number, if a number was found
    bool checkStart = false;    // for setting first index in a number. 1 time for each number.
    bool checkFirstSpace = false;
    long long sum = 0;
    bool forDouble = false;
    for (int i = 0; i <= str.length(); i++)
    {
        if ((str[i] >= 48 && str[i] <= 57) && checkStart == false)
        {
            startWordSize = i;
            wordSize += startWordSize;  // If index was lost after 1+ spaces we can save order
            checkStart = true;      // setting start index 1 time for each number
        }

        if (i >= 1) forDouble = true;  // so as not to check str[-1] if i - 1

        if (str[i] >= 48 && str[i] <= 57)
        {
            wordSize++;
        }
        else if (forDouble && !(str[i] >= 48 && str[i] <= 57) && !(str[i - 1] >= 48 && str[i - 1] <= 57))
        {
            check = false;  // if 2 or more spaces. Then it's not a typical case (need't check = true), so we need to skip
        }
        else if (!(str[i] >= 48 && str[i] <= 57) || str[i] == '\0')
        {
            check = true;
            wordSize--;
        }
        if (!(str[0] >= 48 && str[0] <= 57) && checkFirstSpace == false)
        {
            checkFirstSpace = true;
            wordSize++;     // so as not to lose wordSize, if the first is space. It's not a typical situation, when space. Can be used only 1 time, if need
        }

        if (check == true && wordSize != startWordSize)  // true because a number was found. Then we need to check this number and check it if need
        {
            char* arr = new char [wordSize - startWordSize + 2];
            arr[wordSize - startWordSize + 1] = '\0';
            for (int i = 0; startWordSize <= wordSize; startWordSize++, i++)
            {
                arr[i] = str[startWordSize];
            }

            sum += atoi(arr);
            check = false;
            checkStart = false;
            wordSize = 0;
            delete[] arr;
        }
        else if (check == true && wordSize == startWordSize)    // if only 1 number
        {
            if (str[wordSize] >= 48 && str[wordSize] <= 57) sum += int(str[wordSize]) - '0';
            check = false;
            checkStart = false;
            wordSize = 0;
        }
    }
    cout << endl << "Sum= " << sum;
}
