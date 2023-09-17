import unittest
import os
from unittest.mock import patch
from io import BytesIO
from download_file_from_url import download_file


class TestDownloadFile(unittest.TestCase):
    def setUp(self):
        # Создаем временную директорию для тестов
        self.temp_dir = 'temp_test_dir'
        os.makedirs(self.temp_dir, exist_ok=True)

    def tearDown(self):
        # Удаляем временную директорию после тестов
        os.rmdir(self.temp_dir)

    @patch('requests.get')
    def test_download_file_invalid_url(self, mock_get):
        # Настройка мока запроса
        mock_response = BytesIO(b"Test content")
        mock_response.status_code = 404
        mock_get.return_value = mock_response

        url = "invalid_url"
        file_name = "testfile.txt"

        # Вызываем функцию download_file с некорректным URL
        with self.assertRaises(ValueError) as context:
            download_file(url, self.temp_dir, file_name)

        # Проверяем, что функция выбрасывает исключение ValueError с соответствующим сообщением
        self.assertEqual(str(context.exception), "Некорректный URL. Убедитесь, что URL начинается с http:// или https://")


if __name__ == '__main__':
    unittest.main()
