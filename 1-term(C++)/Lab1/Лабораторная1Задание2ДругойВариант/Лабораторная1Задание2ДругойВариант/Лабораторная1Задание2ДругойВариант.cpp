// Вариант 1
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    double D;
    cout << "Введите D " << endl;
    cin >> D;
    double x;
    cout << "Введите x " << endl;
    cin >> x;
    double b = x + D;
    double A = D * x / b;

    double S = (pow(A, 2) + b * cos(x)) / (pow(D, 3) + (A + D - b));
    cout << S;

}

