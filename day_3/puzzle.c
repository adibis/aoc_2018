#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

#define REALLOC_SIZE 32

typedef struct {
    int coord_x;
    int coord_y;
    int size_x;
    int size_y;
    int id;
} fabric_t;

void setup_max_coord(int *min_x, int *max_x, int *min_y, int *max_y, const fabric_t fabric) {
    int this_min_x = fabric.coord_x;
    int this_min_y = fabric.coord_y;
    int this_max_x = fabric.coord_x + fabric.size_x;
    int this_max_y = fabric.coord_y + fabric.size_y;

    if (*min_x > this_min_x)
        *min_x = this_min_x;
    if (*min_y > this_min_y)
        *min_y = this_min_y;
    if (*max_x < this_max_x)
        *max_x = this_max_x;
    if (*max_y < this_max_y)
        *max_y = this_max_y;
}

int main() {

    FILE *fp;
    size_t realloc_counter = REALLOC_SIZE;

    int total_fabrics = 0;

    // Maximum X and Y coordinates seen in the input.
    int max_x = 0;
    int max_y = 0;
    int min_x = INT_MAX;
    int min_y = INT_MAX;

    fabric_t fabric;
    fabric_t *fabrics = (fabric_t*)malloc(REALLOC_SIZE*realloc_counter*sizeof(fabric_t));

    int **big_fabric;

    int overlap_counter = 0;
    bool good_fabric = true;

    // Read the file.
    fp = fopen("./input.txt", "r");
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while((fscanf(fp, "#%d @ %d, %d: %dx%d\n", &fabric.id
                                             , &fabric.coord_x
                                             , &fabric.coord_y
                                             , &fabric.size_x
                                             , &fabric.size_y
                                               )) != EOF) {

        setup_max_coord(&min_x, &max_x, &min_y, &max_y, fabric);
        fabrics[total_fabrics] = fabric;
        total_fabrics++;
        if(total_fabrics >= (int)realloc_counter) {
            realloc_counter += REALLOC_SIZE;
            fabrics = (fabric_t*)realloc(fabrics, realloc_counter*sizeof(fabric_t));
        }
    }
    fclose(fp);

    // Create the big fabric (of all coordinates)
    // All the shenanigans with the max coordinates was to save space.
    big_fabric = (int **)calloc((max_x - min_x), sizeof(int *));
    for(int i = 0; i < (max_x - min_x); i++) {
        big_fabric[i] = (int *)calloc((max_y - min_y), sizeof(int));
    }

    // My logic here is to tag each square which has been seen.
    // If you encounter same square twice then mark that separately.
    for(int i = 0; i < total_fabrics; i++) {
        fabric = fabrics[i];
        for (int j = 0; j < fabric.size_x; j++) {
            for (int k = 0; k < fabric.size_y; k++) {
                big_fabric[fabric.coord_x+j-min_x][fabric.coord_y+k-min_y] += 1;
            }
        }
    }

    // Go through the whole graph and see which elements were tagged more than once.
    for(int j = 0; j < (max_x - min_x); j++) {
        for (int k = 0; k < (max_y - min_y); k++) {
            if (big_fabric[j][k] > 1) {
                overlap_counter++;
            }
        }
    }
    printf("Overlap Counter is: %d\n", overlap_counter);

    // Loop through all the fabrics to see which ones are good {no overlap}
    for(int i = 0; i < total_fabrics; i++) {
        good_fabric = true;
        fabric = fabrics[i];
        for (int j = 0; j < fabric.size_x; j++) {
            for (int k = 0; k < fabric.size_y; k++) {
                if((big_fabric[fabric.coord_x+j-min_x][fabric.coord_y+k-min_y]) > 1) {
                    good_fabric = false;
                }
            }
        }
        if (good_fabric == true) {
            printf("Good fabric ID is: %d\n", fabric.id);
            break;
        }
    }

    // Free all the allocated memory.
    free(fabrics);
    for(int i = 0; i < (max_x - min_x); i++) {
        free(big_fabric[i]);
    }
    free(big_fabric);

    return 0;
}
