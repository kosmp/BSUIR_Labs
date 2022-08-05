#include <iostream>
using namespace std;

int enterArray(char arr[], int& n)
{
    int size = n;
    cin.get(arr, size);
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '\0')         
        {
            n = i + 1;
            break;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[0] == ' ')
        {
            return 0;
        }
        if (arr[i] != '0' && arr[i] != '1' && arr[i] != ' ')
        {
            cout << "You need to enter only 0, 1, space." << endl;
            return 401;
        }
    }
    return 0;
}

int main()
{
    cout << "This program calculates count of five 0 or 1 in a row(five in a row between spaces). So, let's fill array, which consist of 0, 1, spaces." << endl;
    char arr[80] = {};
    int n = 80;
    if (enterArray(arr, n) != 0)
    {
        return 0;
    }

    cout << "Original array: " << arr << endl;
    int count = 0;
    for (int i = 0, k = 0; i < n; i++)
    {
        if (arr[i] == '0' || arr[i] == '1')
        {
            k++;
        }
        else
        {
            if (k == 5)
            {
                count += 1;
            }
            k = 0;
        }
    }
    cout << "5 numbers in a row (each number is 0 or 1) between spaces " << count << " times" << endl;
}