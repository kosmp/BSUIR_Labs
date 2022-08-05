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
    char* st2 = new char[1000000];   // массив, созданный только для проверки.
    cout << "Enter the size of the matrix(NxM). Enter M: ";
    cin >> st2;
    if (checkSymbolsPositive(n, st2) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    M = n;

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

    int** matrix2 = new int* [N];
    for (int i = 0; i < N; i++)
    {
        matrix2[i] = new int[M];
    }

    
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (i == 0 && j == 0)   // Если это левый верхний угол, то просматривать нужно только 1 элемент, т.е. он будет неизменен и в новой матрице.
                {
                    matrix2[i][j] = matrix[i][j];
                }
                else if (j == 0)    // Если это 0-й столбец, то просматривать при сравнении нужно только 2 элемента. Текущий и на 1 выше, т.к. левее нету.
                {                  
                    if (matrix[i][j] >= matrix[i - 1][j])
                    {
                        matrix2[i][j] = matrix[i][j];
                    }
                    else
                    {
                        matrix2[i][j] = matrix[i - 1][j];
                    }
                }
                else if (i == 0)    // Если это 0-я строка, то просматривать при сравнении нужно только по 2 элемента. Текущий и на 1 влево, т.к. выше нету.
                {
                    if (matrix[i][j] >= matrix[i][j - 1])
                    {
                        matrix2[i][j] = matrix[i][j];
                    }
                    else
                    {
                        matrix2[i][j] = matrix[i][j - 1];
                    }
                }
                else if (j > 0) // Если это не 0-й столбец и не 0-я строка, то просматривать при сравнении нужно по 4 элемента
                {
                    if (matrix[i][j] >= matrix[i - 1][j - 1] && matrix[i][j] >= matrix[i - 1][j] && matrix[i][j] >= matrix[i][j - 1]) // Проверяем, будет ли наибольшим текущий элемент
                    {
                        matrix2[i][j] = matrix[i][j];
                    }
                    else if (matrix[i - 1][j - 1] >= matrix[i][j] && matrix[i - 1][j - 1] >= matrix[i - 1][j] && matrix[i - 1][j - 1] >= matrix[i][j - 1]) // Проверяем, будет ли наибольшим соседний по диагонали элемент
                    {
                        matrix2[i][j] = matrix[i - 1][j - 1];
                    }
                    else if (matrix[i - 1][j] >= matrix[i][j] && matrix[i - 1][j] >= matrix[i - 1][j - 1] && matrix[i - 1][j] >= matrix[i][j - 1]) // Проверяем, будет ли наибольшим соседний верхний элемент
                    {
                        matrix2[i][j] = matrix[i - 1][j];
                    }
                    else  // И остаётся только 1 вариант, когда наибольшим будет левый соседний элемент. Если ни один из 3 не был больше, либо равен другого, значит какой-то элемент из этих 4 был по-любому больше 3-х, либо больше некоторых из 3-х и некоторым был равен.
                    {
                        matrix2[i][j] = matrix[i][j - 1];
                    }
                }
            }
        }
        cout << "The largest element is selected from the adjacent elements located on the left, top, diagonal and the current element and put in place of the current one in the new matrix." << endl;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (j % M == 0) cout << "\n";
                cout << matrix2[i][j] << "\t";
            }
        }

        for (int i = 0; i < N; i++)
        {
            delete[] matrix[i];
            delete[] matrix2[i];
        }
        delete[] matrix;
        delete[] matrix2;


}
