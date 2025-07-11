"""
Computer Systems Architecture - Lab 3

Threadpool assignment:
    Use a pool of threads to search for a DNA sequence in a list of DNA samples
"""
from concurrent.futures import ThreadPoolExecutor as ThreadPool
import random

random.seed(0)
MAX_THREADS = 30
SAMPLE_COUNT = 100
SAMPLE_SIZE = 10000
# generate many DNA samples, need to be large, otherwise there's no point of a concurrent program
dna_samples = [''.join(random.choice("ATGC") for _ in range(SAMPLE_SIZE))
                    for _ in range(100) ]

SEARCH_SEQUENCE = "TCCGTAGTAT"


def search_dna_sequence(sequence, sample):
    """
    :return: True if the sequence was found, False otherwise
    """
    return sequence in sample


def thread_job(sample_index):
    """
    Each thread searches the sequence in a given sample
    """
    if search_dna_sequence(SEARCH_SEQUENCE, dna_samples[sample_index]):
        return "DNA sequence found in sample {}".format(sample_index)
    return "DNA sequence not found in sample {}".format(sample_index)


if __name__ == "__main__":

    thread_pool = ThreadPool(MAX_THREADS)

    futures = []

    print(dna_samples)

    with thread_pool:
        futures = thread_pool.map(thread_job, range(SAMPLE_COUNT))

        for future in futures:
            print(future)
