#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "AKosireddyIM.h"
#define BUFFERSIZE 100

int all_paths(int start_city, int current_city, int end_city, int** adj_matrix, int n);
int* fastest_paths(int** path_matrix);
int main(int argc, char* argv[])
{
    char buffer[BUFFERSIZE];
    const int n = atoi(fgets(buffer, BUFFERSIZE, stdin));
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) adj_matrix[i] = (int*)malloc((n - 1) * sizeof(int));
    int i = 0;
    int j = 0;
    //int i;
    while (fgets(buffer, BUFFERSIZE, stdin)) {
        char* token = strtok(buffer, " \n");
        while (token != NULL) {
            if (strcmp(token, "x") == 0) adj_matrix[i][j] = -1;
            else adj_matrix[i][j] = atoi(token);
            token = strtok(NULL, " \n");
            printf("%d ", adj_matrix[i][j]);
            ++j;
        }
        j = 0;
        //    printf("\n");
        ++i;
    }

    int minimum_times = all_paths(1, 1, 2, adj_matrix, n);
    /*for (int path_row = 0; path_row < n; ++path_row) {
        for (int path_col = 0; path_col < n; ++path_col) {
            printf("%d ", path_matrix[path_row][path_col]);
        }
        printf('\n');
    }*/

    return 0;
}

int all_paths(int start_city, int current_city, int end_city, int** adj_matrix, int n) {
    if (current_city > n) return INT_MAX;
    int* times = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) times[i] = INT_MAX;
    static bool visited[300];
    visited[start_city - 1] = true;
    if (current_city != end_city)visited[current_city - 1] = true;
    int* queue = malloc(n * sizeof(int));
    int i = 0;
    for (; i < n; ++i) {
        if (!visited[i] && current_city != end_city) {
            if (times[i] == INT_MAX) times[i] = 0;
            times[i] += all_paths(start_city + 1, i + 1, end_city, adj_matrix, n);
        }
    }
    int min_time = INT_MAX;
    if (current_city == end_city) return adj_matrix[current_city - 2][end_city - 2];
    if (current_city > 1) return adj_matrix[current_city - 2][end_city - 1] + adj_matrix[current_city - 2][start_city - 2];
    else if (current_city == 1) {
        for (int i = 0; i < n; ++i) {
            if (times[i] < min_time && times[i] > -1) {
                min_time = times[i];
            }
        }
    }
    else return min(adj_matrix[current_city - 2][end_city - 1], all_paths(start_city, current_city + 1, end_city, adj_matrix, n));

    return min_time;
}

/*int** all_paths(int start_city, int end_city, int** adj_matrix) {
    int length = sizeof(adj_matrix) / 2;
    int** path_matrix = (int**)malloc(sizeof(adj_matrix) * sizeof(int*));
    for (int i = 0; i < length; ++i) path_matrix[i] = (int*)malloc(length * sizeof(int));
    int stops_offset = 1;
    int first_stop_offset = 3;
    for (int stops = 0; stops < length; ++stops) {
        path_matrix[stops][current_city] = adj_matrix[current_city][0];
    //    printf("%d ", path_matrix[0][current_city]);
    }
    for (int path_col = 1; path_col < length; ++path_col) {
        for (int path_row = 1; path_row < length; ++path_row) {
            path_matrix[path_row][path_col] = path_matrix[path_row - 1][path_col] + adj_matrix[path_row][path_col];
        }
    }

    return path_matrix;
}*/

int* fastest_paths(int** path_matrix) {
    int length = sizeof(path_matrix) / sizeof(int*);
    int* fastest_paths = (int*)malloc(length * sizeof(int));
    return fastest_paths;
}