#include <iostream> 
using namespace std;

int checkSymbolsPositive(int& n, char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод.
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
    n = f;
    if (n == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
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
    cout << "Enter size of array(k)(from 3): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int values.";
        return 0;
    }
    k = n;
    if (k < 3)
    {
        cout << "You need to enter array with size 3 or more. k<3 is useless" << endl;
        return 0;
    }

    int* arr = new int[k];
    cout << "This program replaces all elements that are in cells with zeros between the minimum and maximum elements(not including them)." << endl;
    cout << "If after this action most of the array contains zeros, then remove all zero elements from the array (with saving the order of the rest elements)." << endl;
    cout << "----------------------------------------------------------------------" << endl;
    cout << "Lets fill this array with int numbers. You needn't to enter duplicates" << endl;
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

    for (int i = 0; i < k; i++) // Проверка на дубликаты
    { 
        for (int h = i + 1; h < k; h++)
            if (arr[i] == arr[h])
            {
                cout << "You entered duplicates. Error" << endl;
                return 0;
            }
    }

    int min = arr[0];
    int max = arr[k - 1];
    int maxInd, minInd;
    for (int i = 0; i < k; i++)
    {
        if (arr[i] <= min)
        {
            min = arr[i];
            minInd = i;
        }
    }
    for (int i = k - 1; i >= 0; i--)
    {
        if (arr[i] >= max)
        {
            max = arr[i];
            maxInd = i;
        }
    }
    cout << "max: " << max << " min: " << min << endl;

    int z = abs(maxInd - minInd) - 1;   // Кол-во нулей между max и min
    int f = 0;   // Счётчик первоначальных нулей. Первоначально может быть только один 0!!!!
    for (int i = 0; i < k; i++) // Ищем нули, которые были сразу
    {
        if (minInd < maxInd)    // нули между min и max не играют роли. Если 0 заменятся на 0 ничего плохого не произойдёт.
        {
            if (arr[i] == 0 && (i <= minInd || i >= maxInd)) f++;
        }
        else
        {
            if (arr[i] == 0 && (i <= maxInd || i >= minInd)) f++;
        }

    }

    if (z == 0)    // Сразу мог быть только один 0(f=1 или f=0). Если нет места между min и max, т.е. z == 0, то массив остаётся неизменным.
    {
        for (int i = 0; i < k; i++)
        {
            cout << arr[i] << "\t";
        }
    }
    else if (f > 0 && z > 0)
    {
        if (min == 0 || max == 0)   // Обязательно нужно рассматривать этот вариант. Т.к. нулей вместе с z + 1 может быть достаточно, для того, чтобы создавать новый массив без 0.
        {                           // Этим единственным первоначальным нулём(не между min и max) может оказаться сам min или max.        
            if (z + 1 > k / 2)  
            {
                if (min == 0 && minInd < maxInd)
                {
                    int* arr2 = new int[k - z - 1];
                    for (int i = 0; i < minInd; i++)    // Копируем все элементы массива до min, не включая его, т.к. в этой ветке min = 0
                    {
                        arr2[i] = arr[i];
                    }
                    for (int i = 0; maxInd + i < k; i++)    // Нужно покопировать элементы начиная от ненулевого max, до конца массива
                    {
                        arr2[minInd + i] = arr[maxInd + i];   // Копируем все оставшиеся элементы до конца. От max, включительно
                    }
                    for (int i = 0; i < k - z - 1; i++)
                    {
                        cout << arr2[i] << "\t";
                    }
                    delete[] arr2;
                }
                else if (max == 0 && maxInd > minInd)
                {
                    int* arr2 = new int[k - z - 1];
                    for (int i = 0; i <= minInd; i++)
                    {
                        arr2[i] = arr[i];   // Нужно скопировать все элементы, до минимального, неравного нулю, включительно.
                    }
                    for (int i = 1; maxInd + i < k; i++)    // Нужно покопировать элементы начиная, со следующего за нулвым min и до конца массива
                    {
                        arr2[minInd + i] = arr[maxInd + i];   // Копируем все оставшиеся элементы до конца. От max, включительно
                    }
                    for (int i = 0; i < k - z - 1; i++)
                    {
                        cout << arr2[i] << "\t";
                    }
                    delete[] arr2;
                }
                else if (min == 0 && minInd > maxInd)
                {
                    int* arr2 = new int[k - z - 1];
                    for (int i = 0; i <= maxInd; i++)
                    {
                        arr2[i] = arr[i]; // Скопировали до max не равного 0, включительно.
                    }
                    for (int i = 1; minInd + i < k; i++)    // Нужно покопировать элементы начиная, со следующего за нулвым min и до конца массива
                    {
                        arr2[maxInd + i] = arr[minInd + i];   // Копируем все оставшиеся элементы до конца. От max, включительно
                    }
                    for (int i = 0; i < k - z - 1; i++)
                    {
                        cout << arr2[i] << "\t";
                    }
                    delete[] arr2;
                }
                else if (max == 0 && maxInd < minInd)
                {
                    int* arr2 = new int[k - z - 1];
                    for (int i = 0; i < maxInd; i++)    // Нужно скопировать все элементы до максимального, не включительно, т.к. max = 0 и он будет выпадать дальше
                    {
                        arr2[i] = arr[i];
                    }
                    for (int i = 0; minInd + i < k; i++)
                    {
                        arr2[maxInd + i] = arr[minInd + i];

                    }
                    for (int i = 0; i < k - z - 1; i++)
                    {
                        cout << arr2[i] << "\t";
                    }
                    delete[] arr2;
                }
            }   
            else   // иначе, если даже с первоначальным нулём и с заменой элементов между min и max на нули, нулей будет недостаточно, то просто вывод с заменой на нули между min и max
            {
                if (minInd < maxInd)
                {
                    for (; minInd + 1 < maxInd; minInd++)
                    {
                        arr[minInd + 1] = 0;
                    }
                }
                else
                {
                    for (; maxInd + 1 < minInd; maxInd++)
                    {
                        arr[maxInd + 1] = 0;
                    }
                }
                for (int i = 0; i < k; i++)
                {
                    cout << arr[i] << "\t";
                }
            }
        }
        else if (z + f > k / 2) // Случай, если единственный первоначальный 0 был не min и не max, а значит его надо найти. Причём с этим нулём кол-во нулей будет большей частью
        {
            int* arr2 = new int[k - z];     // В такой ситуации есть смысл создать промежуточный массив. В нём просто выпадают числа между min и max
            if (minInd < maxInd)
            {
                for (int i = 0; i <= minInd; i++)
                {
                    arr2[i] = arr[i];   // Копируем нормальную часть, до минимального, включительно.
                }
                for (int i = 0, j = 1; maxInd + i < k; i++, j++)
                {
                    arr2[minInd + j] = arr[maxInd + i];
                }
            }
            else
            {   
                for (int i = 0; i <= maxInd; i++)
                {
                    arr2[i] = arr[i];   // Копируем нормальную часть, до максимального, включительно.
                }
                for (int i = 0, j = 1; minInd + i < k; i++, j++)
                {
                    arr2[maxInd + j] = arr[minInd + i];
                }
            }

            //for (int i = 0; i < k - z; i++) // Вывод промежуточно для ТЕСТА
            //{
            //    cout << arr2[i] << "\t";
            //}

            int* arr3 = new int[k - z - 1];     // Окончательный массив. Остаётся найти 0 и сдвинуть все элементы. 0 по-любому есть, исходя из условий выше.
            for (int i = 0; i < k - z; i++)     // Цикл поиска и заполнения окончательного массива без 0.
            {
                if (arr2[i] == 0)
                {
                    if(i != 0)  // Если 0 не в начале и не в конце промежуточного массива
                    { 
                        for (int j = 0; j < i; j++)
                        {
                            arr3[j] = arr2[j];
                        }
                        for (; i + 1 < k - z; i++)
                        {
                            arr3[i] = arr2[i + 1];
                        }                    
                        break;
                    }
                    else if (i == k - z - 1) // Если 0 это последний член
                    {
                        for (int j = 0; j < i; j++)
                        {
                            arr3[j] = arr2[j];
                        }
                        break;
                    }
                    else // Осталась ситуация, если 0 в промежуточном массиве первый (т.е. 0-й)
                    {
                        for (; i + 1 < k - z; i++)
                        {
                            arr3[i] = arr2[i + 1];
                        }
                        break;
                    }
                }
            }

            delete[] arr2;
            cout << "\n";
            for (int i = 0; i < k - z - 1; i++)
            {
                cout << arr3[i] << "\t";
            }
            delete[] arr3;
        }
        else  // Если нулей вместе с первоначальным не большая часть, то просто заменяем элементы между min и max на 0. Удалять 0 не нужно и трогать отдельный 0 не нужно, поэтому старый массив.
        {
            if (minInd < maxInd)
            {
                for (; minInd + 1 < maxInd; minInd++)
                {
                    arr[minInd + 1] = 0;
                }
            }
            else
            {
                for (; maxInd + 1 < minInd; maxInd++)
                {
                arr[maxInd + 1] = 0;
                }
            }
                for (int i = 0; i < k; i++)
                {
                cout << arr[i] << "\t";
                }
            }
    }
    else if (f == 0 && z > 0)
    {
        if (z > k / 2)  // Если между min и max нулей вмещается большая часть от всех элементов массива
        {
            //нужно создать новый и сдвинуть 
            int* arr2 = new int[k-z];

            if (minInd < maxInd)
            {
                for (int i = 0; i <= minInd; i++)
                {
                    arr2[i] = arr[i];   // Копируем нормальную часть, до минимального, включительно.
                }
                for (int i = 0, j = 1; maxInd + i < k; i++, j++)  // Переносим все оставшиеся элементы позиции, начиная от следующей за minInd + 1 и пока они не закончатся
                {
                    arr2[minInd + j] = arr[maxInd + i];
                }
                for (int i = 0; i < k - z; i++)
                {
                    cout << arr2[i] << "\t";
                }
                delete[] arr2;
            }
            else
            {
                for (int i = 0; i <= maxInd; i++)
                {
                    arr2[i] = arr[i];   // Копируем нормальную часть, до максимального, включительно.
                }
                for (int i = 0, j = 1; minInd + i < k; i++, j++)
                {
                    arr2[maxInd + j] = arr[minInd + i];
                }
                for (int i = 0; i < k - z; i++)
                {
                    cout << arr2[i] << "\t";
                }
                delete[] arr2;
            }

        }
        else // иначе нулей не большая часть, а значит массив может остаться неизменным, НО нужно заменить числа между min и max на нули в СТАРОМ массиве. Причём какие-то нули МЕЖДУ min и max не важны.
        {
            if (minInd < maxInd)
            {
                for (; minInd + 1 < maxInd; minInd++)
                {
                    arr[minInd + 1] = 0;
                }
            }
            else
            {
                for (; maxInd + 1 < minInd; maxInd++)
                {
                    arr[maxInd + 1] = 0;
                }
            }
            for (int i = 0; i < k; i++)
            {
                cout << arr[i] << "\t";
            }
        }          
    }

    delete[] arr;
}
