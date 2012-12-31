#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef GRAPH_H
#define GRAPH_H

#define CYCLE_GRAPH 0
#define COMPLETE_GRAPH 1
#define COMPLETE_BIPARTITE_GRAPH 2
#define UNIFORM_TREE 3
#define GRID_GRAPH 4

typedef struct
{
    GSList **edges;
    int n;
    int type;
}graph_t;

graph_t *graph_new(int graph_type, int p1, int p2);
void free_graph(graph_t *g);

GSList *graph_get_neighbours_of(graph_t *g, int i);
int graph_number_of_neighbours_of(graph_t *g, int i);
void graph_print(graph_t *g);

#endif