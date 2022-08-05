//  Задача 4. Дан квадрат с вершинами в точках (0, 0), (0, k), (k, k), (k, 0).
//  Вычислите наименьшее из расстояний от точки с координатами(x, y), лежащей
//  внутри квадрата, до сторон данного квадрата.Координаты вещественные.Если
//  точка лежит за пределами квадрата, выведите сообщение об этом и расстояние
//  до ближайшей стороны квадрата
#include <iostream>
#include<cmath>
using namespace std;

int main()
{
    double k;
    cout << "Insert k: " << endl;
    cin >> k;
    double x, y;
    cout << "Insert coord x y: " << endl;
    cin >> x >> y;

        if (x <= k && x >=0 && y > k)
        {
            cout << "The dot is out of square" << endl;
            cout << "The lenght is " << y - k;
            return 0;
        } else if (x <= k && x >= 0 && y < 0)
        {
            cout << "The dot is out of square" << endl;
            cout << "The lenght is " << -y;
            return 0;
        } else if (x > k && y <= k && y >= 0)
        {
            cout << "The dot is out of square" << endl;
            cout << "The lenght is " << x - k;
            return 0;
        } else if (x < 0 && y <= k && y >= 0)
        {
            cout << "The dot is out of square" << endl;
            cout << "The length is " << -x;
            return 0;
        } else if (x > k && y > k)
        {
            cout << "The dot is out of square" << endl;
            cout << sqrt(pow(x - k, 2) + pow(y - k, 2)) << endl;
            return 0;
            // вывод правой верхней диагональки
        } else if (x < 0 && y < 0)
        {
            cout << "The dot is out of square" << endl;
            cout << sqrt(pow(0 - x, 2) + pow(0 - y, 2)) << endl;
            return 0;
            // вывод левой нижней диагональки
        } else if (x > k && y < 0)
        {
            cout << "The dot is out of square" << endl;
            cout << sqrt(pow(x - k, 2) + pow(0 - y, 2)) << endl;
            return 0;
            // вывод правой нижней диагональки
        } else if (x < 0 && y > k)
        {
            cout << "The dot is out of square" << endl;
            cout << sqrt(pow(0 - x, 2) + pow(y - k, 2)) << endl;
            return 0;
            // вывод левой верхней диагональки
        } 
 
    double l1, l2, l3, l4;
    l1 = k - y;
    l2 = k - x;
    l3 = y;
    l4 = x;

    if (l1 == l2 && l3 == l4 && l2==l3) 
        cout << "The dot is in the centre and the length to a side= " << l1 << endl;
    else
    if (l1 < l2 && l1 < l3 && l1 < l4) 
        cout << "l1 is the smallest= " << l1 << endl;
    else
    if (l2 < l1 && l2 < l3 && l2 < l4) 
        cout << "l2 is the smallest= " << l2 << endl;
    else
    if (l3 < l1 && l3 < l2 && l3 < l4) 
        cout << "l3 is the smallest= " << l3 << endl;
    else
    if (l4 < l1 && l4 < l2 && l4 < l3) 
        cout << "l4 is the smallest= " << l4 << endl;

    // Рассматривается случай, когда равны 2 расстояния(по 2)
    if (l1 < l3 && l1 < l4 && l1 == l2)
        cout << "l1=l2 and they are the smallest and = " << l1 << endl;
    else if (l2 < l3 && l2 < l4 && l2 == l1)
        cout << "l2=l1 and they are the smallest and = " << l2 << endl;
    else if (l3 < l1 && l3 < l2 && l3 == l4)
        cout << "l3=l4 and they are the smallest and = " << l3 << endl;
    else if (l4 < l1 && l4 < l2 && l4 == l3)
        cout << "l4=l3 and they are the smallest and = " << l4 << endl;

    if (l1 < l2 && l1 < l3 && l1 == l4)
        cout << "l1=l4 and they are the smallest and = " << l1 << endl;
    else if (l4 < l2 && l4 < l3 && l4 == l1)
        cout << "l4=l1 and they are the smallest and = " << l4 << endl;
    else if (l3 < l4 && l3 < l1 && l3 == l2)
        cout << "l3=l2 and they are the smallest and = " << l3 << endl;
    else if (l2 < l4 && l4 < l1 && l2 == l3)
        cout << "l2=l3 and they are the smallest and = " << l2 << endl;
    /////////////////////////////////////////////////////// 
    
    

}

