#ifndef AKOSIREDDYIM_H
#define AKOSIREDDYIM_H
//Purpose:
//    This function will find the fastest path between the start city and end city
//Inputs:
//    start_city: 
//        The city that the message will originate from
//    end_city: 
//        The city that you want to find a path to
//    adj_matrix: 
//        The adjacency matrix that is used to find a path
//    n:
//        The dimension of adj_matrix
int fastest_path(int start_city, int end_city, int** adj_matrix, int n);

//Purpose:
//    This function will crawl around the adjacency matrix to find the most efficient path. It does the heavy lifting for fastest_path()
//Inputs:
//    start_city: 
//        The city that you just traveled from.
//    current_city:
//        The city that you are currently in
//    end_city: 
//        The city that you want to find a path to
//    adj_matrix: 
//        The adjacency matrix that is used to find a path
//    n:
//        The dimension of adj_matrix
int search(int start_city, int current_city, int end_city, int** adj_matrix, int n, int prev_time);
#endif