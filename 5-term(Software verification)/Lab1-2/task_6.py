import os, sys
from download_file_from_url import download_file


def task_6():
    if len(sys.argv) != 4:
        print("Использование: python download_file.py <URL> <путь к папке для сохранения> <имя файла>")
        sys.exit(1)

    url = sys.argv[1]
    save_dir = sys.argv[2]
    file_name = sys.argv[3]

    if not os.path.isdir(save_dir):
        print("Указанный путь для сохранения не является директорией.")
        sys.exit(1)

    download_file(url, save_dir, file_name)


task_6()