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
    int n;
    cout << "Enter the order of the magic square you want to see. (can't be 2)" << endl;
    char* st1 = new char[1000000];   // массив, созданный только для проверки. 
    cin >> st1;
    if (checkSymbolsPositive(n, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    if (n == 2)
    {
        cout << "You entered 2" << endl;
        return 0;
    }
    
    if (n % 2 == 1)
    {
        int** matrix = new int* [2 * n - 1];
        for (int i = 0; i < 2 * n - 1; i++)
        {
            matrix[i] = new int[2 * n - 1];
        }
        for (int i = 0; i < 2 * n - 1; i++)
        {
            for (int j = 0; j < 2 * n - 1; j++)
            {
                matrix[i][j] = 0;
            }
        }

        int counter = 1;    // счётчик, чтобы ставить цифры в нужном порядке.
        for (int i = (2 * n - 1) / 2, j = 0; i < 2 * n - 1; i++, j++)   // Данный цикл отвечает за крайние левые нижние положения точек отсчёта. Начальное i, j это стартовая точка, середина и самый крайний элемент терассы. 1 раз прошёлся внутренний цикл и после этого меняется стартовая точка в данном цикле(внешнем).
        {
            for (int y = i, x = j, num = 1; num <= n; y--, x++, num++)    // Доходим диагональю до верха, заполняя числами, последовательно. Как только дошли, сдвигаемся на 1 ячейку по диагонали вправо вниз и делаем тоже самое.
            {                                                                     // num отвечает за кол-во цифр, которое мы можем поставить за такой проход.
                matrix[y][x] = counter;
                counter++;
            }
        }

        for (int i = 0; i < 2 * n - 1; i++)
        {
            for (int j = 0; j < 2 * n - 1; j++)
            {
                if (i > ((n / 2) * 3) && matrix[i][j] != 0)     // Переставляем элементы, который были за пределами нужной на матрицы и стояли ВНИЗУ.
                {
                    matrix[i - n][j] = matrix[i][j];
                }
                else if (i < n / 2 && matrix[i][j] != 0)        // Переставляем элементы, который были за пределами нужной на матрицы и стояли ВВЕРХУ.
                {
                    matrix[i + n][j] = matrix[i][j];
                }
                else if (j > ((n / 2) * 3) && matrix[i][j] != 0)    // Переставляем элементы, который были за пределами нужной на матрицы и стояли СПРАВА.
                {
                    matrix[i][j - n] = matrix[i][j];
                }
                else if (j < n / 2 && matrix[i][j] != 0)    // Переставляем элементы, который были за пределами нужной на матрицы и стояли СЛЕВА.
                {
                    matrix[i][n + j] = matrix[i][j];
                }
            }
        }
        int** matrix2 = new int* [n];
        for (int i = 0; i < n; i++)
        {
            matrix2[i] = new int[n];
        }

        for (int i = n / 2, y = 0; y < n; i++, y++)    // Здесь повышается номер строки(высота)
        {
            for (int j = n / 2, x = 0; x < n; j++, x++)    // Здесь проходим в строке по столбцам. Изменяется тоолько номер столбца. Каждый раз начинаем с тех же столбиков просто уже в новых строках.
                matrix2[y][x] = matrix[i][j];
        }

        cout << "Our magic square of order " << n << " :" << endl;
        // вывод и очистка
        for (int i = 0; i < n; i++)
        {
            cout << endl;
            for (int j = 0; j < n; j++)
            {
                cout << matrix2[i][j] << "\t";
            }
        }

        for (int i = 0; i < 2 * n - 1; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        for (int i = 0; i < n; i++)
        {
            delete[] matrix2[i];
        }
        delete[] matrix2;
    }
    else if (n % 4 == 2)
    {
        int k = n / 2;  // Делим на 2, т.к. нечётный магический квадрат должен быть размера в 4 раза меньше
        int** matrix = new int* [2 * k - 1];
        for (int i = 0; i < 2 * k - 1; i++)
        {
            matrix[i] = new int[2 * k - 1];
        }
        for (int i = 0; i < 2 * k - 1; i++)   // Заполнили матрицу нулями.
        {
            for (int j = 0; j < 2 * k - 1; j++)
            {
                matrix[i][j] = 0;
            }
        }

        int counter = 1;    // счётчик, чтобы ставить цифры в нужном порядке. Далее заполняем матрицу цифрами в виде ромба.
        for (int i = (2 * k - 1) / 2, j = 0; i < 2 * k - 1; i++, j++)   // Данный цикл отвечает за крайние левые нижние положения точек отсчёта. Начальное i, j это стартовая точка, середина и самый крайний элемент терассы
        {
            for (int y = i, x = j, num = 1; num <= k; y--, x++, num++)    // Доходим диагональю до верха, заполняя числами, последовательно. Как только дошли, сдвигаемся на 1 ячейку по диагонали вправо вниз и делаем тоже самое.
            {                                                                     // num отвечает за кол-во цифр, которое мы можем поставить за такой проход.
                matrix[y][x] = counter;
                counter++;
            }
        }

        for (int i = 0; i < 2 * k - 1; i++)
        {
            for (int j = 0; j < 2 * k - 1; j++)
            {
                if (i > ((k / 2) * 3) && matrix[i][j] != 0)     // Переставляем элементы, который были за пределами нужной на матрицы и стояли ВНИЗУ.
                {
                    matrix[i - k][j] = matrix[i][j];
                }
                else if (i < k / 2 && matrix[i][j] != 0)        // Переставляем элементы, который были за пределами нужной на матрицы и стояли ВВЕРХУ.
                {
                    matrix[i + k][j] = matrix[i][j];
                }
                else if (j > ((k / 2) * 3) && matrix[i][j] != 0)    // Переставляем элементы, который были за пределами нужной на матрицы и стояли СПРАВА.
                {
                    matrix[i][j - k] = matrix[i][j];
                }
                else if (j < k / 2 && matrix[i][j] != 0)    // Переставляем элементы, который были за пределами нужной на матрицы и стояли СЛЕВА.
                {
                    matrix[i][k + j] = matrix[i][j];
                }
            }
        }
        int** matrix2 = new int* [k];
        for (int i = 0; i < k; i++)
        {
            matrix2[i] = new int[k];
        }

        for (int i = k / 2, y = 0; y < k; i++, y++)
        {
            for (int j = k / 2, x = 0; x < k; j++, x++) // Данный цикл копирует одну строчку за другой. По 1. Сдвигается y и i и поэтому происходит переход на новую.
                matrix2[y][x] = matrix[i][j];
        }

        for (int i = 0; i < 2 * k - 1; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        /////////// Выше создание нечётного магического квадрата нужного размера, чтобы мы могли из 4 изменённый склеить 1 большой

        int** matrixF = new int* [n];   // Матрица, которая будет хранить в себе 4 матрицы
        for (int i = 0; i < n; i++)
        {
            matrixF[i] = new int[n];
        }
        for (int i = 0; i < k; i++) // Заполняем левую верхнюю часть матрицы. Индексы для этого случая совпадают.
        {
            for (int j = 0; j < k; j++)
            {
                matrixF[i][j] = matrix2[i][j];
            }                            
        }
        for (int i = k, g = 0; i < n; i++, g++) // Заполняем правую нижнюю часть матрицы.  
        {
            for (int j = k, t = 0; j < n; j++, t++)
            {
                matrixF[i][j] = matrix2[g][t] + k * k;
            }
        }
        for (int i = 0, g = 0; i < k; i++, g++) // Заполняем правую верхнюю часть матрицы.
        {
            for (int j = k, t = 0; j < n; j++, t++)
            {
                matrixF[i][j] = matrix2[g][t] + 2 * k * k;
            }
        }
        for (int i = k, g = 0; i < n; i++, g++) // Заполняем левую нижнюю часть матрицы.
        {
            for (int j = 0, t = 0; j < k; j++, t++)
            {
                matrixF[i][j] = matrix2[g][t] + 3 * k * k;
            }
        }

        // Вывод матрицы, состоящей из 4, но просто с увеличенными элементами. Для ТЕСТА.
        //for (int i = 0; i < n; i++) 
        //{
        //    cout << endl;
        //    for (int j = 0; j < n; j++)
        //    {
        //        cout << matrixF[i][j] << "\t";
        //    }
        //}
        //cout << endl;
        
        int** matrixFF = new int* [n];   // Финальная матрица, которая будет магическим квадратом чётно - нечётного порядка
        for (int i = 0; i < n; i++)
        {
            matrixFF[i] = new int[n];
        }
        for (int i = 0; i < n; i++) // Заполняем левую верхнюю часть матрицы. Индексы для этого случая совпадают.
        {
            for (int j = 0; j < n; j++)
            {
                matrixFF[i][j] = matrixF[i][j];
            }
        }
        matrixFF[0][0] = matrixF[k][0];
        matrixFF[k - 1][0] = matrixF[n - 1][0];
        matrixFF[k][0] = matrixF[0][0];
        matrixFF[n - 1][0] = matrixF[k - 1][0];

        for (int i = 1, j = k + 1; i < k - 1; i++, j++)   // этот алгоритм и алгоритм выше копируют с перемещением левую дугу. Остаётся только разобраться с центром.
        {
            matrixFF[i][1] = matrixF[j][1];
            matrixFF[j][1] = matrixF[i][1];
        }

        for (int g = (k - 3) / 2, p = k; g > 0; g--, p++)   //  p отвечает за кол-во столбиков к замене справа. Сколько отработает для левой части, столько и для правой.
        for (int i = 0, f = k; i < k; i++, f++)     // Условие f < n и не трубуется, т.к. квадраты с одинаковым кол-во элементов
        {
            matrixFF[i][k - g] = matrixF[f][k - g];
            matrixFF[f][k - g] = matrixF[i][k - g];
            matrixFF[i][p] = matrixF[f][p];
            matrixFF[f][p] = matrixF[i][p];
        }

        
        cout << "Our magic square of order " << n << " :" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << endl;
            for (int j = 0; j < n; j++)
            {
                cout << matrixFF[i][j] << "\t";
            }
        }
        for (int i = 0; i < k; i++)
    {
        delete[] matrix2[i];
    }
        delete[] matrix2;
        for (int i = 0; i < n; i++)
    {
        delete[] matrixF[i];
    }
        delete[] matrixF;
        for (int i = 0; i < n; i++)
    {
        delete[] matrixFF[i];
    }
        delete[] matrixFF;
    }
    else if (n % 2 == 0)
    {
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }


    int count = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (i % 4 == 0 || i % 4 == 3)   // Строки, в которых первый элемент - это пропуск.
            {
                if (j % 4 != 0 && j % 4 != 3)   // В строках, где первый элемент пропуск - нужно заполнять только ячейка, остаток от деления номера столбика которых не равен 0 и 3
                {
                    matrix[i][j] = count;
                }
                
            }
            else
            {
                if (j % 4 == 0 || j % 4 == 3)   // В строках, где первый элемент не пропуск - нужно заполнять только ячейки, остаток от деления номера столбца которых равен 0 или 3.
                {
                    matrix[i][j] = count;
                }
            }
            count++;
        }
    }

    int count1 = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = n - 1; j >= 0; j--)
        {

            if (i % 4 == 0 || i % 4 == 3)   // Строки, в которых первый элемент - это не пропуск.
            {
                if (j % 4 == 0 || j % 4 == 3)   // В строках, где первый элемент не пропуск - нужно заполнять только ячейки, остаток от деления номера столбика которых равен 0 или 3
                {
                    matrix[i][j] = count1;
                }

            }
            else
            {
                if (j % 4 != 0 && j % 4 != 3)   // В строках, где первый элемент пропуск - нужно заполнять только ячейки, остаток от деления номера столбца которых не равен 0 и 3.
                {
                    matrix[i][j] = count1;
                }
            }
            count1++;
        }
    }

    cout << "Our magic square of order " << n << " :" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "\t";
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    }


}
