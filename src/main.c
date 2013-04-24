
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
#include "config.h"

void usage()
{
    g_print("usage: simulator [-g] [-G graph type] [-a graph parameter 1] [-b graph parameter 1]\n");
    g_print("                 [-h] [-i increments] [-p percentage] [-r repetitions] [-t time] \n");
    g_print("                 [-u update rule] [-v]\n");
    exit(0);
}

int main(int argc, char** argv)
{
    
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
    while (1)
    {
        static struct option long_options[] =
        {
            {"verbose",     no_argument,       0, 'v'},
            {"update",      required_argument, 0, 'u'},
            {"percentage",  required_argument, 0, 'p'},
            {"generations", required_argument, 0, 't'},
            {"repetitions", required_argument, 0, 'r'},
            {"graph",       required_argument, 0, 'G'},
            {"graphp1",     required_argument, 0, 'a'},
            {"graphp2",     required_argument, 0, 'b'},
            {"increments",  required_argument, 0, 'i'},
            {"gui",         required_argument, 0, 'g'},
            {"threaded",    no_argument, 0, 'm'},
            {"position",    no_argument, 0, 'o'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "a:b:gG:hi:mop:r:t:u:v",
                                long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;
            
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
            
        #ifndef HAVE_GLIB_2_32
        g_thread_init(NULL);
        #endif
        
        result_t *result = experiment_run_simulation(flags);
        experiment_save_results(flags, result);
        result_free(result);
    }
    
    return 0;
}
