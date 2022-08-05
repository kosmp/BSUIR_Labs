#include <iostream>
#include <cmath>
using namespace std;

long long int k;

long long int checkSymbolsPositive(long long int* n, char* st)   // function which checks what we have entered
{
    long long int f = 0;
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

int enterValues(long long int& n, long long int& t)
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

long long int f(long long int n, long long int r)
{
    long long int sum = 0;
    if (n == 0 && r == 0)
    {
        return 1;
    }
    else if (n > 0 && 0 <= r && r < (n*(k-1) + 1))
    {
        for (register long long int i = 0; i <= k - 1; i++)
        {
            sum += f((n - 1), (r - i));
        }
        return sum;
    }
    else
    {
        return 0;
    }
}

int main()
{
    cout << "This program calculates the sum, which consists of function calls" << endl;
    long long int n, t;
    long long int x = 0;
    if (enterValues(n, t) != 0)
    {
        return 0;
    }

    int m = int(pow(10, t));
    if (k != n != t)
    {
        for (register long long int i = 0; i <= n * (k - 1); i++)
        {
            x += f(n, i);
        }
        cout << "x(sum)= " << x % m << endl;
    }
    else
    {
        cout << "Values are not processed, because they are equal." << endl;
    }
}
