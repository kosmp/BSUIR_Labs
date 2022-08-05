//  Задача 7. Составить программу для решения уравнений трёх видов:
//  7.1 ax ^ 4 + bx ^ 2 + c = 0;
//  7.2 ax ^ 4 + bx ^ 3 + cx ^ 2 + bx + a = 0
//  7.3 x ^ 3 + px + q = 0
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double a, b, c, p, x1, x2, q;
    cout << "Insert a, b, c, p, q" << endl;
    cin >> a >> b >> c >> p >> q;
   
    // 7.1
    double D = b * b - 4 * a * c;
    if (a == 0 && b == 0)
    {
        if (c == 0) {
            cout << "x any" << endl;
            goto next;   // использую goto, т.к. склеил 3 примера в 1 программу. Так бы вернул значение и завершил бы выполнение программы.
        }
        cout << "No roots" << endl;
        goto next;      // использую goto, т.к. склеил 3 примера в 1 программу. Так бы вернул значение и завершил бы выполнение программы. Можно было if D > 0 поставить раньше, но прилепить в условие, что а и б не равны 0
    }
    else if (a == 0)
    {
        if((-c / b) > 0)
        {
            cout << "x1= " << sqrt(-c / b) << endl;
            cout << "x2= " << -sqrt(-c / b) << endl;
        }
        else if ((-c / b) == 0)
        {
            cout << "x= 0" << endl;
        }
        else
        {
            cout << "No roots" << endl;
        }
        goto next;      // использую goto, т.к. склеил 3 примера в 1 программу. Так бы вернул значение и завершил бы выполнение программы.
    }
    if (D > 0)
    { 
        if (((-b + sqrt(D))/2*a >= 0) && ((-b - sqrt(D)) / (2 * a) >= 0))
        { 
            x1 = sqrt((-b + sqrt(D)) / (2 * a));
            x2 = -sqrt((-b - sqrt(D)) / (2 * a));
            cout << "x1= " << x1 << " x2= " << x2 << endl;

        }  else if ((-b + sqrt(D)) / (2 * a) >= 0)
        {
            x1 = sqrt((-b + sqrt(D)) / (2 * a));
            cout << "x= " << x1 << endl;
        }
        else if ((-b - sqrt(D)) / (2 * a) >= 0)
        {
            x2 = -sqrt((-b - sqrt(D)) / (2 * a));
            cout << "x= " << x2 << endl;
        }
        else 
        {
            cout << "No roots" << endl;
        }
    } 
    else if (D == 0)
    {
        if (-b / (2 * a) >= 0)
        {
            if ((-b / (2 * a)) == 0)
            {           
                cout << "x= 0" << endl;
            }
            else
            {
                x1 = sqrt(-b / (2 * a));
                x2 = -sqrt(-b / (2 * a));
                cout << "x1= " << x1 << " x2= " << x2 << endl;
            }
        }
        else
        {
            cout << "No roots" << endl;
        }
    }
    else
    {
        cout << "Discriminant is smaller than 0, no roots" << endl;
    }
    ///////////////////////////////////////////////////////

    next:           // использую goto, т.к. склеил 3 примера в 1 программу. Так бы вернул значение и завершил бы выполнение программы.
    cout << "\n";

    // 7.2 ax ^ 4 + bx ^ 3 + cx ^ 2 + bx + a = 0   
    double D1 = b * b + 8 * a * a - 4 * a * c;
    double D2 = pow((-b + sqrt(D1)) / (2 * a), 2) - 4;
    double D3 = pow((-b - sqrt(D1)) / (2 * a), 2) - 4;

    if (a == 0)
    {
        cout << "x1 = 0" << endl;
        if (b != 0) 
        {
            if ((c * c - 4 * b * b) > 0)
            {
                cout << "x2= " << (-c + (c * c - 4 * b * b)) / (2 * b) << endl;
                cout << "x3= " << (-c - (c * c - 4 * b * b)) / (2 * b) << endl;
            }
            else if ((c * c - 4 * b * b) == 0)
            {
                cout << "x2= " << -c / (2 * b) << endl;
            }
        }
        goto next2;         // использую goto, т.к. склеил 3 примера в 1 программу. Так бы вернул значение и завершил бы выполнение программы.
    }
    if (D1 > 0)
    {
        if (D2 > 0 && D3 > 0)
        {
            cout << "x1= " << -(((-b + sqrt(D1)) / (2 * a)) + sqrt(D2)) / 2 << endl;
            cout << "x2= " << -(((-b + sqrt(D1)) / (2 * a)) - sqrt(D2)) / 2 << endl;
            cout << "x3= " << -(((-b - sqrt(D1)) / (2 * a)) + sqrt(D3)) / 2 << endl;
            cout << "x4= " << -(((-b - sqrt(D1)) / (2 * a)) - sqrt(D3)) / 2 << endl;            
        }
        else if (D2 == 0 && D3 == 0) 
        {
            cout << "x1= " << -((-b + sqrt(D1)) / (2 * a)) / 2 << endl;
            cout << "x2= " << -((-b - sqrt(D1)) / (2 * a)) / 2 << endl;
        }
        else if (D2 > 0 && D3 == 0)
        {
            cout << "x1= " << -(((-b + sqrt(D1)) / (2 * a)) + sqrt(D2)) / 2 << endl;
            cout << "x2= " << -(((-b + sqrt(D1)) / (2 * a)) - sqrt(D2)) / 2 << endl;
            cout << "x3= " << -((-b - sqrt(D1)) / (2 * a)) / 2 << endl;
        }
        else if (D2 == 0 && D3 > 0)
        {
            cout << "x1= " << -((-b + sqrt(D1)) / (2 * a)) / 2 << endl;
            cout << "x2= " << -(((-b - sqrt(D1)) / (2 * a)) + sqrt(D3)) / 2 << endl;
            cout << "x3= " << -(((-b - sqrt(D1)) / (2 * a)) - sqrt(D3)) / 2 << endl;

        }
        else if (D2 < 0 && D3 == 0)
        {
            cout << "x1= " << -((-b - sqrt(D1)) / (2 * a)) / 2 << endl;
            cout << "Discriminant 2 is smaller than 0" << endl;
        }
        else if (D2 == 0 && D3 < 0)
        {
            cout << "x1= " << -((-b + sqrt(D1)) / (2 * a)) / 2 << endl;
            cout << "Discriminant 3 is smaller than 0" << endl;
        } 
        else if (D2 > 0 && D3 < 0)
        {
            cout << "x1= " << -(((-b + sqrt(D1)) / (2 * a)) + sqrt(D2)) / 2 << endl;
            cout << "x2= " << -(((-b + sqrt(D1)) / (2 * a)) - sqrt(D2)) / 2 << endl;
            cout << "Discriminant 3 is smaller than 0" << endl;
        }
        else if (D2 < 0 && D3 > 0)
        {
            cout << "x3= " << -(((-b - sqrt(D1)) / (2 * a)) + sqrt(D3)) / 2 << endl;
            cout << "x4= " << -(((-b - sqrt(D1)) / (2 * a)) - sqrt(D3)) / 2 << endl;
            cout << "Discriminant 2 is smaller than 0" << endl;
        }
        else if (D2 < 0 && D3 < 0)
        {
            cout << "Discriminant 2 and 3 are smaller than 0, no roots" << endl;
        }


    }
    else if (D1 == 0)
    {
        double D4 = pow(b / (2 * a), 2) - 4;
        if (D4 > 0)
        {
            cout << "x1= " << (-b / (2 * a) + sqrt(D4)) / 2 << endl;
            cout << "x2= " << (-b / (2 * a) - sqrt(D4)) / 2 << endl;
        }
        else if (D4 == 0)
        {
            cout << "x1= " << -b / (4 * a) << endl;
        }
        else
        {
            cout << "Discriminants are smaller than 0, no roots" << endl;
        }
    }
    else
    {
        cout << "Discriminant is smaller than 0, no roots" << endl;
    }

    /////////////////////////////////////////////////////////

    next2:      // использую goto, т.к. склеил 3 примера в 1 программу. Так бы вернул значение и завершил бы выполнение программы.
    cout << "\n";

    // 7.3 x ^ 3 + px + q = 0     ----------  x ^ 3 + 0 * x ^ 2 + p* x + q = 0
    //double Q = 1 / 9;
    //double R = (2 + 27 * p) / 54;
    //double S = pow(Q, 3) - pow(R, 2);
    //double f = 1 / 3 * acos(R / pow(Q, 1 / 3));
    //cout << "x1= " << -2 * sqrt(Q) * cos(f) - a / 3 << endl;
    //cout << "x2= " << -2 * sqrt(Q) * cos(f + 2 / 3 * 3.14) - a / 3 << endl;
    //cout << "x3= " << -2 * sqrt(Q) * cos(f - 2/ 3 * 3.14) - a / 3 << endl;
    
    double D5 = q * q + 4 * pow(p, 3) / 27;
    if (D5 > 0)
    {
        cout << "x1= " << pow((-q + sqrt(D5)) / 2, 1 / 3) - p / (3 * pow((-q + sqrt(D5)) / 2, 1 / 3)) << " x2= " << pow((-q - sqrt(D5)) / 2, 1 / 3) - p / (3 * pow((-q - sqrt(D5)) / 2, 1 / 3)) << endl;
    }
    else if (D5 == 0)
    {
        cout << "x1= " << pow(-q / 2, 1 / 3) - p / (3 * pow(-q / 2, 1 / 3)) << endl;
    }
    else {
        cout << "Discriminant is smaller than 0, no roots" << endl;
    }

    /////////////////////////////////////////////////////////

}

