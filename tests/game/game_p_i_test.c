#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/game.h"
#include "../../src/graph.h"
#include "../../src/random.h"

#define N 100

static void game_p_i_test(game_t *game, mpq_t p_i_c, mpq_t p_i_d)
{
    mpq_t p_i;
    
    mpq_init(p_i);
    
    int i;
    for(i = 0; i < N; ++i)
    {
        game_compute_p_i(game, i, (i + 1) % N, p_i);
        if(game->current_config[i] == COOPERATE)
        {
            g_assert(mpq_cmp(p_i_c, p_i) == 0);
        }
        else
        {
            g_assert(mpq_cmp(p_i_d, p_i) == 0);
        }
    }
    
    mpq_clear(p_i);
}

static void game_p_i_test_1()
{
    mpq_t p_c;
    mpq_t p_i_c;
    mpq_t p_i_d;
    
    mpq_inits(p_c, p_i_c, p_i_d, NULL);
    mpq_set_si(p_c, 1, 2);
    
    game_t *game = game_new(CYCLE_GRAPH, N, 0, p_c);
    int i;
    for(i = 0; i < N; ++i)
    {
        game->current_config[i] = i % 2;
    }
    
    mpq_set_si(game->t, 1, 1);
    mpq_set_si(game->s, 0, 1);
    mpq_set_si(p_i_c, 1, 1);
    mpq_set_si(p_i_d, 0, 1);
    
    game_p_i_test(game, p_i_c, p_i_d);
    
    mpq_clears(p_c, p_i_c, p_i_d, NULL);
    game_free(game);
}

static void game_p_i_test_2()
{
    mpq_t p_c;
    mpq_t p_i_c;
    mpq_t p_i_d;
    
    mpq_inits(p_c, p_i_c, p_i_d, NULL);
    mpq_set_si(p_c, 1, 2);
    
    game_t *game = game_new(CYCLE_GRAPH, N, 0, p_c);
    int i;
    for(i = 0; i < N; ++i)
    {
        game->current_config[i] = i % 2;
    }
    
    mpq_set_si(game->t, 1, 2);
    mpq_set_si(game->s, 0, 1);
    mpq_set_si(p_i_c, 1, 2);
    mpq_set_si(p_i_d, 0, 1);
    
    game_p_i_test(game, p_i_c, p_i_d);
    
    mpq_clears(p_c, p_i_c, p_i_d, NULL);
    game_free(game);
}

static void game_p_i_test_3()
{
    mpq_t p_c;
    mpq_t p_i_c;
    mpq_t p_i_d;
    
    mpq_inits(p_c, p_i_c, p_i_d, NULL);
    mpq_set_si(p_c, 1, 2);
    
    game_t *game = game_new(CYCLE_GRAPH, N, 0, p_c);
    int i;
    for(i = 0; i < N; ++i)
    {
        game->current_config[i] = i % 2;
    }
    
    mpq_set_si(game->t, 2, 1);
    mpq_set_si(game->s, 1, 2);
    mpq_set_si(p_i_c, 3, 4);
    mpq_set_si(p_i_d, 0, 1);
    
    game_p_i_test(game, p_i_c, p_i_d);
    
    mpq_clears(p_c, p_i_c, p_i_d, NULL);
    game_free(game);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Game p_i Test 1 ", game_p_i_test_1);
    g_test_add_func("/Game p_i Test 2 ", game_p_i_test_2);
    g_test_add_func("/Game p_i Test 3 ", game_p_i_test_3);
    
    return g_test_run();
}