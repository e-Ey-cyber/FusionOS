#include "app_manager.h"
#include "../../apps/apps.h"
#include "init.h"  // Fix include path
#include <stdlib.h>

#define MAX_APPS 50

static AppInfo apps[] = {
    {"Telefon", "phone", "phone_app", "İletişim", app_phone_launch, NULL},
    {"Mesajlar", "chat", "messages_app", "İletişim", app_messages_launch, NULL},
    {"Kişiler", "contact-new", "contacts_app", "İletişim", app_contacts_launch, NULL},
    {"Takvim", "calendar", "calendar_app", "Araçlar", app_calendar_launch, NULL},
    {"Hesap Makinesi", "accessories-calculator", "calc_app", "Araçlar", app_calculator_launch, NULL},
    {"Notlar", "text-editor", "notes_app", "Araçlar", app_notes_launch, NULL},
    {"Galeri", "image-viewer", "gallery_app", "Medya", app_gallery_launch, NULL},
    {"Kamera", "camera-photo", "camera_app", "Medya", app_camera_launch, NULL},
    {"Müzik", "audio-player", "music_app", "Medya", app_music_launch, NULL},
    {"Dosyalar", "system-file-manager", "files_app", "Sistem", app_files_launch, NULL},
    {"Ayarlar", "preferences-system", "settings_app", "Sistem", app_settings_launch, NULL},
    {"Güvenlik", "security-high", "security_app", "Sistem", app_security_launch, NULL}
};

void app_manager_init(void) {
    if (!main_stack) {
        g_error("main_stack is not initialized");
        return;
    }
    // Initialize each app's UI components
    for (int i = 0; apps[i].name != NULL; i++) {
        if (apps[i].launch) {
            // Pre-initialize UI components if needed
        }
    }
}

static void on_app_window_destroy(GtkWidget *window, gpointer data) {
    (void)window; // Suppress unused parameter warning
    const char* app_id = (const char*)data;
    
    for (size_t i = 0; i < sizeof(apps)/sizeof(apps[0]); i++) {
        if (!apps[i].name) break;
        if (g_strcmp0(apps[i].exec, app_id) == 0) {
            apps[i].window = NULL;
            break;
        }
    }
}

void app_manager_launch(const char* app_id) {
    if (!app_id) {
        g_warning("app_id is NULL");
        return;
    }
    
    for (size_t i = 0; i < sizeof(apps)/sizeof(apps[0]); i++) {
        if (!apps[i].name) break;
        
        if (g_strcmp0(apps[i].exec, app_id) == 0) {
            if (apps[i].window) {
                gtk_window_present(GTK_WINDOW(apps[i].window));
                return;
            }
            
            if (apps[i].launch) {
                g_print("Launching app: %s\n", apps[i].name);
                apps[i].launch();
                // Add window destroy handler
                g_signal_connect(G_OBJECT(apps[i].window), "destroy",
                    G_CALLBACK(on_app_window_destroy), (gpointer)apps[i].exec);
            }
            return;
        }
    }
    g_warning("Uygulama bulunamadı: %s", app_id);
}

static void on_app_activated(GtkButton *button, gpointer data) {
    (void)button; // Suppress unused parameter warning
    const char* app_id = (const char*)data;
    app_manager_launch(app_id);
}

GtkWidget* create_scrollable_app_grid(void) {
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    GtkWidget *viewport = gtk_viewport_new(NULL, NULL);
    GtkWidget *grid = gtk_grid_new();
    
    gtk_grid_set_row_spacing(GTK_GRID(grid), 15);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
    gtk_container_set_border_width(GTK_CONTAINER(grid), 20);
    
    int row = 0, col = 0;
    for (int i = 0; apps[i].name != NULL; i++) {
        GtkWidget *app_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_widget_set_name(app_box, "app-box");
        
        GtkWidget *icon = gtk_image_new_from_icon_name(apps[i].icon, GTK_ICON_SIZE_DIALOG);
        gtk_image_set_pixel_size(GTK_IMAGE(icon), 64);
        
        GtkWidget *label = gtk_label_new(apps[i].name);
        gtk_widget_set_name(label, "app-label");
        
        gtk_box_pack_start(GTK_BOX(app_box), icon, FALSE, FALSE, 2);
        gtk_box_pack_start(GTK_BOX(app_box), label, FALSE, FALSE, 2);
        
        GtkWidget *button = gtk_button_new();
        gtk_container_add(GTK_CONTAINER(button), app_box);
        gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);
        gtk_widget_set_name(button, "app-button");
        
        g_signal_connect(button, "clicked", G_CALLBACK(on_app_activated), 
                        (gpointer)apps[i].exec);
        
        gtk_grid_attach(GTK_GRID(grid), button, col, row, 1, 1);
        
        col++;
        if (col >= 3) {
            col = 0;
            row++;
        }
    }
    
    gtk_container_add(GTK_CONTAINER(viewport), grid);
    gtk_container_add(GTK_CONTAINER(scroll), viewport);
    
    // Kaydırma çubuğu ayarları
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                 GTK_POLICY_NEVER,
                                 GTK_POLICY_AUTOMATIC);
    
    return scroll;
}

void app_manager_cleanup(void) {
    for (size_t i = 0; i < sizeof(apps)/sizeof(apps[0]); i++) {
        if (!apps[i].name) break;
        if (apps[i].window) {
            gtk_widget_destroy(apps[i].window);
            apps[i].window = NULL;
        }
    }
}
