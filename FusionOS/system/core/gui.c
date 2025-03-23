#include "gui.h"
#include "security.h"
#include "network.h"

extern GtkWidget *main_stack;  // Change to extern declaration
static GtkWidget *window;
static GtkWidget *headerbar;

static const LanguageInfo available_languages[] = {
    {"English (US)", "en_US", "en_US.UTF-8"},
    {"Türkçe", "tr_TR", "tr_TR.UTF-8"},
    {"Deutsch", "de_DE", "de_DE.UTF-8"},
    {"Français", "fr_FR", "fr_FR.UTF-8"},
    {"Español", "es_ES", "es_ES.UTF-8"},
    {NULL, NULL, NULL}
};

static const KeyboardInfo available_keyboards[] = {
    {"English (US)", "us", ""},
    {"Turkish Q", "tr", "q"},
    {"Turkish F", "tr", "f"},
    {"German", "de", ""},
    {"French", "fr", ""},
    {NULL, NULL, NULL}
};

void gui_init_window(void) {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FusionOS Control Panel");
    gtk_window_set_default_size(GTK_WINDOW(window), 1024, 768);
    
    // Create modern headerbar
    headerbar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "FusionOS");
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "System Control");
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

    // Create main container
    main_stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(main_stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    
    // Add main pages
    gtk_stack_add_titled(GTK_STACK(main_stack), gui_create_system_monitor(), "dashboard", "Dashboard");
    gtk_stack_add_titled(GTK_STACK(main_stack), gui_create_security_panel(), "security", "Security");
    gtk_stack_add_titled(GTK_STACK(main_stack), gui_create_network_panel(), "network", "Network");

    // Create stack switcher
    GtkWidget *stack_switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(main_stack));
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), stack_switcher);

    gtk_container_add(GTK_CONTAINER(window), main_stack);
    gtk_widget_show_all(window);
}

GtkWidget* gui_create_system_monitor(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *cpu_bar = gtk_progress_bar_new();
    GtkWidget *mem_bar = gtk_progress_bar_new();
    
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(cpu_bar), "CPU: 0%");
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(mem_bar), "Memory: 0%");
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(cpu_bar), TRUE);
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(mem_bar), TRUE);
    
    gtk_box_pack_start(GTK_BOX(box), cpu_bar, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), mem_bar, FALSE, FALSE, 5);
    
    return box;
}

GtkWidget* gui_create_security_panel(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *frame = gtk_frame_new("Security Settings");
    
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    
    // Add security controls
    gtk_grid_attach(GTK_GRID(grid), 
        gtk_check_button_new_with_label("Enable Secure Boot"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), 
        gtk_check_button_new_with_label("Anti-Tampering"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), 
        gtk_check_button_new_with_label("App Signing"), 0, 2, 1, 1);
    
    gtk_container_add(GTK_CONTAINER(frame), grid);
    gtk_box_pack_start(GTK_BOX(box), frame, TRUE, TRUE, 0);
    
    return box;
}

GtkWidget* gui_create_network_panel(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *frame = gtk_frame_new("Network Settings");
    GtkWidget *grid = gtk_grid_new();
    
    // WiFi list
    GtkWidget *wifi_list = gtk_list_box_new();
    GtkWidget *wifi_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(wifi_scroll), wifi_list);
    
    // Add some dummy networks
    const char *networks[] = {"Home WiFi", "Office Network", "Guest Network"};
    for (int i = 0; i < 3; i++) {
        GtkWidget *row = gtk_list_box_row_new();
        GtkWidget *label = gtk_label_new(networks[i]);
        gtk_container_add(GTK_CONTAINER(row), label);
        gtk_list_box_insert(GTK_LIST_BOX(wifi_list), row, -1);
    }
    
    // Controls
    GtkWidget *scan_button = gtk_button_new_with_label("Scan Networks");
    GtkWidget *connect_button = gtk_button_new_with_label("Connect");
    
    gtk_grid_attach(GTK_GRID(grid), wifi_scroll, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), scan_button, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), connect_button, 1, 1, 1, 1);
    
    gtk_container_add(GTK_CONTAINER(frame), grid);
    gtk_box_pack_start(GTK_BOX(box), frame, TRUE, TRUE, 0);
    
    return box;
}

void gui_create_toolbar(void) {
    GtkWidget *toolbar = gtk_toolbar_new();
    
    // Add toolbar buttons
    GtkToolItem *new_button = gtk_tool_button_new(NULL, "New");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(new_button), "document-new");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_button, -1);
    
    GtkToolItem *save_button = gtk_tool_button_new(NULL, "Save");
    gtk_tool_button_set_icon_name(GTK_TOOL_BUTTON(save_button), "document-save");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save_button, -1);
    
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), GTK_WIDGET(toolbar));
}

void gui_create_system_stats(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *frame = gtk_frame_new("System Statistics");
    
    // CPU Usage
    GtkWidget *cpu_label = gtk_label_new("CPU Usage:");
    GtkWidget *cpu_bar = gtk_level_bar_new_for_interval(0, 100);
    gtk_level_bar_set_value(GTK_LEVEL_BAR(cpu_bar), 45); // Example value
    
    // Memory Usage
    GtkWidget *mem_label = gtk_label_new("Memory Usage:");
    GtkWidget *mem_bar = gtk_level_bar_new_for_interval(0, 100);
    gtk_level_bar_set_value(GTK_LEVEL_BAR(mem_bar), 60); // Example value
    
    // Network Speed
    GtkWidget *net_label = gtk_label_new("Network Speed:");
    GtkWidget *net_bar = gtk_level_bar_new_for_interval(0, 100);
    gtk_level_bar_set_value(GTK_LEVEL_BAR(net_bar), 30); // Example value
    
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    
    gtk_grid_attach(GTK_GRID(grid), cpu_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cpu_bar, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), mem_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), mem_bar, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), net_label, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), net_bar, 1, 2, 1, 1);
    
    gtk_container_add(GTK_CONTAINER(frame), grid);
    gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 0);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "stats", "System Stats");
}

void gui_create_performance_monitor(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *frame = gtk_frame_new("Performance Monitor");
    
    // Real-time graphs
    GtkWidget *cpu_graph = gtk_drawing_area_new();
    GtkWidget *mem_graph = gtk_drawing_area_new();
    GtkWidget *net_graph = gtk_drawing_area_new();
    
    gtk_widget_set_size_request(cpu_graph, 300, 150);
    gtk_widget_set_size_request(mem_graph, 300, 150);
    gtk_widget_set_size_request(net_graph, 300, 150);
    
    // Pack components
    gtk_box_pack_start(GTK_BOX(box), cpu_graph, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), mem_graph, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), net_graph, FALSE, FALSE, 5);
    
    gtk_container_add(GTK_CONTAINER(frame), box);
    gtk_stack_add_titled(GTK_STACK(main_stack), frame, "performance", "Performance");
}

void gui_create_app_manager(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *toolbar = gtk_toolbar_new();
    GtkWidget *app_list = gtk_list_box_new();
    
    // Toolbar buttons
    GtkToolItem *install_btn = gtk_tool_button_new(NULL, "Install");
    GtkToolItem *remove_btn = gtk_tool_button_new(NULL, "Remove");
    GtkToolItem *update_btn = gtk_tool_button_new(NULL, "Update");
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), install_btn, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), remove_btn, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), update_btn, -1);
    
    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), app_list, TRUE, TRUE, 5);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "apps", "Applications");
}

void gui_create_settings_panel(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *notebook = gtk_notebook_new();
    
    // System settings
    GtkWidget *system_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), system_page, 
        gtk_label_new("System"));
        
    // Theme settings
    GtkWidget *theme_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *dark_mode = gtk_switch_new();
    gtk_box_pack_start(GTK_BOX(theme_page), dark_mode, FALSE, FALSE, 5);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), theme_page, 
        gtk_label_new("Appearance"));
    
    gtk_box_pack_start(GTK_BOX(box), notebook, TRUE, TRUE, 0);
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "settings", "Settings");
}

void gui_set_dark_mode(gboolean enabled) {
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-application-prefer-dark-theme", enabled, NULL);
}

void gui_create_terminal(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *label = gtk_label_new("Terminal functionality coming soon...");
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "terminal", "Terminal");
}

void gui_create_file_manager(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *toolbar = gtk_toolbar_new();
    GtkWidget *file_view = gtk_tree_view_new();
    
    // Add file operations buttons
    GtkToolItem *new_folder = gtk_tool_button_new(NULL, "New Folder");
    GtkToolItem *delete = gtk_tool_button_new(NULL, "Delete");
    GtkToolItem *copy = gtk_tool_button_new(NULL, "Copy");
    GtkToolItem *paste = gtk_tool_button_new(NULL, "Paste");
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_folder, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), delete, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), copy, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), paste, -1);
    
    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), file_view, TRUE, TRUE, 0);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "files", "Files");
}

void gui_create_process_manager(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *process_view = gtk_tree_view_new();
    GtkWidget *toolbar = gtk_toolbar_new();
    
    // Add process control buttons
    GtkToolItem *refresh = gtk_tool_button_new(NULL, "Refresh");
    GtkToolItem *end_task = gtk_tool_button_new(NULL, "End Task");
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), refresh, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), end_task, -1);
    
    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), process_view, TRUE, TRUE, 0);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "processes", "Processes");
}

void gui_create_backup_panel(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *frame = gtk_frame_new("System Backup");
    
    // Backup controls
    GtkWidget *grid = gtk_grid_new();
    GtkWidget *backup_btn = gtk_button_new_with_label("Create Backup");
    GtkWidget *restore_btn = gtk_button_new_with_label("Restore System");
    GtkWidget *location = gtk_file_chooser_button_new("Select Backup Location", 
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
    
    gtk_grid_attach(GTK_GRID(grid), location, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), backup_btn, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), restore_btn, 1, 1, 1, 1);
    
    gtk_container_add(GTK_CONTAINER(frame), grid);
    gtk_box_pack_start(GTK_BOX(box), frame, FALSE, FALSE, 0);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "backup", "Backup");
}

GtkWidget* gui_create_language_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *frame = gtk_frame_new("System Language");
    GtkWidget *list = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    
    // Add languages to list
    for (int i = 0; available_languages[i].name != NULL; i++) {
        GtkWidget *row = gtk_list_box_row_new();
        GtkWidget *label = gtk_label_new(available_languages[i].name);
        gtk_container_add(GTK_CONTAINER(row), label);
        gtk_list_box_insert(GTK_LIST_BOX(list), row, -1);
    }
    
    gtk_container_add(GTK_CONTAINER(scroll), list);
    gtk_container_add(GTK_CONTAINER(frame), scroll);
    gtk_box_pack_start(GTK_BOX(box), frame, TRUE, TRUE, 0);
    
    GtkWidget *apply_btn = gtk_button_new_with_label("Apply Language");
    gtk_box_pack_start(GTK_BOX(box), apply_btn, FALSE, FALSE, 5);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "language", "Language");
    return box;
}

GtkWidget* gui_create_keyboard_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *frame = gtk_frame_new("Keyboard Layout");
    GtkWidget *grid = gtk_grid_new();
    
    // Keyboard layout selector
    GtkWidget *layout_combo = gtk_combo_box_text_new();
    for (int i = 0; available_keyboards[i].name != NULL; i++) {
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(layout_combo), 
            available_keyboards[i].name);
    }
    
    // Test area
    GtkWidget *test_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(test_entry), 
        "Type here to test keyboard layout...");
    
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Select Layout:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), layout_combo, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Test Layout:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), test_entry, 1, 1, 1, 1);
    
    gtk_container_add(GTK_CONTAINER(frame), grid);
    gtk_box_pack_start(GTK_BOX(box), frame, TRUE, TRUE, 0);
    
    GtkWidget *apply_btn = gtk_button_new_with_label("Apply Keyboard Layout");
    gtk_box_pack_start(GTK_BOX(box), apply_btn, FALSE, FALSE, 5);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "keyboard", "Keyboard");
    return box;
}
