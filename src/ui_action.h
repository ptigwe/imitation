#include <gtk/gtk.h>

#ifndef UI_ACTION_H
#define UI_ACTION_H

#include <gtk/gtk.h>
#include <cv.h>
#include <highgui.h>
#include "ui.h"
#include "result.h"

gboolean ui_action_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
void ui_action_destroy(GtkWidget *widget, gpointer data);
void ui_action_save_data(GtkFileChooser* fchooser, GtkWindow* window);
void ui_action_save_file(GtkWidget *widget, GtkWindow* window);
gboolean ui_action_should_quit(GtkWindow *window);
void ui_action_show_about_dialog(GtkWidget* widget, gpointer data);
void ui_action_run_simulation(GtkWidget* widget, gpointer data);

#endif