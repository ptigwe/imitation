#include <gtk/gtk.h>

#ifndef UI_ACTIONS_H
#define UI_ACTIONS_H

#include <gtk/gtk.h>
#include <cv.h>
#include <highgui.h>
#include "ui.h"

gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
void destroy(GtkWidget *widget, gpointer data);
void saveData(GtkFileChooser* fchooser, GtkWindow* window);
void saveFile(GtkWidget *widget, GtkWindow* window);
gboolean shouldQuit(GtkWindow *window);
gboolean updateStatusbar(GtkWidget* widget, GdkEventProximity* event, gchar* context);
void enableCheckBox(GtkWidget* widget, GtkWidget* checkbox);
void enableWidget(GtkWidget* widget, GtkWidget* enable);
void showAboutDialog(GtkWidget* widget, gpointer data);
void runSimulation(GtkWidget* widget, gpointer data);

#endif