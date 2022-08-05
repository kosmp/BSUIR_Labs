#include <iostream>
using namespace std;

int main()
{
    cout << "We need to find armstrong numbers from 153 to 10^6" << endl;
    cout << "They are: " << endl;
    int i = 153;
    while (i <= pow(10, 6))
    {
        if (i >= 100000 && i < 1000000)    // крайние цифры находятся сразу, а для того, чтобы найти цифры в середине нужно уменьшить число.
        {
            int f = i % 10;

            int e = (i / 10) % 10;

            int d = (i / 100) % 10;

            int c = (i / 1000) % 10;
            
            int b = (i / 10000) % 10;

            int a = i / 100000;

            if (i == (pow(a, 6) + pow(b, 6) + pow(c, 6) + pow(d, 6) + pow(e, 6) + pow(f, 6)))
            {
                cout << i << endl;
            }
            
        }
        if (i >= 10000 && i < 100000)
        {
            int e = i % 10;

            int d = (i / 10) % 10;

            int c = (i / 100) % 10;

            int b = (i / 1000) % 10;

            int a = i / 10000;

            if (i == (pow(a, 5) + pow(b, 5) + pow(c, 5) + pow(d, 5) + pow(e, 5)))
            {
                cout << i << endl;
            }
        }
        if (i >= 1000 && i < 10000)
        {
            int d = i % 10;

            int c = (i / 10) % 10;

            int b = (i / 100) % 10;

            int a = i / 1000;

            if (i == (pow(a, 4) + pow(b, 4) + pow(c, 4) + pow(d, 4)))
            {
                cout << i << endl;
            }
        }
        if (i >= 153 && i < 1000)
        {
            int c = i % 10;

            int b = (i / 10) % 10;

            int a = i / 100;

            if (i == (pow(a, 3) + pow(b, 3) + pow(c, 3)))
            {
                cout << i << endl;
            }
        }

        i++;
        

    }

    
}

