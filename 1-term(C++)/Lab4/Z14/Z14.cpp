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
    cout << "Enter the size of the field(NxM)(NxM must include >=4 elements). Enter N: ";
    cin >> st1;
    if (checkSymbolsPositive(n, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    N = n;
    char* st2 = new char[1000000];   // массив, созданный только для проверки.
    cout << "Enter the size of the field(NxM). Enter M: ";
    cin >> st2;
    if (checkSymbolsPositive(n, st2) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    M = n;
    cout << "We have field " << N << "x" << M << endl;
    if (N < 4 && M < 4)
    {
        cout << "Field fewer, than 4 elements is useless" << endl;
        return 0;
    }

    char** field = new char* [N];
    for (int i = 0; i < N; i++)
    {
        field[i] = new char[M];
    }

    cout << "Lets fill this field with '*' or '.' ." << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char* element = new char[100];
            cout << "[" << i << "]" << "[" << j << "]: ";
            cin >> element;           
            if ((element[0] != '*' && element[0] != '.') || strlen(element) > 1)
            {
                cout << "You have entered smth incorrect.";
                return 0;
            }
            field[i][j] = element[0];
            delete[] element;
        }
    }
    bool check1 = false;
    bool check2 = false;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (field[i][j] == '*') check1 = true;
            if (field[i][j] == '.') check2 = true;
        }
    }
    if (!check1) 
    {
        cout << "You haven't entered *" << endl;
        return 0;
    }
    if (!check2)
    {
        cout << "You haven't entered ." << endl;
        return 0;
    }
    // Выше заполнение и проверка, ввёл ли пользователь хотя бы 1 * и . и ввёл ли пользователь корректный символ (* или .)
    cout << "This program complements the field with numbers, just like in the original game." << endl;
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < M; j++)
        {
            cout << field[i][j] << "\t";
        }
    }
    cout << "\n--------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) // Цикл, который подсчитывает, сколько мин вокруг текущей ячейки и потом присваивает значение счётчика данной ячейке. Если в текущей ячейке мина(*), то переходим на след ячейку, т.к. мину менять на значение не нужно.
    { 
        for (int j = 0; j < M; j++)
        {
            int count = 48;
            if (i == 0 && j == 0)
            {
                if (field[i][j] == '*') continue;
                if (field[i + 1][j] == '*') count++;    // вниз
                if (field[i][j + 1] == '*') count++;    // вправо
                if (field[i + 1][j + 1] == '*') count++;    // вниз и вправо, по диагонали
            }
            else
            if (i == N - 1 && j == M - 1)
            {
                if (field[i][j] == '*') continue;
                if (field[i - 1][j] == '*') count++;   // вверх
                if (field[i][j - 1] == '*') count++;    // влево
                if (field[i - 1][j - 1] == '*') count++;    // вверх и влево, по диагонали
            }
            else
            if (i == N - 1 && j == 0)
            {
                if (field[i][j] == '*') continue;
                if (field[i][j + 1] == '*') count++;    // вправо
                if (field[i - 1][j] == '*') count++;   // вверх
                if (field[i - 1][j + 1] == '*') count++;    // вверх и вправо, по диагонали
            }
            else
            if (i == 0 && j == M - 1)
            {
                if (field[i][j] == '*') continue;
                if (field[i + 1][j] == '*') count++;    // вниз
                if (field[i][j - 1] == '*') count++;    // влево
                if (field[i + 1][j - 1] == '*') count++;    // вниз и влево, по диагонали
            }
            else if (i == 0) //  && j != 0 && j != M - 1
            {
                if (field[i][j] == '*') continue;
                if (field[i + 1][j] == '*') count++;    // вниз
                if (field[i][j + 1] == '*') count++;    // вправо
                if (field[i + 1][j + 1] == '*') count++;    // вниз и вправо, по диагонали
                if (field[i][j - 1] == '*') count++;    // влево
                if (field[i + 1][j - 1] == '*') count++;    // вниз и влево, по диагонали
            }
            else if (j == 0)    //  && i != 0 && i != N - 1
            {
                if (field[i][j] == '*') continue;
                if (field[i - 1][j] == '*') count++;   // вверх
                if (field[i][j + 1] == '*') count++;    // вправо
                if (field[i + 1][j] == '*') count++;    // вниз
                if (field[i + 1][j + 1] == '*') count++;    // вниз и вправо, по диагонали
                if (field[i - 1][j + 1] == '*') count++;    // вверх и вправо, по диагонали
            }
            else if (i == N - 1)    //  && j !=0 && j != M - 1
            {
                if (field[i][j] == '*') continue;
                if (field[i - 1][j] == '*') count++;   // вверх
                if (field[i][j + 1] == '*') count++;    // вправо
                if (field[i][j - 1] == '*') count++;    // влево
                if (field[i - 1][j - 1] == '*') count++;    // вверх и влево, по диагонали
                if (field[i - 1][j + 1] == '*') count++;    // вверх и вправо, по диагонали
            }
            else if (j == M - 1)    //  && i != 0 && i != N - 1
            {
                if (field[i][j] == '*') continue;
                if (field[i + 1][j] == '*') count++;    // вниз
                if (field[i - 1][j] == '*') count++;   // вверх
                if (field[i][j - 1] == '*') count++;    // влево
                if (field[i + 1][j - 1] == '*') count++;    // вниз и влево, по диагонали
                if (field[i - 1][j - 1] == '*') count++;    // вверх и влево, по диагонали
            }
            else
            {
                if (field[i][j] == '*') continue;
                if (field[i + 1][j] == '*') count++;    // вниз
                if (field[i][j + 1] == '*') count++;    // вправо
                if (field[i + 1][j + 1] == '*') count++;    // вниз и вправо, по диагонали
                if (field[i - 1][j] == '*') count++;   // вверх
                if (field[i][j - 1] == '*') count++;    // влево
                if (field[i - 1][j - 1] == '*') count++;    // вверх и влево, по диагонали
                if (field[i - 1][j + 1] == '*') count++;    // вверх и вправо, по диагонали
                if (field[i + 1][j - 1] == '*') count++;    // вниз и влево, по диагонали
            }

            char a;
            if (count == 48)
            {
                a = 46;
            }
            else
            {
                a = count;
            }
            field[i][j] = a; 
        }
    }
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < M; j++)
        {
            cout << field[i][j] << "\t";
        }
    }
}
