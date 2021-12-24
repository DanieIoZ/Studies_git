#ifndef __GRAPH_UTILS_H__
#define __GRAPH_UTILS_H__

#include "graph.h"

graph_t * allocate_graph(void);

void free_graph(graph_t **graph);

graph_t * enlarge_graph(graph_t *graph);

void print_graph(graph_t *graph);

/* Load a graph from the text file. */
int load_txt(const char *fname, graph_t *graph);
/* Load a graph from the binary file. */
int load_bin(const char *fname, graph_t *graph);

/* Save the graph to the text file. */
int save_txt(const graph_t * const graph, const char *fname);
/* Save the graph to the binary file. */
int save_bin(const graph_t * const graph, const char *fname);

#endif
