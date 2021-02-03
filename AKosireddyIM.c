#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include "AKosireddyIM.h"
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define BUFFERSIZE 100
#define STATICSIZE 300

int main(int argc, char* argv[]) {
    printf("Atirath Kosireddy 2/21/2021\n");

    //This section of code gets the input size, and itializes a 2-D array according to the size
    char buffer[BUFFERSIZE];
    const int n = atoi(fgets(buffer, BUFFERSIZE, stdin));
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) adj_matrix[i] = (int*)malloc((i + 1) * sizeof(int));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++)
            adj_matrix[i][j] = INT_MAX;
    int i = 0;
    int j = 0;

    // This section of code reads from stdin, and places the data into a 2-D array
    while (fgets(buffer, BUFFERSIZE, stdin)) {
        char* token = strtok(buffer, " \n");
        while (token != NULL) {
            if (strcmp(token, "x") != 0)
                adj_matrix[i][j] = atoi(token);
            token = strtok(NULL, " \n");
            ++j;
        }
        j = 0;
        ++i;
    }

    // This loop gathers the least amount of time it takes to get to each destination into an array.
    int* times = malloc((n + 1) * sizeof(int));
    for (int i = 2; i <= n; ++i) {
        times[i - 2] = fastest_path(1, i, adj_matrix, n);
    }

    // This loop picks out the amount of time for the message to reach the very last city.
    int minimum_time = 0;
    for (int i = 0; i < n; i++) {
        if (minimum_time < times[i]) {
            minimum_time = times[i];
        }
    }

    // The result is printed here.
    printf("%d\n", minimum_time);
    return 0;
}

int fastest_path(int start_city, int end_city, int** adj_matrix, int n) {
    return search(start_city, start_city, end_city, adj_matrix, n, 0);
}

int search(int start_city, int current_city, int end_city, int** adj_matrix, int n, int prev_time) {
    // These return statements allow the function to deal with cases where the BFS reaches the end of a particular route
    if (current_city == end_city) {
        if (current_city < start_city)
            return adj_matrix[start_city - 2][current_city - 1] + prev_time;
        else
            return adj_matrix[current_city - 2][start_city - 1] + prev_time;
    }

    // This section performs a BFS and gathers how much time it takes to travel along different routes. It will gather the most efficient routes
    // into the time array.
    int* time = calloc(n, sizeof(int));
    static int fastest_times[STATICSIZE];
    static int fast_index = 0;
    static bool searched[STATICSIZE][STATICSIZE];
    searched[0][0] = true;
    for (int i = start_city - 1; i < n; ++i) {
        if (!(searched[current_city - 1][i] == true || searched[i][current_city - 1] == true || current_city == i + 1)) {
            searched[start_city - 1][current_city - 1] = true;
            searched[current_city - 1][start_city - 1] = true;
            if (current_city > 1)
                if (i > 0 && current_city <= i)
                    time[i] = min(search(current_city, i + 1, end_city, adj_matrix, n, adj_matrix[i - 1][current_city - 1]), adj_matrix[current_city - 2][end_city - 1]);
                else
                    time[i] = min(search(current_city, i + 1, end_city, adj_matrix, n, adj_matrix[current_city - 2][i]), adj_matrix[current_city - 2][end_city - 1]);
            else
                time[i] = min(search(start_city, i + 1, end_city, adj_matrix, n, adj_matrix[i - 1][current_city - 1]), adj_matrix[end_city - 2][current_city - 1]);
        }
    }

    // This sifts through the the time array to find thhe best route from a particular city in the middle of the empire
    int min_time = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (time[i] < min_time)
            if (time[i] > 0 || min_time < 0)
                min_time = time[i];
    }

    // This searches for the most efficient subroute, and then adds the subroute time to the total route time.
    if(min_time != INT_MAX) fastest_times[current_city - 1] = min_time + prev_time;
    return fastest_times[current_city - 1];
}