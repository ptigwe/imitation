#include "experiment.h"

gboolean experiment_validate_flags(ExperimentFlags flags)
{
    if(flags.generations <= 0)
    {
        return FALSE;
    }
    
    if(flags.repetitions <= 0)
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
    mpq_init(s);
    mpq_init(t);
    mpq_init(tmp);
    mpq_init(sum);
    mpq_set_si(s, S_MIN, 1);
    mpq_set_si(t, T_MIN, 1);
    
    int completed = 0;
    int total_games = pow((2 * flags.increments) + 1, 2);
    
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
            
            ++completed;
            
            if(flags.verbose)
            {
                gmp_printf("%Qd, %Qd -> %d \n", s, t, game_get_number_of_cooperators(game));
            }
            else
            {
                double per = (((double) completed) / total_games) * 100;
                g_print("\r%.1f %% games completed.", per);
            }
            //mpq_add(sum, results[s_inc][t_inc], tmp);
            //mpq_set(results[s_inc][t_inc], sum);
            
            mpq_set_si(tmp, 1, flags.increments);
            mpq_add(t, t, tmp);
        }
        mpq_set_si(tmp, 1, flags.increments);
        mpq_add(s, s, tmp);
    }
    
    mpq_clear(s);
    mpq_clear(t);
    mpq_clear(tmp);
    mpq_clear(sum);
}

ExperimentFlags exp_flags;

void *experiment_run_thread(gpointer num, void *res)
{
    result_t *result = (result_t *) res;

    ExperimentFlags flags = exp_flags;
    mpq_t p_c;
    mpq_init(p_c);
    mpq_set_si(p_c, flags.percentage, 100);
    
    int i = GPOINTER_TO_INT(num);
    g_print("Starting Experiment %d\n", i);

    game_t *game;
    game = game_new(flags.graph_type, flags.graph_parameter_1, flags.graph_parameter_2, p_c);

    game_set_initial_configuration(game, flags.position);
    
    experiment_run_simulation1(exp_flags, game, result);

    game_free(game);
    mpq_clear(p_c);
    return NULL;
}

result_t *experiment_run_simulation_threaded(ExperimentFlags flags)
{
    exp_flags = flags;
    
    double **results;
    int n = 2 * flags.increments;
    result_t *result = result_new(n + 1);
    
    mpq_t p_c;
    mpq_init(p_c);
    mpq_set_si(p_c, flags.percentage, 100);
    
    game_t *game;
    game = game_new(flags.graph_type, flags.graph_parameter_1, flags.graph_parameter_2, p_c);
    
    GThreadPool *pool = g_thread_pool_new((GFunc)experiment_run_thread, result, MAX_THREADS, FALSE, NULL);

    int i;
    for(i = 1; i <= flags.repetitions; ++i)
    {
        gpointer num = GINT_TO_POINTER(i);
        gboolean b = g_thread_pool_push(pool, num, NULL);
        g_print("Started %d %d\n", b, i);
    }
    g_thread_pool_free(pool, 0, 1);
    
    for(i = 0; i <= n; ++i)
    {
        int j;
        for(j = 0; j <= n; ++j)
        {
            result->result[i][j] = result->result[i][j] / (flags.repetitions * game->graph->n);
            result->cooperate[i][j] /= flags.repetitions;
            result->defect[i][j] /= flags.repetitions;
            result->mixed[i][j] /= flags.repetitions;
            
            if(flags.verbose)
            {
                g_print("%.3f ", result->result[i][j]);
            }
        }
        if(flags.verbose)
            gmp_printf("\n");
    }
    
    mpq_clear(p_c);
    game_free(game);
    
    return result;
}

result_t *experiment_run_simulation_non_threaded(ExperimentFlags flags)
{
    double **results;
    int n = 2 * flags.increments;
    result_t *result = result_new(n + 1);
    
    //printf("n = %d\n", n);
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
    for(i = 0; i < flags.repetitions; ++i)
    {    
        if(!flags.verbose)
        {
            g_print("\nExperiment %d / %d: \n", i + 1, flags.repetitions);
        }
        game_set_initial_configuration(game, flags.position);
        experiment_run_simulation1(flags, game, result);
    }
    
    for(i = 0; i <= n; ++i)
    {
        int j;
        for(j = 0; j <= n; ++j)
        {
            result->result[i][j] = result->result[i][j] / (flags.repetitions * game->graph->n);
            result->cooperate[i][j] /= flags.repetitions;
            result->defect[i][j] /= flags.repetitions;
            result->mixed[i][j] /= flags.repetitions;
            
            if(flags.verbose)
            {
                g_print("%.3f ", result->result[i][j]);
            }
        }
        if(flags.verbose)
            gmp_printf("\n");
    }
    
    //result_to_image(result, result_img, coop_img, def_img, mix_img);
    /*
    for(i = 0; i <= n; ++i)
    {
        g_free(results[i]);
    }
    g_free(results);*/
    //experiment_save_results(flags, result);
    //result_free(result);
    
    mpq_clear(p_c);
    game_free(game);
    
    return result;
}

result_t *experiment_run_simulation(ExperimentFlags flags)
{
    if(flags.threaded)
    {
        return experiment_run_simulation_threaded(flags);
    }
    else
    {
        return experiment_run_simulation_non_threaded(flags);
    }
}

void experiment_save_results(ExperimentFlags flags, result_t *result)
{
    double whratio = (double) 250/165;
    double height = 400;
    int width = height * whratio;
    height += (2 * Y_OFFSET);
    width += (X_OFFSET1 + X_OFFSET2);
    CvSize size = cvSize(width, height);
    
    IplImage *res_img = cvCreateImage(size, IPL_DEPTH_64F, 3);
    cvRectangle(res_img, cvPoint(0, 0), cvPoint(width, height), CV_RGB(1, 1, 1), CV_FILLED, 8, 0);
    IplImage *coop_img = cvCloneImage(res_img);
    IplImage *def_img = cvCloneImage(res_img);
    IplImage *mix_img = cvCloneImage(res_img);
    
    IplImage *r_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage *c_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage *d_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage *m_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    
    result_to_image(result, res_img, coop_img, def_img, mix_img);
    
    cvConvertScale(res_img, r_img, 255, 0);
    cvConvertScale(coop_img, c_img, 255, 0);
    cvConvertScale(def_img, d_img, 255, 0);
    cvConvertScale(mix_img, m_img, 255, 0);
    
    char file_name[50];
    
    sprintf(file_name, "G%d-a%d-b%d-p%d-r%d-t%d-u%d-result.jpg", flags.graph_type,
            flags.graph_parameter_1, flags.graph_parameter_2, flags.percentage, 
            flags.repetitions, flags.generations, flags.update_rule);
    cvSaveImage(file_name, r_img, 0);
    
    sprintf(file_name, "G%d-a%d-b%d-p%d-r%d-t%d-u%d-cooperators.jpg", flags.graph_type,
            flags.graph_parameter_1, flags.graph_parameter_2, flags.percentage, 
            flags.repetitions, flags.generations, flags.update_rule);
    cvSaveImage(file_name, c_img, 0);
    
    sprintf(file_name, "G%d-a%d-b%d-p%d-r%d-t%d-u%d-defectors.jpg", flags.graph_type,
            flags.graph_parameter_1, flags.graph_parameter_2, flags.percentage, 
            flags.repetitions, flags.generations, flags.update_rule);
    cvSaveImage(file_name, d_img, 0);
    
    sprintf(file_name, "G%d-a%d-b%d-p%d-r%d-t%d-u%d-mixed.jpg", flags.graph_type,
            flags.graph_parameter_1, flags.graph_parameter_2, flags.percentage, 
            flags.repetitions, flags.generations, flags.update_rule);
    cvSaveImage(file_name, m_img, 0);
    
    cvReleaseImage(&r_img);
    cvReleaseImage(&d_img);
    cvReleaseImage(&m_img);
    cvReleaseImage(&c_img);
    cvReleaseImage(&res_img);
    cvReleaseImage(&def_img);
    cvReleaseImage(&mix_img);
    cvReleaseImage(&coop_img);
}