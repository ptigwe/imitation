#include <gtk/gtk.h>
#include <cv.h>
#include <highgui.h>
#include "ui_action.h"

#ifndef MENU_BAR_H
#define MENU_BAR_H

GtkWidget *menu_bar_init(GtkWindow* window, GtkWidget* vbox);

#endif