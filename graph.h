#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef GRAPH_H
#define GRAPH_H

struct graph_t
{
    GSList** edges;
    int n;
    gchar* type;
}graph_t;
typedef struct graph_t Graph;

Graph* new_graph(int n);
Graph* new_cycle(int n);
Graph* new_complete_graph(int n);
Graph* new_complete_bipartite_graph(int n);
Graph* new_uniform_tree(int b, int d);
Graph* new_grid(int m, int n);
void free_graph(Graph* g);
GSList* get_neighbours_of(Graph* g, int i);

void print_graph(Graph* g);

#endif