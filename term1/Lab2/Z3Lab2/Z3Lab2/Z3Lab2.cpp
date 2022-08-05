// Первый вариант программы
#include <iostream>
using namespace std;

int main()
{
    double x, y;
    cin >> x >> y;
    
    (x > y) ? cout << "x is the biggest" : (x < y) ? cout << "y is the biggest" : cout << "x is equal y";

}

