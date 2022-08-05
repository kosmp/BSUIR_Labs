#include <iostream>
using namespace std;

unsigned long long k;

unsigned long long int checkSymbolsPositive(unsigned long long int* n, char* st)   // function which checks what we have entered
{
    unsigned long long int f = 0;
    for (long long int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            cout << "You have entered incorrect symbol. You need to enter natural number." << endl;
            return 401;
        }
        f *= 10;
        f += st[i] - '0';
    }
    *n = f;
    if (*n == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

int enterValues(unsigned long long int& n, unsigned long long int& t)
{
    do
    {
        char* st = new char[1000];   // array is using only for checking 
        cout << "Enter k(0 < k < 10^19): ";
        cin >> st;
        if (checkSymbolsPositive(&k, st) != 0)
        {
            return 400;
        }
    } while (k >= pow(10, 19));
    do
    {
        char* st = new char[1000];   // array is using only for checking 
        cout << "Enter n(0 < k < 10^19): ";
        cin >> st;
        if (checkSymbolsPositive(&n, st) != 0)
        {
            return 400;
        }
    } while (n >= pow(10, 19));
    do
    {
        char* st = new char[1000];   // array is using only for checking 
        cout << "Enter t(0 < k < 10): ";
        cin >> st;
        if (checkSymbolsPositive(&t, st) != 0)
        {
            return 400;
        }
        else
        {
            return 0;
        }
    } while (t >= 10);
}

int main()
{
    unsigned long long n, t;
    cout << "This program calculates the sum of functions" << endl;
    if (enterValues(n, t) != 0)
    {
        return 0;
    }

    long int m = long int(pow(10, t));
    unsigned long long int len = log(n) / log(2) + 1;  // log2(n) + 1
    unsigned long long int* arr = new unsigned long long int[len];
    unsigned long long int* bitsInv = new unsigned long long int[len];
    for (unsigned long long int i = 0; i < len; i++)
    {
        bitsInv[i] = n % 2;
        n /= 2;
    }
    arr[0] = k;
    for (unsigned long long int i = 1; i < len; i++)
    {
        arr[i] = (arr[i - 1] * arr[i - 1]) % m;
    }
    unsigned long long int x = 1;

    for (unsigned long long int i = 0; i < len; i++)
    {
        x = x * (unsigned long long int)pow(arr[i], bitsInv[i]) % m;
    }

    cout << "x(sum)= " << x % m << endl;

    delete[] arr;
    delete[] bitsInv;
}