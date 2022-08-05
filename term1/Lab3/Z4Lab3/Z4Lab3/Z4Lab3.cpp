#include <iostream>
using namespace std;

int main()
{
    int a, sum = 0;
    cout << "This programm calculates the sum of even numbers in the range from 1 to a" << endl;
    cout << "Enter a, this is the last value. a must be > 0" << endl;

    char *st = new char [1000000000]; // наша строка, в виде динамческого массива, для того, чтобы можно было изменить его
    cin >> st;

    /*a = atoi(st);*/   // функция, которая переводит число, которое было в виде символов, составляющих массив, в int. Иначе, если есть лишние символы, то в 0, но отрабатывает некорректно. Нужно дописывать проверки. Например, -2 или 2- пройдёт и даст невеный результат.
    
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
    a = f;  // f просто для лучшего вопсриятия. Можно a = 0 сделать в начале и вообще f не вводить

    if (a == 0)
    {
        cout << "you have entered 0" << endl;
        return 0;
    }
    delete[] st;

    //if (a < 0)  // Если использовать atoi, то при вводе, например, -2 неверный результат. Хотя просто на - она реагирует.
    //{
    //    cout << "you have enterted incorrect symbol" << endl;
    //    return 0;
    //}

    for (int i = 1; i <= a; i++)
    {
        if (i % 2 == 0)
        {
            sum += i;
        }
    }
    cout << "Sum1= " << sum << endl;


    // 4.2
    double s, n;
    if (a % 2 == 0)
    {
        n = a / 2;
    }
    else
    {
        n = (a - 1) / 2;
    }
    s = (4 + 2 * (n - 1)) / 2 * n;
    cout << "Sum2= " << s << endl;
    cout << "These sums were obtained in a different ways such as with cycle and without" << endl;

}

