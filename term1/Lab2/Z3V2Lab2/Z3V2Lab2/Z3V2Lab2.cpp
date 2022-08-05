#include <iostream>
using namespace std;

int main()
{
	double x, y;
	cin >> x >> y;
	
	bool xbm = false, ybm = false;
	(x > y) ? xbm = true : (x < y) ? ybm = true : 0;
	(xbm) ? cout << "x is the biggest" : (ybm) ? cout << "y is the biggest" : cout << "x is equal y";

}

