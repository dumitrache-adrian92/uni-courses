import pytest
import sys
from car import Car

""" Exercise 0a: Write a fixture that returns a car instance. """

# TODO
@pytest.fixture
def my_car():
    return Car()


def test_car_accelerate_simple(my_car):
    """ Exercise 0b: Using the just created fixture test the accelerate method. Hint: accelerate, then check. """
    # TODO
    initial_speed = my_car.speed
    my_car.accelerate()
    assert my_car.speed - initial_speed == 5


def test_car_brake_simple(my_car):
    """ Exercise 0c: Using the just created fixture test the brake method. Hint: break, then check. """
    # TODO
    initial_speed = my_car.speed
    my_car.brake()
    assert my_car.speed - initial_speed == -5

#--------------------------------------------------------------------------------------------------------------------

speed_data = {45, 50, 75, 45}

@pytest.mark.parametrize("speed_brake", speed_data)
def test_car_brake_crazy(speed_brake):
    car = Car(speed_brake)
    car.brake()
    assert car.speed == speed_brake - 5




""" Exercise 1a: Write a parameterized test for accelerate. You can use the speed_data dataset. """
@pytest.mark.parametrize("speed_accelerate", speed_data)
def test_car_accelerate_crazy(speed_accelerate):
    car = Car(speed_accelerate)
    car.accelerate()
    assert car.speed == speed_accelerate + 5


@pytest.mark.parametrize("speed, expected_speed", [(50, 55), (40, 45), (30, 35), (85, 90)])
def test_car_accelerate(speed, expected_speed):
    car = Car(speed)
    car.accelerate()
    assert car.speed == expected_speed


""" Exercise 1b: Write a parameterized test for brake that receives different speeds and checks the
speed update after brake method is called. Hint: Look up! """
# TODO
@pytest.mark.parametrize("speed, expected_speed", [(50, 45), (40, 35), (30, 25), (85, 80)])
def test_car_brake(speed, expected_speed):
    car = Car(speed)
    car.brake()
    assert car.speed == expected_speed

#--------------------------------------------------------------------------------------------------------------------

""" Exercise 2a: Mark this test to be skipped. """
# TODO
@pytest.mark.skip(reason="This test was bad")
def test_average_speed():
    car = Car(50)
    car.step()
    assert car.average_speed() == 50


""" Exercise 2b: Write a test and mark it as skippable if Python version is less than 3.7 """
# TODO
@pytest.mark.skipif(sys.version_info.major < 3 or sys.version_info.minor < 7, reason="Python version is less than 3.7")
def test_skipped():
    print("This test will be skipped")


""" Exercise 2c: Write a test you expect to fail for any of the car methods and mark it accordingly (provide a reason
too). """
# TODO
@pytest.mark.xfail(reason="This test is expected to fail")
def test_fail():
    car = Car(50)
    car.step()
    assert car.distance == 0
