"""First SCD lab solution"""

import json
import requests

payload = json.dumps({
        "username": "scd",
        "password": "admin",
        "nume": "Adrian-George Dumitrache"
    })

def solve1():
    """Solve the first task"""
    url = "https://scd.dfilip.xyz/lab1/task1/check"

    response = requests.post(url,
                             params={
                                "nume": "Adrian-George Dumitrache",
                                "grupa": "342C1"
                            },
                             headers={
                                "secret2": "SCDisBest",
                                "Content-Type": "application/x-www-form-urlencoded"
                            },
                             data="secret=SCDisNice",
                             timeout=5)

    print(response.text)

def solve2():
    """Solve the second task"""
    url = "https://scd.dfilip.xyz/lab1/task2"

    response = requests.post(url,
                             headers={"Content-Type": "application/json"},
                             data=payload,
                             timeout=5)

    print(response.text)

def solve3():
    """Solve the third task"""
    login_url = "https://scd.dfilip.xyz/lab1/task3/login"
    get_url = "https://scd.dfilip.xyz/lab1/task3/check"

    with requests.Session() as s:
        response = s.post(login_url,
                          headers={"Content-Type": "application/json"},
                          data=payload,
                          timeout=5)

        response = s.get(get_url,
                         timeout=5)

        print(response.text)


if __name__ == "__main__":
    solve1()
    solve2()
    solve3()

