"""Lab 2 SM - Exercise 2"""

import matplotlib.pyplot as plt
import numpy as np

def weighted_mean_harmonic_rate(n):
    R1 = 10
    R2 = 60
    p1 = n * 0.3
    p2 = 1.0 - p1

    result = p1 / R1 + p2 / R2

    return 1 / result

if __name__ == "__main__":
    x = np.linspace(1, 3, 100)

    fig, ax1 = plt.subplots()

    ax1.set_xlabel('n')
    ax1.set_ylabel('Weighted Mean Harmonic Rate')

    ax1.plot(x, weighted_mean_harmonic_rate(x), color='black', label='Weighted Mean Harmonic Rate')
    plt.xticks(np.arange(0, 4, 1))

    plt.legend(loc='upper left')

    plt.savefig('ex2.png')
