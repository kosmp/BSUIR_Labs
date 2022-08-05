#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{ 
    ifstream fin;
    fin.open("inputFile.txt");
    ofstream fout;
    fout.open("outputFile.txt");
    fout << "First, the program removes the four letters C, Q, W and X. Instead of c, before the letters e, i, y, you will need to write the letter s, and in other cases, the letter k." << endl;
    fout << "Instead of the letter q, you will need to write the letter k, instead of the combination qu - kv, instead of x - ks, and instead of w - v." << endl;
    fout << "Secondly, the combination of letters ph will be written as f, youand oo - as u, ee - as i, th - as z." << endl;
    fout << "In addition, all double consonants (including those formed after substitutions) will become single." << endl;
    fout << "If the first letter of the letter combination to be replaced was uppercase, then the first letter of the replacement must also be uppercase." << endl;
    fout << "The first letter in the replacements x --> ks, qu --> kv must always be lowercase." << endl;
    while (!fin.eof())
    {
        char* st1 = new char[100];
        char* st2 = new char[100];
        fin.getline(st1, 100);
        for (int g = 0; g < 100; g++)
        {
            st2[g] = st1[g];
        }
        for (int i = 0; st1[i] != '\0'; i++)
        {
            if (st1[i] == 67)
            {
                cout << "C doesn't exist" << endl;
                return 0;
            }
            else if (st1[i] == 81)
            {
                cout << "Q doesn't exist" << endl;
                return 0;
            }
            else if (st1[i] == 87)
            {
                cout << "W doesn't exist" << endl;
                return 0;
            }
            else if (st1[i] == 88)
            {
                cout << "X doesn't exist" << endl;
                return 0;
            }

            if ((st1[i + 1] == 'e' || st1[i + 1] == 'i' || st1[i + 1] == 'y' || st1[i + 1] == 'E' || st1[i + 1] == 'I' || st1[i + 1] == 'Y') && st1[i] == 'c')
            {
                if (st1[i + 1] == 'E' || st1[i + 1] == 'I' || st1[i + 1] == 'Y')
                {
                    st2[i] = 'S';
                }
                else
                {
                    st2[i] = 's';
                }
            }
            else if (st1[i] == 'c' && ((st1[i + 1] != 'e' && st1[i + 1] != 'i' && st1[i + 1] != 'y') || st1[i + 1] != 'E' && st1[i + 1] != 'I' && st1[i + 1] != 'Y'))
            {
                st2[i] = 'k';
            }

            if (st1[i] == 'w')
            {
                st2[i] = 'v';
            }

            if ((st1[i] == 'y' || st1[i] == 'Y') && st1[i + 1] == 'o' && st1[i + 2] == 'u')
            {
                bool checkEnd = true;
                int j = i + 1;
                for (; checkEnd; j++)
                {
                    if (st1[j + 2] == '\0')
                    {
                        st1[j] = '\0';
                        checkEnd = false;
                    }
                    else
                    {
                        st1[j] = st1[j + 2];
                    }
                }
                if (st1[i] == 'Y')
                {
                    st1[i] = 'U';
                }
                else
                {
                    st1[i] = 'u';
                }
                for (int k = i; k < j; k++)
                {
                    st2[k] = st1[k];
                }
            }
            if ((st1[i] == 'o' || st1[i] == 'O') && st1[i + 1] == 'o')
            {
                bool checkEnd = true;
                int j = i + 1;
                for (; checkEnd; j++)
                {
                    if (st1[j + 1] == '\0')
                    {
                        st1[j] = '\0';
                        checkEnd = false;
                    }
                    else
                    {
                        st1[j] = st1[j + 1];
                    }
                }
                if (st1[i] == 'O')
                {
                    st1[i] = 'U';
                }
                else
                {
                    st1[i] = 'u';
                }
                for (int k = i; k < j; k++)
                {
                    st2[k] = st1[k];
                }

            }

            if (st1[i] == 'q' && st1[i + 1] == 'u')
            {
                st2[i] = 'k';
                st2[i + 1] = 'v';
            }
            else if (st1[i] == 'q')
            {
                st2[i] = 'k';
            }

            if ((st1[i] == 'p' || st1[i] == 'P') && st1[i + 1] == 'h')
            {
                bool checkEnd = true;
                int j = i + 1;
                for (; checkEnd; j++)
                {
                    if (st1[j + 1] == '\0')
                    {
                        st1[j] = '\0';
                        checkEnd = false;
                    }
                    else
                    {
                        st1[j] = st1[j + 1];
                    }
                }
                if (st1[i] == 'P')
                {
                    st1[i] = 'F';
                }
                else
                {
                    st1[i] = 'f';
                }
                for (int k = i; k < j; k++)
                {
                    st2[k] = st1[k];
                }
            }

            if (st1[i] == 'x')
            {
                st2[i] = 'k';
                int j = i + 1;
                for (; st1[j] != '\0'; j++)
                {
                    st2[j + 1] = st1[j];
                }
                st2[j + 1] = st1[j];
                st2[i + 1] = 's';
            }

            if ((st1[i] == 't' || st1[i] == 'T') && st1[i + 1] == 'h')
            {
                bool checkEnd = true;
                int j = i + 1;
                for (; checkEnd; j++)
                {
                    if (st1[j + 1] == '\0')
                    {
                        st1[j] = '\0';
                        checkEnd = false;
                    }
                    else
                    {
                        st1[j] = st1[j + 1];
                    }
                }
                if (st1[i] == 'T')
                {
                    st1[i] = 'Z';
                }
                else
                {
                    st1[i] = 'z';
                }
                for (int k = i; k < j; k++)
                {
                    st2[k] = st1[k];
                }
            }

            if ((st1[i] == 'e' || st1[i] == 'E') && st1[i + 1] == 'e')
            {
                bool checkEnd = true;
                int j = i + 1;
                for (; checkEnd; j++)
                {
                    if (st1[j + 1] == '\0')
                    {
                        st1[j] = '\0';
                        checkEnd = false;
                    }
                    else
                    {
                        st1[j] = st1[j + 1];
                    }
                }
                if (st1[i] == 'E')
                {
                    st1[i] = 'I';
                }
                else
                {
                    st1[i] = 'i';
                }
                for (int k = i; k < j; k++)
                {
                    st2[k] = st1[k];
                }
            }

            for (int k = 0; k < 100; k++)   // update st1
            {
                st1[k] = st2[k];
            }
        }
        for (int j = 0; st2[j] != '\0'; j++)    // checking full line, so as to remove duplicates
        {
            if (st2[j] == st2[j + 1])   // if founded duplicates we need to shift line by one.
            {
                for (int k = j + 1; k < 100; k++)
                {
                    if (k + 1 <= 100)
                    {
                        st2[k] = st2[k + 1];
                    }
                }
            }
        }
        fout << endl;
        fout << st2;

        delete[] st1;
        delete[] st2;
    }
    fin.close();
    fout.close();
}