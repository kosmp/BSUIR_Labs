#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int a1;
    int a100;
    cin >> a1;
    cin >> a100;
    int d = (a100 - a1) / 99;

    int n = 1;
    auto S = (2*a1+d*(n+9))*(n+10)/2;

    cout << d << endl;
    cout << S << endl;
}

