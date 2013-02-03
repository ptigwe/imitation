#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/graph.h"

static void cycle_graph_test_left(graph_t *graph)
{
    int i = 0;
    int next = -1;
    while(next != 0)
    {
        int j = (next == -1) ? 0 : next;
        GSList *list = graph_get_neighbours_of(graph, j);
        next = GPOINTER_TO_INT(g_slist_nth_data(list, 0));
        ++i;
    }
    g_assert(i == graph->n);
}

static void cycle_graph_test_right(graph_t *graph)
{
    int i = 0;
    int next = -1;
    while(next != 0)
    {
        int j = (next == -1) ? 0 : next;
        GSList *list = graph_get_neighbours_of(graph, j);
        next = GPOINTER_TO_INT(g_slist_nth_data(list, 1));
        ++i;
    }
    g_assert(i == graph->n);
}

static void cycle_graph_test(graph_t *graph)
{
    cycle_graph_test_left(graph);
    cycle_graph_test_right(graph);
}

static void cycle_graph_test_0()
{
    graph_t *graph = graph_new(CYCLE_GRAPH, 10, 0);
    cycle_graph_test(graph);
    graph_free(graph);
}

static void cycle_graph_test_1()
{
    graph_t *graph = graph_new(CYCLE_GRAPH, 100, 0);
    cycle_graph_test(graph);
    graph_free(graph);
}

static void cycle_graph_test_2()
{
    graph_t *graph = graph_new(CYCLE_GRAPH, 500, 0);
    cycle_graph_test(graph);
    graph_free(graph);
}

static void cycle_graph_test_3()
{
    graph_t *graph = graph_new(CYCLE_GRAPH, 1000, 0);
    cycle_graph_test(graph);
    graph_free(graph);
}

static void cycle_graph_test_4()
{
    graph_t *graph = graph_new(CYCLE_GRAPH, 2000, 0);
    cycle_graph_test(graph);
    graph_free(graph);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Cycle Graph Test 1", cycle_graph_test_0);
    g_test_add_func("/Cycle Graph Test 2", cycle_graph_test_1);
    g_test_add_func("/Cycle Graph Test 3", cycle_graph_test_2);
    g_test_add_func("/Cycle Graph Test 4", cycle_graph_test_3);
    g_test_add_func("/Cycle Graph Test 5", cycle_graph_test_4);
    
    return g_test_run();
}