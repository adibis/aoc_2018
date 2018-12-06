#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

#define REALLOC_SIZE 32

int sort_inputs(const void *input_a, const void *input_b) {
    return (strcmp( *(const char **)input_a, *(const char **)input_b));
}

int main() {

    FILE *fp;
    size_t realloc_counter = REALLOC_SIZE;

    char input[256];
    char **inputs = malloc(realloc_counter*(sizeof(char*)));
    int total_inputs = 0;

    // We only care about minutes so create a list of guards each with 60 minutes of data.
    size_t guard_counter = REALLOC_SIZE;
    int (*guards)[60] = malloc(guard_counter*(sizeof(int[60])));
    int total_guards = 0;

    int spleepiest_guard;
    int consistent_guard;
    int max_sleep;
    int sleepiest_minute;

    // Read the file.
    fp = fopen("./test.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while((fscanf(fp, "%s\n", &input)) != EOF) {
        inputs[total_inputs] = malloc(strlen(input)+1);
        strcpy(inputs[total_inputs], input);
        total_inputs++;
        if(total_inputs >= (int)realloc_counter) {
            realloc_counter += REALLOC_SIZE;
            inputs = realloc(inputs, realloc_counter*sizeof(char*));
        }
    }
    fclose(fp);

    // We need to sort the inputs. Use the library qsort function for it.
    qsort(inputs, total_inputs, sizeof(char*), sort_inputs);

    // Go through all the lines and figure out the start and stop sleep times.
    // Accordingly populate the guards sleep tables.
    for(int i = 0; i < total_inputs; i++) {
        if(inputs[i][25] == '#') {
        }

        if(total_guards >= (int)guard_counter) {
            guard_counter += REALLOC_SIZE;
            guards = realloc(guards, guard_counter*sizeof(char*));
        }
    }

    // Free all the allocated memory.
    for(int i = 0; i < total_inputs; i++) {
        free(inputs[total_inputs]);
    }
    free(inputs);

    return 0;
}
