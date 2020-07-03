#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"

int main(void) {
    int i = 0;
    int j = 0;
    graph g;
    
    /* FILE* file = fopen("example-1.txt", "r"); */
    fscanf(stdin, "%d", &i);
    g = graph_new(i);
    while(fscanf(stdin, "%d %d", &i, &j) == 2) {
        graph_add_edge(g, i, j);
    }
    /* fclose(file);*/
    
    graph_dfs(g);
   
    print_sort(g);
    /*graph_print(g);*/
    graph_free(g);
    return EXIT_SUCCESS;
}
