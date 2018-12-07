#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

#define REALLOC_SIZE 32

typedef struct {
    int x;
    int y;
    int influence;
} node_t;

void setup_max_coord(int *min_x, int *max_x, int *min_y, int *max_y, const node_t node) {

    if (*min_x > node.x)
        *min_x = node.x;
    if (*min_y > node.y)
        *min_y = node.y;
    if (*max_x < node.x)
        *max_x = node.x;
    if (*max_y < node.y)
        *max_y = node.y;
}

void gen_dist_values(int min_x, int min_y, int max_x, int max_y, int total_nodes, node_t **nodes) {
#ifdef TEST
    int bounded_area = 32;
#else
    int bounded_area = 10000;
#endif
    int bounded_region = 0;
    for (int x = min_x; x < max_x; x++) {
        for (int y = min_y; y < max_y; y++) {
            int min_dist = INT_MAX;
            int closest_node = -1;
            bool eq_dist = false;
            int this_dist = 0;
            int total_dist = 0;
            for (int i = 0; i < total_nodes; i++) {
                this_dist = abs((*nodes)[i].x - x) + abs((*nodes)[i].y - y);
#ifdef DEBUG
                printf("Dist for (x,y) = (%d,%d) for node[i] = node[%d]\n", x, y, i);
                printf("Dist = %d\n", this_dist);
#endif
                total_dist += this_dist;
                if (this_dist <= min_dist) {
                    if (this_dist != min_dist) {
                        min_dist = this_dist;
                        eq_dist = false;
                        closest_node = i;
                    } else {
                        eq_dist = true;
                    }
                }
            }
            if (eq_dist == false) {
                (*nodes)[closest_node].influence += 1;
            }
            if (total_dist < bounded_area) {
                bounded_region += 1;
            }
        }
    }

    printf("PART 2: Total bounded region = %d\n", bounded_region);
}

int main() {

    FILE *fp;
    size_t realloc_counter = REALLOC_SIZE;

    // Maximum X and Y coordinates seen in the input.
    int max_x = 0;
    int max_y = 0;
    int min_x = INT_MAX;
    int min_y = INT_MAX;

    node_t node;
    node_t *nodes_a = malloc(realloc_counter*sizeof(node_t));
    node_t *nodes_b = malloc(realloc_counter*sizeof(node_t));
    int total_nodes = 0;

    int max_influence = 0;

    // Read the file.
#ifdef TEST
    fp = fopen("./test.txt", "r");
#else
    fp = fopen("./input.txt", "r");
#endif
    if (fp == NULL) {
        perror("input.txt");
        exit(EXIT_FAILURE);
    }

    // Store all values in a buffer.
    while((fscanf(fp, "%d, %d\n", &node.x, &node.y)) != EOF) {

        setup_max_coord(&min_x, &max_x, &min_y, &max_y, node);
        node.influence = 0;
        nodes_a[total_nodes] = node;
        nodes_b[total_nodes] = node;
        total_nodes++;
#ifdef DEBUG
        printf("Adding node: %d, %d\n", node.x, node.y);
#endif
        if(total_nodes >= (int)realloc_counter) {
            realloc_counter += REALLOC_SIZE;
            nodes_a = realloc(nodes_a, realloc_counter*sizeof(node_t));
            nodes_b = realloc(nodes_b, realloc_counter*sizeof(node_t));
        }
    }
    fclose(fp);

#ifdef DEBUG
    printf("Coord: %d, %d\n", min_x, max_x);
    printf("Coord: %d, %d\n", min_y, max_y);
#endif

    gen_dist_values(min_x, min_y, max_x, max_y, total_nodes, &nodes_a);
    gen_dist_values(min_x-1, min_y-1, max_x+1, max_y+1, total_nodes, &nodes_b);

    for (int i = 0; i < total_nodes; i++) {
        if (nodes_a[i].influence == nodes_b[i].influence) {
            if(nodes_a[i].influence > max_influence) {
                max_influence = nodes_a[i].influence;
            }
        }
    }

    printf("PART 1: Max Influence = %d\n", max_influence);

    // Free all the allocated memory.
    free(nodes_a);
    free(nodes_b);

    return 0;
}
