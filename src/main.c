
#include <cv.h>
#include <highgui.h>
#include "ui.h"
#include "graph.h"
#include <glib.h>
#include <gmp.h>
#include "random.h"
#include "game.h"
#include "experiment.h"
#include "colourmap.h"
#include "result.h"
#include <getopt.h>

void usage()
{
    g_print("usage: simulator [-g] [-G graph type] [-a graph parameter 1] [-b graph parameter 1]\n");
    g_print("                 [-h] [-i increments] [-p percentage] [-r repetitions] [-t time] \n");
    g_print("                 [-u update rule] [-v]\n");
    exit(0);
}

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
    mpq_set_si(p_c, 50, 100);
    game_t *game = game_new(CYCLE_GRAPH, 100, 1, p_c);
    mpq_set_si(game->s, 4, 10);
    mpq_set_si(game->t, 1, 5);
    game_set_initial_configuration(game);
    g_print("Cooperators: %d\n", game_get_number_of_cooperators(game));
    game_play_t_rounds(game, 1, 1000);
    
    int i = 0;
    int n = game->graph->n;
    for(i = 0; i < n; ++i)
    {
        int j = GPOINTER_TO_INT(g_slist_nth_data(game->graph->edges[i], 0));
        g_print("%d: %d -> %d (%d)\n", i, game->initial_config[i], game->current_config[i], game_is_in_steady_state(game));
        //game_compute_p_i(game, i, 0, p_c);
    }
    g_print("Cooperators: %d\n", game_get_number_of_cooperators(game));
    game_free(game);
    mpq_clear(p_c);*/
    
    /*
    mpq_t p_c;
    mpq_init(p_c);
    mpq_set_si(p_c, 1, 2);
    game_t *game = game_new(COMPLETE_GRAPH, 10, 3, p_c);
    mpq_set_si(game->s, 1, 2);
    mpq_set_si(game->t, 1, 5);
    mpq_t *p_ij;
    p_ij = (mpq_t *)malloc(sizeof(mpq_t) * game->graph->n);
    int n = game->graph->n;
    
    int i = 0;
    for(i = 0; i < n; ++i)
    {
        mpq_init(p_ij[i]);
    }
    
    game_set_initial_configuration(game);
    game_play_t_rounds(game, 2, 3);
    
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
    mpq_clear(p_c);*/
    
    ExperimentFlags flags;
    flags.update_rule = -1;
    flags.percentage = -1;
    flags.generations = -1;
    flags.repetitions = -1;
    flags.graph_type = -1;
    flags.graph_parameter_1 = -1;
    flags.increments = -1;
    flags.verbose = 0;
    flags.gui = FALSE;
    flags.threaded = 0;
    flags.position = 0;
    
    int args = 0;
    
    int c;
    while ((c = getopt (argc, argv, "a:b:gG:hi:mop:r:t:u:v")) != -1)
    {
        switch(c)
        {
            case 'a':
                flags.graph_parameter_1 = atoi(optarg);
                break;
            case 'b':
                flags.graph_parameter_2 = atoi(optarg);
                break;
            case 'g':
                flags.gui = 1;
                break;
            case 'G':
                flags.graph_type = atoi(optarg);
                break;
            case 'h':
                usage();
            case 'i':
                flags.increments = atoi(optarg);
                break;
            case 'm':
                flags.threaded = 1;
                break;
            case 'o':
                flags.position = 1;
                break;
            case 'p':
                flags.percentage = atoi(optarg);
                break;
            case 'r':
                flags.repetitions = atoi(optarg);
                break;
            case 't':
                flags.generations = atoi(optarg);
                break;
            case 'u':
                flags.update_rule = atoi(optarg);
                break;
            case 'v':
                flags.verbose = 1;
                break;
            case '?':
                usage();
                break;
            default:
                abort();
        }
        ++args;
    }
    
    if(args == 0)
    {
        usage();
    }
    
    if(flags.gui)
    {
        ui_init(&argc, &argv);
    }
    else
    {
        if(!experiment_validate_flags(flags))
            exit(1);
        
        //draw_colour_bar(img, 1000);
        
        result_t *result = experiment_run_simulation(flags);
        experiment_save_results(flags, result);

        //g_print("width - %f, height - %f\n", width, height);
        //cvWaitKey(0);
    }
    
    return 0;
}
