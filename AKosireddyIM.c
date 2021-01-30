#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AKosireddyIM.h"
#define BUFFERSIZE 100

int** all_paths(int start_city, int** adj_matrix);
int* fastest_paths(int** path_matrix);
int main(int argc, char* argv[])
{
    char buffer[BUFFERSIZE];
    const int n = atoi(fgets(buffer, BUFFERSIZE, stdin));
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) adj_matrix[i] = (int*)malloc(n * sizeof(int));
    int i = 0;
    int j = 0;
    //int i;
    while (fgets(buffer, BUFFERSIZE, stdin)) {
        char* token = strtok(buffer, " \n");
        while (token != NULL) {
            adj_matrix[i][j] = atoi(token);
            token = strtok(NULL, " \n");
            printf("%d ", adj_matrix[i][j]);
            ++j;
        }
        printf("\n");
        ++i;
    }


    return 0;
}

int** all_paths(int start_city, int** adj_matrix) {
    int length = size_of(adj_matrix);
    int** path_matrix = (int**)malloc(length * sizeof(int));
    for (int i = 0; i < length; ++i) adj_matrix[i] = (int*)malloc(length * sizeof(int));
    int row_offset = 2;
    int col_offset = 1;
    for (int current_city = 0; current_city < length; ++current_city) {
        path_matrix[current_city][0] = adj_matrix[current_city][start_city - col_offset];
    }
    for (int path_col = 1; path_col < length; ++path_col) {
        for (int path_row = 1; path_row < length; ++path_row) {
            path_matrix[path_row][path_col] = path_matrix[path_row][path_col - 1] + adj_matrix[path_row][path_col];
        }
    }
    return path_matrix;
}

int* fastest_paths(int** path_matrix) {
    int length = size_of(path_matrix);
    int* fastest_paths = (int*)malloc(length * sizeof(int));
    return fastest_paths;
}