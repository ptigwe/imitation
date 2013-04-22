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
    
    IplImage *res_img = cvCreateImage(size, IPL_DEPTH_64F, 3);
    IplImage *coop_img = cvCloneImage(res_img);
    IplImage *def_img = cvCloneImage(res_img);
    IplImage *mix_img = cvCloneImage(res_img);
    
    IplImage *r_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage *c_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage *d_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    IplImage *m_img = cvCreateImage(size, IPL_DEPTH_8U, 3);
    
    result_to_image(result, res_img, coop_img, def_img, mix_img);
    
    cvConvertScale(res_img, r_img, 255, 0);
    cvConvertScale(coop_img, c_img, 255, 0);
    cvConvertScale(def_img, d_img, 255, 0);
    cvConvertScale(mix_img, m_img, 255, 0);
    
    cvCvtColor(r_img, r_img, CV_BGR2RGB);
    cvCvtColor(c_img, c_img, CV_BGR2RGB);
    cvCvtColor(d_img, d_img, CV_BGR2RGB);
    cvCvtColor(m_img, m_img, CV_BGR2RGB);
    
    GdkPixbuf* r_pixbuf = gdk_pixbuf_new_from_data((guchar*)r_img->imageData, GDK_COLORSPACE_RGB,
                                                    FALSE, r_img->depth,
                                                    r_img->width,
                                                    r_img->height,
                                                    (r_img->widthStep),
                                                    NULL, NULL );
    
    GdkPixbuf* c_pixbuf = gdk_pixbuf_new_from_data((guchar*)c_img->imageData, GDK_COLORSPACE_RGB,
                                                    FALSE, c_img->depth,
                                                    c_img->width,
                                                    c_img->height,
                                                    (c_img->widthStep),
                                                    NULL, NULL );
    
    GdkPixbuf* d_pixbuf = gdk_pixbuf_new_from_data((guchar*)d_img->imageData, GDK_COLORSPACE_RGB,
                                                    FALSE, d_img->depth,
                                                    d_img->width,
                                                    d_img->height,
                                                    (d_img->widthStep),
                                                    NULL, NULL );

    GdkPixbuf* m_pixbuf = gdk_pixbuf_new_from_data((guchar*)m_img->imageData, GDK_COLORSPACE_RGB,
                                                    FALSE, m_img->depth,
                                                    m_img->width,
                                                    m_img->height,
                                                    (m_img->widthStep),
                                                    NULL, NULL );
    
    gtk_image_set_from_pixbuf(GTK_IMAGE(res_widget), r_pixbuf);
    gtk_image_set_from_pixbuf(GTK_IMAGE(coop_widget), c_pixbuf);
    gtk_image_set_from_pixbuf(GTK_IMAGE(def_widget), d_pixbuf);
    gtk_image_set_from_pixbuf(GTK_IMAGE(mix_widget), m_pixbuf);
    
    cvReleaseImage(&res_img);
    cvReleaseImage(&coop_img);
    cvReleaseImage(&def_img);
    cvReleaseImage(&mix_img);
    
    cvReleaseImage(&r_img);
    cvReleaseImage(&c_img);
    cvReleaseImage(&d_img);
    cvReleaseImage(&m_img);
    
    g_object_unref(G_OBJECT(r_pixbuf));
    g_object_unref(G_OBJECT(c_pixbuf));
    g_object_unref(G_OBJECT(d_pixbuf));
    g_object_unref(G_OBJECT(m_pixbuf));
    
    result_free(result);
}