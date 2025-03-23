#include "init.h"
#include "security.h"
#include "setup.h"
#include "app_manager.h"  // Add this include
#include <gtk/gtk.h>

FusionOS_Init fusion_os = {
    .version = 0x0100,
    .system_name = "FusionOS",
    .init_hardware = NULL,
    .init_security = NULL
};

// Define main_stack here
GtkWidget *main_stack = NULL;  // Global definition

void fusion_system_init(void) {
    // Initialize hardware components
    if (fusion_os.init_hardware) {
        fusion_os.init_hardware();
    }
    
    // Initialize security modules
    fusion_security_init();
    
    // Initialize user interface
    fusion_ui_init();
}

void fusion_security_init(void) {
    printf("Initializing enhanced security features...\n");
    security_init_all();
    security_set_system_level(SECURITY_LEVEL_MAXIMUM);
    
    if (fusion_os.init_security) {
        fusion_os.init_security();
    }
}

void fusion_ui_init(void) {
    // Initialize basic UI components
}

void run_system_tests(void) {
    printf("Running FusionOS tests...\n");
    
    int hw_test = test_hardware_init();
    int sec_test = test_security_init();
    
    printf("Hardware init test: %s\n", hw_test ? "PASS" : "FAIL");
    printf("Security init test: %s\n", sec_test ? "PASS" : "FAIL");
}

int test_hardware_init(void) {
    // Simulate hardware initialization
    return 1; // Return 1 for success
}

int test_security_init(void) {
    // Simulate security initialization
    return 1; // Return 1 for success
}

static SystemStatus system_status = {
    .battery_level = 100,
    .network_signal = 85,
    .current_network = "FusionOS_Network",
    .security_level = SECURITY_LEVEL_HIGH,
    .is_secure_boot = true,
    .is_debugging = false
};

SystemStatus* fusion_get_system_status(void) {
    return &system_status;
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    printf("Starting FusionOS...\n");

    // Ana pencereyi oluştur
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FusionOS");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 580);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    
    // Ana stack'i oluştur
    main_stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(main_stack), 
        GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(main_stack), 200);
    
    // Pencereye stack'i ekle
    gtk_container_add(GTK_CONTAINER(window), main_stack);
    
    // Pencere kapatma sinyalini bağla
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Sistemi başlat
    fusion_system_init();
    run_system_tests();
    
    // Kilit ekranını göster
    phone_ui_show_lock_screen();
    
    // Tüm widget'ları göster
    gtk_widget_show_all(window);
    gtk_main();
    
    return 0;
}
