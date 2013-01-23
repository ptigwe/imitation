#include "experiment.h"

gboolean experiment_validate_flags(ExperimentFlags flags)
{
    if(flags.generations <= 0)
    {
        return FALSE;
    }
    
    if(flags.repititions <= 0)
    {
        return FALSE;
    }
    
    if(flags.update_rule != PROPORTIONAL_RULE && flags.update_rule != MOD_PROPORTIONAL_RULE)
    {
        return FALSE;
    }
    
    if(flags.increments <= 0)
    {
        return FALSE;
    }
    
    if(flags.percentage < 0)
    {
        return FALSE;
    }
    
    if(flags.graph_type < 0 || flags.graph_type > 4)
    {
        return FALSE;
    }
    
    if(flags.graph_parameter_1 <= 0)
    {
        return FALSE;
    }
    
    if(flags.graph_type == UNIFORM_TREE && flags.graph_parameter_2 <= 0)
    {
        return FALSE;
    }
    
    if(flags.graph_type == GRID_GRAPH && flags.graph_parameter_2 <= 0)
    {
        return FALSE;
    }
    
    return TRUE;
}

void experiment_run_simulation1(ExperimentFlags flags, game_t *game, result_t *result)
{
    int s_inc, t_inc;
    
    mpq_t s;
    mpq_t t;
    mpq_t tmp;
    mpq_t sum;
    mpq_inits(s, t, tmp, sum, NULL);
    mpq_set_si(s, S_MIN, 1);
    mpq_set_si(t, T_MIN, 1);
    
    for(s_inc = 0; s_inc <= 2 * flags.increments; ++s_inc)
    {
        mpq_set(game->s, s);
        mpq_set_si(t, T_MIN, 1);
        
        for(t_inc = 0; t_inc <= 2 * flags.increments; ++t_inc)
        {
            mpq_set(game->t, t);
            
            game_restore_initial_configuration(game);
            game_play_t_rounds(game, flags.update_rule, flags.generations);
            
            result->result[s_inc][t_inc] += game_get_number_of_cooperators(game);
            
            int state = game_is_in_steady_state(game);
            
            switch(state)
            {    
                case ALL_COOPERATE_STATE:
                    result->cooperate[s_inc][t_inc] += 1;
                    break;
                case ALL_DEFECT_STATE:
                    result->defect[s_inc][t_inc] += 1;
                    break;
                case MIXED_STATE:
                    result->mixed[s_inc][t_inc] += 1;
                    break;
                default:
                    break;
            }
            
            gmp_printf("%Qd, %Qd -> %d \n", s, t, game_get_number_of_cooperators(game));
            
            //mpq_add(sum, results[s_inc][t_inc], tmp);
            //mpq_set(results[s_inc][t_inc], sum);
            
            mpq_set_si(tmp, 1, flags.increments);
            mpq_add(t, t, tmp);
        }
        mpq_set_si(tmp, 1, flags.increments);
        mpq_add(s, s, tmp);
    }
    
    mpq_clears(s, t, tmp, sum, NULL);
}

void experiment_run_simulation(ExperimentFlags flags, IplImage *result_img, IplImage *coop_img, IplImage *def_img, IplImage *mix_img)
{
    double **results;
    int n = 2 * flags.increments;
    result_t *result = result_new(n + 1);
    
    printf("n = %d\n", n);
    /*
    results = (double **)g_malloc(sizeof(double *) * (n + 1));
    int i;
    for(i = 0; i <= n; ++i)
    {
        results[i] = (double *)g_malloc(sizeof(double) * (n + 1));
        int j;
        for(j = 0; j <= n; ++j)
        {
            results[i][j] = 0;
        }
        gmp_printf("\n");
    }*/
    
    mpq_t p_c;
    mpq_init(p_c);
    mpq_set_si(p_c, flags.percentage, 100);
    
    game_t *game;
    game = game_new(flags.graph_type, flags.graph_parameter_1, flags.graph_parameter_2, p_c);
    
    int i;
    for(i = 0; i < flags.repititions; ++i)
    {
        game_set_initial_configuration(game);
        experiment_run_simulation1(flags, game, result);
    }
    
    for(i = 0; i <= n; ++i)
    {
        int j;
        for(j = 0; j <= n; ++j)
        {
            result->result[i][j] = result->result[i][j] / (flags.repititions * game->graph->n);
            result->cooperate[i][j] /= flags.repititions;
            result->defect[i][j] /= flags.repititions;
            result->mixed[i][j] /= flags.repititions;
            g_print("%.3f ", result->result[i][j]);
        }
        gmp_printf("\n");
    }
    
    result_to_image(result, result_img, coop_img, def_img, mix_img);
    /*
    for(i = 0; i <= n; ++i)
    {
        g_free(results[i]);
    }
    g_free(results);*/
    result_free(result);
    
    mpq_clear(p_c);
    game_free(game);
}