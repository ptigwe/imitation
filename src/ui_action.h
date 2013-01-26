#include <gtk/gtk.h>

#ifndef UI_ACTION_H
#define UI_ACTION_H

#include <gtk/gtk.h>
#include <cv.h>
#include <highgui.h>
#include "ui.h"

gboolean ui_action_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
void ui_action_destroy(GtkWidget *widget, gpointer data);
void ui_action_save_data(GtkFileChooser* fchooser, GtkWindow* window);
void ui_action_save_file(GtkWidget *widget, GtkWindow* window);
gboolean ui_action_should_quit(GtkWindow *window);
gboolean ui_action_update_statusbar(GtkWidget* widget, GdkEventProximity* event, gchar* context);
void ui_action_enable_check_box(GtkWidget* widget, GtkWidget* checkbox);
void ui_action_enable_widget(GtkWidget* widget, GtkWidget* enable);
void ui_action_show_about_dialog(GtkWidget* widget, gpointer data);
void ui_action_run_simulation(GtkWidget* widget, gpointer data);

#endif