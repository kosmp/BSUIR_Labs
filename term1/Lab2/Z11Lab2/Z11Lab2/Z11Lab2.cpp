#include <iostream>
using namespace std;

int main()
{
    double a, r;
    cin >> a >> r;
    double S1 = a * a;
    double S2 = 3.14 * r * r;

    if (S1 > S2) 
    {
        cout << "The square has bigger square than circle";
    }
    else if (S1 == S2)
    {
        cout << "S1(square) = S2(circle)" << endl;
    }
    else
    {
        cout << "The square has smaller square than circle";
    }
    

}

