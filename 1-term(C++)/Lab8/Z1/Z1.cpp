// Variant 1
#include <iostream>
#include <cstring>
using namespace std;

int n;     // n - стартовый размер массива. Если в нём не найдём клиента с 5%-й скидкой, то нужно увеличивать размер массива на 1 пока не найдём

struct Clients
{
    char name[100];
    char surname[100];
    char patronymic[100];
    char address[100];
    int discount = 0;
};

int checkSymbolsPositive(int* n, char* st)
{
    int f = 0;
    for (int i = 0; i < strlen(st); i++)
    {
        if (st[i] < '0' || st[i] > '9')
        {
            printf("you have entered incorrect symbol\n");
            return 401;
        }
        f *= 10;
        f += st[i] - '0';
    }
    *n = f;
    if ((*n) == 0)
    {
        printf("You enterted 0. Error.\n");
        return 401;
    }
    delete[] st;
    return 0;
}

int checkNum(int* t)
{
    char* st = new char[100];   // array is using only for checking 
    cin.get(st, 100);
    if (checkSymbolsPositive(t, st) != 0)
    {
        printf("You needn't to enter symbols or 0. Only int values.\n");
        return 400;
    }
    else
    {
        return 0;
    }
}

bool checkDiscount(Clients* objects, int i)    // функцию просмотра содержимого
{
    if (objects[i].discount == 5)  // если 5-ти процентная скидка есть хотя бы у одного клиента, который прошёл проверки на ввод, то в дальнейшем не нужно дополнять массив
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkData(Clients* objects, int i)  // функция просмотра содержимого динамического массива структур. Проверка правильности ввода клиентом
{
    // не пройдут тест два пробела и более после слова, пробелы перед словом(своеобразное выравнивание) и любые пробелы внутри строки(пропускает только 1 слово). Тест проходят только слова с первой заглавной буквой(только одна большая).
    if (!(objects[i].name[0] > 64 && objects[i].name[0] < 91))
    {
        return false;
    }
    for (int j = 1; objects[i].name[j] != '\0'; j++)
    {
        if (objects[i].name[j] == ' ' && objects[i].name[j + 1] != '\0')
        {
            return false;
        }
        if (!(objects[i].name[j] > 96 && objects[i].name[j] < 123) && objects[i].name[j] != ' ')
        {
            return false;
        }
    }
    if (!(objects[i].surname[0] > 64 && objects[i].surname[0] < 91))
    {
        return false;
    }
    for (int j = 1; objects[i].surname[j] != '\0'; j++)
    {
        if (objects[i].surname[j] == ' ' && objects[i].surname[j + 1] != '\0')
        {
            return false;
        }
        if (!(objects[i].surname[j] > 96 && objects[i].surname[j] < 123) && objects[i].surname[j] != ' ')
        {
            return false;
        }
    }
    if (!(objects[i].patronymic[0] > 64 && objects[i].patronymic[0] < 91))
    {
        return false;
    }
    for (int j = 1; objects[i].patronymic[j] != '\0'; j++)
    {
        if (objects[i].patronymic[j] == ' ' && objects[i].patronymic[j + 1] != '\0')
        {
            return false;
        }
        if (!(objects[i].patronymic[j] > 96 && objects[i].patronymic[j] < 123) && objects[i].patronymic[j] != ' ')
        {
            return false;
        }
    }
    return true;
}

void changeData(Clients* objects, int i)     // функция изменения
{
    strcpy_s(objects[i].name, "VoidName");
    strcpy_s(objects[i].surname, "VoidSurname");
    strcpy_s(objects[i].patronymic, "Voidpatronymic");
    strcpy_s(objects[i].address, "VoidAddress");
}

void sort(Clients* x)   // сортировка вставкой по возрастанию. Сортировка по алфавиту по первой букве name.
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        Clients temp = x[i];
        for (j = i - 1; j >= 0 && x[j].name[0] > temp.name[0]; j--)
        {
            x[j + 1] = x[j];
        }
        x[j + 1] = temp;
    }
}

void searchAndShow(Clients* x)   // функция поиска и вывода на экран структуры (структур) с заданным значением элемента
{
    printf("\nClients with discount = 5:\n");
    for (int i = 0; i < n; i++)
    {
        if (x[i].discount == 5)
        {
            printf("%s\n", x[i].name);
            printf("%s\n", x[i].surname);
            printf("%s\n", x[i].patronymic);
            printf("%s\n", x[i].address);
            printf("%i\n", x[i].discount);
            printf("\n");
        }
    }
    printf("--------------------------------------------------------\n");
}

void show(Clients* x)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", x[i].name);
        printf("%s\n", x[i].surname);
        printf("%s\n", x[i].patronymic);
        printf("%s\n", x[i].address);
        printf("%i\n", x[i].discount);
        printf("\n");
    }
    printf("--------------------------------------------------------\n");
}

Clients* addClient(Clients* objects, const int amount)
{
    printf("Console: Adding a client...\n");
    Clients* tempObjects = new Clients[amount + 1];
    
    for (int i = 0; i < amount; i++)
    {
        tempObjects[i] = objects[i]; // копируем во временный объект
    }
    delete[] objects;

    return tempObjects;
}

Clients* removeClient(Clients* objects, const int amount)
{
    printf("Console: Client was removed.\n");

    if ((amount - 1) > 0)
    {
        Clients* tempObjects = new Clients[amount];
        for (int i = 0; i < amount; i++)
        {
            tempObjects[i] = objects[i]; // копируем во временный объект
        }
        delete[] objects;
        return tempObjects;
    }
    else
    {
        return objects;
    }
}

Clients* formatting()     // функция форматирования 
{
	int q;
    do
    {
        printf("Enter number of structs(clients): \n");
        q = checkNum(&n);
    } while (q != 0);

	Clients* arr = new Clients[n];
    bool found = false;     // true если нашли в заданном массиве человека с 5%-й скидкой
    for (int i = 0; i < n; i++)
    {
        // Ввод хотя бы одного поля
        cin.ignore(100, '\n');
        printf("\nEnter Name(with the capital letter and 1 word):\n");
        cin.getline(arr[i].name, 100, '\n');
        printf("Enter SurName(with the capital letter and 1 word):\n");
        cin.getline(arr[i].surname, 100);
        printf("Enter Patronymic(with the capital letter and 1 word):\n");
        cin.getline(arr[i].patronymic, 100);
        printf("Enter Address:\n");
        cin.getline(arr[i].address, 100);
        printf("Enter Discount: \n");
        int q = checkNum(&arr[i].discount);
        if (q != 0)
        {
            arr[i].discount = 0;    // Если введено не число, то просто замена на 0.
        }
        bool clientRemoved = false;
        if (arr[i].discount >= 0 && arr[i].surname[0] == '\0' && arr[i].name[0] == '\0' && arr[i].patronymic[0] == '\0' && arr[i].address[0] == '\0')
        {
            // если пользователь ввёл только discount, то всё остальное заполнить автоматически. Нужна функция изменения
            changeData(arr, i);
        }
        else if ((arr[i].discount < 0 || arr[i].discount >= 100) || (arr[i].discount >= 0 && (arr[i].name[0] == '\0' || arr[i].surname[0] == '\0' || arr[i].patronymic[0] == '\0' || arr[i].address[0] == '\0')))    // Если ввёл обязательную discount >= 100 или < 0 или если ввёл discount и ещё что-то, то не всё остальное, то тогда удалить клиента.
        {
            // тогда удалить 1 элемент из массива. Т.е. 1 клиента
            arr = removeClient(arr, n);
            clientRemoved = true;
            printf("Console: You entered smth incorrect. Try again.\n");
            i--;    // т.к. дальше нужно будет вводить тот же элемент массива(тот же номер элемента), но данные клиента будут другие
        }
        bool check = true;  // проверка на корректность ввода
        if (clientRemoved == false)
        {
            check = checkData(arr, i);
        }
        if (check == false)
        {
            // Клиент ввёл что-то некорректно, удалим его. В том числе, если name, surname или patronymic начинались с маленькой буквы.
            printf("Console: Deleting a client... You entered smth incorrect. Try again.\n");
            arr = removeClient(arr, n);
            clientRemoved = true;
            i--;    // т.к. дальше нужно будет вводить тот же элемент массива(тот же номер элемента), но данные клиента будут другие
        }

        if (checkDiscount(arr, i) == true && clientRemoved != true)    // ввод до появления структуры с заданным признаком (5%-я скидка)
        {
            found = true;
        }
    }
    if (found == false)
    {
        do
        {
            printf("\nYou need to continue entering, because in the starting array wasn't found a client with 5 discount. So you need to increase the number of structs.\n");
            arr = addClient(arr, n);
            // Ввод хотя бы одного поля
            cin.ignore(100, '\n');
            printf("Enter Name(with the capital letter and 1 word):\n");
            cin.getline(arr[n].name, 100, '\n');
            printf("Enter SurName(with the capital letter and 1 word):\n");
            cin.getline(arr[n].surname, 100);
            printf("Enter Patronymic(with the capital letter and 1 word):\n");
            cin.getline(arr[n].patronymic, 100);
            printf("Enter Address:\n");
            cin.getline(arr[n].address, 100);
            printf("Enter Discount: \n");
            int q = checkNum(&arr[n].discount);
            if (q != 0)
            {
                arr[n].discount = 0;    // Если введено не число, то просто замена на 0.
            }
            bool clientRemoved = false;
            if (arr[n].discount >= 0 && arr[n].surname[0] == '\0' && arr[n].name[0] == '\0' && arr[n].patronymic[0] == '\0' && arr[n].address[0] == '\0')
            {
                // если пользователь ввёл только discount, то всё остальное заполнить автоматически. Нужна функция изменения
                changeData(arr, n);
            }
            else if ((arr[n].discount < 0 || arr[n].discount >= 100) || (arr[n].discount >= 0 && (arr[n].name[0] == '\0' || arr[n].surname[0] == '\0' || arr[n].patronymic[0] == '\0' || arr[n].address[0] == '\0')))    // Если ввёл обязательную discount >= 100 или < 0 или если ввёл discount и ещё что-то, то не всё остальное, то тогда удалить клиента.
            {
                // тогда удалить 1 элемент из массива. Т.е. 1 клиента
                arr = removeClient(arr, n);
                clientRemoved = true;
                printf("Console: You entered smth incorrect. Try again.\n");
                n--;    // т.к. дальше нужно будет вводить тот же элемент массива(тот же номер элемента), но данные клиента будут другие
            }
            bool check = true;  // проверка на корректность ввода
            if (clientRemoved == false)
            {
                check = checkData(arr, n);
            }
            if (check == false)
            {
                // Клиент ввёл что-то некорректно, удалим его. В том числе, если name, surname или patronymic начинались с маленькой буквы.
                printf("Console: Deleting a client... You entered smth incorrect. Try again.\n");
                arr = removeClient(arr, n);
                clientRemoved = true;
                n--;    // т.к. дальше нужно будет вводить тот же элемент массива(тот же номер элемента), но данные клиента будут другие
            }
            n++;
        } while (checkDiscount(arr, n - 1) == false);    // дополнение массива, пока не появится структура с заданным признаком (5%-я скидка)
    }
    return arr;
}

int main()
{
    printf("The store has a list of regular customers,\n");
    printf("which includes the name, home address of the buyer and\n");
    printf("the amount of the discount provided.\n");
    printf("Display all buyers with 5 discount (sort by insertion in ascending order).\n");
    Clients* arr = formatting();
    printf("\nShowing start array of clients(with changes):\n");
    show(arr);
    searchAndShow(arr);
    sort(arr);
    printf("\nSorted start array of clients(with changes):\n");
    show(arr);
    delete[] arr;
}