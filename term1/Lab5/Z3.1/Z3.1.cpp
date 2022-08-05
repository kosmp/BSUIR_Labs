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
    cout << "Enter size of array n*k(1-st size must be = 5, 2-nd size must be = 6): ";
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

int multiply(int* arr, int count)
{
    int m = 1;
    for (int i = 0; i < count; i++)
    {
        m *= arr[i];
    }
    return m;
}

long long int multiplyMatrix(int** arr, int& n, int& k)
{
    long long int m = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            m *= arr[i][j];
        }
    }
    return m;
}

int main()
{
    int n, k;
    int q;
    do
    {
        q = checkAndEnterSizeArray(&n);
    } while (n != 5 || q != 0);    
    do
    {
        q = checkAndEnterSizeArray(&k);
    } while (k != 6 || q != 0);
    int** arr = new int*[n];
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

    int count = 0;
    for (int i = 0, j = 0; i < n && j < k; i++, j++)
    {
        if(arr[i][j] % 2 == 0 && arr[i][j] != 0)
            count++;
    }
    int* arr1 = new int[count];
    for (int i = 0, j = 0, c = 0; i < n && j < k; i++, j++)
    {
        if (arr[i][j] % 2 == 0 && arr[i][j] != 0)
        {
            arr1[c] = arr[i][j];
            c++;
        }
    }
    cout << "New array(consists of even values from main diagonal of original array): " << endl;
    for (int i = 0; i < count; i++)
    {
        cout << arr1[i] << "\t";
    }
    cout << "\nmultiplying of original array= " << multiplyMatrix(arr, n, k) << endl;
    if (count > 0)
        cout << "multiplying of new array= " << multiply(arr1, count) << endl;
    else
        cout << "There aren't any even values" << endl;

    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] arr1;
}