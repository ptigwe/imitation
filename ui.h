#ifndef UI_H
#define UI_H

#include <gtk/gtk.h>
#include <glib.h>
#include "menubar.h"
#include "uiactions.h"

extern GtkWidget *window;
extern GtkWidget *statusbar;
GtkWidget *dstwidget;

void initUI(int* argc, char*** argv);

#endif