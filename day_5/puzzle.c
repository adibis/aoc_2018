#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<limits.h>

#define REALLOC_SIZE 32

// Remove a character from a string
void remove_char(char **input, char c) {
    char *read = *input;
    char *write = *input;

    // Advance read pointer till the end.
    // Only advance write pointer if the char != c
    while (*read) {
        *write = *read++;
        write += (*write!= c);
    }
    *write = '\0';

}

// Remove element at ith index.
// Using this since memmove fails on overlapping memory for me.
void remove_ith_elem(char **input, size_t i) {
    size_t len = strlen(*input);

    for (; i < len - 1; i++) {
        (*input)[i] = (*input)[i+1];
    }
    (*input)[i] = '\0';
}

// Remove opposite poles from the string.
void remove_poles(char **input, size_t *input_len) {
    bool was_reduced = true;
    while (was_reduced == true) {
        was_reduced = false;
        // Go through the string from the end - compare and remove opposite poles.
        // Keep repeating until one pass completes without reduction.
        for(int i = *input_len-1; i > 0; i--) {
            if (i == (int)*input_len-1) {
                continue;
            } else {
                // Check if the letters are a small/caps pair.
                if((*input)[i] - (*input)[i+1] == 32 || (*input)[i] - (*input)[i+1] == -32) {
                    // For some reason memmove doesn't work here.
                    // Could be due to overlapping memory.
                    // Use own function to remove from the string.
                    remove_ith_elem(input, i+1);
                    remove_ith_elem(input, i);
                    *input_len -= 2;
                    was_reduced = true;
                }
            }
        }
    }
}

int main() {

    FILE *fp;
    size_t realloc_counter = REALLOC_SIZE;

    size_t input_len = 0;
    size_t golden_len = 0;
    char *input = malloc(realloc_counter);
    char *golden_input;
    char letter;

    int small_letter = 65;
    int caps_letter = 97;
    int smallest_length;

    // Read the file.
    fp = fopen("./input.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while ((letter = fgetc(fp)) != EOF) {
        input[input_len++] = (char)letter;
        if(input_len >= realloc_counter) {
            realloc_counter += REALLOC_SIZE;
            input = realloc(input, realloc_counter);
        }
    }
    input[input_len] = '\0';
    fclose(fp);

    // Before making any changes to the input, save a golden copy for part 2.
    golden_len = input_len;
    golden_input = malloc(golden_len);
    strcpy(golden_input, input);

    // Now go ahead and reduce the input to find the final length.
    remove_poles(&input, &input_len);

    // Final length is 1 less than the string length to account for \0
    printf ("Final reduced length = %d\n", (int)input_len - 1);

    // Now start off removing one letter from the string at a time.
    // Then reduce it and find the smallest length.
    smallest_length = strlen(golden_input);
    for (int i = 0; i < 26; i++) {
        // Reset the input on each pass.
        strcpy(input, golden_input);
        // Use ASCII code of letters to remove them from string.
        remove_char(&input, (i+small_letter));
        remove_char(&input, (i+caps_letter));
        input_len = strlen(input);
        remove_poles(&input, &input_len);
        if ((int)input_len < smallest_length) {
            smallest_length = (int)input_len;
        }
    }

    printf ("Final smallest length = %d\n", (int)smallest_length - 1);

    // Free all the allocated memory.
    free(input);
    free(golden_input);

    return 0;
}
