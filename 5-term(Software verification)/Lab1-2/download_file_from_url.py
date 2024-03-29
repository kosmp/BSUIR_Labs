import os
import requests
from urllib.parse import urlparse


def download_file(url, save_dir, file_name):
    try:
        # Проверяем, что URL является корректным
        parsed_url = urlparse(url)
        if not all([parsed_url.scheme, parsed_url.netloc]):
            raise ValueError("Некорректный URL. Убедитесь, что URL начинается с http:// или https://")

        response = requests.get(url)
        response.raise_for_status()  # Проверяем наличие ошибок HTTP

        save_path = os.path.join(save_dir, file_name)

        os.makedirs(save_dir, exist_ok=True)  # Создаем директорию, если она не существует

        with open(save_path, 'wb') as file:
            file.write(response.content)
        print(f"Файл успешно загружен и сохранен по пути: {save_path}")
    except requests.exceptions.RequestException as e:
        raise ValueError(f"Произошла ошибка при загрузке файла: {e}")
    except ValueError as e:
        raise e  # Просто передаем исключение ValueError дальше
    except Exception as e:
        raise ValueError(f"Произошла неизвестная ошибка: {e}")
