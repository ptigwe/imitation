#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>
#include <glib.h>
#include "menu_bar.h"
#include "ui_action.h"

extern GtkWidget *window;
extern GtkWidget *statusbar;
GtkWidget *dstwidget;

void ui_init(int *argc, char ***argv);

#endif