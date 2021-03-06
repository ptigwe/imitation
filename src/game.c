#include "game.h"

#define ROUND(x) (int)(x +.5f);

game_t *game_new(int graph_type, int g_p1, int g_p2, mpq_t p_c)
{
    game_t *game = (game_t *)g_malloc(sizeof(game_t));
    
    game->graph = graph_new(graph_type, g_p1, g_p2);
    
    mpq_init(game->s);
    mpq_set_si(game->s, S_MIN, 1);
    mpq_init(game->t);
    mpq_set_si(game->t, T_MIN, 1);
    mpq_init(game->p_c);
    mpq_set(game->p_c, p_c);
    
    game->initial_config = (int *)g_malloc(sizeof(int) * game->graph->n);
    game->current_config = (int *)g_malloc(sizeof(int) * game->graph->n);
    game->next_config = (int *)g_malloc(sizeof(int) * game->graph->n);
    
    int i;
    for(i = 0; i < game->graph->n; ++i)
    {
        game->initial_config[i] = 0;
        game->current_config[i] = 0;
        game->next_config[i] = 0;
    }
    return game;
}

void game_free(game_t *game)
{
    graph_free(game->graph);
    
    mpq_clear(game->s);
    mpq_clear(game->t);
    mpq_clear(game->p_c);
    
    g_free(game->initial_config);
    g_free(game->current_config);
    g_free(game->next_config);
    
    g_free(game);
}

void game_set_initial_configuration_position(game_t *game)
{
    random_set_seed(time(NULL));
    
    int n = game->graph->n;
    GArray *players = g_array_new(FALSE, FALSE, sizeof(int));
    
    int i;
    for(i = 0; i < n; ++i)
    {
        game->initial_config[i] = 0;
        game->current_config[i] = 0;
        
        g_array_append_val(players, i);
    }
    
    mpq_t e;
    mpq_init(e);
    mpq_set_si(e, game->graph->n, 1);
    mpq_mul(e, game->p_c, e);
    int m = ROUND(mpq_get_d(e));
    mpq_clear(e);
    for(i = 0; i < m; ++i)
    {
        int j = random_integer(n);
        int x = g_array_index(players, int, j);
        
        game->initial_config[x] = 1;
        game->current_config[x] = 1;
        
        g_array_remove_index_fast(players, j);
        n--;
    }
    
    g_array_free(players, TRUE);
}

void game_set_initial_configuration_population(game_t *game)
{
    game_set_initial_configuration_position(game);
    random_set_seed(time(NULL));
    
    int n = game->graph->n;
    int i;
    for(i = 0; i < n; ++i)
    {
        game->initial_config[i] = random_boolean_with_probability(game->p_c);
        game->current_config[i] = game->initial_config[i];
    }
}

void game_set_initial_configuration(game_t *game, gboolean position)
{
    if(position)
    {
        game_set_initial_configuration_position(game);
    }
    else
    {
        game_set_initial_configuration_population(game);
    }
}

void game_restore_initial_configuration(game_t *game)
{
    int n = game->graph->n;
    int i;
    for(i = 0; i < n; ++i)
    {
        game->current_config[i] = game->initial_config[i];
    }
}

int *game_get_current_configuration(game_t *game)
{
    return game->current_config;
}

int game_get_number_of_cooperators(game_t *game)
{
    int i;
    int n = game->graph->n;
    int sum = 0;
    
    for(i = 0; i < n; ++i)
    {
        sum += game->current_config[i];
    }
    
    return sum;
}

int game_get_number_of_cooperators_in_list(game_t *game, GSList* list)
{
    int n = g_slist_length(list);
    int sum = 0;
    
    int i;
    for(i = 0; i < n; ++i)
    {
        int j = GPOINTER_TO_INT(g_slist_nth_data(list, i));
        sum += game->current_config[j];
    }
    
    return sum;
}

void game_get_payoff_of_player(game_t *game, int i, mpq_t payoff)
{
    GSList *list = graph_get_neighbours_of(game->graph, i);
    int n = g_slist_length(list) + 1;
    
    int delta = game_get_number_of_cooperators_in_list(game, list);
    delta += game->current_config[i];
    //printf("n= %d, d= %d", n, delta);
    
    mpq_t tmp;
    mpq_init(tmp);
    
    //double payoff = 0;
    
    if(game->current_config[i] == COOPERATE)
    {
        //int pay = (delta - 1) + ((n - delta) * -1);
        //printf("pay = %d", pay);
        //payoff = (delta - 1) + (n - delta) * game->s;
        mpq_set_si(tmp, (n - delta), 1);
        mpq_mul(tmp, game->s, tmp);
        
        mpq_set(payoff, tmp);
        mpq_set_si(tmp, (delta - 1), 1);
        mpq_add(payoff, tmp, payoff);
    }
    else
    {
        //payoff = delta * game->t;
        mpq_set_si(tmp, delta, 1);
        mpq_mul(payoff, tmp, game->t);
    }
    
    mpq_clear(tmp);
}

void game_get_alpha(game_t *game, mpq_t alpha)
{
    mpq_t max_t_1;
    mpq_t min_s_0;
    
    mpq_init(max_t_1);
    mpq_init(min_s_0);
    
    //MAX(game->t, 1)
    if(mpq_cmp_si(game->t, 1, 1) > 0)
    {
        mpq_set(max_t_1, game->t);
    }
    else
    {
        mpq_set_si(max_t_1, 1, 1);
    }
    
    //MIN(game->s, 0)
    if(mpq_cmp_si(game->s, 0, 1) < 0)
    {
        mpq_set(min_s_0, game->s);
    }
    else
    {
        mpq_set_si(min_s_0, 0, 1);
    }
    
    //return MAX(game->t, 1) - MIN(game->s, 0);
    mpq_sub(alpha, max_t_1, min_s_0);
    
    mpq_clear(max_t_1);
    mpq_clear(min_s_0);
}

void game_compute_p_i(game_t *game, int i, int j, mpq_t p_i)
{
    mpq_t payoff_i;
    mpq_t payoff_j;
    mpq_t alpha;
    mpq_t tmp;
    mpq_t tmp2;
    
    mpq_init(payoff_i);
    mpq_init(payoff_j);
    mpq_init(alpha);
    mpq_init(tmp);
    mpq_init(tmp2);
    
    game_get_payoff_of_player(game, i, payoff_i);
    game_get_payoff_of_player(game, j, payoff_j);
    game_get_alpha(game, alpha);

    int n_i = graph_number_of_neighbours_of(game->graph, i);
    int n_j = graph_number_of_neighbours_of(game->graph, j);
    int m = MAX(n_i, n_j);
    
    mpq_sub(tmp, payoff_j, payoff_i);
    //gmp_printf(" %Qd - %Qd = %Qd", payoff_j, payoff_i,tmp);
    //max(P_j - P_i, 0)
    if(mpq_cmp_si(tmp, 0, 1) < 0)
    {
        mpq_set_si(tmp, 0, 1);
    }
    
    mpq_set_si(tmp2, m, 1);
    mpq_mul(tmp2, tmp2, alpha);
    
    mpq_div(p_i, tmp, tmp2);
    
    mpq_clear(payoff_i);
    mpq_clear(payoff_j);
    mpq_clear(alpha);
    mpq_clear(tmp);
    mpq_clear(tmp2);
}

gboolean game_compute_p_ij(game_t *game, int i, mpq_t *p_ij)
{    
    GSList *list = graph_get_neighbours_of(game->graph, i);
    int n = g_slist_length(list);
    
    mpq_t sum;
    mpq_init(sum);
    mpq_set_si(sum, 0, 1);
    
    int j, k;
    for(j = 0; j < n; ++j)
    {
        k = GPOINTER_TO_INT(g_slist_nth_data(list, j));
        game_compute_p_i(game, i, k, p_ij[j]);
        mpq_canonicalize(p_ij[j]);
        mpq_add(sum, sum, p_ij[j]);
    }
    
    for(j = 0; j < n; ++j)
    {
        if(mpq_cmp_si(sum, 0, 1) == 0)
        {
            mpq_set_si(p_ij[j], 0, 1);
        }
        else
        {
            mpq_div(p_ij[j], p_ij[j], sum);
            mpq_canonicalize(p_ij[j]);
        }
    }
    
    mpq_clear(sum);
    
    int res = mpq_cmp_si(sum, 0, 1);
    return (res == 0);
}

void game_update_with_proportional_imitate(game_t *game)
{
    int n = game->graph->n;
    
    int i;
    for(i = 0; i < n; ++i)
    {
        int n_i = graph_number_of_neighbours_of(game->graph, i);
        int k = random_integer(n_i);
        
        mpq_t p_i;
        mpq_init(p_i);
        int j = GPOINTER_TO_INT(g_slist_nth_data(game->graph->edges[i], k));
        game_compute_p_i(game, i, j, p_i);
        
        gboolean imitate = random_boolean_with_probability(p_i);
        
        //printf("%d copying %d\n", i, j);
        if(imitate)
        {
            //printf("%d copied %d\n", i, j);
            game->next_config[i] = game->current_config[j];
        }
        else
        {
            game->next_config[i] = game->current_config[i];
        }
        mpq_clear(p_i);
    }
    
    for(i = 0; i < n; ++i)
    {
        game->current_config[i] = game->next_config[i];
    }
}

void game_update_with_mod_proportional_imitate(game_t *game)
{
    int n = game->graph->n;
    
    int i;
    for(i = 0; i < n; ++i)
    {
        int n_i = graph_number_of_neighbours_of(game->graph, i);
        
        mpq_t *p;
        p = (mpq_t *)g_malloc(sizeof(mpq_t) * n_i);
        
        int j;
        for(j = 0; j < n_i; ++j)
        {
            mpq_init(p[j]);
        }
        
        gboolean zero_sum = game_compute_p_ij(game, i, p);
        
        if(zero_sum)
        {
            game->next_config[i] = game->current_config[i];
        }
        else
        {
            j = random_integer_with_probability(p, n_i);
            int k = GPOINTER_TO_INT(g_slist_nth_data(game->graph->edges[i], j));
            game->next_config[i] = game->current_config[k];
        }
        
        for(j = 0; j < n_i; ++j)
        {
            mpq_clear(p[j]);
        }
        g_free(p);
    }

    for(i = 0; i < n; ++i)
    {
        game->current_config[i] = game->next_config[i];
    }
}

void game_play_round(game_t *game, int rule)
{
    switch(rule)
    {
        case PROPORTIONAL_RULE:
            game_update_with_proportional_imitate(game);
            break;
        case MOD_PROPORTIONAL_RULE:
            game_update_with_mod_proportional_imitate(game);
            break;
    }
}

void game_play_t_rounds(game_t *game, int rule, int t)
{
    int i;
    for(i = 0; i < t; ++i)
    {
        game_play_round(game, rule);
    }
}

int game_is_in_steady_state(game_t *game)
{
    int state = 0;
    int n = game->graph->n;
    mpq_t tmp;
    mpq_t m;
    mpq_init(m);
    mpq_init(tmp);
    
    gboolean s = TRUE;
    game_get_payoff_of_player(game, 0, m);
    
    int i;
    for(i = 1; i < n; ++i)
    {
        game_get_payoff_of_player(game, i, tmp);
        
        if(mpq_cmp(tmp, m) != 0)
        {
            s = FALSE;
            break;
        }
    }
    
    int coop = game_get_number_of_cooperators(game);
    if(coop == 0)
    {
        state = ALL_DEFECT_STATE;
    }
    else if(coop == n)
    {
        state = ALL_COOPERATE_STATE;
    }
    else if(s)
    {
        state = MIXED_STATE;
    }
    
    mpq_clear(m);
    mpq_clear(tmp);
    return state;
}