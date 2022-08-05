#include <iostream>
#include <string>
using namespace std;

int maxRes = 0;

void checkSub(int left, int right, string S)
{
    if ((right - left + 1) % 2 == 0)  // number of elements in this limits
    {
        bool check = false;
        int middle = (right + left) / 2 + 1;
        for (int i = middle - 1, j = middle; i >= left && j <= right; i--, j++)
        {
            if (S[i] != S[j])
            {
                check = true;
                if (maxRes < (j - i + 1))
                {
                    maxRes = j - i + 1;
                }
            }
            if (check)  // if at least one pair of not the same is found in a substring, then the whole substring will no longer be a palindrome
            {
                if (maxRes < (right - left + 1))
                {
                    maxRes = right - left + 1;
                }
            }
        }
    }
    else
    {
        bool check = false;
        int middle = (right + left) / 2;
        for (int i = middle - 1, j = middle + 1; i >= left && j <= right; i--, j++)
        {
            if (S[i] != S[j])
            {
                check = true;
                if (maxRes < (j - i + 1))
                {
                    maxRes = j - i + 1;
                }
            }
            if (check)    // if at least one pair of not the same is found in a substring, then the whole substring will no longer be a palindrome
            {
                if (maxRes < (right - left + 1))
                {
                    maxRes = right - left + 1;
                }
            }
        }
    }
}

int main()
{
    cout << "In a given string S, find the longest substring that is not a palindrome." << endl;
    string S;
    cout << "Let's enter line S. Only latin lowercase letters.(1 <= size <= 105)" << endl;
    cin >> S;
    int z = 0;
    for (; S[z] != '\0'; z++){}
    if (S[z] == '\0' && (z == 1 || z >= 106))
    {
        cout << "Incorrect size" << endl;
        return 0;
    }
    for (int i = 0; S[i] != '\0'; i++)
    {
        if (!(S[i] >= 97 && S[i] <= 122))
        {
            cout << "Incorrect enter." << endl;
            return 0;
        }
    }

    for (int i = 0; i < S.length() - 1; i++) // substring includes S[i]. We need to check all varients so as not to lose any substring.
    {
        for (int j = i + 1; j <= S.length() - 1; j++)  // middle between i and i - 1
        {
            checkSub(i, j, S);
        }
    }

    if (maxRes != 0)
    {
        cout << "Length of the maximum non-palindrome: " << maxRes << endl;
    }
    else
    {
        cout << " -1" << endl;
    }
}