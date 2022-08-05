#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double a, b, c;
	int N;
	cin >> a >> b >> c >> N;
	double Y;

	switch (N) 
	{
	case 2:
		Y = b * c - a * a;
		break;
	case 56:
		Y = b * c;
		break;
	case 7: 
		Y = a * a + c;
		break;
	case 3:
		Y = a - b * c;
		break;
	default: 
		Y = pow(a + b, 3);
		break;
	}
}