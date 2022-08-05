#include <iostream>
#include <cmath>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    double x1, y1, x2, y2, x3, y3;

    cout << "Insert x1: ";
    cin >> x1;

    cout << "Insert y1: ";
    cin >> y1;

    cout << "Insert x2: ";
    cin >> x2;

    cout << "Insert y2: ";
    cin >> y2;

    cout << "Insert x3: ";
    cin >> x3;

    cout << "Insert y3: ";
    cin >> y3;


    double a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); 
    double b = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2));
    double c = sqrt(pow(x3 - x1, 2) + pow(y3 - y1, 2));
    cout << "Все стороны треугольника: a " << a << " b " << b << " c " << c << endl;

    double P = a + b + c;
    double p = P / 2;
    cout << "Периметр треугольника " << P << endl;

    double s1 = sqrt(p * (p - a) * (p - b) * (p - c));         // Нахождение площади первым способом
    cout << "Площадь треугольника " << s1 << endl;

    double r = s1 / p;
    cout << "Радиус вписанной окружности r= " << r << endl;

    double R = a * b * c / (4 * s1);
    cout << "Радиус описанной окружности R= " << R << endl;

    double sor = 3.14 * r * r;
    double soR = 3.14 * R * R;
    cout << "Площадь вписанной " << sor << " и описанной " << soR << " окружности" << endl;

    double lor = 2 * 3.14 * r;
    double loR = 2 * 3.14 * R;
    cout << "Длина вписанной " << lor << " и описанной " << loR << " окружности" << endl;
    
    double sinn = sqrt(1-pow(a*a+b*b-c*c,2)/(4*a*a*b*b));       
    double s2 = 0.5 * a * b * sinn;                                                 // Нахождение площади вторым способом
    double s22 = 0.5 * a * b * sin(acos((a * a + b * b - c * c) / (2 * a * b)));    // Дополнение второго способа нахождения площади. Альтернативный вариант
    double s3 = a * b * c / (4 * R);                                                // Нахождение площади третьим способом
    double s4 = r * p;                                                              // Нахождение четвёртым способом площади 
    
    double ha = 2 * s1 / a;
    double hb = 2 * s1 / b;
    double hc = 2 * s1 / c;
    cout << "Все высоты треугольника: ha " << ha << " hb " << hb << " hc " << hc << endl;

    double ma = 0.5 * sqrt(2*b*b+2*c*c-a*a);
    double mb = 0.5 * sqrt(2*a*a+2*c*c-b*b);
    double mc = 0.5 * sqrt(2*a*a+2*b*b-c*c);
    cout << "Все медианы треугольника: ma " << ma << " mb " << mb << " mc " << mc << endl;

    double lc = 2 * sqrt(a * b * p * (p - c)) / (a + b);
    double la = 2 * sqrt(c * b * p * (p - a)) / (c + b);
    double lb = 2 * sqrt(a * c * p * (p - b)) / (a + c);
    cout << "Все биссектрисы треугольника: la " << la << " lb " << lb << " lc " << lc << endl;


    cout << "Радианная мера всех углов: alfa " << acos(a / (2*R)) << " beta " << acos(b / (2*R)) << " gama " << acos(c / (2*R)) << endl;  // сторона не может быть больше, чем два радиуса, т.к. треугольник не сомкнётся
    cout << "Градусная мера всех углов: alfa " << acos(a / (2 * R))*180/ 3.14 << " beta " << acos(b / (2 * R)) * 180 / 3.14 << " gama " << acos(c / (2 * R)) * 180 / 3.14 << endl;
    return 0;
}
