#include <iostream>
using namespace std;

int main()
{
    int x, y;
    cin >> x >> y;

    if (x < y)
    {
        x = 0;
    }
    else if (y < x)
    {
        y = 0;
    }
    else
    {
        x = y = 0;
    }

    cout << "x=" << x << " y=" << y << endl;

    int A, B, C, K;
    cin >> A >> B >> C >> K;    // A B C по условию различны

    if (A > B && A > C) 
        A -= K;
    else
    if (B > A && B > C) 
        B -= K;
    else
    if (C > A && C > B) 
        C -= K;


    cout << "A=" << A << " B=" << B << " C=" << C << endl;
}

