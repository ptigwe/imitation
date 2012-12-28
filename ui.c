#include "ui.h"

GtkWidget *window;
GtkWidget *statusbar;
GtkWidget *resultImage;
GtkWidget *graphType;
GtkWidget *players;
GtkWidget *branching, *depth;
GtkWidget *rows, *cols;
GtkWidget *pc;
GtkWidget *orig, *mod;
GtkWidget *t;

GtkWidget *compBtn;

void ui_create_input_frame(GtkWidget* inputBox)
{
    GtkWidget *inputTable;
    inputTable = gtk_table_new(14, 4, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(inputTable), 10);
    
    GtkWidget* graphLabel = gtk_label_new("Graph Structure");
    gtk_table_attach(GTK_TABLE(inputTable), graphLabel, 0, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GList *list = NULL;
    list = g_list_append(list, "Cycle graph");
    list = g_list_append(list, "Complete graph");
    list = g_list_append(list, "Complete bi-partite graph");
    list = g_list_append(list, "Grid");
    list = g_list_append(list, "Tree");
    
    graphType = gtk_combo_new();
    gtk_combo_set_popdown_strings(GTK_COMBO(graphType), list);
    gtk_table_attach(GTK_TABLE(inputTable), graphType, 2, 4, 0, 1, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    g_list_free(list);
    
    gtk_table_attach(GTK_TABLE(inputTable), gtk_hseparator_new(), 0, 4, 1, 2, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* playersLabel = gtk_label_new("Number of Players");
    gtk_table_attach(GTK_TABLE(inputTable), playersLabel, 0, 2, 2, 3, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    players = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(players), 10);
    gtk_table_attach(GTK_TABLE(inputTable), players, 2, 4, 2, 3, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* bLabel = gtk_label_new("Branching Factor");
    gtk_table_attach(GTK_TABLE(inputTable), bLabel, 0, 1, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    branching = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(branching), 10);
    gtk_table_attach(GTK_TABLE(inputTable), branching, 1, 2, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* dLabel = gtk_label_new("Depth");
    gtk_table_attach(GTK_TABLE(inputTable), dLabel, 2, 3, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    depth = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(depth), 10);
    gtk_table_attach(GTK_TABLE(inputTable), depth, 3, 4, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* rowsLabel = gtk_label_new("Rows");
    gtk_table_attach(GTK_TABLE(inputTable), rowsLabel, 0, 1, 4, 5, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    rows = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(rows), 10);
    gtk_table_attach(GTK_TABLE(inputTable), rows, 1, 2, 4, 5, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* colsLabel = gtk_label_new("Columns");
    gtk_table_attach(GTK_TABLE(inputTable), colsLabel, 2, 3, 4, 5, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    cols = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(cols), 10);
    gtk_table_attach(GTK_TABLE(inputTable), cols, 3, 4, 4, 5, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(inputTable), gtk_hseparator_new(), 0, 4, 5, 6, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* pcLabel = gtk_label_new("Probability of Cooperation");
    gtk_table_attach(GTK_TABLE(inputTable), pcLabel, 0, 2, 6, 7, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    pc = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(pc), 10);
    gtk_table_attach(GTK_TABLE(inputTable), pc, 2, 4, 6, 7, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(inputTable), gtk_hseparator_new(), 0, 4, 7, 8, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* propLabel = gtk_label_new("Proportional Imitate Rule");
    gtk_table_attach(GTK_TABLE(inputTable), propLabel, 0, 4, 8, 9, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    orig = gtk_radio_button_new_with_label(NULL, "Original");
    gtk_table_attach(GTK_TABLE(inputTable), orig, 0, 2, 9, 10, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    mod = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(orig), "Modified");
    gtk_table_attach(GTK_TABLE(inputTable), mod, 2, 4, 9, 10, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(inputTable), gtk_hseparator_new(), 0, 4, 10, 11, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* tLabel = gtk_label_new("Number of Generations");
    gtk_table_attach(GTK_TABLE(inputTable), tLabel, 0, 2, 11, 12, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    t = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(t), 10);
    gtk_table_attach(GTK_TABLE(inputTable), t, 2, 4, 11, 12, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(inputTable), gtk_hseparator_new(), 0, 4, 12, 13, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    compBtn = gtk_button_new_with_label("Run simulation");
    g_signal_connect(G_OBJECT(compBtn), "clicked", G_CALLBACK(ui_action_run_simulation), NULL);
    gtk_table_attach(GTK_TABLE(inputTable), compBtn, 1, 3, 13, 14, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_box_pack_start_defaults(GTK_BOX(inputBox), inputTable);
}

void ui_init(int *argc, char ***argv)
{
    gtk_init(argc, argv);
    
    GtkWidget *menubox, *table, *subtable, *srcbox, *dstbox;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simulator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, -1, -1);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    
    table = gtk_table_new(2, 1, FALSE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    
    menubox = gtk_vbox_new(TRUE, 10);
    menu_bar_init(GTK_WINDOW(window), menubox);
    gtk_table_attach(GTK_TABLE(table), menubox, 0, 1, 0, 1,  GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);
    
    subtable = gtk_table_new(1, 2, FALSE);
    GtkWidget* inputFrame = gtk_frame_new("Input");
    srcbox = gtk_vbox_new(FALSE, 10);
    ui_create_input_frame(srcbox);
    gtk_container_add(GTK_CONTAINER(inputFrame), srcbox);
    gtk_table_attach(GTK_TABLE(subtable), inputFrame, 0, 1, 0, 1, GTK_SHRINK,GTK_EXPAND | GTK_FILL, 1, 1);
    
    GtkWidget* resultFrame = gtk_frame_new("Result");
    GtkWidget* dstalign = gtk_alignment_new(0.5, 0, 1, 0);
    dstbox = gtk_vbox_new(TRUE, 10);
    dstwidget = gtk_image_new_from_file("");
    gtk_box_pack_start_defaults(GTK_BOX(dstbox), dstwidget);
    gtk_container_add(GTK_CONTAINER(dstalign), dstbox);
    gtk_container_add(GTK_CONTAINER(resultFrame), dstalign);
    gtk_table_attach_defaults(GTK_TABLE(subtable), resultFrame, 1, 2, 0, 1);
    
    gtk_table_attach_defaults(GTK_TABLE(table), subtable, 0, 1, 1, 2);
    
    statusbar = gtk_statusbar_new();
    gtk_statusbar_set_has_resize_grip(GTK_STATUSBAR(statusbar), FALSE);
    gtk_table_attach(GTK_TABLE(table), statusbar, 0, 1, 2, 3,  GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);
    
    gtk_container_add(GTK_CONTAINER(window), table);
    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(ui_action_delete_event), NULL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(ui_action_destroy), NULL);
    
    GdkScreen* screen = gdk_screen_get_default();
    int width = gdk_screen_get_width(screen);
    int height = gdk_screen_get_height(screen) - 100;
    gtk_widget_set_size_request(window, width, height);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_widget_show_all(window);
    
    gtk_main();
}