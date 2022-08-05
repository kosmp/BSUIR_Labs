#include <iostream>
using namespace std;

int main()
{
    unsigned x, y, z;
    cout << "Insert sides of triangle(x, y, z)" << endl;
    cin >> x >> y >> z;
    if ((x + y) > z && (x + z) > y && (y + z) > x)
    {
        cout << "This triangle exists" << endl;
    }
    else
    {
        cout << "This triangle can't exist" << endl;
    }
}

