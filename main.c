#include "ui.h"
#include "graph.h"
#include <glib.h>

int main(int argc, char** argv)
{
    g_mem_set_vtable(glib_mem_profiler_table);
    g_atexit(g_mem_profile);
    
    Graph* g = new_grid(3, 3);
    print_graph(g);
    free_graph(g);
    //initUI(&argc, &argv);
    
    return 0;
}