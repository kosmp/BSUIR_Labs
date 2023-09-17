import os
import sys

def search_files_with_extension(folder_path, extension):
    try:
        for root, dirs, files in os.walk(folder_path):
            for file in files:
                if file.endswith(extension):
                    file_path = os.path.join(root, file)
                    print(file_path)
    except Exception as e:
        print(f"Произошла ошибка при поиске файлов: {e}")

def task_5():
    try:
        if len(sys.argv) != 3:
            raise ValueError("Использование: python search_files.py <путь к папке> <расширение файла>")

        folder_path = sys.argv[1]
        extension = sys.argv[2]

        if not os.path.exists(folder_path):
            raise FileNotFoundError("Указанная папка не существует.")

        if not os.path.isdir(folder_path):
            raise NotADirectoryError("Указанный путь не является папкой.")

        if not extension.startswith("."):
            raise ValueError("Расширение файла должно начинаться с точки (например, '.txt').")

        if len(extension) < 2:
            raise ValueError("Расширение файла слишком короткое.")

        search_files_with_extension(folder_path, extension)
    except Exception as e:
        print(f"Произошла ошибка: {e}")


task_5()
