#include <iostream>
using namespace std;

int main()
{
    setlocale(0, "ru");
    double K;
    cout << "Введите число грибов" << endl;
    cin >> K;
    if (int(K) == K){
    if (int(K) == 11)
    {
        cout << "мы нашли 11 грибов в лесу" << endl;
    }
    else if (int(K) == 12 || int(K) == 13 || int(K) == 14)
    {
        cout << "Мы нашли " << int(K) << " грибов в лесу" << endl;
    }
    else if (int(K) % 10 == 1)
    {
        cout << "Мы нашли " << int(K) << " гриб в лесу" << endl;
    } 
    else if (int(K) % 10 == 2 || int(K) % 10 == 3 || int(K) % 10 == 4)
    {
        cout << "Мы нашли " << int(K) << " гриба в лесу" << endl;
    }
    else
    {
        cout << "Мы нашли " << int(K) << " грибов в лесу" << endl;
    }
    }
    else 
    {
        cout << "Мы нашли " << K << " гриба в лесу" << endl;
    }
}
