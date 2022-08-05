// it's fast verison of Z3Ad. Can calcalute 10^9 n
#include <iostream>
using namespace std;

long long int checkSymbolsPositive(long long int& n, char* st)   // function which checks what we have entered
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
    n = f;
    if (n == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

long long int f(long long int n) // this function calculates sum from n to 1
{
    if (n == 0) return 0;   // when n will be = 1 than 1 / 2 = 0. We needn't to check even numbers(only left term), because 1 doesn't contain even number(only 1, only odd).

    if (n % 2 != 0)
        return (n + 1) * (n + 1) / 4 + f((n - 1) / 2);    // sum of odd = sum of all but to ((n - 1)/2). But if would be (n/2) 11 / 2 = 5.5 = 5 it doesn't matter. Left term, it's sum from f(1) to f(last). Arithmetic progression
    else
        return n * n / 4 + f(n / 2);    // sum of odd = sum of all but to (n/2). Left term, it's sum from f(1) to f(last - 1) (calculated with arithmetic progression sum), because last isn't odd. Last number will be checked int the right term f(n/2)
}

int main()
{
    cout << "f (n) is the largest odd divisor of a natural number n. For a given natural n, the value of the sum f (1) + f (2) + ... + f (n) will be calculated" << endl;
    long long int n;
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

    cout << "Sum= " << f(n);
}