#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/graph.h"

static void uniform_tree_test_depth(graph_t *graph, int d)
{
    int i = 0;
    GSList *list = graph_get_neighbours_of(graph, i);
    int depth = 0;
    while(g_slist_length(list) != 1)
    {
        i = GPOINTER_TO_INT(g_slist_nth_data(list, 1));
        list = graph_get_neighbours_of(graph, i);
        depth++;
    }
    g_assert(depth == d);
}

static void uniform_tree_test_branching_factor(graph_t *graph, int b)
{
    int i = 0;
    for(i = 0; i < graph->n; ++i)
    {
        GSList *list = graph_get_neighbours_of(graph, i);
        int length = g_slist_length(list);
        
        if(i == 0)
        {
            g_assert(length == b);
        }
        else
        {
            g_assert(length == 1 || length == b + 1);
        }
    }
}

static void uniform_tree_test(graph_t *graph, int b, int d)
{
    uniform_tree_test_branching_factor(graph, b);
    uniform_tree_test_depth(graph, d);
}

static void uniform_tree_test_0()
{
    graph_t *graph = graph_new(UNIFORM_TREE, 2, 3);
    uniform_tree_test(graph, 2, 3);
    graph_free(graph);
}

static void uniform_tree_test_1()
{
    graph_t *graph = graph_new(UNIFORM_TREE, 2, 5);
    uniform_tree_test(graph, 2, 5);
    graph_free(graph);
}

static void uniform_tree_test_2()
{
    graph_t *graph = graph_new(UNIFORM_TREE, 2, 10);
    uniform_tree_test(graph, 2, 10);
    graph_free(graph);
}

static void uniform_tree_test_3()
{
    graph_t *graph = graph_new(UNIFORM_TREE, 3, 6);
    uniform_tree_test(graph, 3, 6);
    graph_free(graph);
}

static void uniform_tree_test_4()
{
    graph_t *graph = graph_new(UNIFORM_TREE, 4, 6);
    uniform_tree_test(graph, 4, 6);
    graph_free(graph);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Uniform Tree Test 1", uniform_tree_test_0);
    g_test_add_func("/Uniform Tree Test 2", uniform_tree_test_1);
    g_test_add_func("/Uniform Tree Test 3", uniform_tree_test_2);
    g_test_add_func("/Uniform Tree Test 4", uniform_tree_test_3);
    g_test_add_func("/Uniform Tree Test 5", uniform_tree_test_4);
    
    return g_test_run();
}