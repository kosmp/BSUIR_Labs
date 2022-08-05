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

int checkSymbolsPositive(int& n, char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод. Но отрицательные не пропускает
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
    if (f == 0)
    {
        cout << "You inserted 0" << endl;
        return 401;
    }

    n = f;

    delete[] st;
    return 0;
}

int main()
{
    int n;  // используется для хранения обработанного значения, которое мы ввели и получили из функции обработанным.
    int N, M;
    char* st1 = new char[1000000];   // массив, созданный только для проверки. 
    cout << "Enter the size of the matrix(NxM). Enter N: ";
    cin >> st1;
    if (checkSymbolsPositive(n, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    N = n;
    if (N < 2)
    {
        cout << "You need to enter matrix with size 2 or more. N<2 is useless" << endl;
        return 0;
    }
    char* st2 = new char[1000000];   // массив, созданный только для проверки.
    cout << "Enter the size of the matrix(NxM). Enter M: ";
    cin >> st2;
    if (checkSymbolsPositive(n, st2) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    M = n;
    if (M < 2)
    {
        cout << "You need to enter matrix with size 2 or more. M<2 is useless" << endl;
        return 0;
    }

    int** matrix = new int* [N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new int[M];
    }
    cout << "We have matrix " << N << "x" << M << endl;
    cout << "Lets fill this matrix with int values" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char* st = new char[1000000];   // массив, созданный только для проверки. 
            cin >> st;
            if (checkSymbols(n, st) != 0)
            {
                cout << "You needn't to enter symbols. Only int values.";
                return 0;
            }
            matrix[i][j] = n;
        }
    }

    int count = 0; // Счётчик локальных минимумов
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i == 0 && j == 0)   // если в данный момент работаем с элементом в левом верхнем углу
            {
                if (matrix[i][j] < matrix[i][j + 1] && matrix[i][j] < matrix[i + 1][j])
                    count++;
            }
            else if (i == N - 1 && j == M - 1)   // если в данный момент работаем с элементом в правом нижнем углу
            {
                if (matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i - 1][j])
                    count++;
            }
            else if (i == N - 1 && j == 0)   // если в данный момент работаем с элементом в левом нижнем углу
            {
                if (matrix[i][j] < matrix[i][j + 1] && matrix[i][j] < matrix[i - 1][j])
                    count++;
            }
            else if (i == 0 && j == M - 1)   // если в данный момент работаем с элементом в правом верхнем углу
            {
                if (matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i + 1][j])
                    count++;
            }
            else if (i == 0)    // элементы самой верхней строки
            {
                if (matrix[i][j] < matrix[i][j + 1] && matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i + 1][j])
                    count++;
            }
            else if (j == 0)    // элементы самого левого столбца
            {
                if (matrix[i][j] < matrix[i][j + 1] && matrix[i][j] < matrix[i - 1][j] && matrix[i][j] < matrix[i + 1][j])
                    count++;
            }
            else if (i == N - 1)    // элементы самой нижней строки
            {
                if (matrix[i][j] < matrix[i][j + 1] && matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i - 1][j])
                    count++;
            }
            else if (j == M - 1)    // элементы самого правого столбца
            {
                if (matrix[i][j] < matrix[i][j - 1] && matrix[i][j] < matrix[i + 1][j] && matrix[i][j] < matrix[i - 1][j])
                    count++;
            }
            else
            {
                // Проверяем с 4 сторон
                if (matrix[i][j] < matrix[i + 1][j] && matrix[i][j] < matrix[i - 1][j] && matrix[i][j] < matrix[i][j + 1] && matrix[i][j] < matrix[i][j - 1])
                    count++;
            }
        }
    }
    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
    cout << "This program calculates count of local minimums" << endl;
    cout << "There are " << count << " local minimums" << endl;
}



