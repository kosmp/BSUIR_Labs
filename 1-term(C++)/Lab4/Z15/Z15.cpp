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
    cout << "Enter number you want to find in this matrix, given by a special algorithm: ";
    int n;
    char* st1 = new char[1000000];   // массив, созданный только для проверки. 
    cin >> st1;
    if (checkSymbolsPositive(n, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    int sizeM = sqrt(n) + 1;
    int** matrix = new int* [sizeM];
    for (int i = 0; i < sizeM; i++)
    {
        matrix[i] = new int[sizeM];
    }
    for (int i = 0; i < sizeM; i++)
    {
        for (int j = 0; j < sizeM; j++)
        {
            matrix[i][j] = 0;
        }
    }

    matrix[0][0] = 1;
    int count = 2;  // Счётчик с помощью которого расставляются цифры в нужном порядке, с каждым новым присваиваним след. число.
    bool check = false;
    int j = 1;  // Начальное значение рядка
    int i = 0;  // Начальное значение строки
    int g; // для сохранения и хранения значения, с которого столбика нужно продолжать двигаться, после того, как дошли справа налево до 0.
    while (j < sizeM)
    {
        if (matrix[i][j - 1] != 0)
        {
            matrix[i][j] = count;
            count++;
            i++;
            if (matrix[i][j - 1] == 0)  // проверили, есть ли сосед слева у следующей ячейки в этом столбике.
            {
                check = true;   // Как только выяснили, что соседа(слева) у следующего внизу не будет, то активируем обратный ход(справа налево)
                g = j + 1;  // Так как активировали обратный ход и идём справа налево, то нужно сохранить значение столбика, чтобы после завершения обратного хода продолжить со следующего выполнять тот же алгоритм.
            }
        }
        while (check)   // Цикл для обратного хода(справа налево). Заканчивается, когда доходит до 0, включительно. После этого перескакиваем на сохранённый столбик и 0 строку.
        {
            matrix[i][j] = count;
            count++;
            j--;
            if (j == -1)    // как только дошли обратный ходом до конца нужно его отключить и повторить весь алгоритм заново, 
            {               // пока не дойдём до последнего столбика. После выполнения обратного хода всегда нужно вернуться на 0 строку и сохранённый столбец
                check = false;  // отключаем обратный ход
                j = g;  // Так мы вернёмся на следующий столбик
                i = 0; // Так мы возвращаемся на нулевую строку
            }
        }
    }

    cout << endl;
    for (int p = 0; p < sizeM; p++)
    {
        for (int k = 0; k < sizeM; k++)
        {
            if (matrix[p][k] == n)
            {
                cout << "Your value: " << n << " is in " << p << " row and " << k << " column" << endl;
            }
        }
    }
        
    for (int p = 0; p < sizeM; p++)
        {
            cout << endl;
            for (int u = 0; u < sizeM; u++)
            {
                cout << matrix[p][u] << "\t";
            }
        }
    for (int p = 0; p < sizeM; p++)
        {
            delete[] matrix[p];
        }
    delete[] matrix;
}
