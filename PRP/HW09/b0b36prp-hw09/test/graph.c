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
   FILE * f = fopen(fname, "r");
   int reading = 1;
   while (f && reading)
   {
      if (graph->num_pts == graph->size) 
      {
         increase_size(graph);
      }
      int cur_num = 0;
      int reads = 0;
      char buff[20];
      int nums[3];
      while ((graph->num_pts < graph->size)) 
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
            graph->pts[graph->num_pts].pt1 = nums[0];
            graph->pts[graph->num_pts].pt2 = nums[1];
            graph->pts[graph->num_pts].cost = nums[2];
            cur_num = 0;
            graph->num_pts++;
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
      fclose(f);
   }
}

// - function -----------------------------------------------------------------
void load_bin(const char *fname, graph_t *graph)
{
   FILE * f = fopen(fname, "rb");
   int reading = 1;
   while (f && !feof(f) && reading) 
   {
      if (graph->num_pts == graph->size) 
      {
         increase_size(graph);
      }
      while (graph->num_pts < graph->size) 
      {
         int reads = 0;
         reads += fread(&(graph->pts[graph->num_pts].pt1), BIN_BUFFER, 1, f);
         reads += fread(&(graph->pts[graph->num_pts].pt2), BIN_BUFFER, 1, f);
         reads += fread(&(graph->pts[graph->num_pts].cost), BIN_BUFFER, 1, f);

         if (reads < 3)
         {
            reading = 0;
            break;
         }
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
