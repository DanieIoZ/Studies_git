#include <stdio.h>
#include <stdlib.h>

#include "graph_utils.h"

int load_graph_simple(const char *fname, graph_t *graph) 
{
   int c = 0;
   FILE * f = fopen(fname, "r");
   int reading = 1;
   while (f && reading)
   {
      if (graph->num_edges == graph->capacity) 
      {
         enlarge_graph(graph);
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
            c += 1;
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
      fclose(f);
   }
   return c;
}
