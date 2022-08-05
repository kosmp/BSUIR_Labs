#include <iostream>
using namespace std;

int checkSymbols(int& n, char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод.
{
    int f = 0;
    if (st[0] == '-')   // Благодаря этой проверке отрицательные числа также будут проходить в массив.
    {
        if (strlen(st) == 1)    // strlen не учитывает \0, который ставится автоматически
            return 401;
        for (int i = 1; i < strlen(st); i++)
        {
            if (st[i] < '0' || st[i] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 401;
            }
            f *= 10;
            f += st[i] - '0';
        }
        n = -f;
    }
    else {                // Но если даже первый символ не -, то идёт полная проверка
        for (int i = 0; i < strlen(st); i++)
        {
            if (st[i] < '0' || st[i] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 401;
            }
            f *= 10;
            f += st[i] - '0';
        }
        n = f;
    }
    delete[] st;
    return 0;
}

int main()
{
    const int k = 5;
    int arr[k] = {};
    cout << "You need to feel array:" << endl;
    int n;
    for (int i = 0; i < k; i++) // Заполнение вручную массива, с проверкой на неверный ввод. Отрицательные числа и 0 проходят.
    {
        char* st = new char[1000000];   // массив, созданный только для проверки. 
        cin >> st;
        if (checkSymbols(n, st) != 0)
        {
            cout << "You needn't to enter symbols. Only int values.";
            return 0;
        }
        arr[i] = n;
    }
    int arr2[k] = {};
    cout << "We have array: ";
    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << "\t";
    }
    cout << '\n';
    cout << "This program rearranges negative numbers at the beginning of the array, and positive numbers at the end of the array." << endl;

    int j = 0;
    int count = 0;
    for (int i = 0; i < k; i++)  // Перестановка отрицательных чисел в начало
    {
        if (arr[i] < 0)
        {
            arr2[j] = arr[i];
            j++;
            count++;
        }
    }
    for (int i = 0, j = 0; i < k; i++)  // Перестановка положительных чисел после отрицательных. Счётчик отрицательных(count) для того, чтобы знать, куда ставить нужно, откуда начинать.
                                        // Т.к. нумерация в массиве с 0, то count + 0 ячейка это следующая, за установленным отрицательным элементом
    {
        if (arr[i] >= 0) 
        {       
            arr2[count + j] = arr[i];
            j++;
        }
    }

    cout << "After moving we have array: ";
    for (int i = 0; i < k; i++)
    {
        cout << arr2[i] << "\t";
    }



}
