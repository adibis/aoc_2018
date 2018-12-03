#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int has_n_letters(char *line, int n) {
    int len = strlen(line);
    int chars[26] = {0};
    for (int i = 0; i < len; i++) {
        // Implicit conversion from character ASCII code to integer.
        chars[line[i] - 'a'] += 1;
    }
    // If any letter was seen multiple times, that array element is > 1.
    // Check if it is what we want. Return 1 if it is.
    for (int i = 0; i < 26; i++) {
        if(chars[i] == n) {
            return 1;
        }
    }
    return 0;
}

int has_one_diff(char* code_1, char* code_2, int print) {
    // The puzzle input specifies that codes are of the same length.
    // We just calculate one and proceed from there.
    int len = strlen(code_1);
    int diff = 0;
    for(int i = 0; i < len; i++) {
        if(code_1[i] != code_2[i]) {
            diff += 1;
        } else {
            // If we want to print the code, do it.
            if (print) {
                printf("%c", code_1[i]);
            }
        }
    }
    if (diff == 1) {
        return 1;
    }
    return 0;
}

int main() {

    FILE *fp;
    char input[256];

    int total_twos = 0;
    int total_threes = 0;

    int total_inputs = 0;
    char **input_strings = malloc(sizeof(char*));

    int code_found = 0;
    int checksum = 0;


    // Read the file.
    fp = fopen("./input.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while((fscanf(fp, "%s\n", input)) != EOF) {
        total_twos += has_n_letters(input, 2);
        total_threes += has_n_letters(input, 3);

        total_inputs++;
        input_strings = realloc(input_strings, sizeof(char*) * total_inputs);
        input_strings[total_inputs-1] = malloc((strlen(input)+1) * sizeof(char));
        strcpy(input_strings[total_inputs-1], input);
    }
    fclose(fp);

    // Print the checksum.
    checksum = total_twos*total_threes;
    printf("The checksum is: %d\n", checksum);

    // Now find the strings that differ by just one.
    // This is again O(n*n) since we're checking each code against all others.
    for(int i = 0; i < total_inputs; i++) {
        for(int j = i; j < total_inputs; j++) {
            if(has_one_diff(input_strings[i], input_strings[j], 0)) {
                printf("The expected code is: ");
                has_one_diff(input_strings[i], input_strings[j], 1);
                printf("\n");
                code_found = 1;
                break;
            }
        }
        if (code_found) {
            break;
        }
    }

    // Free all the allocated memory.
    for(int i = 0; i < total_inputs; i++) {
        free(input_strings[i]);
    }
    free(input_strings);

    return 0;
}
