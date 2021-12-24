#include <stdbool.h>
#include <stdlib.h>


#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct {
   int from;
   int to;
   int cost;
} edge_t;

typedef struct {
   edge_t *edges;
   int num_edges;
   int capacity;
} graph_t;

graph_t * allocate_graph(void);

void free_graph(graph_t **graph);

graph_t * enlarge_graph(graph_t *graph);

void print_graph(graph_t *graph);

/* Load a graph from the text file. */
_Bool load_txt(const char *fname, graph_t *graph);
/* Load a graph from the binary file. */
_Bool load_bin(const char *fname, graph_t *graph);

/* Save the graph to the text file. */
_Bool save_txt(const graph_t * const graph, const char *fname);
/* Save the graph to the binary file. */
_Bool save_bin(const graph_t * const graph, const char *fname);

#endif
