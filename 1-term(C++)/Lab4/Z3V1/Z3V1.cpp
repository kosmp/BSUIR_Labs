#include <iostream>
using namespace std;

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
    int N;
    char* st1 = new char[1000000];   // массив, созданный только для проверки. 
    cout << "Enter the size of the matrix(NxN). Enter N: ";
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

    double** matrix = new double* [N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new double[N];
    }
    cout << "We have matrix " << N << "x" << N << endl;
    cout << "Lets fill this matrix with double values" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
        }
    }

    double min = matrix[0][0];
    double max = matrix[0][0];
    int k = 0, g = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matrix[i][j] > max)
            {
                max = matrix[i][j]; // Находим макс значение во всей матрице
                k = i;          // сохраняем номер строки c max значением
            }
            if (matrix[i][j] < min)
            {
                min = matrix[i][j]; // Находим мин значение во всей матрице
                g = i;          // сохраняем номер строки c min значением
            }
        }
    }
    
    double z; // для сохранения значений
    if (k == g)
    {
        cout << "Max and min values in one row" << endl;
    }
    else
    {

        for (int j = 0; j < N; j++)
        {
            z = matrix[k][j];
            matrix[k][j] = matrix[g][j];
            matrix[g][j] = z;
        }
    }
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j % N == 0) cout << "\n";
            cout << matrix[i][j] << "\t";
        }
    }
    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;

    
}
