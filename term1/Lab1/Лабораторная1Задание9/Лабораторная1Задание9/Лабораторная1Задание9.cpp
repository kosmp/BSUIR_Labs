#include <iostream>
using namespace std;

int main()
{
    double b1;
    cin >> b1;
    double n = 1;
    double q = 1 / (n + 1);
    double S = b1 / (1 - q);
    cout << S;
}
