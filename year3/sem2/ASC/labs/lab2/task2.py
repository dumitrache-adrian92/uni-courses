"""
    Basic thread handling exercise:

    Use the Thread class to create and run more than 10 threads which print their name and a random
    number they receive as argument. The number of threads must be received from the command line.

    e.g. Hello, I'm Thread-96 and I received the number 42

"""
import sys
import threading
import random
from threading import Thread

class Task2(Thread):
    """ A thread class that prints its id and a random number """

    def __init__(self, number):
        Thread.__init__(self)
        self.number = number

    def run(self):
        print(f'Hello, I\'m Thread-{threading.get_ident()} and I received the number {self.number}')


if __name__ == '__main__':
    thread_count = int(sys.argv[1])

    thread_pool = [Task2(random.randint(1, 420)) for _ in range(thread_count)]

    for thread in thread_pool:
        thread.start()

    for thread in thread_pool:
        thread.join()
