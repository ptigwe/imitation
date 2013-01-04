#include <glib.h>
#include <gmp.h>
#include <cv.h>
#include <highgui.h>
#include "colourmap.h"
#include "game.h"

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

typedef struct
{
    int update_rule;
    int percentage;
    int generations;
    int gui;
    int repititions;
    int graph_type;
    int graph_parameter_1;
    int graph_parameter_2;
    int increments;
    int verbose;
}ExperimentFlags;

void experiment_run_simulation1(ExperimentFlags flags, game_t *game, double **results);
void experiment_run_simulation(ExperimentFlags flags, IplImage *result_img);

#endif