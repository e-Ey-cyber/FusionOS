#ifndef FUSION_GUI_H
#define FUSION_GUI_H

#include <gtk/gtk.h>
#include "types.h"
#include "init.h"  // For SystemStatus definition

// Global variables
extern GtkWidget *main_stack;

// Main window components
void gui_init_window(void);
void gui_create_toolbar(void);
void gui_create_sidebar(void);
void gui_create_main_area(void);

// Dashboard widgets
GtkWidget* gui_create_system_monitor(void);  // Changed return type
GtkWidget* gui_create_security_panel(void);  // Changed return type
GtkWidget* gui_create_network_panel(void);   // Changed return type
void gui_update_status(const char* message);

// Additional widgets
void gui_create_system_stats(void);
void gui_update_system_stats(void);

// New dashboard widgets
void gui_create_performance_monitor(void);
void gui_create_app_manager(void);
void gui_create_update_center(void);
void gui_create_settings_panel(void);

// System monitoring
void gui_update_performance_stats(void);
void gui_update_battery_status(void);
void gui_update_network_speed(void);

// Theme management
void gui_set_dark_mode(gboolean enabled);
void gui_apply_theme(const char* theme_name);

// Event handlers
void on_network_scan_clicked(GtkButton *button, gpointer user_data);
void on_network_connect_clicked(GtkButton *button, gpointer user_data);
void on_security_level_changed(GtkComboBox *widget, gpointer user_data);

// Terminal emulator
void gui_create_terminal(void);
void gui_terminal_execute(const char* command);

// File manager
void gui_create_file_manager(void);
void gui_file_manager_refresh(void);

// System backup
void gui_create_backup_panel(void);
void gui_backup_create(const char* location);
void gui_backup_restore(const char* backup_file);

// Update center
void gui_check_for_updates(void);
void gui_install_updates(void);

// Process manager
void gui_create_process_manager(void);
void gui_process_list_refresh(void);
void gui_process_kill(int pid);

// Language and keyboard settings
typedef struct {
    const char* name;
    const char* code;
    const char* locale;
} LanguageInfo;

typedef struct {
    const char* name;
    const char* layout;
    const char* variant;
} KeyboardInfo;

// Language and keyboard pages
GtkWidget* gui_create_language_page(void);  // Changed return type
GtkWidget* gui_create_keyboard_page(void);  // Changed return type

void gui_apply_language(const char* locale);
void gui_apply_keyboard(const char* layout);
void gui_load_language_list(void);
void gui_load_keyboard_list(void);

// Phone interface
void gui_create_phone_interface(void);
void gui_update_call_status(const char* status);
void gui_show_incoming_call(const char* number);
void gui_show_message_notification(const char* sender, const char* message);

// System tray
void gui_create_system_tray(void);
void gui_update_system_tray(SystemStatus* status);

// Quick settings
void gui_create_quick_settings(void);
void gui_toggle_wifi(void);
void gui_toggle_bluetooth(void);
void gui_toggle_airplane_mode(void);

// Notifications
void gui_show_notification(const char* title, const char* message);

#endif
