#include <iostream>
using namespace std;

int main()
{
    int n;

    char* st = new char[100]; // наша строка
    cout << "Enter number of terms " << endl;
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
    n = f;

    if (n == 0)
    {
        cout << "you have entered 0" << endl;
        return 0;
    }

    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cout << "Enter a" << i << endl;
        
        char *st1 = new char[100]; // наша строка
        cin >> st1;

        int f = 0;    // Реализация функции atoi с полезными исправлениями.
        for (int k = 0; k < strlen(st1); k++)
        {
            if (st1[k] < '0' || st1[k] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 0;
            }
            f *= 10;
            f += st1[k] - '0';
        }
        a = f;

        delete []st1;

        sum += pow(2, i) * pow(-1, i) * a;
    }
    cout << "sum (a0 - 2*a1 + 4*a2 - 8*a3 + ... + 2^(n-1)*(-1)^(n-1)*a(n-1)) = " << sum << endl;
}

