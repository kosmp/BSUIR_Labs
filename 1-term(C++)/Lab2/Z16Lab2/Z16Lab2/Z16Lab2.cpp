#include <iostream>
using namespace std;

int main()
{
    int a, b, nod, nok;
    cin >> a >> b;

    //if (a % b == 0)
    //{
    //    int nod = b;
    //    int nok = a;
    //    cout << "nod= " << nod << " nok= " << nok << endl;
    //    return 0;
    //}
    //else if (b % a == 0)
    //{
    //    int nod = a;
    //    int nok = b;
    //    cout << "nod= " << nod << " nok= " << nok << endl;
    //    return 0;
    //}

    int c = a * b;
    while (a != b)      // Алгоритм евклида
    { 
        if (a > b)
        {
            a = a - b;
        }
        else 
        {
            b = b - a;
        }
    }
    nod = a; // nod = a = b
    nok = c / nod;
    cout << "nod= " << nod << " nok= " << nok << endl;

}

