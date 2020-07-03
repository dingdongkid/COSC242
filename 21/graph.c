#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mylib.h"

typedef enum { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

typedef struct vertex *vert;

struct vertex {
    state_t state;
    int predecessor;
    int distance;
    int finish;
};

struct graphrec {
    int size;
    int **edges;
    vert *vertices;
};

static int step;

/**
 * Creates a new graph, setting size, array matrix, edges array, and vertices
 * array.
 * @param i a desired size for the graph.
 * @return a new graph.
 */
graph graph_new(int i) {
    int rows;
    int cols;
    graph result = emalloc(sizeof *result);
    result->size = i;
    result->edges = emalloc(i * sizeof result->edges[0]);
    for(rows = 0; rows < i; rows++) {
        result->edges[rows] = emalloc(i * sizeof result->edges[0][0]);
    }
    for(rows = 0; rows < i; rows++) {
        for(cols = 0; cols < i; cols++) {
            result->edges[rows][cols] = 0;
        }
    }
    result->vertices = emalloc(i * sizeof result->vertices[0]);
    return result;
}

/**
 * Frees the memory used by a graph.
 * @param g a graph to be freed.
 */
void graph_free(graph g) {
    int i;
    for(i = 0; i < g->size; i++) {
        free(g->edges[i]);
        free(g->vertices[i]);
    }
    free(g->edges);
    free(g->vertices);
    free(g);
}

/**
 * Connects two vertices with a directed link
 * @param g a graph with vertices.
 * @param src first vertex.
 * @param des second vertex.
 */
void graph_add_edge(graph g, int src, int des) {
    g->edges[src][des] = 1;
}

/**
 * Connects two vertices with an undirected link
 * @param g a graph with vertices.
 * @param src first vertex.
 * @param des second vertex.
 */
void graph_add_2edge(graph g, int src, int des) {
    g->edges[src][des] = 1;
    g->edges[des][src] = 1;
}

/**
 * Prints the contents of a graph.
 * @param a graph to print from.
 */
void graph_print(graph g) {
    int rows;
    int cols;
    for(rows = 0; rows < g->size; rows++) {
        for(cols = 0; cols < g->size; cols++) {
            printf("%d ", g->edges[rows][cols]);
        }
        printf("\n");
    }
}

/**
 * Allocates memory for a new vertex.
 * @return an empty vertex.
 */
vert vert_new() {
    vert result = emalloc(sizeof *result);
    result->state = UNVISITED;
    result->distance = -1;
    result->predecessor = -1;
    result->finish = 0;
    return result;
}

/**
 * Visit each vertex in the graph.
 * @param g graph to search in.
 * @param v vertex to search from.
 */
void visit(graph g, int v) {
    int u;
    g->vertices[v]->state = VISITED_SELF;
    step++;
    g->vertices[v]->distance = step;
    for (u = 0; u < g->size; u++) {
        if(g->edges[v][u] == 1) {
            if (g->vertices[u]->state == UNVISITED) {
                g->vertices[u]->predecessor = v;
                visit(g, u);
            }
        }
    }
    step++;
    g->vertices[v]->state = VISITED_DESCENDANTS;
    g->vertices[v]->finish = step;
}

/**
 * Depth first search implementation.
 * @param g graph to search from.
 */
void graph_dfs(graph g) { 
    int i;
    for(i = 0; i < g->size; i++) {
	g->vertices[i] = vert_new();
	g->vertices[i]->state = UNVISITED;
	g->vertices[i]->predecessor = -1;
    }
    step = 0;
    for (i = 0; i < g->size; i++) {
	if (g->vertices[i]->state == UNVISITED) {
            visit(g, i);
        }
    }
}

/**
 * Prints statistics of a given graph.
 * @param g a graph to search through.
 */
void print_sort(graph g) {
    int i;
    int j;
    int toPrint;
    int printed;
    
    printf("adjacency list:\n");
    for(i = 0; i < g->size; i++) {
        printf("%d | ", i);
        toPrint = 0;
        printed = 0;
        
        for(j = 0; j < g->size; j++) {
            if(g->edges[i][j] == 1) {
                toPrint++;
            }
        }

        if(toPrint == 0) {
            printf("\n");
        } else {
            for (j = 0; j < g->size; j++) {
                if(g->edges[i][j] == 1) {
                    printf("%d", j);
                    printed++;
                    if(printed < toPrint) {
                        printf(", ");
                    }
                }
            }
            printf("\n");
        }
    }

    printf("\n");
    printf("vertex distance pred finish\n");
    for(i = 0; i < g->size; i++) {
        printf("   %d       %d   %2d   %2d\n", i, g->vertices[i]->distance,
               g->vertices[i]->predecessor, g->vertices[i]->finish);
    }
    printf("\n");
}
