#include<stdio.h>
#include<stdlib.h>

int main() {

    FILE *fp;
    int input;

    int total_changes = 1;
    int *changes = malloc(total_changes * sizeof(int));

    int frequency = 0;
    int total_frequencies = 1;
    int *frequencies = malloc(total_frequencies * sizeof(int));
    int duplicate_frequency = 0;

    int is_first_loop = 1;

    // Read the file.
    fp = fopen("./input.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while((fscanf (fp, "%d\n", &input)) != EOF) {
        changes[total_changes - 1] = input;
        total_changes++;
        changes = realloc(changes, total_changes * sizeof(int));
    }
    fclose(fp);

    // Check for duplicate frequency and also report the result of one iteration.
    while(duplicate_frequency == 0) {
        for(int i = 0; i < total_changes - 1; i++) {
            frequency += changes[i];
            for (int j = 0; j < total_frequencies && duplicate_frequency == 0; j++) {
                if(frequencies[j] == frequency) {
                    duplicate_frequency = frequency;
                    printf("Duplicate frequency = %d\n", frequency);
                }
            }
            if(duplicate_frequency != 0 && is_first_loop == 0) {
                break;
            }
            total_frequencies++;
            frequencies = realloc(frequencies, total_frequencies * sizeof(int));
            frequencies[total_frequencies - 1] = frequency;
        }
        if (is_first_loop) {
            printf("Frequency after first loop = %d\n", frequency);
            is_first_loop = 0;
        }
    }

    free(frequencies);
    free(changes);

    return 0;
}
