#include "pch.h"
#include <utility>
#include <limits.h>
#include "DynamicLib.h"
bool checkSin;

int checkSymbolsPositive(int& n, char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод.
{
    int f = 0;
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 401;
        }
        f *= 10;
        f += st[i] - '0';
    }
    n = f;
    if (n == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

int checkSymbols(int& n, char* st)
{
    int f = 0;
    if (st[0] == '-')   // check on negative value
    {
        if (strlen(st) == 1)
            return 401;
        for (int i = 1; i < strlen(st); i++)
        {
            if (st[i] < '0' || st[i] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 401;
            }
            f *= 10;
            f += st[i] - '0';
        }
        n = -f;
    }
    else    // if not negative value
    {
        for (int i = 0; i < strlen(st); i++)
        {
            if (st[i] < '0' || st[i] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 401;
            }
            f *= 10;
            f += st[i] - '0';
        }
        n = f;
    }
    delete[] st;
    return 0;
}

int checkAndEnterSizeArray(int& n)
{
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter size of array(n): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int values." << endl;
        return 400;
    }
    else
    {
        return 0;
    }
}

int enterArray(int* arr, int i)
{
    int n;  // for containing of value to check, local n
    char* st = new char[1000];   // array is using only for checking 
    cin >> st;
    if (checkSymbols(n, st) != 0)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 400;
    }
    arr[i] = n;
    return 0;
}

bool func(int left, int right, int* arr)
{
    int i = left;
    int j = right;
    int k = (left + right + 1) / 2;

    for (; i < k; i++)    // left
    {
        if (sin(arr[i]) > 0) checkSin = true;
    }
    if (left < i - 1)   // if elements > 1, we can try to divide and then check 2 parts again. i - 1 because if we started (for) then i will be 1 more than real. If the cycle did not start, then it will be true, but this condition will not affect
    {
        func(left, i - 1, arr);
    }

    for (; j >= k; j--)  // right, including k
    {
        if (sin(arr[j]) > 0) checkSin = true;
    }
    if (right > j + 1)    // if elements > 1, we can try to divide and then check 2 parts again. j + 1 because if we started (for) then j will be 1 less than real. If the cycle did not start, then it will be true, but this condition will not affect
    {
        func(j + 1, right, arr);        
    }
    else
    {
        return checkSin;
    }
    return checkSin;
}