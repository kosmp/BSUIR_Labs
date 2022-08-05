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

    double** matrix = new double* [N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new double[M];
    }
    cout << "We have matrix " << N << "x" << M << endl;
    cout << "Lets fill this matrix with int values" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> matrix[i][j];
        }
    }


    double** matrix2 = new double* [N];
    for (int i = 0; i < N; i++)
    {
        matrix2[i] = new double[M];
    }


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i == 0 && j == 0)   // если в данный момент работаем с элементом в левом верхнем углу
            {
                    matrix2[i][j] = (matrix[i][j + 1] + matrix[i + 1][j]) / 2.0;
            }
            else if (i == N - 1 && j == M - 1)   // если в данный момент работаем с элементом в правом нижнем углу
            {
                    matrix2[i][j] = (matrix[i][j - 1] + matrix[i - 1][j]) / 2.0;     
            }
            else if (i == N - 1 && j == 0)   // если в данный момент работаем с элементом в левом нижнем углу
            {
                    matrix2[i][j] = (matrix[i][j + 1] + matrix[i - 1][j]) / 2.0;                   
            }
            else if (i == 0 && j == M - 1)   // если в данный момент работаем с элементом в правом верхнем углу
            {
                    matrix2[i][j] = (matrix[i][j - 1] + matrix[i + 1][j]) / 2.0;              
            }
            else if (i == 0)    // элементы самой верхней строки
            {
                    matrix2[i][j] = (matrix[i][j + 1] + matrix[i][j - 1] + matrix[i + 1][j]) / 3.0;
                    
            }
            else if (j == 0)    // элементы самого левого столбца
            {
                matrix2[i][j] = (matrix[i][j + 1] + matrix[i - 1][j] + matrix[i + 1][j]) / 3.0;
            }
            else if (i == N - 1)    // элементы самой нижней строки
            {
                matrix2[i][j] = (matrix[i][j + 1] + matrix[i][j - 1] + matrix[i - 1][j]) / 3.0;
            }
            else if (j == M - 1)    // элементы самого правого столбца
            {
                matrix2[i][j] = (matrix[i][j - 1] + matrix[i + 1][j] + matrix[i - 1][j]) / 3.0;
            }
            else
            {
                // С 4 сторон
                matrix2[i][j] = (matrix[i + 1][j] + matrix[i - 1][j] + matrix[i][j + 1] + matrix[i][j - 1]) / 4.0;
            }
        }
    }
    cout << "This program builds a smoothed matrix from the original one. Each element of the new matrix is the arithmetic mean of the neighbors of each element of the original matrix." << endl;
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
