#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
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
 * Frees memory used by the graph.
 * @param g graph to be freed.
 */
void graph_free(graph g) {
    int i;
    for(i = 0; i < g->size; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    for(i = 0; i < g->size; i++) {
        free(g->vertices[i]);
    }
    free(g->vertices);
    free(g);
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
 * Connects two vertices with a directed link
 * @param g a graph with vertices.
 * @param src first vertex.
 * @param des second vertex.
 */
void graph_add_edge(graph g, int src, int des) {
    g->edges[src][des] = 1;
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
 * Breadth-first search implementation.
 * @param g a graph to search.
 * @param src a vertex to start from.
 */
void graph_bfs (graph g, int src) {
    int i;
    int u;
    int v;
    queue q = queue_new();

    /* Initialise all vertices */
    for(i = 0; i < g->size; i++) {
	g->vertices[i] = vert_new();
    }

    /* Set source vertex to visited, distance to 0, and add to queue */
    g->vertices[src]->state = VISITED_SELF;
    g->vertices[src]->distance = 0;
    enqueue(q, src);

    /* Search through vertices associated with the source and set their
       distances and predecessors */
    while(queue_size(q) > 0) {
	u = dequeue(q);
        /* Look at all adjacent, unvisited vertices, add them to the queue */
        for (v = 0; v < g->size; v++) {
            if(g->edges[u][v] == 1) {
                if (g->vertices[v]->state == UNVISITED) {
                    g->vertices[v]->state = VISITED_SELF;
                    g->vertices[v]->distance = g->vertices[u]->distance + 1;
                    g->vertices[v]->predecessor = u;
                    enqueue(q, v);
                }
            }
        }
        g->vertices[u]->state = VISITED_DESCENDANTS;
    }
    queue_free(q);
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

    /* Read adjacency matrix and print as an adjacency list */
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

    /* Print statistics of each vertex */
    printf("\n");
    printf("vertex distance pred\n");
    for(i = 0; i < g->size; i++) {
        printf("   %d       %d   %d\n", i, g->vertices[i]->distance,
               g->vertices[i]->predecessor);
    }
}
