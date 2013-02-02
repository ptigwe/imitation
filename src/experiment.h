#include <glib.h>
#include <gmp.h>
#include <cv.h>
#include <highgui.h>
#include "colourmap.h"
#include "game.h"
#include "result.h"

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

gboolean experiment_validate_flags(ExperimentFlags flags);
void experiment_run_simulation1(ExperimentFlags flags, game_t *game, result_t *result);
void experiment_run_simulation(ExperimentFlags flags, IplImage *result_img, IplImage *coop_img, IplImage *def_img, IplImage *mix_img);

#endif