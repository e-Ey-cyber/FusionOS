#ifndef FUSION_APP_MANAGER_H
#define FUSION_APP_MANAGER_H

#include <gtk/gtk.h>

typedef struct {
    const char* name;
    const char* icon;
    const char* exec;
    const char* category;
    void (*launch)(void);  // Moved before window
    GtkWidget* window;     // Moved to end
} AppInfo;

void app_manager_init(void);
void app_manager_launch(const char* app_id);
GtkWidget* create_scrollable_app_grid(void);
void app_manager_cleanup(void);  // Add cleanup function

extern GtkWidget *main_stack;  // Add main_stack declaration

#endif
