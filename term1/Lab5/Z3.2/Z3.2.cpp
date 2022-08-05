#include <iostream>
#include <cstdlib>
using namespace std;

int checkSymbolsPositive(int* n, char* st)   // function for check if we entered a number or symbols
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

int checkSymbols(double& n, char* st)   // &n for local n (in enterArray function)
{
    bool check = false;
    int c = 0;
    if (st[0] == '-')   // check on negative value
    {
        if (strlen(st) == 1)
            return 401;
        if (st[1] == '.' || (st[strlen(st) - 1] == '.'))
            return 401;
        for (int i = 1; i < strlen(st); i++)
        {
            if (st[i] == '.')
            {
                check = true;
                c = i;
                break;
            }
        }
        if (check) // if char array contains at least one symbol '.' then we need to check all symbols. if . > 1 then error
        {
            for (int i = 1; i < c; i++)
            {
                if (st[i] < '0' || st[i] > '9')
                {
                    cout << "you have entered incorrect symbol" << endl;
                    return 401;
                }
            }

            for (int i = c + 1; i < strlen(st); i++)
            {
                if (st[i] < '0' || st[i] > '9')
                {
                    cout << "you have entered incorrect symbol" << endl;
                    return 401;
                }
            }
        }
        else
        {
            for (int i = 1; i < strlen(st); i++)
            {
                if (st[i] < '0' || st[i] > '9')
                {
                    cout << "you have entered incorrect symbol" << endl;
                    return 401;
                }
            }
        }
    }
    else    // if not negative value
    {
            if (st[0] == '.' || (st[strlen(st) - 1] == '.'))
                return 401;
            for (int i = 0; i < strlen(st); i++)
            {
                if (st[i] == '.')
                {
                    check = true;
                    c = i;
                    break;
                }
            }
            if (check) // if char array contains at least one symbol '.' then we need to check all symbols. if . > 1 then error
            {
                for (int i = 0; i < c; i++)
                {
                    if (st[i] < '0' || st[i] > '9')
                    {
                        cout << "you have entered incorrect symbol" << endl;
                        return 401;
                    }
                }

                for (int i = c + 1; i < strlen(st); i++)
                {
                    if (st[i] < '0' || st[i] > '9')
                    {
                        cout << "you have entered incorrect symbol" << endl;
                        return 401;
                    }
                }
            }
            else
            {
                for (int i = 0; i < strlen(st); i++)
                {
                    if (st[i] < '0' || st[i] > '9')
                    {
                        cout << "you have entered incorrect symbol" << endl;
                        return 401;
                    }
                }
            }
    }
    return 0;
}

int checkAndEnterSizeArray(int* n)
{
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter size of array(matrix) n*k(n - rows, k - cols): ";
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

int enterArray(double** arr, int i, int j)
{
    double n;  // for containing of value to check, local n
    char* st = new char[1000];   // array is using only for checking 
    cin >> st;
    if (checkSymbols(n, st) != 0)   // for checking if two . or this is not negative value (when 2- 2-2 -)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 400;
    }
    arr[i][j] = atof(st);   // for converting char to double
    delete[] st;
    return 0;
}

void checkNullElem(double** arr, int& n, int& k)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (arr[i][j] == 0)
            {
                count++;
                cout << "Indices of elements which value = 0: i=" << i << ", j=" << j << endl;
            }
        }
    }
    cout << "Number of 0 values= " << count;
}

void transposMatrix(double** arr, int& n, int& k)
{
    int save;
    double** arrNew = new double* [n];
    for (int i = 0; i < n; i++)
    {
        arrNew[i] = new double [k] ;
    }

    for (int i = 0, p = n - 1; i < n; i++, p--)
    {
        for (int j = 0, q = k - 1; j < k; j++, q--)
        {
            arrNew[i][j] = arr[p][q];
        }
    }
    cout << "\n\nArray(matrix) with elements rearranged in reverse order:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < k; j++)
        {
            cout << arrNew[i][j] << "\t";
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] arrNew[i];
    }
    delete[] arrNew;
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
    double** arr = new double* [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new double[k];
    }
    cout << "Lets fill our arr(matrix) with double or int values" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (enterArray(arr, i, j) != 0)
                return 0;
        }
    }
    cout << "You have entered" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < k; j++)
        {
            cout << arr[i][j] << "\t";
        }
    }

    cout << endl;
    checkNullElem(arr, n, k);
    transposMatrix(arr, n, k);

    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}
