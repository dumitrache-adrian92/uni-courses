import unittest
from unittest.mock import patch
import ex3


class TestTotal(unittest.TestCase):
    def test_calculate_total(self):
        with patch('ex3.read') as mock_read:
            mock_read.return_value = [1, 2, 3, 4, 5]

            assert ex3.calculate_total("") == 15

if __name__ == '__main__':
    unittest.main()