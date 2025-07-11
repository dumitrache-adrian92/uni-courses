#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** args) {

    int nr_threads = argc > 1 ? atoi(args[1]) : 4;
    omp_set_num_threads(nr_threads);
    map<char, int> letters;
    vector<string> words;
    int i, j;

    for (i = 32; i < 128; i++) {
        letters[(char)i] = 0;
    }

    #pragma omp parallel for shared(words) private(i)
    for (i = 1; i <= 100; i++) {
        string filename = "files/f" + to_string(i);
        char content[10000];
        FILE *file;

        file = fopen(filename.c_str(),"r");
        while (fgets(content, sizeof(content), file) != NULL)
        {
            string temp(content);
            #pragma omp critical
            words.push_back(string(content));
        }
        fclose(file);
    }

    #pragma omp parallel for shared(letters, words) private(i)
    for (i = 0; i < words.size(); i++) {
        #pragma omp parallel for shared(letters, words) private(j)
        for (j = 0; j < words[i].size(); j++) {
            #pragma omp atomic
            letters[words[i][j]]++;
        }
    }

    for (i = 32; i < 128; i++) {
        cout << (char)i << ": " << letters[char(i)] << endl;
    }
}