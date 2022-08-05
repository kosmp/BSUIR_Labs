#include <iostream>
#include <cmath>
using namespace std;

long int checkSymbolsPositive(long int& n, char* st)   // function which checks what we have entered
{
    long int f = 0;
    for (long int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            cout << "You have entered incorrect symbol. You need to enter natural number." << endl;
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

long int checkOddDivisor(long int n)
{
    long int maxDivisor = 1;    // max odd divisor
    if (n % 2 != 0)
    {
        maxDivisor = n;
    }
    else
    { 
        for (register long int i = 1; i <= n / 2; i++)
        {
            if ((n % i == 0) && (i % 2 != 0)) maxDivisor = i;
        }
    }

    return maxDivisor;
}

long long int sum(long int& n)
{
    long long int sum = 0;
    for (register long int i = 1; i <= n; i++)
        sum += checkOddDivisor(i);
    return sum;
}

int main()
{
    cout << "f (n) is the largest odd divisor of a natural number n. For a given natural n, the value of the sum f (1) + f (2) + ... + f (n) will be calculated" << endl;
    long int n;
    do
    { 
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter n(natural number)(n <= 10^9): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        return 0;
    }
    } while (n > pow(10, 9));

    cout << "Sum= " << sum(n);

}
