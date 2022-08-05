#include <iostream>
#include <string>
using namespace std;

int checkSymbolsPositive(int& n, string st)   // function for check if we entered a number or or other symbols
{
    int f = 0;
    for (int i = 0; i < st.length(); i++)
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
    if (n == 0)
    {
        cout << "You enterted 0. Error." << endl;
        return 401;
    }
    return 0;
}

int enterNumber(int& n)
{
    string st;   // array is using only for checking 
    cout << "Enter a number in the arabic system: ";
    getline(cin, st);
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

int main()
{
    cout << "This program converts a number from Arabic to Roman." << endl;
    int n, q;   // n = our number, q just for checking n
    do
    {
        q = enterNumber(n);    // checking enter
    } while (n >= 4000 || q != 0);   // n < 4000 because if 4000+ then we need to use dashes and we cann't do it beautiful in console, but without dashes it's not beautiful

    char* roman = new char[100];
    int thous = n / 1000;   // thousand rank
    int hund = (n % 1000) / 100;    // hundreds rank
    int doz = ((n % 1000) % 100) / 10;  // dozens rank
    int uni = ((n % 1000) % 100) % 10;  // units rank
    // 1 - I, 5 - V, 10 - X, 50 - L, 100 - C, 500 - D, 1000 - M. 
    // If from 0 to 3 in a rank, then just repeat, If 5 in a rank then only one of this letters, if from 6 to 8 in a rank, then one of this letter + repeat of another letter, if 9 in a rank, then one letter in front of the other (like IX) 

    for (int i = 0; i < thous; i++) // can be max 3 M because further, for writing, we need to use dashes, which cannot be implemented beautifully in the console.
    {
        roman[i] = 'M';
    }
    int lastInd = thous;    // first index after last filled index. Index for the next inserting

    if (hund == 5)     // if number of hundreds = 5, then only D
    {
        roman[thous] = 'D';
        lastInd = thous + 1;
    }
    else if (hund == 4)    // if number of hundreds = 4, then CD (500-100=400)
    {
        roman[thous] = 'C';
        roman[thous + 1] = 'D';
        lastInd = thous + 2;
    }
    else if (hund > 0 && hund < 4)
    {
        for (int i = thous, counter = 1; counter <= hund; i++, counter++)     // if number of hundreds 0 < hundreds < 4 then 1 - C, 2 or 3 
        {
            roman[i] = 'C';
        }
        lastInd = thous + hund;
    }
    else if (hund > 5 && hund < 9)    // if number of hundreads 5 < hundreds < 9, then one D and (hund - 5) times C
    {
        roman[thous] = 'D';
        lastInd = thous + 1;
        for (int i = thous + 1, counter = 1; counter <= hund - 5; i++, counter++)
        {
            roman[i] = 'C';
            lastInd++;
        }
    }
    else if (hund == 9)    // if number of hundreds = 9 then CM (1000-100)
    {
        roman[thous] = 'C';
        roman[thous + 1] = 'M';
        lastInd = thous + 2;
    }
    roman[lastInd] = '\0';
    
    // for dozens almost the same algorithm as for hundreds
    if (doz == 5)
    {
        roman[lastInd] = 'L';
        lastInd++;
    }
    else if (doz == 4)
    {
        roman[lastInd] = 'X';
        roman[lastInd + 1] = 'L';
        lastInd += 2;
    }
    else if (doz > 0 && doz < 4) 
    {
        for (int i = lastInd, counter = 1; counter <= doz; i++, counter++)     // if number of dozens 0 < dozens < 4 then 1 - X, 2 or 3 
        {
            roman[i] = 'X';
            lastInd++;
        }
    }
    else if (doz > 5 && doz < 9)
    {
        roman[lastInd] = 'L';
        lastInd++;
        for (int i = lastInd, counter = 1; counter <= doz - 5; i++, counter++)
        {
            roman[i] = 'X';
            lastInd++;
        }
    }
    else if (doz == 9)
    {
        roman[lastInd] = 'X';
        roman[lastInd + 1] = 'C';
        lastInd += 2;
    }
    roman[lastInd] = '\0';

    // for units almost the same algorithm as for dozens
    if (uni == 5) 
    {
        roman[lastInd] = 'V';
        lastInd++;
    }
    else if (uni == 4)
    {
        roman[lastInd] = 'I';
        roman[lastInd + 1] = 'V';
        lastInd += 2;
    }
    else if (uni > 0 && uni < 4)
    {
        for (int i = lastInd, counter = 1; counter <= uni; i++, counter++)
        {
            roman[i] = 'I';
            lastInd++;
        }
    }
    else if (uni > 5 && uni < 9)
    {
        roman[lastInd] = 'V';
        lastInd++;
        for (int i = lastInd, counter = 1; counter <= uni - 5; i++, counter++)
        {
            roman[i] = 'I';
            lastInd++;
        }
    }
    else if (uni == 9)
    {
        roman[lastInd] = 'I';
        roman[lastInd + 1] = 'X';
        lastInd += 2;
    }
    roman[lastInd] = '\0';
    cout << "Number converted to roman: " << roman;
    
    delete[] roman;
}