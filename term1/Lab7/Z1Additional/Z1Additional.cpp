// Variant without using arrays. 1-st variant in the list.
#include <iostream>
using namespace std;

int checkSymbolsPositive(int* n, char* st)   // function for check if we entered a number or symbols
{
    int f = 0;
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '6')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 401;
        }
        f *= 10;
        f += st[i] - '0';
    }
    *n = f;
    delete[] st;
    return 0;
}

int checkNumber(int* n)
{
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter a number in the septenary system" << endl;
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols." << endl;
        return 400;
    }
    else
    {
        return 0;
    }
}

void convert(int deNumber)  // function for converting to duodecimal system
{
    if (deNumber >= 12)     // can be devide or not
    {
        convert(deNumber / 12); // Recursive calls are needed because the numbers will be written out from the end, only after the end of the division and in the reverse order.
        if (deNumber % 12 == 10)
        {
            cout << 'A';
        }
        else if (deNumber % 12 == 11)
        {
            cout << 'B';
        }
        else
        {
            cout << deNumber % 12;  // The remainder of the division is written out according to the division using the column.
        }
    }
    else
    {
        if (deNumber == 10)
        {
            cout << 'A';
        }
        else if (deNumber == 11)
        {
            cout << 'B';
        }
        else
        {
            cout << deNumber;   // Final digit is written out according to the division using the column. It's critical digit.
        }
        return;     // exit recursion
    }
}

int main()
{
    cout << "The program converts from the septenary to the duodecimal system." << endl;
    int n, q;   // n = our number
    do
    {
        q = checkNumber(&n);
    } while (q != 0);   // check enter

    int deNumber = 0;
    bool checkNumber = true;
    for (int i = 10, j = 0, t = 10; checkNumber; i *= 10, j++)  // instead o array you can find the remainders of the division so as to use the digits of the number one by one.
    {
        if (n % i == n)
        {
            checkNumber = false;
        }
        if (i == 10)
        {
            int digit = n % i;
            deNumber += digit * pow(7, j);   // example: if 132 in 7 --> in 10. 1*7^2 + 3*7^1 + 2*7^0 = 72
        }
        else
        {
            int digit = (n % i) / t;
            deNumber += digit * pow(7, j);   // example: if 132 in 7 --> in 10. 1*7^2 + 3*7^1 + 2*7^0 = 72
            t*=10;
        }

    }
    
    cout << "Number in duodecimal system : " << endl;
    convert(deNumber);
}