#include <iostream>
#include "StaticLib.h"
using namespace std;

int main()
{
    int n;  // size of array 1 and array 2
    int q;
    cout << "This program calculates x in the equation arr1[i]*x + arr2[j] = 0" << endl;
    cout << "arr1 and arr2 are arrays with size 7. This programm goes through various combinations of elements of these arrays" << endl;
    cout << "i and j are changing from 0 to 7(n)" << endl;
    cout << "If arr1[i] = 0 ---> x = 0" << endl;
    do
    { 
        q = checkAndEnterSizeArray(n);
    } while (n != 7 || q != 0);
    
    int* arr1 = new int[n]; // array A
    int* arr2 = new int[n]; // array B

    cout << "Lets fill our arr1 with int values" << endl;
    for (int i = 0; i < n; i++)
    {
        if (enterArray(arr1, i) != 0)
            return 0;       
    }
    cout << "Lets fill our arr2 with int values" << endl;
    for (int i = 0; i < n; i++)
    {
        if (enterArray(arr2, i) != 0)
            return 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double x;
            if (arr1[i] != 0)
            {
                x = -double(arr2[j]) / arr1[i];
                if (arr2[j] == 0) x = 0;
                cout << "arr1[i]= " << arr1[i] << "; arr2[j]= " << arr2[j] << "; i= " << i << "; j= " << j << endl;
                cout << "x= " << x << endl;
            }
            else
            {
                x = 0;
                cout << "arr1[i]= " << arr1[i] << "; arr2[j]= " << arr2[j] << "; i= " << i << "; j= " << j << endl;
                cout << "x= " << x << endl;
            }
        }
    }

    delete[] arr1;
    delete[] arr2;
}
