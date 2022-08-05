#include <iostream>
#include <cmath>
using namespace std;

void convert(int deNumber)  // функция для конвертации в троичную систему заданного числа, но в троичную систему без 0, а с 1 2 3. Т.к. цифры при делении столбиком для перевода из десятичной системы в троичную записываются с конца, то нужно применять рекурсию.
{
    if (deNumber > 3)
    {
        if (deNumber % 3 == 0)  // если в остатке 0, то значит нужно взять кол-во частей на 1 меньше, тогда будет 3 в остатке. Нас устраивают только 1 2 3
        {
            convert(deNumber / 3 - 1);
            cout << deNumber % 3 + 3;   // прибавляем к 0 три, т.к. взяли на 1 целую часть меньше (к примеру, 21 / 3. Возьмём не по 7, а по 6, т.к. в остатке не может быть 0)
        }
        else
        {
            convert(deNumber / 3);  // тогда применяем обычное деление и дальше работаем с оставшейся полной целой частью
            cout << deNumber % 3;
        }
    }
    else
    {
        // 0 тут не может получиться, но если получилось <= 3, то дальше не нужно делить. Даже если 3, то не нужно делить, т.к. 3 нас устроивает.
        cout << deNumber;
        return;     // выход из рекурсии
    }
}

int main()
{
    cout << "The program converts a number from the decimal system to ternary (without 0, but with 3, i.e. 1 2 3)." << endl;
    int n;
    cout << "Enter the number n in the decimal system. 1 <= n <= 2 * 10 ^ 9." << endl;
    cin >> n;
    if (n <= 0 || n > 2 * (int)pow(10, 9))  // проверка на ввод согласно условию
    {
        cout << "Incorrect enter. Error." << endl;
        return 0;
    }
    cout << "Result: " << endl;
    convert(n);
}