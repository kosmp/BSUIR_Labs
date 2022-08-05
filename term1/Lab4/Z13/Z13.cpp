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
    cout << "This program calculates how many sockets you will get if you optimally connect extension cords." << endl;
    int n; // для хранения проверенного значения
    int N;
    char* st1 = new char[1000000];   // массив, созданный только для проверки. 
    cout << "Enter number of extension cords. Enter N: ";
    cin >> st1;
    if (checkSymbolsPositive(n, st1) != 0)
    {
        cout << "You needn't to enter symbols. Only int values.";
        return 0;
    }
    N = n;
   
    int* ext = new int[N];
    cout << "Enter number of outputs for each extension cord" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << i + 1<< ": ";
        char* st = new char[1000000];   // массив, созданный только для проверки. 
        cin >> st;
        if (checkSymbolsPositive(n, st) != 0)
        {
            cout << "You needn't to enter symbols. Only int values.";
            return 0;
        }
        ext[i] = n;
    }

    int numberOfSocets = 0;
    for (int i = 0; i < N; i++)
    {
        numberOfSocets = numberOfSocets + ext[i] - 1;   
    }
    numberOfSocets += 1;
    cout << "Number of sockets= " << numberOfSocets;
}
