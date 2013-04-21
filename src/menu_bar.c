#include "menu_bar.h"

#define MENUCONTEXT "menuhint"

GtkWidget *menu_bar_init(GtkWindow* window, GtkWidget* vbox)
{
    GtkWidget *menubar, *filemenu, *file, *save, *about, *close, *separator;
    GtkAccelGroup *group;
    
    group = gtk_accel_group_new();
    menubar = gtk_menu_bar_new();
    file = gtk_menu_item_new_with_label("File");
    filemenu = gtk_menu_new();
    
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);
    
    save = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, group);
    separator = gtk_separator_menu_item_new();
    about = gtk_image_menu_item_new_from_stock(GTK_STOCK_ABOUT, group);
    close = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE, group);
    
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), save);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), separator);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), about);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), close);
    
    g_signal_connect(G_OBJECT(save), "activate", G_CALLBACK(ui_action_save_file), window);
    g_signal_connect(G_OBJECT(about), "activate", G_CALLBACK(ui_action_show_about_dialog), NULL);
    g_signal_connect_swapped(G_OBJECT(close), "activate", G_CALLBACK(ui_action_destroy), window);
    
    gtk_window_add_accel_group(window, group);
    gtk_box_pack_start_defaults(GTK_BOX(vbox), menubar);
    
    return menubar;
}