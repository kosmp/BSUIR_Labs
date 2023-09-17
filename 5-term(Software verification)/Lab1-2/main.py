import random, builtins


def task_1(random_num):
    return 'Hello, world!\nAndhiagain!\n' + '!' * random_num


def task_2():
    list_of_people = []
    while True:
        name = input('Enter name: ')
        surname = input('Enter surname: ')

        try:
            age = int(input('Enter age: '))
            if age <= 0:
                print('Age must be a positive integer. Enter again.')
                continue
        except ValueError:
            print('Invalid age format. Enter again as a positive integer.')
            continue

        list_of_people.append(
            {'name': name,
             'surname': surname,
             'age': age
             }
        )

        answer = input('Do you want to stop? Print Y or N: ')
        if answer.lower() == 'y':
            break

    av_age = 0

    for obj in list_of_people:
        av_age += obj["age"]
        print(f'{obj["surname"]} {obj["name"]} {obj["age"]}')

    max_age = max(list_of_people, key=lambda x: x["age"])["age"]
    min_age = min(list_of_people, key=lambda x: x["age"])["age"]

    if av_age != 0:
        av_age /= len(list_of_people)
        av_age = round(av_age, 2)

    print(f'min age: {min_age}, max age: {max_age}, av age: {av_age:.2f}')

    return {
        'list_of_people': list_of_people,
        'min_age': min_age,
        'max_age': max_age,
        'av_age': av_age
    }


def task_3():
    while True:
        try:
            length = float(input("Введите длину прямоугольника: "))
            if length <= 0:
                print('Длина должна быть положительным числом. Попробуйте снова.')
                continue

            width = float(input("Введите ширину прямоугольника: "))
            if width <= 0:
                print('Ширина должна быть положительным числом. Попробуйте снова.')
                continue

            area = length * width
            print(f"Площадь прямоугольника: {area}")
            return area

        except ValueError:
            print("Ошибка: Введите числовые значения для длины и ширины.")


def task_4():
    # Открываем файл для записи
    with open("gradient_table.html", "w") as html_file:
        # Начинаем запись HTML-кода
        html_file.write("<html>\n")
        html_file.write("<head>\n")
        html_file.write("<style>\n")
        html_file.write("table {\n")
        html_file.write("    border-collapse: collapse;\n")
        html_file.write("    width: 100%;\n")
        html_file.write("    background: linear-gradient(to bottom, white, black);\n")
        html_file.write("}\n")
        html_file.write("th, td {\n")
        html_file.write("    border: none;\n")
        html_file.write("    padding: 8px;\n")
        html_file.write("}\n")
        html_file.write("</style>\n")
        html_file.write("</head>\n")
        html_file.write("<body>\n")
        html_file.write("<table>\n")

        # Заполняем таблицу данными
        for i in range(1, 11):
            html_file.write("<tr>\n")
            html_file.write(f"    <td>Row {i}</td>\n")
            html_file.write(f"    <td>Data {i}</td>\n")
            html_file.write("</tr>\n")

        # Завершаем запись HTML-кода
        html_file.write("</table>\n")
        html_file.write("</body>\n")
        html_file.write("</html>\n")

    # Теперь читаем сгенерированный HTML-код из файла и возвращаем его
    with builtins.open("gradient_table.html", "r") as html_file:
        html_code = html_file.read()

    return html_code


# random_number = random.randint(5, 50)
# print(task_1(random_number))
# task_2()
# task_3()
# task_4()
