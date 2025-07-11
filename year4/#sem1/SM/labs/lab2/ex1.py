"""Lab 2 SM - Exercise 1"""

import matplotlib.pyplot as plt
import numpy as np

def O1(n):
    return n**3

def On(n):
    return n**3 + n**2 * np.log2(n)

def T1(n):
    return n**3

def Tn(n):
    return (4 * n**3) / (n + 3)

def S(n):
    return T1(n) / Tn(n)

def E(n):
    return S(n) / n

def R(n):
    return On(n) / O1(n)

def U(n):
    return R(n) * E(n)

def Q(n):
    return (S(n) * E(n)) / R(n)

if __name__ == "__main__":
    x = np.linspace(1, 32, 1000)

    fig, ax1 = plt.subplots()

    ax1.set_xscale('log', base=2)
    ax1.set_xlim(1, 32)
    ax1.set_xticks([1, 2, 4, 8, 16, 32])
    ax1.get_xaxis().set_major_formatter(plt.ScalarFormatter())

    ax1.set_xlabel('n')
    ax1.set_ylabel('E(n), U(n)')
    # plot each function
    ax1.plot(x, U(x), color='black', label='U(n)')
    ax1.plot(x, E(x), color='blue', label='E(n)')
    ax1.tick_params(axis='y')

    plt.yticks(np.arange(0, 1.1, 0.1))

    # set legend
    plt.legend(loc='upper left')

    ax2 = ax1.twinx()

    ax2.set_xlabel('n')
    ax2.set_ylabel('S(n), R(n), Q(n)')
    # plot each function
    ax2.plot(x, S(x), color='red', label='S(n)')
    ax2.plot(x, R(x), color='green', label='R(n)')
    ax2.plot(x, Q(x), color='purple', label='Q(n)')
    ax2.tick_params(axis='y')

    # set legend
    plt.legend(loc='upper right')

    # set log scale with numbers instead of 2^x
    ax2.set_yscale('log', base=2)
    ax2.yaxis.set_major_formatter(plt.ScalarFormatter())

    plt.savefig('ex1.png')
