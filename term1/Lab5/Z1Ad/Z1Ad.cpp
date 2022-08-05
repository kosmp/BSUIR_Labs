#include <iostream>
using namespace std;
int checkSymbols(int* n, char* st)
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
        *n = -f;
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
        *n = f;
    }
    delete[] st;
    return 0;
}

int F(int n)
{
    if (n % 10 > 0)
    {
        return n % 10;
    }
    else if (n == 0)
    {
        return 0;
    }
    else
    {
        return F(n / 10);
    }
}

int S(int& p, int& q)
{   
    static int sum = 0;
    while (p <= q)
    {
        sum += F(p);
        p++;
    }
    return sum;
}

int main()
{
    cout << "This program will calculate sum with recursive function calls. Recursive functions will be called with numbers from i to q." << endl;
    cout << "Recursive function will return 0 if current transmitted value = 0, will return i % 10 if current transmitted value % 10 > 0," << endl;
    cout << "else will return result from this function, but with value / 10." << endl;
    int i, q;
    char* st1 = new char[1000];   // array is using only for checking 
    cout << "Enter i: ";
    cin >> st1;
    if (checkSymbols(&i, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 0;
    }
    char* st2 = new char[1000];   // array is using only for checking
    cout << "Enter q: ";
    cin >> st2;
    if (checkSymbols(&q, st2) != 0)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 0;
    }

    if (i < q)
        cout << S(i, q);
    else
        cout << "These i, q aren't processed, because the condition i < q isn't true" << endl;
}
