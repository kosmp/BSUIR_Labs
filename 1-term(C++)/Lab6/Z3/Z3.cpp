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

int checkAndEnterSizeArray(int* n)
{
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter matrix order (n): ";
    cin >> st;
    if (checkSymbolsPositive(n, st) != 0)
    {
        cout << "You needn't to enter symbols or 0. Only int value." << endl;
        return 400;
    }
    else
    {
        return 0;
    }
}

int main()
{
    cout << "You need to enter a matrix. Matrix elements are lines. Program calculates the sum of the elements codes of each word." << endl;
    cout << "If the sum is even, flips the word in a line." << endl;
    cout << "The resulting matrices are displayed on the screen." << endl;
    int n, q;
    do
    {
        q = checkAndEnterSizeArray(&n);
    } while (q != 0);
    char*** matrix = new char** [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new char* [n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = new char[1000];
        }
    }
    cin.ignore(100, '\n');
    cout << "Let's fill this matrix with symbols." << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin.get(matrix[i][j], 100);
        }
    }
    
    cout << "Original matrix: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << "[" << i << "][" << j << "]" << matrix[i][j] << "\t";
        }
    }

    int** sizesOfLines = new int* [n];
    for (int i = 0; i < n; i++)
    {
        sizesOfLines[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < 1000; k++)
            {
                if (matrix[i][j][k] == '\0')
                {
                    sizesOfLines[i][j] = k + 1;     // identified sizes of words
                    break;
                }
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
                int wordSize = 0;   // counter of last index in a word
                int startWordSize = 0;  // counter of first index in a word
                bool check = false;     // will be completed algorithm for checking the sum of word codes, if a word was found
                bool checkStart = false;    // for setting first index in a word. 1 time for each word.
                bool checkFirstSpace = false;
                bool forDouble = false;
                for (int k = 0; k < sizesOfLines[i][j]; k++)
                {
                    if (matrix[i][j][k] != ' ' && checkStart == false)
                    {
                        startWordSize = k;
                        wordSize += startWordSize;  // because wordSize its index of the last letter of a word and if 1 or more spaces, index will be lost. If index was lost after 1+ spaces we can save order
                        checkStart = true;      // setting start index 1 time for each word
                    }
                    if (k >= 1) forDouble = true;

                    if (matrix[i][j][k] != ' ' && matrix[i][j][k] != '\0')
                    {
                        wordSize++;
                    }
                    else if (forDouble && matrix[i][j][k] == ' ' && matrix[i][j][k - 1] == ' ')
                    {
                        check = false;  // if 2 or more spaces. Then it's not a typical case (need't check = true), so we need to skip
                    }
                    else if(matrix[i][j][k] == ' ' || matrix[i][j][k] == '\0')
                    {
                        check = true;
                        wordSize--;
                    }
                    if (matrix[i][j][0] == ' ' && checkFirstSpace == false)
                    {
                        checkFirstSpace = true;    
                        wordSize++;     // so as not to lose wordSize, if the first is space. It's not a typical situation, when space. Can be used only 1 time, if need
                    }
                    

                    if (check == true && wordSize != startWordSize)  // true because a word was found. Then we need to check this word and reverse if need
                    {
                        long long int sumOfCodes = 0;
                        int startWordConst = startWordSize;     // because startWordSize will be changing
                        for (; startWordSize <= wordSize; startWordSize++)
                        {
                            sumOfCodes += matrix[i][j][startWordSize];
                        }

                        if (sumOfCodes % 2 == 0 && sumOfCodes != 0)    // this condition for reverse a word in a line
                        {
                            // inversion of this line
                            char* wordForReverse = new char[wordSize + 1];     // for saving elements. +1 for \0

                            startWordSize = startWordConst;
                            for (; startWordSize <= wordSize; startWordSize++)   // copy-fill
                            {
                                wordForReverse[startWordSize] = matrix[i][j][startWordSize];     // so as not to lose half of the elements. copying full word
                            }

                            startWordSize = startWordConst;
                            if ((wordSize + startWordConst) % 2 == 0)
                            {
                                for (int z = wordSize; startWordSize < ((wordSize - startWordConst) / 2 + startWordConst); startWordSize++, z--)
                                {
                                    matrix[i][j][startWordSize] = matrix[i][j][z];  // left part
                                }
                                for (int k = (wordSize - startWordConst) / 2 + startWordConst; k <= wordSize; k++)
                                {
                                    matrix[i][j][k] = wordForReverse[wordSize - k + startWordConst];  // right part
                                }
                            }
                            else
                            {
                                for (int z = wordSize; startWordSize <= ((wordSize - startWordConst) / 2 + startWordConst); startWordSize++, z--)   // else for <=. Because we need to include
                                {
                                    matrix[i][j][startWordSize] = matrix[i][j][z];  // left part
                                }
                                for (int k = (wordSize - startWordConst) / 2 + startWordConst + 1; k <= wordSize; k++)  // +1 because we need to do from the next element. the left part is normal
                                {
                                    matrix[i][j][k] = wordForReverse[wordSize - k + startWordConst];  // right part
                                }
                            }
                            check = false;
                            checkStart = false;
                            wordSize = 0;
                            delete[] wordForReverse;
                        }
                    }
                    else if (check == true && wordSize == startWordSize)    // skip if only 1 letter
                    {
                        check = false;
                        checkStart = false;
                        wordSize = 0;
                    }
                }
        }
    }

    cout << "\n\nFinal matrix: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int j = 0; j < n; j++)
        {
            cout << "[" << i << "][" << j << "]" << matrix[i][j] << "\t\t";
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            delete[] matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    for (int i = 0; i < n; i++)
    {
        delete[] sizesOfLines[i];
    }
    delete[] sizesOfLines;
}