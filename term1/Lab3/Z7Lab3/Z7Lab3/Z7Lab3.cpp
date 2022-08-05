#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cout << "We need to find a two-digit number ab which possesses the property (a + b)^3 = (10 * a + b)^2" << endl;
    for (a = 1; a <= 9; a++)
    {
        for (b = 1; b <= 9; b++)
        { 
                if (pow(a + b, 3) == pow(10 * a + b, 2))
                {
                    cout << "It is " << a << b << endl;  
                }
        }
    }
}
