#include <iostream>
using namespace std;

int main()
{
    int parts;
    cout << "Enter number of parts to divide the search area of the root" << endl;

    char* st = new char[1000000000]; // наша строка
    cin >> st;

    /*j = atoi(st);*/   // функция, которая переводит число, которое было в виде символов, составляющих массив, в int. Иначе, если есть лишние символы, то в 0, но отрабатывает некорректно. Нужно дописывать проверки. Например, -2 или 2- пройдёт и даст невеный результат.

    int f = 0;    // Реализация функции atoi с полезными исправлениями.
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 0;
        }
        f *= 10;
        f += st[i] - '0';
    }
    parts = f;

    if (parts == 0)
    {
        cout << "you have entered 0" << endl;
        return 0;
    }
    delete[] st;

    double step = 2.0 / parts;
    cout << "Step of searching= " << step << endl;
    double x = 1;
    double min = fabs(acos(exp(-x)) - 2 * sin(x));
    cout << "y= " << min << " with fabs" << endl;
    double xx;
    for (x = 1 + step; x <= 3; x += step)
    {
        double y;
        y = fabs(acos(exp(-x)) - 2 * sin(x));
        cout << "y= " << y << " with fabs" << endl;
        if (y < min)
        {
            xx = x;
            min = y;
        }
    }
    cout << "min= " << fabs(min) << endl;
    cout << "It was reached with x= " << xx << endl;


}

