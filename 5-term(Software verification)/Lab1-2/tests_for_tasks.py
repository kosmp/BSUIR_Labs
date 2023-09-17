import unittest
from unittest.mock import mock_open, patch
from main import task_4, task_3, task_2, task_1
import builtins


class TestTasks(unittest.TestCase):
    def test_task_1(self):
        result = task_1(5)

        self.assertEqual(result, 'Hello, world!\nAndhiagain!\n' + '!!!!!')

    @patch('builtins.input', side_effect=['John', 'Doe', '25', 'y'])
    def test_task_2(self, mock_input):
        result = task_2()

        expected_result = {
            'list_of_people': [{'name': 'John', 'surname': 'Doe', 'age': 25}],
            'min_age': 25,
            'max_age': 25,
            'av_age': 25.0
        }

        self.assertEqual(result, expected_result)


    @patch('builtins.input', side_effect=['20.43', '30.01'])
    def test_task_3(self, mock_input):
        result = task_3()

        self.assertEqual(round(result, 4), 613.1043)


    def test_task_4(self):
        # Вызываем функцию и сохраняем результат
        html_code = task_4()

        # Проверяем, что функция вернула не пустую строку
        self.assertNotEqual(html_code, "")

        # Проверяем, что сгенерированный HTML-код содержит необходимые элементы
        self.assertIn("<table>", html_code)
        self.assertIn("</table>", html_code)
        self.assertIn("Row 1", html_code)
        self.assertIn("Data 1", html_code)


if __name__ == '__main__':
    unittest.main()
