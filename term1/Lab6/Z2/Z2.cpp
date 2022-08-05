#include <iostream>
using namespace std;

void enterAndCount(char* arr, int& n)
{
    int size = n;
    int countOfWords = 0;
    cin.get(arr, size);
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '\0')
        {
            n = i + 1;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != ' ' && (arr[i + 1] == ' ' || arr[i + 1] == '\0')) // checking end of each word
        {
            countOfWords += 1;
        }
    }
    cout << "Count of words= " << countOfWords << ", if 1 word = 1 ruble, then the sum for telegram=  " << countOfWords << endl;
}

int main()
{
    cout << "This program calculates the sum for telegram. (Count of entered words)" << endl;
    int n = 80;
    char* arr = new char[n];
    enterAndCount(arr, n);
    delete[] arr;
}