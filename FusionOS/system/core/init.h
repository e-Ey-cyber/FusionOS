#ifndef FUSION_INIT_H
#define FUSION_INIT_H

#include <stdio.h>
#include "types.h"
#include "security.h"
#include "setup.h"
#include "phone_ui.h"

// System initialization structure
typedef struct {
    uint32_t version;
    char* system_name;
    void (*init_hardware)(void);
    void (*init_security)(void);
} FusionOS_Init;

// Core initialization functions
void fusion_system_init(void);
void fusion_security_init(void);
void fusion_ui_init(void);

// Test functions
void run_system_tests(void);
int test_hardware_init(void);
int test_security_init(void);

// GUI initialization
void gui_init_window(void);
void setup_gui_init(int *argc, char ***argv);
void setup_show_gui(void);

// Global widgets
extern GtkWidget *main_stack;

// Add new functions
void fusion_network_init(void);
void fusion_phone_init(void);
SystemStatus* fusion_get_system_status(void);

#endif // FUSION_INIT_H
