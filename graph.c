#include "graph.h"

graph_t *graph_alloc(int n)
{
    graph_t *g = (graph_t *) g_malloc(sizeof(graph_t));
    g->edges = (GSList**) g_malloc(sizeof(GSList*) * n);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        g->edges[i] = NULL;
    }
    g->n = n;
    
    return g;
}

graph_t *graph_new_cycle(int n)
{
    graph_t *g = graph_alloc(n);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        if(i == 0)
        {    
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(n - 1));
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(1));
        }
        else if(i == n - 1)
        {    
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(n - 2));
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(0));
        }
        else
        {
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(i - 1));
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(i + 1));
        }
    }
    
    return g;
}

graph_t *graph_new_complete(int n)
{
    graph_t *g = graph_alloc(n);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        int j;
        for(j = 0; j < n; ++j)
        {
            if(i == j) 
                continue;
            
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
        }
    }
    
    return g;
}

graph_t *graph_new_complete_bipartite(int n)
{
    graph_t *g = graph_alloc(n);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        int j = (i % 2 == 0) ? 1 : 0;
        for(; j < n; j += 2)
        {
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
        }
    }
    
    return g;
}

graph_t *graph_new_uniform_tree(int b, int d)
{    
    int n = (pow(b, d + 1) - 1) / (b - 1);
    graph_t *g = graph_alloc(n);
    int m = (pow(b, d) - 1) / (b - 1);
    
    int i;
    for(i = 0; i < m; ++i)
    {
        int j;
        for(j = (b*i + 1); j <= (b*i + b); ++j)
        {
            g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
            g->edges[j] = g_slist_append(g->edges[j], GINT_TO_POINTER(i));
        }
    }
    return g;
}

graph_t *graph_new_grid(int m, int n)
{
    graph_t *g = graph_alloc(m * n);
    int a;
    for(a = 0; a < m; ++a)
    {
        int b;
        for(b = 0; b < n; ++b)
        {
            int i = (a * n) + b;
            printf("i=%d\n", i);
            int j;
            
            if(a > 0)
            {
                j = ((a - 1) * n) + b;
                g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
            }
            if(a < m - 1)
            {
                j = ((a + 1) * n) + b;
                g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
            }
            if(b > 0)
            {
                j = (a * n) + b - 1;
                g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
            }
            if(b < n - 1)
            {
                j = (a * n) + b + 1;
                g->edges[i] = g_slist_append(g->edges[i], GINT_TO_POINTER(j));
            }
        }
    }
    return g;
}

graph_t *graph_new(int graph_type, int p1, int p2)
{
    graph_t *graph;
    switch(graph_type)
    {
        case CYCLE_GRAPH:
            graph = graph_new_cycle(p1);
            break;
        case COMPLETE_GRAPH:
            graph = graph_new_complete(p1);
            break;
        case COMPLETE_BIPARTITE_GRAPH:
            graph = graph_new_complete_bipartite(p1);
            break;
        case UNIFORM_TREE:
            graph = graph_new_uniform_tree(p1, p2);
            break;
        case GRID_GRAPH:
            graph = graph_new_grid(p1, p2);
            break;
    }
    return graph;
}

void graph_free(graph_t *g)
{
    int i;
    for(i = 0; i < g->n; ++i)
    {
        g_slist_free(g->edges[i]);
    }
    g_free(g->edges);
    g_free(g);
}

GSList *graph_get_neighbours_of(graph_t *g, int i)
{
    return g->edges[i];
}

int graph_number_of_neighbours_of(graph_t *g, int i)
{
    GSList *neighbours = graph_get_neighbours_of(g, i);
    
    return g_slist_length(neighbours);
}

void graph_print(graph_t *g)
{
    int i;
    for(i = 0; i < g->n; ++i)
    {
        printf("%d: ", i);
        int j;
        for(j = 0; j < g_slist_length(g->edges[i]); ++j)
        {
            int val = GPOINTER_TO_INT(g_slist_nth_data(g->edges[i], j));
            printf("%d, ", val);
        }
        printf("\n");
    }
}