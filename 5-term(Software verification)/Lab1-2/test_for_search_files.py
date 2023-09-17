import unittest
import os
from io import StringIO
from unittest.mock import patch
from search_files import search_files_with_extension


class TestSearchFilesWithExtension(unittest.TestCase):

    @patch('sys.stdout', new_callable=StringIO)
    def test_search_files_with_extension(self, mock_stdout):
        # Создаем временную папку и в ней временные файлы
        folder_path = 'temp_folder'
        os.makedirs(folder_path, exist_ok=True)

        # Создаем временные файлы с разными расширениями
        with open(os.path.join(folder_path, 'file1.txt'), 'w') as f1:
            f1.write('Test file 1')

        with open(os.path.join(folder_path, 'file2.txt'), 'w') as f2:
            f2.write('Test file 2')

        with open(os.path.join(folder_path, 'file3.jpg'), 'w') as f3:
            f3.write('Test file 3')

        search_files_with_extension(folder_path, '.txt')

        # Проверяем, что вывод содержит только файлы с .txt расширением
        expected_output = os.path.join(folder_path, 'file1.txt') + '\n' + os.path.join(folder_path, 'file2.txt') + '\n'
        self.assertEqual(mock_stdout.getvalue(), expected_output)

        # Удаляем временную папку и файлы после выполнения теста
        for root, dirs, files in os.walk(folder_path, topdown=False):
            for file in files:
                file_path = os.path.join(root, file)
                os.remove(file_path)
            os.rmdir(root)


if __name__ == '__main__':
    unittest.main()
