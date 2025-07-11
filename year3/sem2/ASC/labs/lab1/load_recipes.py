"""
    Bonus task: load all the available coffee recipes from the folder 'recipes/'
    File format:
        first line: coffee name
        next lines: resource=percentage

    info and examples for handling files:
        http://cs.curs.pub.ro/wiki/asc/asc:lab1:index#operatii_cu_fisiere
        https://docs.python.org/3/library/io.html
        https://docs.python.org/3/library/os.path.html
"""

import os

RECIPES_FOLDER = "recipes"

def load_recipes():
    """ Loads recipes from the recipes/ folder """

    recipes = [RECIPES_FOLDER + "/" + f for f in os.listdir(RECIPES_FOLDER)
                            if os.path.isfile(os.path.join(RECIPES_FOLDER, f))]
    result = {}

    for recipe in recipes:
        with open(recipe, "r", encoding="utf-8") as file:
            coffee_name = file.readline().strip()
            recipe = {}
            for line in file:
                resource, percentage = line.strip().split("=")
                recipe[resource] = int(percentage)

            result[coffee_name] = recipe

    return result
