#include <iostream>
using namespace std;

int main()
{
    const double PI = 3.1415;
    double M = 20;
    double A = 0;
    double B = PI / 2;
    double H = (B - A) / M;
    double x = 0;
    for (int i = 1; x <= B; i++)
    {
        x = A + i * H;
        cout << "value of sin(x) - cos(x) on [A, B] = " << sin(x) - cos(x) << endl;
        cout << "\n x = A + i * H, A = 0, M = 20, B = 3.1415 / 2, H = (B - A) / M, i = 1, 2, 3... while x <= B" << endl;
    }

}

