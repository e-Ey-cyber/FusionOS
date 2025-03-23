#ifndef FUSION_SETUP_H
#define FUSION_SETUP_H

#include "init.h"
#include "gui.h"
#include <gtk/gtk.h>

typedef struct {
    char* target_device;
    uint32_t partition_size;
    char* system_path;
} SetupConfig;

int setup_initialize(SetupConfig* config);
int setup_create_partitions(void);
int setup_copy_system_files(void);
int setup_configure_bootloader(void);

// GUI setup functions
void setup_show_gui(void);
void setup_gui_init(int *argc, char ***argv);
void setup_gui_cleanup(void);

// GUI Pages
GtkWidget* create_welcome_page(void);
GtkWidget* create_partition_page(void);
GtkWidget* create_network_page(void);
GtkWidget* create_security_page(void);
GtkWidget* create_progress_page(void);

// GUI Helpers
void update_progress_bar(double fraction);
void show_error_message(const char* message);
void show_success_message(const char* message);

#endif // FUSION_SETUP_H
