#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/graph.h"

static void complete_graph_test(graph_t *graph)
{
    int i;
    for(i = 0; i < graph->n; ++i)
    {
        GSList *neighbours = graph_get_neighbours_of(graph, i);
        int length = g_slist_length(neighbours);
        g_assert(length == graph->n - 1);
    }
}

static void complete_graph_test_0()
{
    graph_t *graph = graph_new(COMPLETE_GRAPH, 10, 0);
    complete_graph_test(graph);
    graph_free(graph);
}

static void complete_graph_test_1()
{
    graph_t *graph = graph_new(COMPLETE_GRAPH, 100, 0);
    complete_graph_test(graph);
    graph_free(graph);
}

static void complete_graph_test_2()
{
    graph_t *graph = graph_new(COMPLETE_GRAPH, 500, 0);
    complete_graph_test(graph);
    graph_free(graph);
}

static void complete_graph_test_3()
{
    graph_t *graph = graph_new(COMPLETE_GRAPH, 1000, 0);
    complete_graph_test(graph);
    graph_free(graph);
}

static void complete_graph_test_4()
{
    graph_t *graph = graph_new(COMPLETE_GRAPH, 2000, 0);
    complete_graph_test(graph);
    graph_free(graph);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Complete Graph Test 1", complete_graph_test_0);
    g_test_add_func("/Complete Graph Test 2", complete_graph_test_1);
    g_test_add_func("/Complete Graph Test 3", complete_graph_test_2);
    g_test_add_func("/Complete Graph Test 4", complete_graph_test_3);
    g_test_add_func("/Complete Graph Test 5", complete_graph_test_4);
    
    return g_test_run();
}