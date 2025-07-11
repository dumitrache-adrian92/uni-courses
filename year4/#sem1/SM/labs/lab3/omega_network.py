import sys

def shuffle(x, n):
    return (2 * x + (2 * x) // n) % n

def same_bit(x, y, idx):
    return ((x >> idx) & 1) ^ ((y >> idx) & 1)

if __name__ == '__main__':
    k = int(input("k = "))
    if k < 3:
        print("k must be greater than or equal to 3")
        sys.exit()

    no_tests = int(input("no.tests = "))
    N = 2 ** k

    for _ in range(no_tests):
        source = int(input("source = "))
        destination = int(input("destination = "))
        value = source

        for i in range(k):
            new_value = shuffle(value, N)

            if same_bit(source, destination, k - i - 1) == 0:
                print(value, "->", new_value, "via block", new_value // 2, "direct")
            else:
                new_value = new_value - 1 if new_value % 2 else new_value + 1

                print(value, "->", new_value, "via block", new_value // 2, "cross")

            value = new_value
