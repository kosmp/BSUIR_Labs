// Variant with using arrays. 1-st variant in the list.
#include <iostream>
#include <cmath>
using namespace std;

void convert(char* st1, int& deNumber, int& i, int& numberOp)   // function for converting
{
    switch (numberOp)
    {
    case 0:
        st1[i] = '0';
        break;
    case 1:
        st1[i] = '1';
        break;
    case 2:
        st1[i] = '2';
        break;
    case 3:
        st1[i] = '3';
        break;
    case 4:
        st1[i] = '4';
        break;
    case 5:
        st1[i] = '5';
        break;
    case 6:
        st1[i] = '6';
        break;
    case 7:
        st1[i] = '7';
        break;
    case 8:
        st1[i] = '8';
        break;
    case 9:
        st1[i] = '9';
        break;
    case 10:
        st1[i] = 'A';
        break;
    case 11:
        st1[i] = 'B';
        break;
    default:
        cout << "error";
    }
}

int main()
{
    cout << "The program converts from the septenary to the duodecimal system." << endl;
    int n, q;
    char* st = new char[1000];
    cout << "Enter a number in the septenary system" << endl;
    cin >> st;   
    for (int i = 0; i < strlen(st); i++)    // check enter
    {
        if (st[i] < '0' || st[i] > '6')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 0;
        }
    }

    int deNumber = 0;   // decimal number
    for (int i = 0; i < strlen(st); i++)
    {
        int temp = 0;   // temporary number for converting from array to int
        temp = st[strlen(st) - 1 - i] - '0';    // converting from char to int

        deNumber += temp * pow(7, i);   // example: if 132 in 7 --> in 10. 1*7^2 + 3*7^1 + 2*7^0 = 72
    }
    
    char* st1 = new char[1000]; // this is not the final notation of the number, but the inverted
    int i = 0;  // index to know where to put the next element
    bool check = true;  // must be at least 1 iteration so as to know, can we further divide our number or not. Example: 125/12 = 10 (rem.5) and 10 < 12 so we need to finish calculating. 10 is critical
    while (check)
    {
        int numberOp = deNumber % 12;
        convert(st1, deNumber, i, numberOp);
        st1[i + 1] = '\0';
        if (deNumber / 12 < 12)
        {
            check = false;
            i = i + 1;
            int numberOp = deNumber / 12;   // if we can not continue the algorithm further, then we need to write down the final digit, since it is also taken into account. The finish digit is the dividend, that < 12.
                                            // but it may be such a situation that even the original decimal number was not divisible by 12. Then an extra digit 0 appears, which will then be removed.
            convert(st1, deNumber, i, numberOp);
            st1[i + 1] = '\0';
        }
        deNumber = deNumber / 12;   // if check isn't false then we need to continue ( not false if quotient >= 12, then we can devide again and this is not finish)
        i++;    // move to next position
    }
    int j = 0;  // just for finding the end of the line
    for (; st1[j] != '\0'; j++){}   // just finding the end of the line
    if (st1[j - 1] == '0' && ('0' <= st1[j - 2] && st1[j - 2] <= '9'))  // for situations if the initial decimal number is less than 12. So as not to write in line useless 0.
    {
        st1[j - 1] = '\0';
    }

    for (int i = 0, j = strlen(st1) - 1; i <= j; i++, j--)  // for reversing line
    {
        int temp;
        temp = st1[i];
        st1[i] = st1[j];
        st1[j] = temp;
    }
    cout << "Number in duodecimal system: " << st1 << endl;

    delete[] st1;
    delete[] st;
}