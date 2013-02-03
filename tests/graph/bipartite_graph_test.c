#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/graph.h"

static void bipartite_graph_test_node(graph_t * graph, int i)
{
    GSList *neighbours = graph_get_neighbours_of(graph, i);
    
    int j = (i % 2 == 0) ? 1 : 0;
    for(; j < graph->n; j += 2)
    {
        g_assert(g_slist_index(neighbours, GINT_TO_POINTER(j)) != -1);
    }
}

static void bipartite_graph_test(graph_t *graph)
{
    int i;
    for(i = 0; i < graph->n; ++i)
    {
        bipartite_graph_test_node(graph, i);
    }
}

static void bipartite_graph_test_0()
{
    graph_t *graph = graph_new(COMPLETE_BIPARTITE_GRAPH, 10, 0);
    bipartite_graph_test(graph);
    graph_free(graph);
}

static void bipartite_graph_test_1()
{
    graph_t *graph = graph_new(COMPLETE_BIPARTITE_GRAPH, 100, 0);
    bipartite_graph_test(graph);
    graph_free(graph);
}

static void bipartite_graph_test_2()
{
    graph_t *graph = graph_new(COMPLETE_BIPARTITE_GRAPH, 500, 0);
    bipartite_graph_test(graph);
    graph_free(graph);
}

static void bipartite_graph_test_3()
{
    graph_t *graph = graph_new(COMPLETE_BIPARTITE_GRAPH, 1000, 0);
    bipartite_graph_test(graph);
    graph_free(graph);
}

static void bipartite_graph_test_4()
{
    graph_t *graph = graph_new(COMPLETE_BIPARTITE_GRAPH, 2000, 0);
    bipartite_graph_test(graph);
    graph_free(graph);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Bipartite Graph Test 1", bipartite_graph_test_0);
    g_test_add_func("/Bipartite Graph Test 2", bipartite_graph_test_1);
    g_test_add_func("/Bipartite Graph Test 3", bipartite_graph_test_2);
    g_test_add_func("/Bipartite Graph Test 4", bipartite_graph_test_3);
    g_test_add_func("/Bipartite Graph Test 5", bipartite_graph_test_4);
    
    return g_test_run();
}