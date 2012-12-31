
#include "graph.h"
#include "random.h"
#include <glib.h>
#include <gmp.h>
#include <math.h>

#ifndef GAME_H
#define GAME_H

#define S_MIN -1
#define S_MAX 1
#define T_MIN 0
#define T_MAX 2

#define COOPERATE 1
#define DEFECT 0

#define PROPORTIONAL_RULE 1
#define MOD_PROPORTIONAL_RULE 2
typedef struct
{
    graph_t *graph;
    mpq_t s;
    mpq_t t;
    mpq_t p_c;
    int *initial_config;
    int *current_config;
    int *next_config;
}game_t;

game_t *game_new(int graph_type, int g_p1, int g_p2, mpq_t p_c);
void game_free(game_t *game);

void game_set_initial_configuration(game_t *game);
void game_restore_initial_configuration(game_t *game);
int* game_get_current_configuration(game_t *game);

int game_get_number_of_cooperators(game_t *game);
int game_get_number_of_cooperators_in_list(game_t *game, GSList* list);
void game_get_payoff_of_player(game_t *game, int i, mpq_t payoff);
void game_get_alpha(game_t *game, mpq_t alpha);
void game_compute_p_i(game_t *game, int i, int j, mpq_t p_i);
gboolean game_compute_p_ij(game_t *game, int i, mpq_t *p_ij);
void game_update_with_proportional_imitate(game_t *game);
void game_update_with_mod_proportional_imitate(game_t *game);
void game_play_round(game_t *game, int rule);
void game_play_t_rounds(game_t *game, int rule, int t);
gboolean game_is_in_steady_state(game_t *game);

#endif