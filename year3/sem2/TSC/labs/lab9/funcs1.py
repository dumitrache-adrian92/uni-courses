import unittest
import pytest
import pytest_regtest
import sys

def sum_array(arr):
    return sum(arr)

def concatenate_string_array(arr):
    return ''.join(arr)


def test_sum_array(regtest):
    print(sum_array([1, 2, 3]), file=regtest)
    regtest.write("gata")

def test_concatenate_string_array(regtest):
    print(concatenate_string_array(['a', 'b', 'c']), file=regtest)
    regtest.write("gata")
