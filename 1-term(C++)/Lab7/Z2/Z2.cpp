#include <iostream>
using namespace std;

int main()
{
    cout << "This program will translate a number written in a forward code into a reverse code." << endl;
    cout << "Enter the number in a forward code. Only 0 or 1." << endl;
    char* st = new char[256];
    cin.getline(st, 256);
    for (int i = 0; st[i] != '\0'; i++)    // check enter. We can enter only binary notation of a number according to the condition.
    {
        if (st[i] != '0' && st[i] != '1')
        {
            cout << "You can enter only 0 or 1. Only binary notation of a number" << endl;
            return 0;
        }
    }

    if (st[0] == '1')   // We need to convert in reverse code only negative numbers. It will be negative number if first bit = 1. Reverse code is the same as forward code for positive numbers.
    {
        for (int i = 1; i < strlen(st); i++)    // so we need to reverse all bits except first(main) bit. In reverse code numbers can also be positiv or negative. first 1 - negative, first 0 - positive
        {
            if (st[i] == '1')
            {
                st[i] = '0';
            }
            else
            {
                st[i] = '1';
            }
        }
    }
    cout << "Reverse code of our forward code: " << st;
    
}