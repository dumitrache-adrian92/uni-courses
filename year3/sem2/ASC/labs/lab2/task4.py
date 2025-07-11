"""
Philosopher's problem
"""

from threading import Thread, Lock

class Philosopher(Thread):
    """ Philosopher class """
    def __init__(self, philosopher_id, left_fork, right_fork):
        Thread.__init__(self)
        self.philosopher_id = philosopher_id
        self.left_fork = left_fork
        self.right_fork = right_fork

    def run(self):
        """ Eat method """
        if self.philosopher_id == 0:
            self.right_fork.acquire()
            self.left_fork.acquire()
            print(f'Philosopher {self.philosopher_id} is eating')
            self.right_fork.release()
            self.left_fork.release()
        else:
            self.left_fork.acquire()
            self.right_fork.acquire()
            print(f'Philosopher {self.philosopher_id} is eating')
            self.left_fork.release()
            self.right_fork.release()


class Table:
    """ Table class """
    def __init__(self, seats):
        self.forks = [Lock() for _ in range(seats)]
        self.philosophers = [Philosopher(i, self.forks[i], self.forks[(i + 1) % seats])
                             for i in range(seats)]

    def start(self):
        """ Start method """
        for philosopher in self.philosophers:
            philosopher.start()

    def join(self):
        """ Join method """
        for philosopher in self.philosophers:
            philosopher.join()

if __name__ == '__main__':
    table = Table(5)
    table.start()
    table.join()
