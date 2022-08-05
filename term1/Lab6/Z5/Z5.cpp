#include <iostream>
using namespace std;

int checkSymbolsPositive(long int* n, char* st)   // function which checks what we have entered
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
    *n = f;
    if ((*n) == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

int enterValue(long int* n)
{
    char* st = new char[1000];   // array is using only for checking 
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

int main()
{
    cout << "Two lines S1 and S2 are given. It is known that one of them was the suffix of the required string S, and the other was its prefix." << endl;
    cout << "The length of the required string L is also known, as well as the fact that the string S consisted only of lowercase letters of the Latin alphabet." << endl;
    cout << "Determines the number of lines that satisfy these restrictions." << endl;
    cout << "Since this number can be large enough, it is necessary to derive it module m." << endl;
    long int t, q;
    cout << "Enter t(1<=t<=100): ";
    do
    {
        q = enterValue(&t);
    } while (t > 100 || q != 0);
    for (int x = 0; x <= t; x++)
    {
        char* S1 = new char[200];
        char* S2 = new char[200];
        long int L, m;
        cout << "Let's enter L (size of S) and m through the space.(1 <= L <= 10 ^ 9)(1 <= m <= 10 ^ 4)" << endl;
        do
        {
            q = enterValue(&L);
        } while (q != 0);
        do
        {
            q = enterValue(&m);
        } while (q != 0);
        if (!(L <= pow(10, 9)))
        {
            cout << "Incorrect L" << endl;
            return 0;
        }
        if (!(m <= pow(10, 4)))
        {
            cout << "Incorrect m" << endl;
            return 0;
        }
        cin.ignore(10, '\n');
        cout << "Let's fill line S1. Only latin lowercase letters.(max size = 200)" << endl;
        cin >> S1;
        for (int i = 0; S1[i] != '\0'; i++)
        {
            if (!(S1[i] >= 97 && S1[i] <= 122))
            {
                cout << "Incorrect enter." << endl;
                return 0;
            }
        }
        cout << "Let's fill line S2. Only latin lowercase letters.(max size = 200)" << endl;
        cin >> S2;
        for (int i = 0; S2[i] != '\0'; i++)
        {
            if (!(S2[i] >= 97 && S2[i] <= 122))
            {
                cout << "Incorrect enter." << endl;
                return 0;
            }
        }


        char* S = new char[L + 1];
        
        long int insideSize = L - strlen(S1) - strlen(S2);
        int count = 0;

        if (insideSize <= 0)    // then we need to check can s1 stick with s2 or not
        {
            for (int i = 0; i <= strlen(S1) - 1; i++)
            {
                    if (S1[i] == S2[0]) // if founded same element we need to check remaining elements in S1 (from this index to the end, if number of remaining elements <= size S2)
                    {
                        count = 1;  // founded 1 letter
                        if ((strlen(S1) - 1) - i <= strlen(S2))     // if we have the right amount of letters
                        {
                            int compLetters = (strlen(S1) - 1) - i;
                            for (int k = i + 1, j = 1; k <= strlen(S1) - 1; k++, j++)
                            {
                                if (S1[k] != S2[j])
                                {
                                    count = 0;
                                    break;
                                }
                                else
                                {
                                    count++;
                                }
                            }
                        }
                    }
            }

        }
        insideSize += count;
        cout << "Inside size: " << insideSize << endl;


        if (insideSize >= 0)
        {
            long long int a = 1;
            for (int i = 1; i <= insideSize; i++)
            {
                a *= 26;
            }
            if (insideSize != 0 ) a = a * 2;    // unknown what is the prefix and what is the suffix.
            cout << "The number of lines satisfying this restrictions: " << a % m << endl;
        }
        else
        {
            cout << "The number of lines satisfying this restrictions: 0" << endl;
        }
        delete[] S1;
        delete[] S2;
        delete[] S;
    }
}