#include <iostream>
#include "DynamicLib.h"
using namespace std;

int main()
{
    cout << "This program for a given one-dimensional array checks that there is at least one element for which the condition sin(arr[i]) > 0 is true." << endl;
    cout << "The recursive function is applied separately for each of the halves of the array." << endl;
    cout << "Recursive calls will end when there is only one element left." << endl;
    int n;  // size of array
    int q;
    do
    {
        q = checkAndEnterSizeArray(n);
    } while (q != 0);
    int* arr = new int[n];
    cout << "Lets fill our arr with int values" << endl;
    for (int i = 0; i < n; i++)
    {
        if (enterArray(arr, i) != 0)
            return 0;
    }

    if (func(0, n - 1, arr)) cout << "This array contains at least 1 element with sin > 0";
    else cout << "This array doesn't contain at least 1 element with sin > 0";

    delete[] arr;
    system("pause");
}
