//Задача 8. Вычислить значение y в зависимости от выбранной функции f(x),
//аргумент определяется из поставленного условия.Возможные значения
//функции f(x) : 2x, x ^ 3, x / 3 (выбор осуществляется используя оператор switch).
//Предусмотреть вывод сообщений, показывающих, при каком условии и с какой
//функцией производились вычисления y
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double z;
    double x;
    cout << "Insert z " << endl;
    cin >> z;
    if (z < 1)
    {
        x = z * z;
        cout << "Calculating will be with x = z * z" << endl;
    } else {
        x = z + 1;
        cout << "Calculating will be with x = z + 1" << endl;
    }

    char n;
    cout << "Insert function f(x) value: if 2x: 1, if x^3: 2, if x/3: 3" << endl;
    cin >> n;
    double f;
    switch (n) {
        case '1':
            f = 2 * x;
            cout << "The value of function f(x) is 2 * x" << endl;
            break;
        case '2':
            f = pow(x, 3);
            cout << "The value of function f(x) is x ^ 3" << endl;
            break;
        case '3':
            f = x / 3;
            cout << "The value of function f(x) is x / 3" << endl;
            break;
        default: 
            break;
    }

    double a;
    cout << "a= ";
    cin >> a;
    double e = a * log(1 + pow(x, 1 / 5));
    cout << "The first part of sum is " << e << " It was calculated with function(log)" << endl;

    double l = pow(cos(f + 1), 2);
    cout << "The second part of sum is " << l << " It was calculated with function(cos)" << endl;

    double y = e + a;
    cout << "y= " << y;





}

