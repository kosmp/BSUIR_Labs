#include <iostream>
#include <cmath>
using namespace std;

int checkSymbols(int n, char* st)
{
    bool check = false;
    int c = 0;
    if (st[0] == '-')   // check on negative value
    {
        if (strlen(st) == 1)
            return 401;
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

void convert(char* st1, int& deNumber, int& i, int& numberOp)   // function for converting
{
    switch (numberOp)
    {
    case 0:
        st1[i] = '0';
        break;
    case 1:
        st1[i] = '1';
        break;
    default:
        cout << "error";
    }
}

void convertToForward(char* resultAdd) // converting from additional to forward code
{
    // we need to invert all bits except sign bit(first bit) and then +1, but save sign bit
    // since if you translate without sign bit into a forward code, then the number can be equal only in absolute value, then you need to take into account the sign bit
    for (int i = 1; i < strlen(resultAdd); i++)
    {
        if (resultAdd[i] == '1')
        {
            resultAdd[i] = '0';
        }
        else
        {
            resultAdd[i] = '1';
        }
    }
    int end = strlen(resultAdd) - 1;
    if (resultAdd[end] == '0') // adding 1
    {
        resultAdd[end] = '1';
    }
    else
    {
        // then you need to find the first 0 by going to the sign bit
        for (int i = end; i > 0; i--)   // adding 1
        {
            if (resultAdd[i] == '0')
            {
                resultAdd[i] = '1';
                break;
            }
            resultAdd[i] = '0';
        }
    }
    cout << "Forward code:\t" << resultAdd << endl;
    delete[] resultAdd;
}

void sumCodes(char* first, char* second, int f, int s)    // function for summing additional codes
{
    char* resultAdd = new char[strlen(first) + 1];
    for (int i = strlen(first) - 1; i >= 0; i--)
    {
        if (first[i] == '0' && second[i] == '0')
        {
            resultAdd[i] = '0';
        }
        else if ((first[i] == '1' && second[i] == '0') || (first[i] == '0' && second[i] == '1'))
        {
            resultAdd[i] = '1';
        }
        else
        {
            resultAdd[i] = '0';
            if (i > 0)
            {
                if ((first[i - 1] == '1' && second[i - 1] == '0') || (first[i - 1] == '0' && second[i - 1] == '1'))
                {
                    resultAdd[i - 1] = '0'; // 1 goes to the next digit and 1 + 1 = 0
                    i--; // and we need to skip 1 iteration
                }
                else if (first[i - 1] == '0' && second[i - 1] == '0')
                {
                    resultAdd[i - 1] = '1'; // 1 goes to the next digit and 1 + 0 or 0 + 1 = 1
                    i--; // and we need to skip 1 iteration
                }
                else
                {
                    // otherwise, you need to find at least 1 zero in two lines, otherwise all the numbers will be 1. 
                    // If we find, then the search and the saved 1 are reset and we go further from the place where the search was dropped.
                    // A stored 1 at the moment before stopping is taken into account.
                    i--;
                    for (; i >= 0; i--)
                    {
                        if (first[i] == '1' && second[i] == '1')
                        {
                            resultAdd[i] = '1'; // and 1 will go to other digits until the moment when 0 is encountered.
                        }
                        else
                        {
                            // if we founded at least one 0
                            if (first[i] == '0' && second[i] == '0')
                            {
                                resultAdd[i] = '1';     // saved 1 + 0 or 0 + saved 1 = 1
                                break;  // and then the same algorithm is repeated until we find 1 and 1 again, or we reach the beginning.
                            }
                            else
                            {
                                resultAdd[i] = '0';     // saved 1 + 1 = 0
                                break;  // and then the same algorithm is repeated until we find 1 and 1 again, or we reach the beginning.
                            }
                        }
                    }
                  
                }
            }
        }
    }
    resultAdd[strlen(first)] = '\0';

    // for situations where the stored 1 did not affect the sign bit
    if (f < 0 && s < 0)
    {
        resultAdd[0] = '1'; // because sum of negative numbers = negative number
    }
    else if (f > 0 && s > 0)
    {
        resultAdd[0] = '0'; // because sum of positive numbers = positive number
    }
    else if (f > 0 && s < 0)
    {
        if (abs(s) > f)
        {
            resultAdd[0] = '1';
        }
        else
        {
            resultAdd[0] = '0';
        }
    }
    else if (f < 0 && s > 0)
    {
        if (abs(f) > s)
        {
            resultAdd[0] = '1';
        }
        else
        {
            resultAdd[0] = '0';
        }
    }
    
    cout << "Result additional code, sum:\t" << resultAdd << endl;
    convertToForward(resultAdd);
}

char* convertToBinary(int deNumber)
{
    if (deNumber < 0)   // sign taken into account in main. We needn't to do it here
    {
        deNumber = deNumber * (-1);
    }
    char* st1 = new char[1000]; // this is not the final notation of the number, but the inverted
    int i = 0;  // index to know where to put the next element
    bool check = true;  // must be at least 1 iteration so as to know, can we further divide our number or not. Example: 125/12 = 10 (rem.5) and 10 < 12 so we need to finish calculating. 10 is critical
    while (check)
    {
        int numberOp = deNumber % 2;
        convert(st1, deNumber, i, numberOp);
        st1[i + 1] = '\0';
        if (deNumber / 2 < 2)
        {
            check = false;
            i = i + 1;
            int numberOp = deNumber / 2;   // if we can not continue the algorithm further, then we need to write down the final digit, since it is also taken into account. The finish digit is the dividend, that < 12.
                                            // but it may be such a situation that even the original decimal number was not divisible by 12. Then an extra digit 0 appears, which will then be removed.
            convert(st1, deNumber, i, numberOp);
            st1[i + 1] = '\0';
        }
        deNumber = deNumber / 2;   // if check isn't false then we need to continue ( not false if quotient >= 12, then we can devide again and this is not finish)
        i++;    // move to next position
    }
    int j = 0;  // just for finding the end of the line
    for (; st1[j] != '\0'; j++) {}   // just finding the end of the line
    if (st1[j - 1] == '0' && ('0' <= st1[j - 2] && st1[j - 2] <= '9'))  // for situations if the initial decimal number is less than 12. So as not to write in line useless 0.
    {
        st1[j - 1] = '\0';
    }

    for (int i = 0, j = strlen(st1) - 1; i <= j; i++, j--)  // for reversing line
    {
        int temp;
        temp = st1[i];
        st1[i] = st1[j];
        st1[j] = temp;
    }
    return st1;
}

int main()
{
    cout << "This program calculates the sum of binary numbers. The sum calculates in additional codes. The answer is expressed in a forward code." << endl;
    int f = 0, s = 0;
    char* st = new char[1000];   // array is using only for checking 
    cout << "Enter first number: " << endl;
    cin >> st;
    if (checkSymbols(f, st) != 0)   // for checking if two . or this is not negative value (when 2- 2-2 -)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 0;
    }
    f = int(atof(st));   // for converting char to double
    delete[] st;
    char* st1 = new char[1000];   // array is using only for checking
    cout << "Enter second number: " << endl;
    cin >> st1;
    if (checkSymbols(s, st1) != 0)   // for checking if two . or this is not negative value (when 2- 2-2 -)
    {
        cout << "You needn't to enter symbols. Only int values." << endl;
        return 0;
    }
    s = int(atof(st1));   // for converting char to double
    delete[] st1;

    char* first = convertToBinary(f);
    char* second = convertToBinary(s);
    int endF = 0;   // \0 in the first line. We  need to move one element, because need forward code.
    for (; first[endF] != '\0'; endF++){}
    first[endF + 1] = '\0';
    for (int i = endF; i > 0; i--)
    {
        first[i] = first[i - 1];
    }
    if (f >= 0)     // setting a sign bit
    {
        first[0] = '0';
    }
    else
    {
        first[0] = '1';
    }
    cout << "Forward code of the first number:\t" << first << endl;
    int endS = 0;   // \0 in the first line. We  need to move one element, because need forward code.
    for (; second[endS] != '\0'; endS++) {}
    second[endS + 1] = '\0';
    for (int i = endS; i > 0; i--)
    {
        second[i] = second[i - 1];
    }
    if (s >= 0)     // setting a sign bit
    {
        second[0] = '0';
    }
    else
    {
        second[0] = '1';
    }
    cout << "Forward code of the second number:\t" << second << endl;

    if (first[0] == '1')    // We need to convert in reverse code only if this is a negative number. If this is a positive number, then code will be the same.
    {
        for (int i = 1; first[i] != '\0'; i++)  // invert all bits except the first one, because because it defines the sign
        {
            if (first[i] == '1')
            {
                first[i] = '0';
            }
            else
            {
                first[i] = '1';
            }
        }
    }
    if (second[0] == '1')    // We need to convert in reverse code only if this is a negative number. If this is a positive number, then code will be the same.
    {
        for (int i = 1; second[i] != '\0'; i++)  // invert all bits except the first one, because it defines the sign
        {
            if (second[i] == '1')
            {
                second[i] = '0';
            }
            else
            {
                second[i] = '1';
            }
        }
    }
    cout << "\nReverse code of the first number:\t" << first << endl;
    cout << "Reverse code of the second number:\t" << second << endl;

    // to get an additional code: we invert the value of a negative number written in direct code (we do not touch the sign bit), add 1 to the resulting inversion
    if (first[0] == '1')    // only for negative number. Additional code for positive numbers the same as forward code.
    {
        if (first[endF] == '0') // adding 1
        {
            first[endF] = '1';
        }
        else
        {
            // then you need to find the first 0 by going to the sign bit
            for (int i = endF; i > 0; i--)   // adding 1
            {
                if (first[i] == '0')
                {
                    first[i] = '1';
                    break;
                }
                first[i] = '0';
            }
        }
    }
    cout << "\nAdditional code of the first number:\t" << first << endl;

    if (second[0] == '1')    // only for negative number. Additional code for positive numbers the same as forward code.
    {
        if (second[endS] == '0') // adding 1
        {
            second[endS] = '1';
        }
        else
        {
            // then you need to find the first 0 by going to the sign bit
            for (int i = endS; i > 0; i--)   // adding 1
            {
                if (second[i] == '0')
                {
                    second[i] = '1';
                    break;
                }
                second[i] = '0';
            }
        }
    }
    cout << "Additional code of the second number:\t" << second << endl;

    char fBitFirst = first[0];  // sign bit in first
    char fBitSecond = second[0];    // sign bit in second

    // If there is a different number of digits in the two's complement code, then the code with fewer digits must be padded with zeros between the sign bit and the rest. But the sign bit remains the first.
    // This is necessary because we need to sum two additional codes.
    if (strlen(first) > strlen(second)) // if first number has more bits
    {
        int size = strlen(first);
        char* secondNew = new char[size + 1];  // We need to create new array for modified code
        int move = strlen(first) - strlen(second);
        for (int j = move + 1, k = 1; j < strlen(first); j++, k++)
        {
            secondNew[j] = second[k];
            secondNew[j + 1] = '\0';
        }
        for (int j = 1; j <= move; j++)
        {
            secondNew[j] = '0';
        }
        secondNew[0] = fBitSecond;
        
        cout << "Extended additional code of the second number:\t" << secondNew << endl;

        sumCodes(first, secondNew, f, s);
        delete[] secondNew;
    }
    else if (strlen(first) < strlen(second))     // if second number has more bits
    {
        int size = strlen(second);
        char* firstNew = new char[size + 1];  // We need to create new array for modified code
        int move = strlen(second) - strlen(first);
        for (int j = move + 1, k = 1; j < strlen(second); j++, k++)
        {
            firstNew[j] = first[k];
            firstNew[j + 1] = '\0';
        }
        for (int j = 1; j <= move; j++)
        {
            firstNew[j] = '0';
        }
        firstNew[0] = fBitFirst;
        cout << "Extended additional code of the first number:\t" << firstNew << endl;

        sumCodes(firstNew, second, f, s);
        delete[] firstNew;
    }
    else
    {
        sumCodes(first, second, f, s);
    }

    delete[] first;
    delete[] second;
}