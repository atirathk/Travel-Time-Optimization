#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "AKosireddyIM.h"
#define BUFFERSIZE 100

int fastest_path(int start_city, int end_city, int** adj_matrix, int n);
int search(int start_city, int current_city, int end_city, int** adj_matrix, int n, int prev_time);
int main(int argc, char* argv[])
{
    char buffer[BUFFERSIZE];
    const int n = atoi(fgets(buffer, BUFFERSIZE, stdin));
    int** adj_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) adj_matrix[i] = (int*)malloc((i + 1) * sizeof(int));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; j++)
            adj_matrix[i][j] = INT_MAX;
    int i = 0;
    int j = 0;
    //int i;
    while (fgets(buffer, BUFFERSIZE, stdin)) {
        char* token = strtok(buffer, " \n");
        while (token != NULL) {
            if (strcmp(token, "x") != 0)
                adj_matrix[i][j] = atoi(token);
            token = strtok(NULL, " \n");
            printf("%d ", adj_matrix[i][j]);
            ++j;
        }
        j = 0;
        //    printf("\n");
        ++i;
    }

    int minimum_times = fastest_path(1, 3, adj_matrix, n);
    return 0;
}

int fastest_path(int start_city, int end_city, int** adj_matrix, int n) {
    return search(start_city, start_city + 1, end_city, adj_matrix, n, 0);
}

int search(int start_city, int current_city, int end_city, int** adj_matrix, int n, int prev_time) {
    if (current_city == end_city) {
        if (current_city < start_city)
            return adj_matrix[start_city - 2][current_city - 1] + prev_time;
        else
            return adj_matrix[current_city - 2][start_city - 1] + prev_time;
    }
    int* time = calloc(n, sizeof(int));
    static bool searched[300];
    for (int i = 0; i < n; ++i) {
        if (!(searched[i] || current_city == i + 1)) {
            searched[current_city - 1] = true;
            if(current_city > 1)
                if (i > 0 && current_city <= i)
                    time[i] = min(search(current_city, i + 1, end_city, adj_matrix, n, adj_matrix[i - 1][current_city - 1]), adj_matrix[current_city - 2][end_city - 1]);
                else
                    time[i] = min(search(current_city, i + 1, end_city, adj_matrix, n, adj_matrix[current_city - 2][i]), adj_matrix[current_city - 2][end_city - 1]);
            else
                time[i] = min(search(current_city, i + 1, end_city, adj_matrix, n, adj_matrix[i - 1][current_city - 1]), adj_matrix[end_city - 2][current_city - 1]);
        }
    }
    searched[current_city - 1];
    int min_time = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (time[i] < min_time)
            if (time[i] > 0 || min_time < 0)
                min_time = time[i];
    }
    return min_time + prev_time;
}