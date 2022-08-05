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
    const int N = 3, M = 5;
    int arr[N][M] = {};
    int n;
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
            arr[i][j] = n;
        }
    }

    int count = 0;
    int k = 0;
    if (N - M >= 0)
    {
        for (int i = N - 1; i > (N - M); i--)
        {
            for (int j = M - 1; j > k; j--)
            {
                if (arr[i][j] > 0)
                {
                    count++;
                }
            }
            k++;
        }
    }
    else 
    {
        for (int i = N - 1; i > 0; i--)
        {
            for (int j = N - 1; j > k; j--)
            {
                if (arr[i][j] > 0)
                {
                    count++;
                }
            }
            k++;
        }
    }

    cout << "We need to count the number of positive numbers under the side diagonal." << endl;
    cout << "There are " << count << " positive elements under the side diagonal." << endl;
}
