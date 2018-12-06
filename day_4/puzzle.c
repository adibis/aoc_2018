#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

#define REALLOC_SIZE 32

// String comparison function.
// Compare function is standard for string. More information at:
// https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/qsort.htm
int sort_inputs(const void *input_a, const void *input_b) {
    return (strcmp( *(const char **)input_a, *(const char **)input_b));
}

int main() {

    FILE *fp;
    size_t realloc_counter = REALLOC_SIZE;

    char* input = NULL;
    size_t input_len;
    size_t read;
    char **inputs = malloc(realloc_counter*(sizeof(char*)));
    int total_inputs = 0;

    // We only care about minutes so create a list of guards each with 60 minutes of data.
    size_t guard_counter = REALLOC_SIZE * 2;
    // FIXME: Figure out a way to realloc this and initialize new mem to zero.
    int (*guards)[61] = calloc(guard_counter,(sizeof(int[61])));
    int total_guards = 0;

    // These names could be clearer.
    int sleepiest_guard;
    int consistent_guard = 0;
    int consistent_guard_id;
    int consistent_minute = 0;
    int sleepiest_minute;
    int max_sleep = 0;

    // Read the file.
    fp = fopen("./input.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while ((read = getline(&input, &input_len, fp)) != -1) {
        input[strcspn(input, "\r\n")] = 0;
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
        //printf ("Current Input = %s\n", inputs[i]);
        int sleep_start, sleep_end, current_guard;
        int dump_id;
        int repeat_guard = 0;
        if(inputs[i][25] == '#') {
            current_guard = atoi(inputs[i]+26);
            // Save the current guard ID in the last element of guards array.
            // Sort of a trick to avoid having to create dictionary.
            for (int j = 0; j < total_guards; j++) {
                if (guards[j][60] == current_guard) {
                    repeat_guard = 1;
                    dump_id = j;
                    break;
                }
            }
            // If it's a new guard create new entry otherwise dump to old one.
            if (repeat_guard != 1) {
                guards[total_guards][60] = current_guard;
                dump_id = total_guards;
                total_guards++;
            }
            // Since we only care about the minute part - ignore the rest.
        } else if(inputs[i][25] == 'a') {
            sleep_start = atoi(inputs[i]+15);
        } else if(inputs[i][25] == 'u') {
            sleep_end = atoi(inputs[i]+15);
            for(int j = sleep_start; j < sleep_end; j++) {
                guards[dump_id][j]++;
            }
        }
    }

    // Now iterate through the set array of guards and compute the necessary values.
    for(int i = 0; i < total_guards; i++) {
        int total_sleep = 0;
        int min_max_slept = 0;
        for(int j = 0; j < 60; j++) {
            total_sleep += guards[i][j];
            // If any guard has slept more minutes on any day then that guard is more consistent and that minute is the most consistent.
            if(guards[i][j] > guards[consistent_guard][consistent_minute]) {
                consistent_guard_id = guards[i][60];
                consistent_guard = i;
                consistent_minute = j;
            }
            // Figure out what is the most minutes each guard has slept.
            if(guards[i][j] > guards[i][min_max_slept]) {
                min_max_slept = j;
            }
        }
        // If current guard has slept the most then we need the minute he slept most on. Capture that.
        if (total_sleep > max_sleep) {
            sleepiest_guard = guards[i][60];
            sleepiest_minute = min_max_slept;
            max_sleep = total_sleep;
        }
    }

    // Calculate and print all results.
    printf ("Guard who slept the most is: %d\n", sleepiest_guard);
    printf ("Sleepiest minute is: %d\n", sleepiest_minute);
    printf ("Guard who sleeps consistently is: %d\n", consistent_guard_id);
    printf ("Consistently slept minute is: %d\n", consistent_minute);
    printf ("PART 1: %d\n", sleepiest_guard*sleepiest_minute);
    printf ("PART 2: %d\n", consistent_guard_id*consistent_minute);

    // Free all the allocated memory.
    for(int i = 0; i < total_inputs; i++) {
        free(inputs[i]);
    }
    free(inputs);
    free(guards);

    return 0;
}
