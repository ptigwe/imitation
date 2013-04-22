#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>
#include <glib.h>
#include <cv.h>
#include <highgui.h>
#include "graph.h"
#include "game.h"
#include "experiment.h"
#include "menu_bar.h"
#include "ui_action.h"

extern GtkWidget *window;
extern GtkWidget *statusbar;
extern GtkWidget *res_widget;
extern GtkWidget *coop_widget;
extern GtkWidget *def_widget;
extern GtkWidget *mix_widget;

extern CvSize size;

void ui_init(int *argc, char ***argv);
ExperimentFlags ui_get_experiment_flags();

#endif