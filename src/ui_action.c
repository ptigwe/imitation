#include "ui_action.h"

static gboolean delete_parsed = FALSE;

gboolean ui_action_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return !(delete_parsed = ui_action_should_quit(GTK_WINDOW(widget)));
}

/* Another callback */
void ui_action_destroy(GtkWidget *widget, gpointer data)
{
    if(delete_parsed || ui_action_should_quit(GTK_WINDOW(widget)))
        gtk_main_quit();
}

gboolean ui_action_should_quit(GtkWindow *window)
{
    GtkWidget* dialog;
    
    dialog = gtk_message_dialog_new(window, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, 
                        GTK_BUTTONS_YES_NO, "Do you want to quit?");
    
    gtk_window_set_title(GTK_WINDOW(dialog), "Exit?");
    int result = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    switch(result)
    {
        case GTK_RESPONSE_YES:
            return TRUE;
        case GTK_RESPONSE_NO:
            return FALSE;
    }
}

void ui_action_save_data(GtkFileChooser* fchooser, GtkWindow* window)
{
}

void ui_action_save_file(GtkWidget *widget, GtkWindow* window)
{
}

void ui_action_show_about_dialog(GtkWidget* widget, gpointer data)
{
    GtkWidget* dialog;
    dialog = gtk_about_dialog_new();
    
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "Simulator");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.0");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "(c) University of Liverpool Computer Science Department");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "");
    const gchar* authors[] = {"Tobenna Peter Igwe (ptigwe@gmail.com)", NULL};
    gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(dialog), authors);
    
    gtk_dialog_run(GTK_DIALOG(dialog));
    
    gtk_widget_destroy(dialog);
}

void ui_action_run_simulation(GtkWidget* widget, gpointer data)
{
    ExperimentFlags flags = ui_get_experiment_flags();
    experiment_validate_flags(flags);
    result_t *result = experiment_run_simulation(flags);
    result_free(result);
}