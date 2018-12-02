#include<stdio.h>

// This is a horrible implementation for this code but - what the heck.
// I am not about to implement a set for C because of this.
// Basically takes pretty much O(n) for each search instead of O(1) for real hash table / set.
int check_seen_values(int frequency, int seen_values[]) {
    for(int i = 0; i < 1000000; i++) {
        if(seen_values[i] == frequency) {
            return 1;
        }
        if(seen_values[i] == 0) {
            return 0;
        }
    }
    return 0;
}

int main() {

    FILE *fp;
    int fr;
    char op;
    int num;

    int frequency = 0;
    int duplicate_frequency = 0;
    int seen_values[1000000];
    int i;

    // This is a horrible implementation for this code but - what the heck.
    // I am not about to implement a set for C because of this.
    for(i = 0; i < 1000000; i++) {
        seen_values[i] = 0;
    }

    i = 0;
    fp = fopen("./input.txt", "r");
    while(duplicate_frequency == 0) {
        while((fr = fscanf (fp, "%c%d\n", &op, &num)) != EOF) {
            if(op == '+') {
                frequency += num;
            }
            if(op == '-') {
                frequency -= num;
            }
            if((check_seen_values(frequency, seen_values)) == 0) {
                seen_values[i] = frequency;
                i++;
            } else {
                duplicate_frequency = 1;
                break;
            }
        }
        fseek(fp, 0, 0);
    }

    printf("Final frequency = %d\n", frequency);

    fclose(fp);
    return 0;
}
