import sys
import random

benes = []

def print_mat(mat):
    for row in mat:
        print(" ".join(map(str, row)))

def generate_permutation_dict(N):
    print("Give valid numbers for the initial permutation:")
    numbers = list(range(N))  
    for i in range(N):
        numbers[i] = int(input(f'{i} -> '))
    
    # comment lines 13 and 14 and uncomment this one for random generation
    # of a permutation using only a given k
    
    # random.shuffle(numbers)
    permutation_dict = {i: numbers[i] for i in range(N)}
    return permutation_dict

def dual(n):
    return n ^ 1

def split_in_c1_c2(P):
    c1 = dict()
    c2 = dict()
    # we have to put the pair into c{turn}
    turn = 1
    for key, value in P.items():
        while (True):
            if key in c1.keys() or key in c2.keys():
                break
            if value in c1.values() or value in c2.values():
                break
            
            if turn == 1:
                c1[key] = value
                output_c2 = dual(value)
                for k, v in P.items():
                    if v == output_c2:
                        key = k
                        value = v
                        break
                turn = 2
            else:
                c2[key] = value
                input_c1 = dual(key)
                for k, v in P.items():
                    if k == input_c1:
                        key = k
                        value = v
                        break
                turn = 1
    
    return dict(sorted(c1.items())), dict(sorted(c2.items()))

def generate(P, start, end, up, down, k):
    if k == 1:
        for key, value in P.items():
            if key != value:
                benes[up][start] = "invers"
            else:
                benes[up][start] = "direct"
        return

    c1, c2 = split_in_c1_c2(P)
    for left, right in c1.items():
        if left % 2 == 0:
            benes[up + left // 2][start] = "direct"
        else:
            benes[up + left // 2][start] = "invers"
        if right % 2 == 0:
            benes[up + right // 2][end] = "direct"
        else:
            benes[up + right // 2][end] = "invers"

    P1 = dict()
    P2 = dict()
    for key, value in c1.items():
        P1[key // 2] = value // 2
    for key, value in c2.items():
        P2[key // 2] = value // 2
    generate(P1, start + 1, end - 1, up, (down + up) // 2, k - 1)
    generate(P2, start + 1, end - 1, (down + up) // 2 + 1, down, k - 1) 

if __name__ == '__main__':
    k = int(input("k = "))
    if k < 3:
        print("k must be greater than or equal to 3")
        sys.exit()
        
    N = 2 ** k
    benes = [[None for _ in range(2 * k - 1)] for _ in range(N // 2)]
    P = dict()
    P = generate_permutation_dict(N)
    print(P)
    
    generate(P=P, start=0, end=2 * k - 2, up=0, down=pow(2, k - 1) - 1, k=k)
    print_mat(benes)
