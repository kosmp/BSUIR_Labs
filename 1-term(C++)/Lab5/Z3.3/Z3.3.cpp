#include <iostream>
using namespace std;

int checkSymbolsPositive(int* n, char* st)   // function which checks what we have entered
{
    int f = 0;
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            cout << "you have entered incorrect symbol" << endl;
            return 401;
        }
        f *= 10;
        f += st[i] - '0';
    }
    *n = f;
    if ((*n) == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    delete[] st;
    return 0;
}

int checkSymbols(int& n, char* st)
{
    int f = 0;
    if (st[0] == '-')   // check on negative value
    {
        if (strlen(st) == 1)
            return 401;
        for (int i = 1; i < strlen(st); i++)
        {
            if (st[i] < '0' || st[i] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 401;
            }
            f *= 10;
            f += st[i] - '0';
        }
        n = -f;
    }
    else    // if not negative value
    {
        for (int i = 0; i < strlen(st); i++)
        {
            if (st[i] < '0' || st[i] > '9')
            {
                cout << "you have entered incorrect symbol" << endl;
                return 401;
            }
            f *= 10;
            f += st[i] - '0';
        }
        n = f;
    }
    delete[] st;
    return 0;
}

int checkAndEnterSizeArray(int* n)
{
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter size of array n*k(n - rows, k - cols): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int values." << endl;
        return 400;
    }
    else
    {
        return 0;
    }
}

int enterArray(int** arr, int i, int j)
{
    int n;  // for containing of value to check, local n
    char* st = new char[1000];   // array is using only for checking 
    cin >> st;
    if (checkSymbols(n, st) != 0)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 400;
    }
    arr[i][j] = n;
    return 0;
}

void createNewArr(int** arr, int& n, int& k)
{
    cout << "\nThis program creates a dynamic array from elements located in even columns of the given array and having an odd value." << endl;
    cout << "And calculates the arithmetic mean of the elements of a dynamic array." << endl;
    if (k > 2)
    {
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (j % 2 == 0 && j != 0 && arr[i][j] % 2 != 0) count++;
            }
        }
        int* arrNew = new int[count];

        int c = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (j % 2 == 0 && j != 0 && arr[i][j] % 2 != 0)
                {
                    arrNew[c] = arr[i][j];
                    c++;
                }
            }
        }
        double average = 0;
        for (int i = 0; i < count; i++)
        {
            cout << arrNew[i] << "\t";
            average += arrNew[i];
        }
        average = double(average) / double(count);
        cout << "\nThe arithmetic mean= " << average << endl;
        delete[] arrNew;
    }
    else
    {
        cout << "!There aren't even columns, so dynamic array can't be created!" << endl;
    }
}

int main()
{
    int n, k;
    int q;
    do
    {
        q = checkAndEnterSizeArray(&n);
    } while (q != 0);
    do
    {
        q = checkAndEnterSizeArray(&k);
    } while (q != 0);
    int** arr = new int* [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[k];
    }
    cout << "Lets fill our arr with int values" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (enterArray(arr, i, j) != 0)
                return 0;
        }
    }
    cout << "Original array(matrix): ";
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < k; j++)
        {
            cout << arr[i][j] << "\t";
        }
    }

    createNewArr(arr, n, k);
    
    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
