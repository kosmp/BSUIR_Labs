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
    int N, M, N1, M1;
    cout << "This program multiplies matrix A*B. If it's possible." << endl;

    char* st1 = new char[1000000];   // массив, созданный только для проверки. 
    cout << "Enter the size of the matrix(NxM). Enter N: ";
    cin >> st1;
    if (checkSymbolsPositive(n, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    N = n;

    char* st2 = new char[1000000];   // массив, созданный только для проверки.
    cout << "Enter the size of the matrix(NxM). Enter M: ";
    cin >> st2;
    if (checkSymbolsPositive(n, st2) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    M = n;

    char* st3 = new char[1000000];   // массив, созданный только для проверки. 
    cout << "Enter the size of the matrix(N1xM1). Enter N1: ";
    cin >> st3;
    if (checkSymbolsPositive(n, st3) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    N1 = n;

    char* st4 = new char[1000000];   // массив, созданный только для проверки.
    cout << "Enter the size of the matrix(N1xM1). Enter M1: ";
    cin >> st4;
    if (checkSymbolsPositive(n, st4) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    M1 = n;

    int** A = new int* [N];
    for (int i = 0; i < N; i++)
    {
        A[i] = new int[M];
    }
    cout << "We have matrix A " << N << "x" << M << endl;
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
            A[i][j] = n;
        }
    }

    int** B = new int* [N1];
    for (int i = 0; i < N1; i++)
    {
        B[i] = new int[M1];
    }
    cout << "We have matrix B " << N1 << "x" << M1 << endl;
    cout << "Lets fill this matrix with int values" << endl;

    for (int i = 0; i < N1; i++)
    {
        for (int j = 0; j < M1; j++)
        {
            char* st = new char[1000000];   // массив, созданный только для проверки. 
            cin >> st;
            if (checkSymbols(n, st) != 0)
            {
                cout << "You needn't to enter symbols. Only int values.";
                return 0;
            }
            B[i][j] = n;
        }
    }
    ///////////////////// Выше инициализация матрицы A и B с проверкой на неверный ввод
    int** C = new int* [N];
    for (int i = 0; i < N; i++)
    {
        C[i] = new int[M1];
    }
    ///////////////////////////// Матрица C, которая будет хранить произведение

    if (M == N1)
    {
        cout << "matrix A is matched with matrix B" << endl;
        // Перемножаем
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M1; j++)
            {
                C[i][j] = 0;
                for (int k = 0; k < M; k++)
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }        
        cout << "A*B: " << endl;
        for (int i = 0; i < N; i++)
        {
            cout << endl;
            for (int j = 0; j < M1; j++)
            {
                cout << C[i][j] << "\t";
            }
        }

    }
    else
    {
        cout << "matrix A is not matched with matrix B" << endl;
    }


    for (int i = 0; i < N; i++)
    {
        delete[] A[i];
    }
    for (int i = 0; i < N1; i++)
    {
        delete[] B[i];
    }
    for (int i = 0; i < N; i++)
    {
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
}
