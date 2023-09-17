import os
import requests
import sys
from urllib.parse import urlparse


def download_file(url, save_dir, file_name):
    try:
        # Проверяем, что URL является корректным
        parsed_url = urlparse(url)
        if not all([parsed_url.scheme, parsed_url.netloc]):
            print("Некорректный URL. Убедитесь, что URL начинается с http:// или https://")
            return

        response = requests.get(url)
        response.raise_for_status()  # Проверяем наличие ошибок HTTP

        save_path = os.path.join(save_dir, file_name)

        os.makedirs(save_dir, exist_ok=True)  # Создаем директорию, если она не существует

        with open(save_path, 'wb') as file:
            file.write(response.content)
        print(f"Файл успешно загружен и сохранен по пути: {save_path}")
    except requests.exceptions.RequestException as e:
        print(f"Произошла ошибка при загрузке файла: {e}")
    except Exception as e:
        print(f"Произошла неизвестная ошибка: {e}")


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
