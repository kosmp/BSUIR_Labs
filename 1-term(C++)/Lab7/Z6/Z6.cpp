#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout << "This program will find the number of interesting numbers. Immediately enter t, this is the number of input number of n. Next, enter n t-the number of times." << endl;
    cout << "We iterate over the numbers (x) from 1 to the current n and compare the sum of the digits in the current x with the number x + 1." << endl;
    cout << "The number x will be interesting only when the rightmost digit in x + 1 equals 0." << endl;
    cout << "Therefore, it makes no sense to calculate the sum of the digits for each numbers." << endl;
    int t;  // число наборов входных данных
    cin >> t;
    if (t < 1 || t > 1000)
    {
        cout << "Incorrect enter. Error." << endl;
        return 0;
    }
    int* output = new int[1000];    // массив просто для красивого вывода, как в тесте. Сохраняем ответы в массив, чтобы выводить не сразу.

    int i = 1;
    for (; i <= t; i++)
    {
        int n;
        cin >> n;   // i-й набор входных данных
        if (n < 1 || n > (int)pow(10, 9))
        {
            cout << "Incorrect enter. Error." << endl;
            return 0;
        }
        int counter = 0;    // кол-во интересных чисел. Когда сумма цифр числа, увеличенного на 1, меньше, чем сумма цифр числа.
        
        // число x будет интересным только тогда, когда самая правая цифра в x + 1 будет равна 0(x изменяется от 1 до n). Поэтому нет смысла вычислять сумму цифр для каждого числа.
        // Но, вообще говоря это и не нужно, нужно количество десятков в числе n + 1. Сколько десятков - такое и количество интерсных чисел будет. Не нужно перебирать все числа от 1 до n. Количество чисел от 1 до n с последним нулём - это количество десятков.
        counter = (n + 1) / 10;
        output[i - 1] = counter;    // просто для красивого вывода
    }
    cout << endl;
    for (int j = 0; j < i - 1; j++)     // вывод как в тесте
    {
        cout << output[j] << endl;
    }
    delete[] output;
}