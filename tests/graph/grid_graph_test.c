#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/graph.h"

static void grid_graph_test_col(graph_t *graph, int i, int m, int row, int col, int a, int b)
{
    GSList *list = graph_get_neighbours_of(graph, i);
    int length = g_slist_length(list);
    
    if(col == 0)
    {
        g_assert(length == a);
    }
    else if(col == m - 1)
    {
        g_assert(length == a);
    }
    else
    {
        g_assert(length == b);
    }
}

static void grid_graph_test(graph_t *graph, int m, int n)
{
    int i;
    for(i = 0; i < graph->n; ++i)
    {
        int col = i % n;
        int row = i / m;
        
        if(row == 0)
        {
            grid_graph_test_col(graph, i, m, row, col, 2, 3);
        }
        else if(row == n - 1)
        {
            grid_graph_test_col(graph, i, m, row, col, 2, 3);
        }
        else
        {
            grid_graph_test_col(graph, i, m, row, col, 3, 4);
        }
    }
}

static void grid_graph_test_0()
{
    graph_t *graph = graph_new(GRID_GRAPH, 3, 3);
    grid_graph_test(graph, 3, 3);
    graph_free(graph);
}

static void grid_graph_test_1()
{
    graph_t *graph = graph_new(GRID_GRAPH, 10, 10);
    grid_graph_test(graph, 10, 10);
    graph_free(graph);
}

static void grid_graph_test_2()
{
    graph_t *graph = graph_new(GRID_GRAPH, 22, 22);
    grid_graph_test(graph, 22, 22);
    graph_free(graph);
}

static void grid_graph_test_3()
{
    graph_t *graph = graph_new(GRID_GRAPH, 31, 31);
    grid_graph_test(graph, 31, 31);
    graph_free(graph);
}

static void grid_graph_test_4()
{
    graph_t *graph = graph_new(GRID_GRAPH, 44, 44);
    grid_graph_test(graph, 44, 44);
    graph_free(graph);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Grid Graph Test 1", grid_graph_test_0);
    g_test_add_func("/Grid Graph Test 2", grid_graph_test_1);
    g_test_add_func("/Grid Graph Test 3", grid_graph_test_2);
    g_test_add_func("/Grid Graph Test 4", grid_graph_test_3);
    g_test_add_func("/Grid Graph Test 5", grid_graph_test_4);
    
    return g_test_run();
}