#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define min(a, b) ((a) > (b) ? (b) : (a))
#define MAP_REDUCE_TASK_COUNT 6
#define MAPPER_COUNT 3
#define MAX_LINE_LENGTH 15
#define COORDONATOR 0
#define VOWEL_REDUCER 4
#define CONSONANT_REDUCER 5

int isVowel(char c)
{

    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int isConsonant(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') && !isVowel(c);
}

int main (int argc, char *argv[])
{
    int numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (numtasks != MAP_REDUCE_TASK_COUNT) {
        if (rank == 0)
            printf("This program requires exactly 6 tasks to run correctly. Please rerun!\n");
        exit(0);
    }

    if (argc < 2) {
        if (rank == 0)
            printf("Usage: mpirun -np 6 %s file.in\n", argv[0]);
        exit(0);
    }

    if (rank == COORDONATOR) {
        FILE *input = fopen(argv[1], "r");

        int line_count;
        fscanf(input, "%d", &line_count);

        char lines[line_count][MAX_LINE_LENGTH + 1];
        for (int i = 0; i < line_count; i++) {
            memset(lines[i], 0, MAX_LINE_LENGTH + 1);
            fscanf(input, "%s", lines[i]);
        }

        for (int i = 0; i < MAPPER_COUNT; i++) {
            int start = i * (double) line_count / MAPPER_COUNT;
            int end = min((i + 1) * (double) line_count / MAPPER_COUNT, line_count);

            int lines_to_be_processed = end - start;
            MPI_Send(&lines_to_be_processed, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);

            for (int j = start; j < end; j++) {
                MPI_Send(lines[j], MAX_LINE_LENGTH + 1, MPI_CHAR, i + 1, 0, MPI_COMM_WORLD);
            }
        }
    } else if (rank >= 1 && rank <= 3) {
        int lines_to_be_processed;
        MPI_Recv(&lines_to_be_processed, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        char lines[lines_to_be_processed][MAX_LINE_LENGTH + 1];

        for (int i = 0; i < lines_to_be_processed; i++) {
            memset(lines[i], 0, MAX_LINE_LENGTH + 1);
            MPI_Recv(lines[i], MAX_LINE_LENGTH + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        int vowel_count = 0;
        int consonant_count = 0;

        for (int i = 0; i < lines_to_be_processed; i++) {
            for (int j = 0; j < strlen(lines[i]); j++) {
                if (isVowel(lines[i][j])) {
                    vowel_count++;
                } else if (isConsonant(lines[i][j])) {
                    consonant_count++;
                }
            }
        }

        for (int i = 0; i < lines_to_be_processed; i++) {
            printf("[%d] %s\n", rank, lines[i]);
        }

        printf("[%d] v=%d c=%d\n", rank, vowel_count, consonant_count);

        MPI_Send(&vowel_count, 1, MPI_INT, VOWEL_REDUCER, 0, MPI_COMM_WORLD);
        MPI_Send(&consonant_count, 1, MPI_INT, CONSONANT_REDUCER, 0, MPI_COMM_WORLD);
    } else if (rank == VOWEL_REDUCER) {
        int vowel_count_total = 0;

        for (int i = 0; i < MAPPER_COUNT; i++) {
            int vowel_count;
            MPI_Recv(&vowel_count, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            vowel_count_total += vowel_count;
        }

        printf("[%d] Vowels: %d\n", rank, vowel_count_total);
    } else if (rank == CONSONANT_REDUCER) {
        int consonant_count_total = 0;

        for (int i = 0; i < MAPPER_COUNT; i++) {
            int consonant_count;
            MPI_Recv(&consonant_count, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            consonant_count_total += consonant_count;
        }

        printf("[%d] Consonants: %d\n", rank, consonant_count_total);
    }

    MPI_Finalize();
}

