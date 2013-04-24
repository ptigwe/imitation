#include <glib.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/game.h"
#include "../../src/graph.h"
#include "../../src/random.h"

#define N 100

static void game_payoff_test_1()
{
    mpq_t p_c;
    mpq_t payoff;
    mpq_t payoff_i;
    
    mpq_inits(payoff, payoff_i, p_c, NULL);
    mpq_set_si(p_c, 1, 1);
    
    game_t *game = game_new(CYCLE_GRAPH, N, 0, p_c);
    game_set_initial_configuration(game, 0);
    
    mpq_set_si(payoff, 2, 1);
    
    int i;
    for(i = 0; i < N; ++i)
    {
        game_get_payoff_of_player(game, i, payoff_i);
        g_assert(mpq_cmp(payoff, payoff_i) == 0);
    }
    
    mpq_clears(payoff, payoff_i, p_c, NULL);
    
    game_free(game);
}

static void game_payoff_test_2()
{
    mpq_t p_c;
    mpq_t payoff;
    mpq_t payoff_i;
    
    mpq_inits(payoff, payoff_i, p_c, NULL);
    mpq_set_si(p_c, 0, 1);
    
    game_t *game = game_new(CYCLE_GRAPH, N, 0, p_c);
    game_set_initial_configuration(game, 0);
    
    mpq_set_si(payoff, 0, 1);
    
    int i;
    for(i = 0; i < N; ++i)
    {
        game_get_payoff_of_player(game, i, payoff_i);
        g_assert(mpq_cmp(payoff, payoff_i) == 0);
    }
    
    mpq_clears(payoff, payoff_i, p_c, NULL);
    
    game_free(game);
}

static void game_payoff_test_3()
{
    mpq_t p_c;
    mpq_t payoff_c;
    mpq_t payoff_d;
    mpq_t payoff_i;
    
    mpq_inits(p_c, payoff_c, payoff_d, payoff_i, NULL);
    mpq_set_si(p_c, 1, 2);
    
    game_t *game = game_new(COMPLETE_GRAPH, N, 0, p_c);
    game_set_initial_configuration(game, 0);
    
    int coop = game_get_number_of_cooperators(game);
    mpq_set_si(p_c, coop, 1);
    
    mpq_mul(payoff_d, p_c, game->t);
    
    mpq_set_si(p_c, N - coop, 1);
    mpq_mul(payoff_c, p_c, game->s);
    mpq_set_si(p_c, coop - 1, 1);
    mpq_add(payoff_c, payoff_c, p_c);
    
    int i;
    for(i = 0; i < N; ++i)
    {
        game_get_payoff_of_player(game, i, payoff_i);
        if(game->current_config[i] == COOPERATE)
        {
            g_assert(mpq_cmp(payoff_c, payoff_i) == 0);
        }
        else
        {
            g_assert(mpq_cmp(payoff_d, payoff_i) == 0);
        }
    }
    
    mpq_clears(p_c, payoff_c, payoff_d, payoff_i, NULL);
    game_free(game);
}

static void game_payoff_test_4()
{
    mpq_t p_c;
    mpq_t payoff_c;
    mpq_t payoff_d;
    mpq_t payoff_i;
    
    mpq_inits(p_c, payoff_c, payoff_d, payoff_i, NULL);
    mpq_set_si(p_c, 1, 5);
    
    game_t *game = game_new(COMPLETE_GRAPH, N, 0, p_c);
    game_set_initial_configuration(game, 0);
    
    int coop = game_get_number_of_cooperators(game);
    mpq_set_si(p_c, coop, 1);
    
    mpq_mul(payoff_d, p_c, game->t);
    
    mpq_set_si(p_c, N - coop, 1);
    mpq_mul(payoff_c, p_c, game->s);
    mpq_set_si(p_c, coop - 1, 1);
    mpq_add(payoff_c, payoff_c, p_c);
    
    int i;
    for(i = 0; i < N; ++i)
    {
        game_get_payoff_of_player(game, i, payoff_i);
        if(game->current_config[i] == COOPERATE)
        {
            g_assert(mpq_cmp(payoff_c, payoff_i) == 0);
        }
        else
        {
            g_assert(mpq_cmp(payoff_d, payoff_i) == 0);
        }
    }
    
    mpq_clears(p_c, payoff_c, payoff_d, payoff_i, NULL);
    game_free(game);
}

static void game_payoff_test_5()
{
    mpq_t p_c;
    mpq_t payoff_c;
    mpq_t payoff_d;
    mpq_t payoff_i;
    
    mpq_inits(p_c, payoff_c, payoff_d, payoff_i, NULL);
    mpq_set_si(p_c, 1, 2);
    
    game_t *game = game_new(CYCLE_GRAPH, N, 0, p_c);
    int i;
    for(i = 0; i < N; ++i)
    {
        game->current_config[i] = i % 2;
    }
    
    mpq_set_si(p_c, 2, 1);
    mpq_mul(payoff_d, p_c, game->t);
    mpq_mul(payoff_c, p_c, game->s);
    
    for(i = 0; i < N; ++i)
    {
        game_get_payoff_of_player(game, i, payoff_i);
        if(game->current_config[i] == COOPERATE)
        {
            g_assert(mpq_cmp(payoff_c, payoff_i) == 0);
        }
        else
        {
            g_assert(mpq_cmp(payoff_d, payoff_i) == 0);
        }
    }
    
    mpq_clears(p_c, payoff_c, payoff_d, payoff_i, NULL);
    game_free(game);
}

int main(int argc, char **argv)
{
    g_test_init(&argc, &argv, NULL);
    
    g_test_add_func("/Game Payoff Test 1 ", game_payoff_test_1);
    g_test_add_func("/Game Payoff Test 2 ", game_payoff_test_2);
    g_test_add_func("/Game Payoff Test 3 ", game_payoff_test_3);
    g_test_add_func("/Game Payoff Test 4 ", game_payoff_test_4);
    g_test_add_func("/Game Payoff Test 5 ", game_payoff_test_5);
    
    return g_test_run();
}