#include "setup.h"
#include <stdio.h>
#include <gtk/gtk.h>

static SetupConfig* current_config = NULL;
static GtkWidget* progress_bar = NULL;

int setup_initialize(SetupConfig* config) {
    if (!config) return -1;
    current_config = config;
    printf("Initializing setup for device: %s\n", config->target_device);
    return 0;
}

int setup_create_partitions(void) {
    printf("Creating system partitions...\n");
    return 0;
}

int setup_copy_system_files(void) {
    printf("Copying system files...\n");
    return 0;
}

int setup_configure_bootloader(void) {
    printf("Configuring bootloader...\n");
    return 0;
}

static void on_install_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; // Suppress unused parameter warning
    
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Are you sure you want to install FusionOS?");

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_YES) {
        setup_create_partitions();
        setup_copy_system_files();
        setup_configure_bootloader();
    }
    
    gtk_widget_destroy(dialog);
}

void setup_show_gui(void) {
    GtkWidget *window;
    GtkWidget *notebook;
    GtkWidget *button_box;
    GtkWidget *install_button;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FusionOS Installer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    notebook = gtk_notebook_new();
    
    // Add pages
    GtkWidget *lang_page = gui_create_language_page();
    GtkWidget *kbd_page = gui_create_keyboard_page();
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), lang_page,
        gtk_label_new("Language"));
    
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), kbd_page,
        gtk_label_new("Keyboard"));

    // Create install button
    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    install_button = gtk_button_new_with_label("Install FusionOS");
    gtk_box_pack_end(GTK_BOX(button_box), install_button, FALSE, FALSE, 5);

    // Connect the install button click handler
    g_signal_connect(install_button, "clicked", G_CALLBACK(on_install_clicked), window);

    // Pack everything
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), notebook, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 5);
    
    gtk_container_add(GTK_CONTAINER(window), main_box);
    gtk_widget_show_all(window);
}

GtkWidget* create_welcome_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *label = gtk_label_new(NULL);
    GtkWidget *image = gtk_image_new_from_icon_name("computer", GTK_ICON_SIZE_DIALOG);
    
    const char *welcome_text = "<span size='x-large' weight='bold'>Welcome to FusionOS</span>\n\n"
                              "This wizard will guide you through the installation process.";
    
    gtk_label_set_markup(GTK_LABEL(label), welcome_text);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 10);
    
    return box;
}

GtkWidget* create_partition_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *combo = gtk_combo_box_text_new();
    
    // Add available devices
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "/dev/sda");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "/dev/sdb");
    
    gtk_box_pack_start(GTK_BOX(box), 
        gtk_label_new("Select installation target:"), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), combo, FALSE, FALSE, 5);
    
    return box;
}

GtkWidget* create_network_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *list = gtk_list_box_new();
    
    gtk_box_pack_start(GTK_BOX(box),
        gtk_label_new("Available Networks:"), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), list, TRUE, TRUE, 5);
    
    return box;
}

GtkWidget* create_security_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    GtkWidget *encryption = gtk_check_button_new_with_label("Enable Disk Encryption");
    GtkWidget *firewall = gtk_check_button_new_with_label("Enable Firewall");
    GtkWidget *updates = gtk_check_button_new_with_label("Enable Automatic Updates");
    
    gtk_box_pack_start(GTK_BOX(box), encryption, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), firewall, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), updates, FALSE, FALSE, 5);
    
    return box;
}

GtkWidget* create_progress_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    progress_bar = gtk_progress_bar_new();
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), "Installing...");
    gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(progress_bar), TRUE);
    
    gtk_box_pack_start(GTK_BOX(box), progress_bar, FALSE, FALSE, 5);
    
    return box;
}

void update_progress_bar(double fraction) {
    if (progress_bar) {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), fraction);
    }
}

void setup_gui_init(int *argc, char ***argv) {
    gtk_init(argc, argv);
}

void setup_gui_cleanup(void) {
    gtk_main_quit();
}
