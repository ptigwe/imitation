#include "ui.h"
#include "graph.h"
#include <glib.h>
#include <gmp.h>
#include "random.h"
#include "game.h"

int main(int argc, char** argv)
{
    /*
    int NUM = atoi(argv[1]);
    random_set_seed(time(NULL));
    
    mpq_t *q = (mpq_t *)g_malloc(sizeof(mpq_t) * NUM);
    int *c = (int *)g_malloc(sizeof(int) * NUM);
    int i;
    mpq_inits(q[0], q[1], q[2], q[3], NULL);
    for(i = 0; i < NUM; ++i)
    {
        //mpq_init(q[i]);
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
    mpq_set_ui(p, 1, 10);
    int count = 0;
    for(i = 0; i < 10000; ++i)
    {
        int b = random_boolean_with_probability(p);
        count += b;
    }    
    g_printf("count = %i\n", count);
    mpq_clear(p);
    
    graph_t *graph = graph_new(COMPLETE_GRAPH, 100, 3);
    graph_print(graph);
    graph_free(graph);*/
    
    /*
    mpq_t p_c;
    mpq_init(p_c);
    mpq_set_si(p_c, 1, 2);
    game_t *game = game_new(CYCLE_GRAPH, 10, 1, p_c);
    game_set_initial_configuration(game);
    
    int i = 0;
    int n = game->graph->n;
    for(i = 0; i < n; ++i)
    {
        int j = GPOINTER_TO_INT(g_slist_nth_data(game->graph->edges[i], 0));
        g_print("%d (%d): %d", i, j, game->initial_config[i]);
        game_get_payoff_of_player(game, i, p_c);
        gmp_printf(" -> %Qd", p_c);
        //game_compute_p_i(game, i, 0, p_c);
        //gmp_printf(" -> %Qd\n", p_c);
    }
    g_print("Cooperators: %d\n", game_get_number_of_cooperators(game));
    game_free(game);
    mpq_clear(p_c);
    */
    
    mpq_t p_c;
    mpq_init(p_c);
    mpq_set_si(p_c, 2, 2);
    game_t *game = game_new(COMPLETE_GRAPH, 10, 3, p_c);
    
    mpq_t *p_ij;
    p_ij = (mpq_t *)malloc(sizeof(mpq_t) * game->graph->n);
    int n = game->graph->n;
    
    int i = 0;
    for(i = 0; i < n; ++i)
    {
        mpq_init(p_ij[i]);
    }
    
    game_set_initial_configuration(game);
    game_play_t_rounds(game, 2, 100);
    
    for(i = 0; i < n; ++i)
    {
        int j = GPOINTER_TO_INT(g_slist_nth_data(game->graph->edges[i], 0));
        g_print("%d: %d -> %d\n", i, game->initial_config[i], game->current_config[i]);
    }
    g_print("Cooperators: %d\n", game_get_number_of_cooperators(game));
    game_free(game);
    
    for(i = 0; i < n; ++i)
    {
        mpq_clear(p_ij[i]);
    }
    mpq_clear(p_c);
    
    //ui_init(&argc, &argv);
    
    return 0;
}
