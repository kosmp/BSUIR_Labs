// sum and dif of duodecimal numbers. 1-st variant
#include <iostream>
using namespace std;

int convertToInt(char f, char s)    // для суммы, переводит число char или A, B в int.
{
    int fNum, sNum;
    if (f == 'A')
    {
        fNum = 10;
    }
    else if (f == 'B')
    {
        fNum = 11;
    }
    else
    {
        fNum = f - '0';
    }

    if (s == 'A')
    {
        sNum = 10;
    }
    else if (s == 'B')
    {
        sNum = 11;
    }
    else
    {
        sNum = s - '0';
    }
    // A эквивалентно 10, B эквивалентно 11
    return fNum + sNum;
}

int convertToIntDif(char f, char s)     // для вычитания
{
    int fNum, sNum;
    if (f == 'A')
    {
        fNum = 10;
    }
    else if (f == 'B')
    {
        fNum = 11;
    }
    else
    {
        fNum = f - '0';
    }

    if (s == 'A')
    {
        sNum = 10;
    }
    else if (s == 'B')
    {
        sNum = 11;
    }
    else
    {
        sNum = s - '0';
    }
    // A эквивалентно 10, B эквивалентно 11
    return fNum - sNum;
}

void sum(char* first, char* second)
{
    if (strlen(first) < strlen(second))
    {
        // тогда нужно поменять местами, чтобы было удобнее складывать. Складывать по видоизменённому алгоритму.
        char* save = new char[strlen(first) + 1];   // сохраним в строку save строку first.
        for (int i = 0; i <= strlen(first); i++)
        {
            save[i] = first[i];
        }
        for (int i = 0; i <= strlen(second); i++)
        {
            first[i] = second[i];
        }
        for (int i = 0; i <= strlen(first); i++)
        {
            second[i] = save[i];
        }
        delete[] save;
    }

    if (strlen(first) > strlen(second))        // Алгоритм основывается на таблице для сложения чисел в двенадцатеричной системе.
    {
        // тогда видоизменённый алгоритм сложение. Индексы будут сдвинуты
        char* result = new char[strlen(first) + 2];     // строка для результата. Если потом вылезет одна цифра, то сдвинем массив.
        result[strlen(first)] = '\0';
        bool saveOne = false;
        bool checkCrit = true;  // если сумма без добавления 1, которую запоминали, строго больше 11, то она уменьшится на 2 и перевода в буквы 10 и 11 не будет, будет просто 0 или 1 и 1 запоминаться
        for (int i = strlen(first) - 1, k = strlen(second) - 1; i >= 0; i--, k--)
        {
            int sum;
            if (k >= 0)
            {
                sum = convertToInt(first[i], second[k]);
            }
            else
            {
                // иначе не нужно брать элементы из second, а это делается в функции convertToInt
                if (first[i] == 'A')
                {
                    sum = 10;
                }
                else if (first[i] == 'B')
                {
                    sum = 11;
                }
                else
                {
                    sum = first[i] - '0';
                }
            }

            if (saveOne)
            {
                sum += 1;
                saveOne = false;    // сохранённая 1 может использовать только в след разряде. Использовали её и продолжаем алгоритм
            }

            if (sum > 11)   // если переходим эту границу, то число будет на 2 меньше, 10 != A и 11 != B.
            {
                sum -= 2;
                checkCrit = false;
            }

            if (sum == 10 && checkCrit)
            {
                result[i] = 'A';
            }
            else if (sum == 11 && checkCrit)
            {
                result[i] = 'B';
            }
            else
            {
                if (sum >= 0 && sum <= 9)    // тогда в следующий разряд не переходит 1
                {
                    result[i] = sum + '0';
                }
                else // тогда в следующий разряд переходит 1, т.к. это sum и не A, и не B и не от 0 до 9
                {
                    if (sum == 20)  // 20 = 1A
                    {
                        result[i] = 'A';
                        saveOne = true;
                    }
                    else if (sum == 21)  // 20 = 1B
                    {
                        result[i] = 'B';
                        saveOne = true;
                    }
                    else
                    {
                        result[i] = (sum - 10) + '0';
                        saveOne = true;     // тогда 1 будет участвовать в след разряде
                    }
                }
            }

            if (i == 0 && saveOne)     // если вылазит сохранённая 1, значит надо поставить её в 0 элемент, а всё остальное сдвинуть вправо на 1
            {
                for (int j = strlen(first); j > 0; j--)
                {
                    result[j] = result[j - 1];
                }
                if (saveOne)
                {
                    result[0] = '1';
                }
                result[strlen(first) + 1] = '\0';
            }
            checkCrit = true;
        }
        cout << "Result sum: " << result << endl;
        delete[] result;
    }
    else if (strlen(first) == strlen(second))   // Алгоритм основывается на таблице для сложения чисел в двенадцатеричной системе.
    {
        // тогда просто алгоритм сложения
        char* result = new char[strlen(first) + 2];     // строка для результата. Если потом вылезет одна цифра, то сдвинем массив.
        result[strlen(first)] = '\0';
        bool saveOne = false;
        bool checkCrit = true;  // если сумма без добавления 1, которую запоминали, строго больше 11, то она уменьшится на 2 и перевода в буквы 10 и 11 не будет, будет просто 0 или 1 и 1 запоминаться
        for (int i = strlen(first) - 1; i >= 0; i--)
        {
            int sum = convertToInt(first[i], second[i]);
            if (saveOne)
            {
                sum += 1;
                saveOne = false;    // сохранённая 1 может использовать только в след разряде. Использовали её и продолжаем алгоритм
            }

            if (sum > 11)   // если переходим эту границу, то число будет на 2 меньше, 10 != A и 11 != B.
            {
                sum -= 2;
                checkCrit = false;
            }

            if (sum == 10 && checkCrit)
            {
                result[i] = 'A';
            }
            else if (sum == 11 && checkCrit)
            {
                result[i] = 'B';
            }
            else
            {
                if (sum >= 0 && sum <= 9)    // тогда в следующий разряд не переходит 1
                {
                    result[i] = sum + '0';
                }
                else // тогда в следующий разряд переходит 1, т.к. это sum и не A, и не B и не от 0 до 9
                {
                    if (sum == 20)  // 20 = 1A
                    {
                        result[i] = 'A';
                        saveOne = true;
                    }
                    else if (sum == 21)  // 20 = 1B
                    {
                        result[i] = 'B';
                        saveOne = true;
                    }
                    else
                    {
                        result[i] = (sum - 10) + '0';
                        saveOne = true;     // тогда 1 будет участвовать в след разряде
                    }
                }
            }

            if (i == 0 && saveOne)     // если вылазит сохранённая 1, значит надо поставить её в 0 элемент, а всё остальное сдвинуть вправо на 1
            {
                for (int j = strlen(first); j > 0; j--)
                {
                    result[j] = result[j - 1];
                }
                if (saveOne)
                {
                    result[0] = '1';
                }
                result[strlen(first) + 1] = '\0';
            }
            checkCrit = true;
        }
        cout << "Result sum: " << result << endl;
        delete[] result;
    }
}

void substraction(char* first, char* second) 
{
    if (strlen(first) < strlen(second))
    {
        // тогда нужно поменять местами, чтобы можно было вычитать.
        char* save = new char[strlen(first) + 1];   // сохраним в строку save строку first.
        for (int i = 0; i <= strlen(first); i++)
        {
            save[i] = first[i];
        }
        for (int i = 0; i <= strlen(second); i++)
        {
            first[i] = second[i];
        }
        for (int i = 0; i <= strlen(first); i++)
        {
            second[i] = save[i];
        }
        delete[] save;
    }

    if (strlen(first) > strlen(second))    // ситуация, когда запись одного числа длинее, чем запись другого. Тогда для удобства лучше доставить в начало second нули, чтобы сделать такой же размер.
    {
        // дополняем строчку
        int difference = strlen(first) - strlen(second);    // столько нулей нужно доставить в начало second, чтобы число не изменилось
        for (int i = strlen(second); i >= 0; i--)
        {
            second[i + difference] = second[i];
        }
        second[strlen(first)] = '\0';
        for (int i = 0, j = difference; i < j; i++)
        {
            second[i] = '0';
        }
    }

    if (strlen(first) == strlen(second))
    {
        char* save = new char[strlen(first) + 1];   // сохраним в строку save строку first.
        for (int i = 0; i <= strlen(first); i++)
        {
            save[i] = first[i];
        }
        char* result = new char[strlen(first) + 2];
        result[strlen(first)] = '\0';
        for (int i = strlen(first) - 1; i >= 0; i--)
        {
            // нужно вычесть из каждого элемента first элемент из second
            // но если нельзя вычесть, то нужно пробывать занимать у следующего разряда единичку (в текущем разряде как 12)
            bool minus = false; // для отслеживания ситуации, когда сразу +11
            if (first[i] == '-')
            {
                first[i] = '0';
                minus = true;   // важно, что обработка 0 была такой же, как и всегда, но тут изначально будет +11 и не надо искать заём. На основе обычного вычитания столбиком.
            }
            int dif = convertToIntDif(first[i], second[i]);
            if (minus)
            {
                dif += 11;
            }
            
            if (i == 0 && dif < 0)      // если сейчас на текущем элементе с индексом i не у чего занять, то тогда нужно поменять местами first и second и повторить всё сначало. Но поменять местами первоначальные строки.
            {
                for (int i = 0; i <= strlen(second); i++)
                {
                    first[i] = second[i];
                }
                for (int i = 0; i <= strlen(first); i++)
                {
                    second[i] = save[i];
                }
                delete[] save;
                i = strlen(first);  // тогда нужно заново пройтесь циклом. Возвращаемся на стартовую позицию + 1, т.к. все равно вычтется 1.
                continue;
            }

            if (dif < 0)
            {
                // тогда нужно попробывать занять 1 у какого-то следующего разряда. Сразу по месту учитывается этот заём.
                bool find = false;
                int j = i - 1;  // индекс элемент, у которого заём
                for (; j >= 0; j--)    // ищем начиная со следующего
                {
                    if (first[j] != '0')
                    {
                        find = true;    // нашли
                        // Сразу по месту уменьшаем значение. Если это буква B, то станет A, а если это A, то станет 9.
                        if (first[j] != 'A' && first[j] != 'B')
                        {
                            first[j] = first[j] - 1;    // если цифра (может быть только от 1 до 9), то просто уменьшаем на 1
                        }
                        else if (first[j] == 'B')
                        {
                            first[j] = 'A';
                        }
                        else
                        {
                            first[j] = '9';
                        }
                        break;
                    }
                }

                if (find)
                {
                    //  Нужно также пройтись до элемента, у которого заём, в поисках нулей. Пройтесь только если find = true
                    for (int t = i - 1; t > j; t--)
                    {
                        if (first[t] == '0')
                        {
                            first[t] = '-';     // Потом, если обнаружили '-', то от разности вычесть ещё 1. dif - 1
                        }
                    }
                    dif += 12;
                    // тогда записываем разность в соответствующий элемент. Число, большее, чем 11 не получится.
                    if (dif == 10)
                    {
                        result[i] = 'A';
                    }
                    else if (dif == 11)
                    {
                        result[i] = 'B';
                    }
                    else
                    {
                        result[i] = dif + '0';
                    }
                }
                else
                {
                    // иначе поменять местами и заново пройтись внешнем циклом, т.к. из first нельзя вычесть second, то из second можно вычесть first.
                    char* save = new char[strlen(first) + 1];   // сохраним в строку save строку first.
                    for (int i = 0; i <= strlen(first); i++)
                    {
                        save[i] = first[i];
                    }
                    for (int i = 0; i <= strlen(second); i++)
                    {
                        first[i] = second[i];
                    }
                    for (int i = 0; i <= strlen(first); i++)
                    {
                        second[i] = save[i];
                    }
                    delete[] save;
                    i = strlen(first);  // тогда нужно заново пройтесь циклом. Возвращаемся на стартовую позицию. Не -1, т.к. i-- в цикле
                    continue;
                }
            }
            else
            {
                // тогда прости вычитаем и записываем соответствующую цифру в результат. Если 10, то A. Если 11, то B.
                if (dif >= 0 && dif <= 9)
                {
                    result[i] = dif + '0';
                }
                else if (dif == 10 || dif == 11)
                {
                    if (dif == 10)
                    {
                        result[i] = 'A';
                    }
                    else if (dif == 11)
                    {
                        result[i] = 'B';
                    }
                }
                else
                {
                    result[i] = (dif - 10) + '0';
                }
            }
        }
        cout << "Difference: " << result << endl;
        delete[] result;
    }
}

int main()
{
    cout << "This program calculates the sum and difference of the numbers in duodecimal system." << endl;
    char* first = new char[100];
    char* second = new char[100];
    cout << "Enter the code of the first number in the duodecimal system: " << endl;
    cin.getline(first, 100);
    for (int i = 0; i < strlen(first); i++)     // check enter
    {
        if (!(('0' <= first[i] && first[i] <= '9') || first[i] == 'A' || first[i] == 'B'))
        {
            cout << "Incorrect enter. Error." << endl;
            return 0;
        }
    }
    cout << "Enter the code of the second number in the duodecimal system: " << endl;
    cin.getline(second, 100);
    for (int i = 0; i < strlen(second); i++)     // check enter
    {
        if (!(('0' <= second[i] && second[i] <= '9') || second[i] == 'A' || second[i] == 'B'))
        {
            cout << "Incorrect enter. Error." << endl;
            return 0;
        }
    }

    sum(first, second);
    substraction(first, second);

    delete[] first;
    delete[] second;
}