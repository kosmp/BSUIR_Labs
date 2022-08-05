//Не пользуясь никакими другими арифметическими действиями,
//кроме сложения, вычитания и умножения, вычислите 23х ^ 3 + 69x ^ 2 + 32x + 8 и
// - 23х ^ 3 + 69x ^ 2 - 32x + 8.
#include <iostream>
using namespace std;

int main()
{    
    double x;
    cout << "insert x" << endl;
    cin >> x;


    
    double b = x * x;
    double a = 69 * b + 8;         

    double e = x*(32 + 23 * b);
    
    cout << "23х ^ 3 + 69x ^ 2 + 32x + 8" << endl;
    cout << a + e;
    cout << "- 23х ^ 3 + 69x ^ 2 - 32x + 8" << endl;
    cout << a - e;


    


}

