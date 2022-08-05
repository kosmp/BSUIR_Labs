// Variant 1
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin;
ofstream fout;

int n = 0;  // кол-во структур в массиве. Постепенно будет увеличиваться, если пользователь не захочет остановиться. Но если элемент удаляется и не остаётся ни одного, то все равно должен создаться хотя бы 1 нормальный элемент
int checkSymbolsPositive(int* n, char* st);
int checkNum(int* t, int zero = 1, int cond = 1);

struct Station
{
    char date[20];
    int code;
    char cityName[20];
    int time;
    int tariff;
    int tel;
    int telSub;
};

int checking(Station* forms)
{
    // формат date: 01.12.2021
    if (strlen(forms[n].date) == 10)
    {
        if (!(forms[n].date[0] > 47 && forms[n].date[0] < 58) || !(forms[n].date[1] > 47 && forms[n].date[1] < 58) || forms[n].date[2] != '.')
        {
            return 400;
        }
        if (!(forms[n].date[3] > 47 && forms[n].date[3] < 58) || !(forms[n].date[4] > 47 && forms[n].date[4] < 58) || forms[n].date[5] != '.')
        {
            return 400;
        }
        if (!(forms[n].date[6] > 47 && forms[n].date[6] < 58) || !(forms[n].date[7] > 47 && forms[n].date[7] < 58) || !(forms[n].date[8] > 47 && forms[n].date[8] < 58) || !(forms[n].date[9] > 47 && forms[n].date[9] < 58))
        {
            return 400;
        }
        if (((forms[n].date[0] - '0') * 10 + forms[n].date[1] - '0') > 31 || ((forms[n].date[0] - '0') * 10 + forms[n].date[1] - '0') == 0 || ((forms[n].date[3] - '0') * 10 + forms[n].date[4] - '0') > 12 || ((forms[n].date[3] - '0') * 10 + forms[n].date[4] - '0') == 0)    // если указали больше 31-го числа или если указали больше 12-го месяца
        {
            return 400;
        }
        if (((forms[n].date[6] - '0') * 1000 + (forms[n].date[7] - '0') * 100 + (forms[n].date[8] - '0') * 10 + (forms[n].date[9] - '0')) != 2021)   // если год указан больше возможного
        {
            return 400;
        }
    }
    else
    {
        return 400;
    }

    if (!(forms[n].cityName[0] > 64 && forms[n].cityName[0] < 91))    // строка не должна быть пустая и слово(название города) должно начинаться с заглавной буквы, но только первая буквы заглавная. 1 слово, пробелы нельзя
    {
        return 400;
    }
    else
    {
        for (int j = 1; forms[n].cityName[j] != '\0'; j++)
        {
            if (!(forms[n].cityName[j] > 96 && forms[n].cityName[j] < 123))
            {
                return 400;
            }
        }
    }
    if (forms[n].tel / 1000000 == 0 || forms[n].tel >= 10000000 || forms[n].telSub / 1000000 == 0 || forms[n].telSub >= 10000000 || forms[n].code / 100 == 0 || forms[n].code >= 1000)
    {
        return 400;
    }
    return 0;
}

int checkSymbolsPositive(int* n, char* st, bool zero)
{
    int f = 0;
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            //printf("you have entered incorrect symbol\n");
            return 401;
        }
        f *= 10;
        f += st[i] - '0';
    }
    *n = f;
    if (zero)
    {
        if ((*n) == 0)
        {
            //printf("You enterted 0. Error.\n");
            return 401;
        }
    }
    delete[] st;
    return 0;
}

int checkNum(int* t, int zero, int cond)
{
    char* st = new char[100];   // array is using only for checking 
    if (cond == 1)
    {
        fin >> st;
    }
    else
    {
        cin >> st;
    }

    if (checkSymbolsPositive(t, st, zero) != 0)
    {
        //printf("You needn't to enter symbols or 0. Only int values.\n");
        return 400;
    }
    else
    {
        return 0;
    }
}

void change(Station* forms, int def)
{
    if (def == 1)
    {
        cout << "Code was converted to 404. Can't be 0." << endl;
        forms[n].code = 404;  // так сказать, универсальный код, если пользователь ввёл 0
    }
    if (def == 2)
    {
        cout << "Time was converted to 1000. Must be <= 1000 and > 0." << endl;
        forms[n].time = 1000;
    }
    if (def == 3)
    {
        cout << "Tariff was converted to 100. Must be <= 100 and > 0." << endl;
        forms[n].tariff = 100;
    }
}

void show(Station* forms)
{
    for (int i = 0; i < n; i++)
    {
        fout << "\nForm number: " << i << ". It's a number of city in the array(counting from 0)." << endl;
        fout << "Date: ";
        fout << forms[i].date << endl;
        fout << "Code: ";
        fout << forms[i].code << endl;
        fout << "CityName: ";
        fout << forms[i].cityName << endl;
        fout << "Tariff: ";
        fout << forms[i].tariff << endl;
        fout << "Tel: ";
        fout << forms[i].tel << endl;
        fout << "TelSub: ";
        fout << forms[i].telSub << endl;
        fout << "Time of conversation in this city: " << forms[i].time << endl;
        fout << "The sum(cost for conversation): " << forms[i].time * forms[i].tariff << endl;
    }
}

Station* add(Station* objects)
{
    if (n == 0)
    {
        objects = (Station*)calloc(n + 1, sizeof(Station));
        return objects;
    }
    else
    {
        cout << "Adding a city(an element of the array)..." << endl;
        Station* tempObjects = (Station*)calloc(n + 1, sizeof(Station));

        for (int i = 0; i < n; i++)
        {
            tempObjects[i] = objects[i]; // копируем во временный объект
        }
        free(objects);
        return tempObjects;
    }
}

Station* remove(Station* objects)
{
    cout << "Console: Client was removed.\n";

    Station* tempObjects = (Station*)calloc(n, sizeof(Station));
    for (int i = 0; i < n; i++)
    {
        tempObjects[i] = objects[i]; // копируем во временный объект
    }
    free(objects);

    return tempObjects;
}

Station* init()
{
    Station* arr = (Station*)calloc(n, sizeof(Station));
    int x;
    bool firstIter = true;
    do
    {
        cout << "You can enter at least 1 city." << endl;
        cout << "Must be at least 1 correct form. If not, entering must be continued" << endl;
        arr = add(arr);

        cout << "Enter date (example: 01.12.2021)(only 2021): " << endl;
        if (n == 0 && firstIter)
        {
            fin >> arr[n].date;     // проверится дальше. Если не тот формат, то удаление элемента.
        }
        else
        {
            cin >> arr[n].date;
        }

        cout << ("Enter code(3 digits): \n");
        if (n == 0 && firstIter)
        {
            if (checkNum(&arr[n].code, 0) != 0)
            {
                arr[n].code = 0;
            }
        }
        else
        {
            if (checkNum(&arr[n].code, 0, 0) != 0)
            {
                arr[n].code = 0;
            }
        }

        if (arr[n].code == 0)
        {
            // Если после неверного ввода(присваивается 0) или по желанию пользователя code = 0, то изменить значение на другое(универсальное)
            change(arr, 1);
        }

        cout << "Enter cityName: " << endl;
        if (n == 0 && firstIter)
        {
            fin >> arr[n].cityName;
        }
        else
        {
            cin >> arr[n].cityName;
        }


        cout << "Enter time(<=1000)(digits): \n";
        if (n == 0 && firstIter)
        {
            if (checkNum(&arr[n].time, 0) != 0)
            {
                arr[n].time = 0;
            }
        }
        else
        {
            if (checkNum(&arr[n].time, 0, 0) != 0)
            {
                arr[n].time = 0;
            }
        }

        if (arr[n].time > 1000 || arr[n].time == 0)
        {
            // Если после неверного ввода(присваивается 0) или по желанию пользователя time = 0, то изменить значение на другое(максимальное). Или если введено число > 1000
            change(arr, 2);
        }

        cout << "Enter tariff (<=100 and >0)(digits): \n";
        if (n == 0 && firstIter)
        {
            if (checkNum(&arr[n].tariff, 0) != 0)
            {
                arr[n].tariff = 0;
            }
        }
        else
        {
            if (checkNum(&arr[n].tariff, 0, 0) != 0)
            {
                arr[n].tariff = 0;
            }
        }

        if (arr[n].tariff == 0 || arr[n].tariff > 100)
        {
            // Если после неверного ввода(присваивается 0) или по желанию пользователя tariff = 0, то изменить значение на другое(максимальное). Или если введено число > 100
            change(arr, 3);
        }

        cout << "Enter tel(7 digits): \n";
        if (n == 0 && firstIter)
        {
            if (checkNum(&arr[n].tel, 0) != 0)
            {
                arr[n].tel = 0;     // и, соответсвенно, не пройдёт общую проверку в checling(должно быть 7 цифр)
            }
        }
        else
        {
            if (checkNum(&arr[n].tel, 0, 0) != 0)
            {
                arr[n].tel = 0;     // и, соответсвенно, не пройдёт общую проверку в checling(должно быть 7 цифр)
            }
        }


        cout << "Enter telSub(7 digits): \n";
        if (n == 0 && firstIter)
        {
            if (checkNum(&arr[n].telSub, 0) != 0)
            {
                arr[n].telSub = 0;     // и, соответсвенно, не пройдёт общую проверку в checling(должно быть 7 цифр)
            }
        }
        else
        {
            if (checkNum(&arr[n].telSub, 0, 0) != 0)
            {
                arr[n].telSub = 0;     // и, соответсвенно, не пройдёт общую проверку в checling(должно быть 7 цифр)
            }
        }

        if (checking(arr) != 0)
        {
            // Если пользователь ввёл дату не в нужном формате или название города неправильно, то удалить элемент структуры
            cout << "Deleting..." << endl;
            arr = remove(arr);
            n--;    // т.к. дальше нужно будет вводить тот же элемент массива(тот же номер элемента), но данные клиента будут другие
        }
        int q;
        do
        {
            cout << "Do you need to add one more cities? Yes - 1, No - 0." << endl;
            q = checkNum(&x, 0, 0);
            if (q != 0)
            {
                cout << "You needn't to enter symbols.\n";
            }
        } while (q != 0 || (x != 0 && x != 1));
        firstIter = false;
        n++;
    } while (x != 0 || n == 0);     // Нельзя допускать удаления единственного элемента без создания нового. Если n = 0. Т.к. если бы единственный элемент не удалился, то было бы n = 1 на этом шаге

    return arr;
}

int main()
{
    // считывает данные из файла, а потом, если нужно, вводим ещё вручную. Вывод осуществляется в файл.
    fin.open("inputFile.txt");
    fout.open("outputFile.txt");
    if (fin.is_open() || fout.is_open())
    {
        Station* station = init();
        show(station);

        free(station);
    }
    fin.close();
    fout.close();
}