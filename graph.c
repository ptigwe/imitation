#include "graph.h"


Graph* new_graph(int n)
{
    Graph *g = (Graph *) g_malloc(sizeof(Graph));
    g->edges = (GSList**) g_malloc(sizeof(GSList*) * n);
    
    int i;
    for(i = 0; i < n; ++i)
    {
        g->edges[i] = NULL;
    }
    g->n = n;
    
    return g;
}

Graph* new_cycle(int n)
{
    Graph *g = new_graph(n);
    
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

Graph* new_complete_graph(int n)
{
    Graph *g = new_graph(n);
    
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

Graph* new_complete_bipartite_graph(int n)
{
    Graph *g = new_graph(n);
    
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

Graph* new_uniform_tree(int b, int d)
{    
    int n = (pow(b, d + 1) - 1) / (b - 1);
    Graph *g = new_graph(n);
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

Graph* new_grid(int m, int n)
{
    Graph *g = new_graph(m * n);
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

void free_graph(Graph* g)
{
    int i;
    for(i = 0; i < g->n; ++i)
    {
        g_slist_free(g->edges[i]);
    }
    g_free(g->edges);
    g_free(g);
}

GSList* get_neighbours_of(Graph* g, int i)
{
    return g->edges[i];
}

void print_graph(Graph* g)
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