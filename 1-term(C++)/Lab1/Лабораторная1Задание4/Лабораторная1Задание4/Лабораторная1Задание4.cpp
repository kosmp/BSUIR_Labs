// Определить время падения камня на поверхность земли с высоты h.
// h = g*t^2/2
#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "ru");
    const double g = 9.8;
    double h;
    cout << "Введите высоту, с которой падает камень. h= ";
    cin >> h;
    if (h >= 0)
    { 
        double t = sqrt(2 * h / g);
        cout << "Время полёта камня до земли= ";
        cout << t;
    } else
    { 
        cout << "Введены неверные данные";
        return 0;
    }
    return 0;
}

