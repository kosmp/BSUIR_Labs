#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double e = pow(10, -3);
	double d;
	int n = 1;
	do
	{
		d = pow(1.0 / 2, n) + pow(1.0 / 3, n);
		++n;
	} while (d >= e);
	cout << "d = (1/2)^n + (1/3)^n = " << d << " and d < epsilon, epsilon = 10^(-3), n is integer";

}

