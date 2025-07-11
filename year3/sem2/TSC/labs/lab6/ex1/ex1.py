import datetime
from unittest.mock import Mock

_2024 = datetime.datetime(year=2024, month=1, day=1)
_2023 = datetime.datetime(year=2023, month=1, day=5)

def is_leap_year():
    today = datetime.datetime.today()
    return today.year % 400 == 0 or (today.year % 4 == 0 and today.year % 100 != 0)


datetime = Mock()

datetime.datetime.today.return_value = _2024
assert is_leap_year()

datetime.datetime.today.return_value = _2023
assert not is_leap_year()
