#include "structs.h"
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int byteCount(void *arr, int len) {
    int i, nr = 0;
    head *aux = malloc(sizeof(head));
    for (i = 0; i < len; i++) {
        memcpy(aux, arr + nr, sizeof(head));
        nr += sizeof(head) + aux->len;
    }
    free(aux);
    return nr;
}

int sizeofType(unsigned char x) {
    if (x == '1')
        return 2 * sizeof(int8_t);
    else if (x == '2')
        return sizeof(int16_t) + sizeof(int32_t);
    else if (x == '3')
        return 2 * sizeof(int32_t);
    return -1;
}

void print(void *arr, int len) {
    head *aux = malloc(sizeof(head));
    char *name1, *name2;
    int8_t bancnota1, bancnota2;
    int16_t bancnota1_16;
    int32_t bancnota1_32, bancnota2_32;
    int i = 0, oct = byteCount(arr, len);
    while (i < oct) {
        memcpy(aux, arr + i, sizeof(head));
        printf("Tipul %c\n", aux->type);
        name1 = arr + i + sizeof(head);
        name2 = arr + i + sizeof(head) + sizeofType(aux->type) + strlen(name1) + 1;
        printf("%s pentru %s\n", name1, name2);
        if (aux->type == '1') {
            memcpy(&bancnota1, arr + i + sizeof(head) + strlen(name1) + 1, sizeof(int8_t));
            memcpy(&bancnota2, arr + i + sizeof(head) + strlen(name1) + 1 + sizeof(int8_t), sizeof(int8_t));
            printf("%d\n%d\n\n", bancnota1, bancnota2);
        } else if (aux->type == '2') {
            memcpy(&bancnota1_16, arr + i + sizeof(head) + strlen(name1) + 1, sizeof(int16_t));
            memcpy(&bancnota2_32, arr + i + sizeof(head) + strlen(name1) + 1 + sizeof(int16_t), sizeof(int32_t));
            printf("%d\n%d\n\n", bancnota1_16, bancnota2_32);
        } else if (aux->type == '3') {
            memcpy(&bancnota1_32, arr + i + sizeof(head) + strlen(name1) + 1, sizeof(int32_t));
            memcpy(&bancnota2_32, arr + i + sizeof(head) + strlen(name1) + 1 + sizeof(int32_t), sizeof(int32_t));
            printf("%d\n%d\n\n", bancnota1_32, bancnota2_32);
        }
        i += sizeof(head) + aux->len;
    }
    free(aux);
}

int add_last(void **arr, int *len, data_structure *data) {
    int oct = byteCount(*arr, *len);
    if (*arr != NULL)
        *arr = realloc(*arr, oct + sizeof(head) + data->header->len);
    else
        *arr = malloc(sizeof(head) + data->header->len);
    if (*arr == NULL)
        return 1;
    memcpy(*arr + oct, data->header, sizeof(head));
    memcpy(*arr + oct + sizeof(head), data->data, data->header->len);
    *len+=1;
    return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index) {
    if (index < 0)
        return 1;
    int dest = 0, oct = byteCount(*arr, *len);
    head *aux = malloc(sizeof(head));
    for (int i = 0; i < index; i++) {
        if (dest >= oct) {
            free(aux);
            return -1;
        }
        memcpy(aux, *arr + dest, sizeof(head));
        dest += sizeof(head) + aux->len;
    }
    if (*arr != NULL)
        *arr = realloc(*arr, oct + sizeof(head) + data->header->len);
    else
        *arr = malloc(sizeof(head) + data->header->len);
    if (*arr == NULL)
        return 1;
    memmove(*arr + dest + sizeof(head) + data->header->len, *arr + dest, oct - dest);
    memcpy(*arr + dest, data->header, sizeof(head));
    memcpy(*arr + dest + sizeof(head), data->data, data->header->len);
    *len += 1;
    free(aux);
    return 0;
}

void find(void *data_block, int len, int index) {
    if (index < 0)
        return;
    head *aux = malloc(sizeof(head));
    int find = 0;
    memcpy(aux, data_block + find, sizeof(head));
    for (int i = 0; i < index; i++) {
        find += sizeof(head) + aux->len;
        memcpy(aux, data_block + find, sizeof(head));
    }
    char *name1, *name2;
    int8_t bancnota1, bancnota2;
    int16_t bancnota1_16;
    int32_t bancnota1_32, bancnota2_32;
    printf("Tipul %c\n", aux->type);
    name1 = data_block + find + sizeof(head);
    name2 = data_block + find + sizeof(head) + sizeofType(aux->type) + strlen(name1) + 1;
    printf("%s pentru %s\n", name1, name2);
    if (aux->type == '1') {
        memcpy(&bancnota1, data_block + find + sizeof(head) + strlen(name1) + 1, sizeof(int8_t));
        memcpy(&bancnota2, data_block + find + sizeof(head) + strlen(name1) + 1 + sizeof(int8_t), sizeof(int8_t));
        printf("%d\n%d\n\n", bancnota1, bancnota2);
    } else if (aux->type == '2') {
        memcpy(&bancnota1_16, data_block + find + sizeof(head) + strlen(name1) + 1, sizeof(int16_t));
        memcpy(&bancnota2_32, data_block + find + sizeof(head) + strlen(name1) + 1 + sizeof(int16_t), sizeof(int32_t));
        printf("%d\n%d\n\n", bancnota1_16, bancnota2_32);
    } else if (aux->type == '3') {
        memcpy(&bancnota1_32, data_block + find + sizeof(head) + strlen(name1) + 1, sizeof(int32_t));
        memcpy(&bancnota2_32, data_block + find + sizeof(head) + strlen(name1) + 1 + sizeof(int32_t), sizeof(int32_t));
        printf("%d\n%d\n\n", bancnota1_32, bancnota2_32);
    }
    free(aux);
}

int delete_at(void **arr, int *len, int index) {
    void *temp;
    int j = 0, removed, oct = byteCount(*arr, *len);
    head *aux = malloc(sizeof(head));
    for (int i = 0; i < index; i++) {
        memcpy(aux, *arr + j, sizeof(head));
        j += sizeof(head) + aux->len;
    }
    memcpy(aux, *arr + j, sizeof(head));
    removed = sizeof(head) + aux->len;
    oct -= removed;
    temp = malloc(oct);
    memcpy(temp, *arr, j);
    memcpy(temp + j, *arr + j + removed, oct - j);
    free(*arr);
    *arr = malloc(oct);
    memcpy(*arr, temp, oct);
    free(temp);
    free(aux);
    *len -= 1;
    return 0;
}

int8_t charToInt_8(char *a) {
    int x;
    x = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '-')
            continue;
        x = x * 10 + (a[i] - '0');
    }
    if (a[0] == '-')
        x *= -1;
    return x;
}

int16_t charToInt_16(char *a) {
    int x;
    x = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '-')
            continue;
        x = x * 10 + (a[i] - '0');
    }
    if (a[0] == '-')
        x *= -1;
    return x;
}

int32_t charToInt_32(char *a) {
    int x;
    x = 0;
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] == '-')
            continue;
        x = x * 10 + (a[i] - '0');
    }
    if (a[0] == '-')
        x *= -1;
    return x;
}

void create_data_structure(data_structure *aux, char *input) {
    char *dedicator, *dedicat, *p;
    int8_t bancnota1, bancnota2;
    int16_t bancnota1_16;
    int32_t bancnota1_32, bancnota2_32;

    p = strtok(input, " ");
    p = strtok(NULL, " ");
    aux->header->type = p[0];
    p = strtok(NULL, " ");
    dedicator = malloc(strlen(p) + 1);
    strcpy(dedicator, p);
    if (aux->header->type == '1') {
        p = strtok(NULL, " ");
        bancnota1 = charToInt_8(p);

        p = strtok(NULL, " ");
        bancnota2 = charToInt_8(p);

        p = strtok(NULL, " ");
        dedicat = malloc(strlen(p) + 1);
        strcpy(dedicat, p);

        aux->header->len = strlen(dedicat) + strlen(dedicator) + sizeof(bancnota1) + sizeof(bancnota2) + 2;
        aux->data = malloc(aux->header->len);
        memcpy(aux->data, dedicator, strlen(dedicator) + 1);
        memcpy(aux->data + strlen(dedicator) + 1, &bancnota1, sizeof(bancnota1));
        memcpy(aux->data + strlen(dedicator) + 1 + sizeof(int8_t), &bancnota2, sizeof(bancnota2));
        memcpy(aux->data + strlen(dedicator) + 1 + 2 * sizeof(int8_t), dedicat, strlen(dedicat) + 1);
    } else if (aux->header->type == '2') {
        p = strtok(NULL, " ");
        bancnota1_16 = charToInt_16(p);

        p = strtok(NULL, " ");
        bancnota2_32 = charToInt_32(p);

        p = strtok(NULL, " ");
        dedicat = malloc(strlen(p) + 1);
        strcpy(dedicat, p);

        aux->header->len = strlen(dedicat) + strlen(dedicator) + sizeof(bancnota1_16) + sizeof(bancnota2_32) + 2;
        aux->data = malloc(aux->header->len);
        memcpy(aux->data, dedicator, strlen(dedicator) + 1);
        memcpy(aux->data + strlen(dedicator) + 1, &bancnota1_16, sizeof(bancnota1_16));
        memcpy(aux->data + strlen(dedicator) + 1 + sizeof(int16_t), &bancnota2_32, sizeof(bancnota2_32));
        memcpy(aux->data + strlen(dedicator) + 1 + sizeof(int16_t) + sizeof(int32_t), dedicat, strlen(dedicat) + 1);
    } else if (aux->header->type == '3') {
        p = strtok(NULL, " ");
        bancnota1_32 = charToInt_32(p);

        p = strtok(NULL, " ");
        bancnota2_32 = charToInt_32(p);

        p = strtok(NULL, " ");
        dedicat = malloc(strlen(p) + 1);
        strcpy(dedicat, p);

        aux->header->len = strlen(dedicat) + strlen(dedicator) + sizeof(bancnota1_32) + sizeof(bancnota2_32) + 2;
        aux->data = malloc(aux->header->len);
        memcpy(aux->data, dedicator, strlen(dedicator) + 1);
        memcpy(aux->data + strlen(dedicator) + 1, &bancnota1_32, sizeof(bancnota1_32));
        memcpy(aux->data + strlen(dedicator) + 1 + sizeof(int32_t), &bancnota2_32, sizeof(bancnota2_32));
        memcpy(aux->data + strlen(dedicator) + 1 + 2 * sizeof(int32_t), dedicat, strlen(dedicat) + 1);
    }
    free(dedicat);
    free(dedicator);
}

int main() {
    // the vector of bytes u have to work with
    // good luck :)
    // te drq
    void *arr = NULL;
    int len = 0, index;
    char *input = malloc(257 * sizeof(char)), *copy, *p;
    data_structure *aux = malloc(sizeof(data_structure));
    head *hAux = malloc(sizeof(head));
    aux->header = hAux;
    do {
        fgets(input, 257, stdin);
        input[strlen(input) - 1] = '\0';
        if (strstr(input, "insert ") == input) {
            create_data_structure(aux, input);
            add_last(&arr, &len, aux);
            free(aux->data);
            aux->header->len = 0;
        } else if (strstr(input, "insert_") == input) {
            copy = malloc(strlen(input) + 1);
            strcpy(copy, input);
            create_data_structure(aux, input + 10);
            p = strtok(copy, " ");
            p = strtok(NULL, " ");
            index = charToInt_32(p);
            if (add_at(&arr, &len, aux, index) == -1)
                add_last(&arr, &len, aux);
            free(aux->data);
            free(copy);
        } else if (strstr(input, "delete_at") == input) {
            p = strtok(input, " ");
            p = strtok(NULL, " ");
            index = charToInt_32(p);
            delete_at(&arr, &len, index);
        } else if (strstr(input, "find") == input) {
            p = strtok(input, " ");
            p = strtok(NULL, " ");
            index = charToInt_32(p);
            find(arr, len, index);
        } else if (strstr(input, "print") == input)
            print(arr, len);
    } while (strcmp(input, "exit"));
    free(input);
    free(arr);
    free(aux);
    free(hAux);
    return 0;
}
