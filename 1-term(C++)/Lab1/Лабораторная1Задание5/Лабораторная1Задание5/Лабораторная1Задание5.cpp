#include <iostream>
using namespace std;

int main()
{
    double t;
    cin >> t;
    double a;
    cin >> a;
    double v0;
    cin >> v0;
    double s = v0 * t + a * t * t / 2;
    cout << s;
}

