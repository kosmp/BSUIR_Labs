#include <iostream>
using namespace std;

double func(double x, double j)
{
    //do
    //{
    //    cout << "Enter number of terms " << endl;
    //    cin >> j;
    //} while (j < 1);
    double n = x;
    double sum = 0;
    int i = 1;

    do
    {
        sum += n;
        n *= x * x / ((2 * i) * (2 * i + 1));
        i++;
    } while (i < j);

    return sum;
}


int main()
{
    int e;
    cout << "Enter number of x to enter(its function arguments) " << endl;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////// Проверка на ввод отриательного числа или не числа вовсе
    char* stt = new char[100]; // наша строка
    cin >> stt;

    int g = 0;    // Реализация функции atoi с полезными исправлениями.
    for (int i = 0; i < strlen(stt); i++)
    {
        if (stt[i] < '0' || stt[i] > '9')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 0;
        }
        g *= 10;
        g += stt[i] - '0';
    }
    e = g;

    if (e == 0)
    {
        cout << "you have entered 0" << endl;
        return 0;
    }
    delete[] stt;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(int u = 1; u<=e; u ++) 
    {
    double x;
    cout << "Enter x (its function argument) (from 0.1 to 1) " << endl;
    cin >> x;

          // Все символы из таблицы ascii при переводе в число, в свой код имеют значения больше 0, 1. Поэтому символы эту проверку не проходят. 
                                // Но если вводится число и потом левый символ, то число присваивается x, остаётся с x, а символ остаётся в потоке. Например 0.2f или 1- и др. 
    if (x < 0.1 || x > 1 )                            // А дальше этот символ автоматически заполняет массив и, соответственно, не проходит. Так реализована проверка, ввёл пользователь дробное число или символы.
    {
        cout << "You need to enter x from 0.1 to 1, error" << endl;
        return 0;
    }

    double func1 = (exp(x) - exp(-x)) / 2;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////// Проверка на ввод отриательного числа или не числа вовсе
    double j;
    char* st = new char[100]; // наша строка
    cout << "Enter number of terms (if your previous enter was correct) " << endl;
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
    j = f;

    if (j == 0)
    {
        cout << "you have entered 0" << endl;
        return 0;
    }
    delete[] st;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////



    double func2 = func(x, j);
    cout.precision(20);
    if (func2 > func1)
    {
        cout << "Left func > right func" << endl;
        cout << "left func " << func2 << endl;
        cout << "right func " << func1 << endl;
    }
    else if (func2 < func1)
    {
        cout << "Left func < right func" << endl;
        cout << "left func " << func2 << endl;
        cout << "right func " << func1 << endl;
    }
    else
    {
        cout << "Functions are equal" << endl;
        cout << "left func " << func2 << endl;
        cout << "right func " << func1 << endl;
    }
    }
}
