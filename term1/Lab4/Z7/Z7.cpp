#include <iostream>
using namespace std;

int checkSymbols(char* st)   // функция, которая сверяет символы, которые мы хотим ввести в массив. Если это не число, то неверный ввод. Но - не даёт ввести.
{
    int f = 0;
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 401;
        }
    }
    return 0;
}

int main()
{
    int k; 
    char* n = new char[1000];
    cout << "Enter a positive number" << endl;
    cin >> n;
    if (checkSymbols(n) != 0)
    {
        cout << "You needn't to enter symbols. Only int numbers.";
        return 0;
    }
    
    cout << "The number of numbers in our number= " << strlen(n) << endl;
    for (int i = 0, j = 1; i < strlen(n); i++, j++)
    {
        cout << "Number rank of " << n[i] << " = " << strlen(n) - j << endl;
    }
    delete[] n;

}

