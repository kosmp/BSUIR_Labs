#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    const int k = 5;
    int arr[k] = {1, 2, 3, 4, 5};
    int arr2[k] = {};
    cout << "We have array: ";
    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << '\n';

    int n; 
    cout << "We need to move this array by n positions" << endl;
    cout << "Enter number of n positions to move by: ";


    //////////////////////////////////////////////////////////////// Ввод числа позиций, на которое надо сместиться с ПРОВЕРКОЙ на НЕВЕРНЫЙ ВВОД
    char* st = new char[1000000000]; // наша строка
    cin >> st;

    int f = 0; 
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
    delete[] st;

    if (n >= k)
    {
        cout << "n must be smaller, than k. ERROR";
        return 0;
    }
    ////////////////////////////////////////////////////////////////

    for (int i = 0; (n + i) < k; i++)   // Перестановка элементов из первоначального массива в изменённый, с учётом пропущеной позиции.
    {
        arr2[i] = arr[n + i];
    }

    for (int j = 0, i = 0; (k - n + j) < k; j++, i++) // Установка в конец изменённого массива пропущенных и не использованных элементов из первоначального. 
    {
        arr2[k - n + j] = arr[i];
    }

    cout << "After moving we have array: ";
    for (int i = 0; i < k; i++)
    {
        cout << arr2[i] << "\t";
    }
}
