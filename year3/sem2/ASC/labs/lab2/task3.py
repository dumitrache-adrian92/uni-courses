"""
Coffee Factory: A multiple producer - multiple consumer approach

Generate a base class Coffee which knows only the coffee name
Create the Espresso, Americano and Cappuccino classes which inherit the base class knowing that
each coffee type has a predetermined size.
Each of these classes have a get message method

Create 3 additional classes as following:
    * Distributor - A shared space where the producers puts coffees and the consumers takes them
    * CoffeeFactory - An infinite loop, which always sends coffees to the distributor
    * User - Another infinite loop, which always takes coffees from the distributor

The scope of this exercise is to correctly use threads, classes and synchronization objects.
The size of the coffee (ex. small, medium, large) is chosen randomly everytime.
The coffee type is chosen randomly everytime.

Example of output:

Consumer 65 consumed espresso
Factory 7 produced a nice small espresso
Consumer 87 consumed cappuccino
Factory 9 produced an italian medium cappuccino
Consumer 90 consumed americano
Consumer 84 consumed espresso
Factory 8 produced a strong medium americano
Consumer 135 consumed cappuccino
Consumer 94 consumed americano
"""

import random
import threading
import sys

class Coffee:
    """ Base class """

    def __init__(self, name, size):
        self.name = name
        self.size = size


    def get_name(self):
        """ Returns the name of the coffee"""
        return self.name

    def get_size(self):
        """ Returns the size of the coffee """
        return self.size


class Espresso(Coffee):
    """ Espresso implementation """

    def __init__(self, size):
        super().__init__("espresso", size)

    def get_message(self):
        """ Returns a message """
        return f"a nice {self.size} {self.name}"

class Capuccino(Coffee):
    """ Capuccino implementation """
    def __init__(self, size):
        super().__init__("capuccino", size)

    def get_message(self):
        """ Returns a message """
        return f"an italian {self.size} {self.name}"

class Americano(Coffee):
    """ Americano implementation """
    def __init__(self, size):
        super().__init__("americano", size)

    def get_message(self):
        """ Returns a message """
        return f"a strong {self.size} {self.name}"

class Distributor:
    """ A shared space where the producers puts coffees and the consumers takes them """

    def __init__(self, size):
        self.coffees = []
        self.size = size
        self.lock = threading.Lock()
        self.empty = threading.Semaphore(size)
        self.full = threading.Semaphore(0)

    def put(self, coffee):
        """ Puts a coffee in the distributor """
        self.coffees.append(coffee)

    def get(self):
        """ Returns a coffee from the distributor """
        return self.coffees.pop()

class CoffeeFactory(threading.Thread):
    """ An infinite loop, which always sends coffees to the distributor """

    def __init__(self, distr, factory_id):
        threading.Thread.__init__(self)
        self.distributor = distr
        self.coffees = [Espresso, Capuccino, Americano]
        self.factory_id = factory_id
        self._dict = {0: "small", 1: "medium", 2: "large"}

    def run(self):
        """ Produces coffee """
        while True:
            coffee = random.choice(self.coffees)(self._dict[random.randint(0, 2)])

            self.distributor.empty.acquire()

            with self.distributor.lock:
                self.distributor.put(coffee)

            self.distributor.full.release()

            print(f"Factory {self.factory_id} produced {coffee.get_message()}")

class User(threading.Thread):
    """ Infinite loop, which always takes coffees from the distributor """

    def __init__(self, distr, user_id):
        threading.Thread.__init__(self)
        self.distributor = distr
        self.user_id = user_id

    def run(self):
        while True:
            self.distributor.full.acquire()
            coffee = None

            with self.distributor.lock:
                coffee = self.distributor.get()

            print(f"Consumer {self.user_id} consumed {coffee.get_name()}")
            self.distributor.empty.release()

            delay = random.randint(1, 5)

            threading.Event().wait(delay)

if __name__ == '__main__':
    producer_count = int(sys.argv[1])
    consumer_count = int(sys.argv[2])

    distributor = Distributor(int(sys.argv[3]))

    producers = [CoffeeFactory(distributor, i) for i in range(producer_count)]
    consumers = [User(distributor, i) for i in range(consumer_count)]

    for producer in producers:
        producer.start()

    for consumer in consumers:
        consumer.start()

    for producer in producers:
        producer.join()

    for consumer in consumers:
        consumer.join()
