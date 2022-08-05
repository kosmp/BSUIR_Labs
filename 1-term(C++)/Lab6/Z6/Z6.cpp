#include <iostream>
#include <string>
using namespace std;

long int calculatingFact(int n)
{
    long int fact = 1;
    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }
    return fact;
}

int main()
{
    cout << "A program that displays the number of different anagrams that can be obtained from this word." << endl;
    cout << "Word contains only letters and must be real. Which exists or it's useless to calculate and it won't be a word, it will be a set of letters." << endl;
    string st;
    st.reserve(14);
    cout << "Let's enter a word. Max 14 letters." << endl;
    getline(cin, st);
    if (st.length() > 14)
    {
        cout << "Your word is too big. Max 14 letters." << endl;
        return 0;
    }
    for (int i = 0; st[i] != '\0'; i++)
    {
        if ((st[i] > 90 && st[i] < 97) || st[i] < 65 || st[i] > 122)
        {
            cout << "You need to enter a word. Only letters." << endl;
            return 0;
        }
    }

    char* saveDupl = new char [10];   // array for containing duplicate letters
    int* countDupl = new int [10];    // array for containing how many times this letter was duplicated
    saveDupl[0] = '\0';
    for (int i = 0; i < 10; i++)
    {
        countDupl[i] = 0;
    }
    for (int i = 0; i <= st.length(); i++)
    {
        for (int j = i + 1; j <= st.length() - 1; j++)
        {
            if (st[i] == st[j] && (st[i] != ' ' && st[j] != ' '))
            {
                for (int k = 0; k < 10; k++) // if founded duplicate we need to check was this letter earlier as duplicate or not. If not we need to save it in saveDupl
                {
                    if (saveDupl[k] == st[j])
                    {
                        countDupl[k] += 1;
                        st[j] = ' ';    // so as not to check and use again this element
                        break;
                    }
                    else
                    {
                        int p = 0;
                        for (; saveDupl[p] != '\0'; p++){}  // Then you need to put a new element after the last in the array
                        saveDupl[p] = st[j];
                        saveDupl[p + 1] = '\0';
                        countDupl[p] += 2;
                        st[j] = ' ';    // so as not to check and use again this element
                        break;
                    }
                }
            }
        }
    }

    bool checkDupl = false;     // check if we have any duplicates
    for (int i = 0; countDupl[i] != '\0'; i++)
    {
        if (countDupl[i] != 0) checkDupl = true;
    }
    if (checkDupl)
    {
        long int numerator;
        long int denominator = 1;
        numerator = calculatingFact(st.length());
        for (int i = 0; countDupl[i] != '\0'; i++)
        {
            denominator *= calculatingFact(countDupl[i]);
        }
        cout << endl << "Number of different anagrams: " << numerator / denominator;
    }
    else
    {
        long int fact;
        fact = calculatingFact(st.length());
        cout << endl << "Number of different anagrams: " << fact;
    }

    delete[] saveDupl;
    delete[] countDupl;
}    
    //for (int i = 0; i < 10; i++)
    //{
    //    cout << saveDupl[i] << "\t";
    //}  
    //cout << endl;
    //for (int i = 0; i < 10; i++)
    //{
    //    cout << countDupl[i] << "\t";
    //}