import unittest
from ex2 import get_marks
from requests.exceptions import Timeout
from unittest.mock import patch

class TestMarks(unittest.TestCase):
    @patch('ex2.requests')
    def test_get_marks_timeout(self, mock_requests):
        mock_requests.get.side_effect = Timeout

        with self.assertRaises(Timeout):
            get_marks()
            mock_requests.get.assert_called_once()


        return 0

if __name__ == '__main__':
    unittest.main()
