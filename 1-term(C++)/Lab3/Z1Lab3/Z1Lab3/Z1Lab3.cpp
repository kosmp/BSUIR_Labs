#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a, b, N;
    N = 0;

    for (int i = 1; i <= 30; i++)
    {
        if (i % 2 == 0)
        {
            a = i / 2;
            b = i * i * i;
        }
        else
        {
            a = i;
            b = i * i;
        }
        N = pow(a - b, 2) + N;
    }
    cout << "N(sum)= " << N << endl;
    cout << "\nN = sum of (a with index i - b with index i)^2 from i = 1 to i = 30" << endl;
    cout << "a with index i = i, if i is odd OR if a with index i is even, then = i / 2" << endl;
    cout << "b with index i = i * i, if i is odd OR if b with index i is even, then = i * i * i" << endl;
}

