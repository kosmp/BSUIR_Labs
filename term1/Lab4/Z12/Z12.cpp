#include <iostream>
using namespace std;

int* removeDuplicates(int &k, int* arr)
{   
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            if (arr[i] == arr[j])
            {
                for (int p = i; p + 1 < k; p++) // Как только нашли одинаковый элемент, то переписываем массив, удаляя дублирующий элемент, который левее. 1 из дублирующих остаётся.
                {
                    arr[p] = arr[p + 1];    // Нашли и, соответственно, сдвинули массив на 1 элемент.
                }
                k--;    // С каждым новым проходом, поиском дубликата нужно проходиться на 1 элемент меньше, т.к. каждый раз выкидываем самый левый дубликат
                if (arr[i] == arr[j]) // Если следующий за этим элементов после сдвига равен этому, то нужно ещё раз прокрутить цикл выше, для этого уменьшим счётчик на 1. Он все равно увеличивается на 1 и получается j ( j - 1 + 1)
                {       
                    j--;    // Чтобы посмотреть элемент, следующий за данным, после сдвига. Чтобы не проскакивать элемент.
                }
            }
        }
    }
        int* arrNew = new int[k];
        for (int i = 0; i < k; i++)
        {
            arrNew[i] = arr[i];
        }
        cout << endl;
        delete[] arr;
    return arrNew;
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
    int k, n;
    char* st = new char[1000000];   // массив, созданный только для проверки. 
    cout << "This program removes duplicates of elements and creates new array with new size with these duplicates" << endl;
    cout << "Enter size of array(k)(can't be = 1): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int values.";
        return 0;
    }
    k = n;
    if (k == 1)
    {
        cout << "You entered 1" << endl;
        return 0;
    }

    int* arr = new int[k];

    cout << "Lets fill this array with int numbers." << endl;
    for (int i = 0; i < k; i++)
    {
        char* st = new char[1000000];   // массив, созданный только для проверки. 
        cin >> st;
        if (checkSymbols(n, st) != 0)
        {
            cout << "You needn't to enter symbols. Only int values.";
            return 0;
        }
        arr[i] = n;
    }
    
    int* arr1 = removeDuplicates(k, arr);
    cout << "New size of new array= " << k << endl;
    for (int i = 0; i < k; i++)
    {
        cout << arr1[i] << "\t";
    }
    delete[] arr1;
}
