#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	setlocale(0, "Ru");
	double r, R;
	cin >> r >> R;
	double x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	if (R >= r + sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)))
	{
		cout << "Да" << endl;
	}
	else if (r > R + sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)))
	{
		cout << "Да, но справедливо обратное для двух фигур" << endl;
	} 
	else if (r < sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) + R)
	{
		cout << "Фигуры пересекаются" << endl;
	} 
	else if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) >= R + r)
	{
		cout << "Ни одно условие не выполнено" << endl;
	}

}

