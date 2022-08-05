//Задача 13. Сможет ли шар радиуса R пройти в ромбообразное отверстие
//стороной P и острым углом Q ?
#include <iostream>
using namespace std;

int main()
{
    double P, Q, R;
    cin >> P >> Q >> R; 
    double r = P * P * sin(Q) / (2 * P);
    
    if (R <= r)
    {
        cout << "The circle can be inside of rhombus" << endl;
    }
    else
    {
        cout << "The circle can't be inside of rhombus" << endl;
    }
 
}

