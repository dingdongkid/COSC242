#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct graphrec *graph;

extern graph graph_new(int i);
extern void  graph_add_edge(graph g, int src, int des);
extern void  graph_add_2edge(graph g, int src, int des);
extern void  graph_dfs(graph g);
extern void  graph_free(graph g);
extern void  graph_print(graph g);
extern void  print_sort(graph g);

#endif
