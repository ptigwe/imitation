#include "ui.h"
#include "graph.h"
#include <glib.h>
#include <gmp.h>
#include "random.h"

int main(int argc, char** argv)
{    
    g_mem_set_vtable(glib_mem_profiler_table);
    g_atexit(g_mem_profile);
    
    int NUM = atoi(argv[1]);
    random_set_seed(time(NULL));
    
    mpq_t *q = (mpq_t *)g_malloc(sizeof(mpq_t) * NUM);
    int *c = (int *)g_malloc(sizeof(int) * NUM);
    int i;
    for(i = 0; i < NUM; ++i)
    {
        mpq_init(q[i]);
        c[i] = 0;
    }
    
    mpq_set_ui(q[0], 1, 2);
    
    for(i = 1; i < NUM; ++i)
    {
        mpq_set_ui(q[i], 1, (NUM - 1) * 2);
        mpq_canonicalize(q[i]);
        gmp_printf("%d: %Qd\n", i, q[i]);
    }
    
    for(i = 0; i < 10000; ++i)
    {
        int x = random_integer_with_probability(q, NUM);
        ++c[x];
    }
    
    for(i = 0; i < NUM; ++i)
    {
        g_print("%d: %d\n", i, c[i]);
    }
    
    for(i = 0; i < NUM; ++i)
    {
        mpq_clear(q[i]);
    }
    g_free(q);
    g_free(c);
    
    mpq_t p;
    mpq_init(p);
    mpq_set_ui(p, 1, 10000);
    int count;
    for(i = 0; i < 10000; ++i)
    {
        gboolean b = random_boolean_with_probability(p);
        count += b;
    }    
    g_printf("count = %i\n", count);
    mpq_clear(p);
    
    Graph* g = new_grid(3, 3);
    print_graph(g);
    free_graph(g);
    //initUI(&argc, &argv);
    
    return 0;
}
