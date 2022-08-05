// Вариант 6
//  S = 10.1 + A/C + D/K^2
//  A = x+y         D=|C-A|
#include <iostream>
#include <cmath>
using namespace std;

int main()
{   
    setlocale(LC_ALL, "Russian");
    

    double x, y;  
      
    cout << "Введите x" << endl;
    cin >> x;

    cout << "Введите y" << endl;
    cin >> y;
 

    double C, K;

    cout << "Введите C" << endl;
    cin >> C;

    cout << "Введите K" << endl;
    cin >> K;
    
    double A = x + y;
    double D = abs(C-A);       // модуль C-A

    double S;
    S = 10.1 + (A / C + D / pow(K, 2));

    cout << A / C + D / pow(K, 2);
    cout << "S: " << S << endl;


}

