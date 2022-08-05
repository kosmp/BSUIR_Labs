#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	int x, y;
	cin >> x >> y;
	
	if (x % y == 0)
	{
		cout << "x делится на y без остатка" << endl;
	} else
	if (y % x==0)
	{
		cout << "y делится на x без остатка" << endl;
	} else
	if (x % y != 0 && y % x != 0)
	{
		cout << "x не делится на y без остатка и y не делится на x без остатка" << endl;
	}

}

