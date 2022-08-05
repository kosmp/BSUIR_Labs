#include <iostream>
using namespace std;

int main()
{
    double a, b, c, x, y;
    cin >> a >> b >> c >> x >> y;
    double Sxy = x * y;
    double Sac = a * c;
    double Sbc = b * c;
    double Sab = a * b;
    if (Sxy >= Sac || Sxy >= Sbc || Sxy >= Sab)
    {
        cout << "The brick can go through the hole xy" << endl;
    }
    else
    {
        cout << "The brick can't go through the hole xy" << endl;
    }

}

