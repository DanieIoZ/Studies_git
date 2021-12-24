#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "my_malloc.h"
#include "graph.h"

#ifndef INIT_SIZE 
#define INIT_SIZE 10



#endif
#define BIN_BUFFER 4
graph_t* allocate_graph(void) 
{
   graph_t * graph = (graph_t*) malloc(sizeof(graph_t));
   graph->edges = malloc(sizeof(edge_t) * INIT_SIZE);
   graph->num_edges = 0;
   graph->capacity = INIT_SIZE;
   return graph;
}

void free_graph(graph_t **g) 
{
   assert(g != NULL && *g != NULL);
   if ((*g)->capacity > 0) {
      free((*g)->edges);
   }
   free(*g);
   *g = NULL;
}

graph_t* enlarge_graph(graph_t *graph) 
{
   graph->capacity *= 2;
   graph->edges = realloc(graph->edges, graph->capacity * sizeof(edge_t) * 2);
   return graph;
}

void print_graph(graph_t *g) 
{
   assert(g != NULL);
   fprintf(stderr, "Graph has %d edges and %d edges are allocated\n", g->num_edges, g->capacity);
   edge_t *e = g->edges;
   for (int i = 0; i < g->num_edges; ++i, ++e) {
      printf("%d %d %d\n", e->from, e->to, e->cost);
   }
}

_Bool load_txt(const char *fname, graph_t *graph)
{
   _Bool ret = false;
   FILE * f = fopen(fname, "r");
   int reading = 1;
   while (f && reading)
   {
      if (graph->num_edges == graph->capacity) 
      {
         graph = enlarge_graph(graph);
      }
      int cur_num = 0;
      int reads = 0;
      char buff[20];
      int nums[3];
      while ((graph->num_edges < graph->capacity)) 
      {
         while ((buff[reads] = getc(f)) >= '0' && buff[reads] <= '9')
         {
            reads++;
         }
         nums[cur_num] = atoi(buff);
         cur_num++;
         reads = 0;
         if (cur_num > 2)
         {
            graph->edges[graph->num_edges].from = nums[0];
            graph->edges[graph->num_edges].to = nums[1];
            graph->edges[graph->num_edges].cost = nums[2];
            cur_num = 0;
            graph->num_edges++;
         }
         if (feof(f))
         {
            reading = 0;
            break;
         }
      }
   }
   if (f) 
   {
      ret = fclose(f) == 0;
   }
   return ret;
}

// - function -----------------------------------------------------------------
_Bool load_bin(const char *fname, graph_t *graph)
{
   _Bool ret = false;
   FILE * f = fopen(fname, "rb");
   int reading = 1;
   while (f && !feof(f) && reading) 
   {
      if (graph->num_edges == graph->capacity) 
      {
         enlarge_graph(graph);
      }
      while (graph->num_edges < graph->capacity) 
      {
         int reads = 0;
         reads += fread(&(graph->edges[graph->num_edges].from), BIN_BUFFER, 1, f);
         reads += fread(&(graph->edges[graph->num_edges].to), BIN_BUFFER, 1, f);
         reads += fread(&(graph->edges[graph->num_edges].cost), BIN_BUFFER, 1, f);

         if (reads < 3)
         {
            reading = 0;
            break;
         }
         graph->num_edges++;
      }
   }
   if (f) 
   {
      ret = fclose(f) == 0;
   }
   return ret;
}

// - function -----------------------------------------------------------------
_Bool save_txt(const graph_t * const graph, const char *fname)
{
   _Bool ret = false;
   FILE * f = fopen(fname, "w");
   for (int i = 0; i < graph->num_edges; i++)
   {
      fprintf(f, "%d %d %d\n", graph->edges[i].from, graph->edges[i].to, graph->edges[i].cost);
   }
   if (f) 
   {
      ret = fclose(f) == 0;
   }
   return ret;
}

// - function -----------------------------------------------------------------
_Bool save_bin(const graph_t * const graph, const char *fname)
{
   _Bool ret = false;
   FILE * f = fopen(fname, "wb");
   for (int i = 0; i < graph->num_edges; i++)
   {
      fwrite((const void*)&(graph->edges[i].from), BIN_BUFFER, 1, f);
      fwrite((const void*)&(graph->edges[i].to), BIN_BUFFER, 1, f);
      fwrite((const void*)&(graph->edges[i].cost), BIN_BUFFER, 1, f);
   }
   if (f) 
   {
      ret = fclose(f) == 0;
   }
   return ret;
}
