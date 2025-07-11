import unittest
import pytest
import pytest_regtest
import sys

def sum_array(arr):
    return sum(arr)

def concatenate_string_array(arr):
    return ''.join(arr)


class TestFuncs(unittest.TestCase):
        def test_sum_array(self, regtest):
            self.assertEqual(sum_array([1, 2, 3]), 6)
            regtest.write("done")

        def test_sum_array2(self, regtest):
            self.assertEqual(sum_array([1, 2, 1]), 4)
            regtest.write("done")

        def test_sum_array3(self, regtest):
            self.assertEqual(sum_array([-1, 0, 1]), 0)
            regtest.write("done")

        def test_concatenate_string_array(self, regtest):
            self.assertEqual(concatenate_string_array(['a', 'b', 'c']), 'abc')
            regtest.write("done")

        def test_concatenate_string_array2(self, regtest):
            self.assertEqual(concatenate_string_array(['m', 'n', 'ppp']), 'mnppp')
            regtest.write("done")

        def test_concatenate_string_array3(self, regtest):
            self.assertEqual(concatenate_string_array([]), '')
            regtest.write("done")

# atheris.Setup(sys.argv, TestFuncs.test_sum_array)
# atheris.Fuzz()

# atheris.Setup(sys.argv, TestFuncs.test_concatenate_string_array)
# atheris.Fuzz()
