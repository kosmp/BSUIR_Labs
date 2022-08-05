#include <iostream>
using namespace std;

int checkSymbolsPositive(int& n, char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод.
{
    int f = 0;
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
    if (n == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

int checkSymbols(int& l, char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод.
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
        l = -f;
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
        l = f;
    }
    delete[] st;
    return 0;
}

int main()
{
    int n;
    char* st = new char[1000000];   // массив, созданный только для проверки. 
    cout << "Enter size of array(k): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int values.";
        return 0;
    }
    int*** arr = new int** [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int* [n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = new int[n];
        }
    }
    cout << "We have matrix " << n << "^3" << endl;
    cout << "Lets fill this matrix with int values" << endl;
    int l;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                char* st = new char[1000000];   // массив, созданный только для проверки. 
                cout << "arr[" << i << "]" << "[" << j << "]" << "[" << k << "]= ";
                cin >> st;
                if (checkSymbols(l, st) != 0)
                {
                    cout << "You needn't to enter symbols. Only int values.";
                    return 0;
                }
                arr[i][j][k] = l;
            }
        }
    }
    // Выше обычное создание и заполнение массива
    
    int sumOfFirst = 0;
    for (int i = 0, j = 0, k = 0; i < n; i++, j++, k++)
    {
        sumOfFirst += arr[i][j][k];
    }    
    cout << "Sum of the first diagonal= " << sumOfFirst << endl;
    
    int sumOfSecond = 0;
    for (int i = 0, j = n - 1, k = n - 1; i < n; i++, j--, k--)
    {
        sumOfSecond += arr[i][j][k];
    }
    cout << "Sum of the second diagonal= " << sumOfSecond << endl;

    int sumOfThird = 0;
    for (int i = 0, j = 0, k = n - 1; i < n; i++, j++, k--)
    {
        sumOfThird += arr[i][j][k];
    }
    cout << "Sum of the third diagonal= " << sumOfThird << endl;

    int sumOfFourth = 0;
    for (int i = 0, j = n - 1, k = 0; i < n; i++, j--, k++)
    {
        sumOfFourth += arr[i][j][k];
    }
    cout << "Sum of the fourth diagonal= " << sumOfFourth << endl;

    if (sumOfFirst >= sumOfSecond && sumOfFirst >= sumOfThird && sumOfThird >= sumOfFourth)
    {
        cout << "Sum of the first is the biggest or the first sum is equal to another sum" << endl;
    }
    else if (sumOfSecond >= sumOfFirst && sumOfSecond >= sumOfThird && sumOfSecond >= sumOfFourth)
    {
        cout << "Sum of the second is the biggest or the second sum is equal to another sum" << endl;
    }
    else if (sumOfThird >= sumOfFirst && sumOfThird >= sumOfSecond && sumOfThird >= sumOfFourth)
    {
        cout << "Sum of the third is the biggest or the third sum is equal to another sum" << endl;
    }
    else if (sumOfFourth >= sumOfFirst && sumOfFourth >= sumOfSecond && sumOfFourth >= sumOfThird)
    {
        cout << "Sum of the fourth is the biggest or the fourth sum is equal to another sum" << endl;
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) delete[] arr[i][j];
    }
    for (int i = 0; i < n; i++) delete[] arr[i];
    delete[] arr;
}
