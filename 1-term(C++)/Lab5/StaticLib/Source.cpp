#include "StaticLib.h"

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

int checkAndEnterSizeArray(int &n) 
{
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter size of array(n)(n must be = 7): ";
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