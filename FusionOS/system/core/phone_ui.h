#ifndef FUSION_PHONE_UI_H
#define FUSION_PHONE_UI_H

#include <gtk/gtk.h>
#include "types.h"
#include "phone.h"

// Add extern declaration
extern GtkWidget *main_stack;

// Lock screen
void phone_ui_show_lock_screen(void);
void phone_ui_unlock(const char* pin);

// Home screen
void phone_ui_show_home_screen(void);
void phone_ui_create_app_grid(void);
void phone_ui_create_status_bar(void);
void phone_ui_create_dock(void);

extern GtkWidget *status_bar_signal_icon;
extern GtkWidget *status_bar_battery_icon;
extern GtkWidget *status_bar_battery_label;

// Quick settings
void phone_ui_show_quick_settings(void);
void phone_ui_update_quick_settings(SystemStatus* status);

// Notifications
void phone_ui_show_notifications(void);
void phone_ui_add_notification(const char* title, const char* message);

// Remove static keyword from function declarations
void update_datetime_labels(GtkWidget *time_label, GtkWidget *date_label);
GtkWidget* create_customizable_dock(void);
void apply_theme(const char* theme_name);

// Add these declarations
static void update_clock_label(GtkWidget *label);
static gboolean periodic_clock_update(gpointer user_data);

// Dock ve bilgi çubuğu fonksiyonları
void create_info_bar(void);
void create_bottom_dock(void);
void update_info_bar(void);
void update_dock_indicators(void);

// Dock yapılandırma
typedef struct {
    const char* icon_name;
    const char* app_id;
    const char* label;
} DockItem;

#endif
