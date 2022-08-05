#include <iostream>
#include <string>
using namespace std;

int checkSymbolsPositive(int* n, char* st)   // function which checks what we have entered
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
    *n = f;
    if ((*n) == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

int enterValue(int* n)
{
    char* st = new char[1000];   // array is using only for checking 
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int value." << endl;
        return 400;
    }
    else
    {
        return 0;
    }
}

int main()
{
    cout << "Determine if it is possible to write out a string t with a token from a string s." << endl;
    cout << "The elements that the chip falls on are written out." << endl;
    cout << "If the number of elements is not enough, then the chip goes in the opposite direction." << endl;
    cout << "This program checks all the options. If it possible to write out string t from string s, then YES otherwise NO." << endl;
    int f, q;
    cout << "Enter q (1<=q<=500): " << endl;
    do
    {
        f = enterValue(&q);
    } while (q >= 500 || f != 0);
    string s;
    string t;
    cout << "Let's fill line s. Only latin lowercase letters.(max size = 500)" << endl;
    cin >> s;
    if (s.length() > 500)
    {
        cout << "Your word is too big. Max 500 letters." << endl;
        return 0;
    }
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!(s[i] >= 97 && s[i] <= 122))
        {
            cout << "Incorrect enter." << endl;
            return 0;
        }
    }
    cout << "Let's fill line t. Only latin lowercase letters.(max size = 2 * size of s - 1)" << endl;
    cin >> t;
    if (t.length() > 2 * s.length() - 1)
    {
        cout << "-1. Your word is too big. (max size = 2 * size of s - 1)" << endl;
        return 0;
    }
    for (int i = 0; t[i] != '\0'; i++)
    {
        if (!(t[i] >= 97 && t[i] <= 122))
        {
            cout << "Incorrect enter." << endl;
            return 0;
        }
    }

    bool check1 = true;
    bool check3 = true; // только для того, что дальше не искать, если уже нашли
    for (int i = 0; i < s.length() && check3; i++)
    {
        for (int j = 0; j <= i; j++)    // проверяем элементы до текущего i
        {
            if (i - j + 1 < t.length())
            {
                // надо пройтись ещё в обратном направлении, если кол-во элементов от этого элемента, не включая его, позволяет это сделать, если нельзя пройтись назад, то значит и строка такая не получится и переходим на след элемент
                // нужно сразу проверить, можно ли вообще пройтись назад так, чтобы хватило кол-ва элементов
                if ((i - j + 1) + i >= t.length())  // -1 т.к. при проходе в обратном направлении не учится повторно текущий элемент, от которого идём назад
                {
                    // теперь нужно проверить, элементы от 0 до j. Должны совпадать подряд. А потом уже в обратном направлении. Если даже эти не совпадают подряд, то нет смысла проверять в обратном направлении
                    int stopInd;   // индекс в t, на котором остановились при проверке в положительном направлении
                    bool check2 = true;
                    for (int k = j, p = 0; k <= i; k++, p++)
                    {
                        if (s[k] != t[p])
                        {
                            check2 = false;
                            break;
                        }
                        if (k == i)
                        {
                            stopInd = p;
                        }
                    }
                    int size1 = i - j + 1; // размер в положительном направлении вместе с самым правым i
                    int left = i - (t.length() - size1);    // левый индекс, до которого нужно идти в обратном направлении

                    if (check2)  // условие для того, чтобы начать проверку в обратном направлении
                    {
                        // причём нужно сверять элементы в t от того индекса, на котором остановились. 
                        for (int k = i - 1, p = stopInd + 1; k >= left; k--, p++)
                        {
                            if (s[k] != t[p])
                            {
                                check2 = false;
                                break;
                            }
                        }
                    }
                    if (check2) // тогда не нужно дальше искать. Такую строку уже можно выписать
                    {
                        check3 = false; 
                        check1 = true;
                        break;
                    }
                    else
                    {
                        check1 = false;
                    }

                }
                else
                {
                    check1 = false;
                }
            }
            else
            {
                // просто сверяем элементы, должны совпадать подряд. Если не совпадают, то переключаемся на следующий элемент
                bool check2 = false;
                for (int k = j, p = 0; k <= i; k++, p++)
                {
                    if (s[k] != t[p])
                    {
                        break;
                    }
                    if (k == i) // если дошли до конца и не было обрыва, значит строку t можно выписать из s
                    {
                        check2 = true;
                    }
                }
                if (check2) // если уже найдена, то не нужно искать дальше
                {
                    check3 = false;
                    check1 = true;
                    break;
                }
                else
                {
                    check1 = false;
                }
            }
        }
    }
    if (check1)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }














}