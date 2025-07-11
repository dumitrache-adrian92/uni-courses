"""
A command-line controlled coffee maker.
"""

import sys
import load_recipes

# Commands
EXIT = "exit"
LIST_COFFEES = "list"
MAKE_COFFEE = "make"  #!!! when making coffee you must first check that you have enough resources!
HELP = "help"
REFILL = "refill"
RESOURCE_STATUS = "status"
commands = [EXIT, LIST_COFFEES, MAKE_COFFEE, REFILL, RESOURCE_STATUS, HELP]

# Coffee examples
ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"

# Resources examples
WATER = "water"
COFFEE = "coffee"
MILK = "milk"

# Coffee maker's resources - the values represent the fill percents
RESOURCES = {WATER: 100, COFFEE: 100, MILK: 100}

"""
Example result/interactions:

I'm a smart coffee maker
Enter command:
list
americano, cappuccino, espresso
Enter command:
status
water: 100%
coffee: 100%
milk: 100%
Enter command:
make
Which coffee?
espresso
Here's your espresso!
Enter command:
refill
Which resource? Type 'all' for refilling everything
water
water: 100%
coffee: 90%
milk: 100%
Enter command:
exit
"""

def make_coffee(recipe_costs):
    """ Intelligent coffee making technology. """

    print("Which coffee?")

    coffee = sys.stdin.readline().strip().lower()

    if coffee == ESPRESSO:
        print("Here's your espresso!")

        if RESOURCES[WATER] < recipe_costs[ESPRESSO][WATER] or \
           RESOURCES[COFFEE] < recipe_costs[ESPRESSO][COFFEE]:
            print("I don't have enough resources to make that.")
            return

        RESOURCES[WATER] -= recipe_costs[ESPRESSO][WATER]
        RESOURCES[COFFEE] -= recipe_costs[ESPRESSO][COFFEE]
    elif coffee == AMERICANO:
        if RESOURCES[WATER] < recipe_costs[AMERICANO][WATER] or \
           RESOURCES[COFFEE] < recipe_costs[AMERICANO][COFFEE]:
            print("I don't have enough resources to make that.")
            return

        print("Here's your americano!")
        RESOURCES[WATER] -= recipe_costs[AMERICANO][WATER]
        RESOURCES[COFFEE] -= recipe_costs[AMERICANO][COFFEE]
    elif coffee == CAPPUCCINO:
        if RESOURCES[WATER] < recipe_costs[CAPPUCCINO][WATER] or \
           RESOURCES[COFFEE] < recipe_costs[CAPPUCCINO][COFFEE] or \
           RESOURCES[MILK] < recipe_costs[CAPPUCCINO][MILK]:
            print("I don't have enough resources to make that.")
            return

        print("Here's your cappuccino!")
        RESOURCES[WATER] -= recipe_costs[CAPPUCCINO][WATER]
        RESOURCES[COFFEE] -= recipe_costs[CAPPUCCINO][COFFEE]
        RESOURCES[MILK] -= recipe_costs[CAPPUCCINO][MILK]
    else:
        print("I am not that intelligent, I can only make espresso, \
                      americano or cappuccino.")

def refill_resources():
    """ Refill the coffee maker's resources."""

    print("Which resource? Type 'all' for refilling everything.")

    rsrc = sys.stdin.readline().strip().lower()

    if rsrc == "all":
        for res in RESOURCES:
            RESOURCES[res] = 100
    elif rsrc in RESOURCES:
        RESOURCES[rsrc] = 100
    else:
        print("I don't know how to refill that.")

    print_resource_status()

def print_resource_status():
    """ Print the status of the coffee maker's resources. """

    for resource, percent in RESOURCES.items():
        print(f"{resource}: {percent}%")

def handle_invalid_command():
    """ Handle invalid commands. """

    print("I don't understand that command. Type 'help' for a list of commands.")

def print_help():
    """ Print the available commands. """

    print("Commands: " + ", ".join(commands))

def print_coffee_choices():
    """ Print the available coffee choices. """

    print(", ".join([ESPRESSO, AMERICANO, CAPPUCCINO]))

if __name__ == "__main__":
    recipes = load_recipes.load_recipes()
    print("I'm a smart coffee maker")
    while True:
        print("Enter command:")
        command = sys.stdin.readline().strip().lower()

        if command == EXIT:
            sys.exit(0)
        elif command == LIST_COFFEES:
            print_coffee_choices()
        elif command == RESOURCE_STATUS:
            print_resource_status()
        elif command == MAKE_COFFEE:
            make_coffee(recipes)
        elif command == REFILL:
            refill_resources()
        elif command == HELP:
            print_help()
        else:
            handle_invalid_command()
