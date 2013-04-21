#include "ui.h"

GtkWidget *window;
GtkWidget *statusbar;
GtkWidget *graph_type;
GtkWidget *players;
GtkWidget *param1, *param2;
GtkWidget *pc;
GtkWidget *orig, *mod;
GtkWidget *t;

GtkWidget *start_btn;

GtkWidget *res_widget;
GtkWidget *coop_widget;
GtkWidget *def_widget;
GtkWidget *mix_widget;

char *types[5] = {"Cycle graph", "Complete graph", "Complete bi-partite graph", "Uniform Tree", "Grid"};

void ui_create_input_frame(GtkWidget* inputBox)
{
    GtkWidget *input_table;
    input_table = gtk_table_new(13, 4, TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(input_table), 10);
    
    GtkWidget* graph_label = gtk_label_new("Graph Structure");
    gtk_table_attach(GTK_TABLE(input_table), graph_label, 0, 2, 0, 1, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    graph_type = gtk_combo_box_new_text();
    int i;
    for(i = 0; i < 5; ++i)
    {
        gtk_combo_box_append_text(GTK_COMBO_BOX(graph_type), types[i]);
    }
    gtk_table_attach(GTK_TABLE(input_table), graph_type, 2, 4, 0, 1, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(input_table), gtk_hseparator_new(), 0, 4, 1, 2, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* players_label = gtk_label_new("Number of Players");
    gtk_table_attach(GTK_TABLE(input_table), players_label, 0, 2, 2, 3, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    players = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(players), 10);
    gtk_table_attach(GTK_TABLE(input_table), players, 2, 4, 2, 3, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* param1_label = gtk_label_new("Parameter 1");
    gtk_table_attach(GTK_TABLE(input_table), param1_label, 0, 1, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    param1 = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(param1), 10);
    gtk_table_attach(GTK_TABLE(input_table), param1, 1, 2, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* param2_label = gtk_label_new("Parameter 2");
    gtk_table_attach(GTK_TABLE(input_table), param2_label, 2, 3, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    param2 = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(param2), 10);
    gtk_table_attach(GTK_TABLE(input_table), param2, 3, 4, 3, 4, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(input_table), gtk_hseparator_new(), 0, 4, 4, 5, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* pcLabel = gtk_label_new("Probability of Cooperation");
    gtk_table_attach(GTK_TABLE(input_table), pcLabel, 0, 2, 5, 6, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    pc = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(pc), 10);
    gtk_table_attach(GTK_TABLE(input_table), pc, 2, 4, 5, 6, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(input_table), gtk_hseparator_new(), 0, 4, 6, 7, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* propLabel = gtk_label_new("Proportional Imitate Rule");
    gtk_table_attach(GTK_TABLE(input_table), propLabel, 0, 4, 7, 8, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    orig = gtk_radio_button_new_with_label(NULL, "Original");
    gtk_table_attach(GTK_TABLE(input_table), orig, 0, 2, 8, 9, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    mod = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(orig), "Modified");
    gtk_table_attach(GTK_TABLE(input_table), mod, 2, 4, 8, 9, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(input_table), gtk_hseparator_new(), 0, 4, 9, 10, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    GtkWidget* tLabel = gtk_label_new("Number of Generations");
    gtk_table_attach(GTK_TABLE(input_table), tLabel, 0, 2, 10, 11, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    t = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(t), 10);
    gtk_table_attach(GTK_TABLE(input_table), t, 2, 4, 10, 11, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_table_attach(GTK_TABLE(input_table), gtk_hseparator_new(), 0, 4, 11, 12, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    start_btn = gtk_button_new_with_label("Run simulation");
    g_signal_connect(G_OBJECT(start_btn), "clicked", G_CALLBACK(ui_action_run_simulation), NULL);
    gtk_table_attach(GTK_TABLE(input_table), start_btn, 1, 3, 12, 13, GTK_EXPAND | GTK_FILL, GTK_SHRINK, 1, 1);
    
    gtk_box_pack_start_defaults(GTK_BOX(inputBox), input_table);
}

void ui_create_result_notebook(GtkWidget *result_box)
{
    GtkWidget *notebook = gtk_notebook_new();
    
    GtkWidget *res_label = gtk_label_new("Result");
    GtkWidget *coop_label = gtk_label_new("Cooperator");
    GtkWidget *def_label = gtk_label_new("Defector");
    GtkWidget *mix_label = gtk_label_new("Mixed");
    
    res_widget = gtk_image_new_from_file("");
    coop_widget = gtk_image_new_from_file("");
    def_widget = gtk_image_new_from_file("");
    mix_widget = gtk_image_new_from_file("");
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), res_widget, res_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), coop_widget, coop_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), def_widget, def_label);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), mix_widget, mix_label);
    
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), TRUE);
    
    gtk_box_pack_start_defaults(GTK_BOX(result_box), notebook);
}

int ui_get_graph_type()
{
    return gtk_combo_box_get_active(GTK_COMBO_BOX(graph_type));
}

int ui_get_parameter_1()
{
    const char* text = gtk_entry_get_text(GTK_ENTRY(param1));
    return atoi(text);
}

int ui_get_parameter_2()
{
    const char* text = gtk_entry_get_text(GTK_ENTRY(param2));
    return atoi(text);
}

int ui_get_percentage()
{
    const char* text = gtk_entry_get_text(GTK_ENTRY(pc));
    return atoi(text);
}

int ui_get_generations()
{
    const char* text = gtk_entry_get_text(GTK_ENTRY(t));
    return atoi(text);
}

int ui_get_update_rule()
{
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(orig)))
    {
        return PROPORTIONAL_RULE;
    }
    
    return MOD_PROPORTIONAL_RULE;
}

int ui_get_repititions()
{
    return 10;
}

ExperimentFlags ui_get_experiment_flags()
{
    ExperimentFlags flags;
    
    flags.graph_type = ui_get_graph_type();
    flags.graph_parameter_1 = ui_get_parameter_1();
    flags.graph_parameter_2 = ui_get_parameter_2();
    flags.percentage = ui_get_percentage();
    flags.generations = ui_get_generations();
    flags.update_rule = ui_get_update_rule();
    flags.repetitions = ui_get_repititions();
    
    flags.increments = 25;
    flags.verbose = 0;
    flags.threaded = 0;
    flags.position = 1;
    
    return flags;
}

void ui_init(int *argc, char ***argv)
{
    gtk_init(argc, argv);
    
    GtkWidget *menu_box, *table, *subtable, *src_box, *dst_box;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simulator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, -1, -1);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    
    table = gtk_table_new(2, 1, FALSE);
    gtk_table_set_row_spacings(GTK_TABLE(table), 10);
    
    menu_box = gtk_vbox_new(TRUE, 10);
    menu_bar_init(GTK_WINDOW(window), menu_box);
    gtk_table_attach(GTK_TABLE(table), menu_box, 0, 1, 0, 1,  GTK_EXPAND | GTK_FILL, GTK_SHRINK, 0, 0);
    
    subtable = gtk_table_new(1, 2, FALSE);
    GtkWidget* inputFrame = gtk_frame_new("Input");
    src_box = gtk_vbox_new(FALSE, 10);
    ui_create_input_frame(src_box);
    gtk_container_add(GTK_CONTAINER(inputFrame), src_box);
    gtk_table_attach(GTK_TABLE(subtable), inputFrame, 0, 1, 0, 1, GTK_SHRINK,GTK_EXPAND | GTK_FILL, 1, 1);
    
    GtkWidget* resultFrame = gtk_frame_new("Result");
    GtkWidget* dstalign = gtk_alignment_new(0.5, 0, 1, 0);
    dst_box = gtk_vbox_new(TRUE, 10);
    ui_create_result_notebook(dst_box);
    gtk_container_add(GTK_CONTAINER(dstalign), dst_box);
    gtk_container_add(GTK_CONTAINER(resultFrame), dstalign);
    gtk_table_attach_defaults(GTK_TABLE(subtable), resultFrame, 1, 2, 0, 1);
    
    gtk_table_attach_defaults(GTK_TABLE(table), subtable, 0, 1, 1, 2);
    
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