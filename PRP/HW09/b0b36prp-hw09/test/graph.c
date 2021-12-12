#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/* This is a testing file just to be able to compile the 
 * examples of binary files to convert graph from txt->bin
 * and bin -> txt
 */
#define MIN_SIZE 10
#define BIN_BUFFER 4
// - function -----------------------------------------------------------------
graph_t * allocate_graph() 
{
   graph_t * graph = (graph_t*) malloc(sizeof(graph_t));
   graph->pts = malloc(sizeof(point_t) * MIN_SIZE);
   graph->num_pts = 0;
   graph->size = MIN_SIZE;
   return graph;
}

// - function -----------------------------------------------------------------
void free_graph(graph_t ** graph)
{
   if ((*graph)->size > 0) {
      free((*graph)->pts);
   }
   free(*graph);
   *graph = NULL;
}

graph_t * increase_size(graph_t * graph)
{
   graph->size *= 2;
   graph->pts = realloc(graph->pts, graph->size * sizeof(point_t) * 2);
   return graph;
}
// - function -----------------------------------------------------------------
void load_txt(const char *fname, graph_t *graph)
{
   int exit = 0;
   FILE * f = fopen(fname, "r");
   while (f && !exit) 
   {
      if (graph->num_pts == graph->size) 
      {
         increase_size(graph);
      }
      while (graph->num_pts < graph->size) 
      {
         if (fscanf(f, "%d %d %d\n", &(graph->pts[graph->num_pts].pt1), &(graph->pts[graph->num_pts].pt2), &(graph->pts[graph->num_pts].cost)) == 3) 
         {
            graph->num_pts += 1;
         } 
         else 
         {
            exit = 1; /* neco je spatne ukoncujeme naciteni */
            break;
         }
      }
      
   }
   if (f) 
   {
      fclose(f);
   }
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
   FILE * f = fopen(fname, "rb");
   while (f && !feof(f)) 
   {
      if (graph->num_pts == graph->size) 
      {
         increase_size(graph);
      }
      while (graph->num_pts < graph->size) 
      {
         fread(&(graph->pts[graph->num_pts].pt1), BIN_BUFFER, 1, f);
         fread(&(graph->pts[graph->num_pts].pt2), BIN_BUFFER, 1, f);
         fread(&(graph->pts[graph->num_pts].cost), BIN_BUFFER, 1, f);
         graph->num_pts++;
      }
   }
   if (f) 
   {
      fclose(f);
   }
}

// - function -----------------------------------------------------------------
void save_txt(const graph_t * const graph, const char *fname)
{
   FILE * f = fopen(fname, "w");
   for (int i = 0; i < graph->num_pts; i++)
   {
      fprintf(f, "%d %d %d\n", graph->pts[i].pt1, graph->pts[i].pt2, graph->pts[i].cost);
   }
   if (f) 
   {
      fclose(f);
   }
}

// - function -----------------------------------------------------------------
void save_bin(const graph_t * const graph, const char *fname)
{
   FILE * f = fopen(fname, "wb");
   for (int i = 0; i < graph->num_pts; i++)
   {
      fwrite((const void*)&(graph->pts[i].pt1), BIN_BUFFER, 1, f);
      fwrite((const void*)&(graph->pts[i].pt2), BIN_BUFFER, 1, f);
      fwrite((const void*)&(graph->pts[i].cost), BIN_BUFFER, 1, f);
   }
   if (f) 
   {
      fclose(f);
   }
}
