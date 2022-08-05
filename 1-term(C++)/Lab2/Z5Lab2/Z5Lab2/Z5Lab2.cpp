#include <iostream>
using namespace std;

int main()
{
	double a, b, c, d;
	cin >> a >> b >> c >> d;

	double z;
	if (c >= d && a < d)
	{
		z = a + b / c;
		cout << z;
	}
	else if (c < d && a >= d)
	{
		z = a - b / c;
		cout << z;
	}
	else
	{
		z = 0;
		cout << z;
	}

}

