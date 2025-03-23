#include "apps.h"

static GtkWidget *calc_window = NULL;
static GtkWidget *display = NULL;
static char current_number[32] = "";

static void on_number_clicked(GtkButton *button, gpointer data) {
    (void)data; // Suppress unused parameter warning
    const char* number = gtk_button_get_label(button);
    strcat(current_number, number);
    gtk_entry_set_text(GTK_ENTRY(display), current_number);
}

static void on_clear_clicked(void) {
    current_number[0] = '\0';
    gtk_entry_set_text(GTK_ENTRY(display), "0");
}

static void setup_calculator_buttons(GtkWidget *grid) {
    const char* button_labels[] = {
        "7", "8", "9", "/",
        "4", "5", "6", "*",
        "1", "2", "3", "-",
        "C", "0", "=", "+"
    };

    for (int i = 0; i < 16; i++) {
        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        gtk_widget_set_size_request(button, 50, 50);
        if (g_strcmp0(button_labels[i], "C") == 0) {
            g_signal_connect_swapped(button, "clicked", G_CALLBACK(on_clear_clicked), NULL);
        } else {
            g_signal_connect(button, "clicked", G_CALLBACK(on_number_clicked), NULL);
        }
        gtk_grid_attach(GTK_GRID(grid), button, i % 4, (i / 4) + 1, 1, 1);
    }
}

void app_calculator_launch(void) {
    if (calc_window) {
        gtk_window_present(GTK_WINDOW(calc_window));
        return;
    }

    calc_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(calc_window), "Hesap Makinesi");
    gtk_container_set_border_width(GTK_CONTAINER(calc_window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

    display = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(display), 1);
    gtk_entry_set_text(GTK_ENTRY(display), "0");
    gtk_widget_set_can_focus(display, FALSE);
    gtk_grid_attach(GTK_GRID(grid), display, 0, 0, 4, 1);

    setup_calculator_buttons(grid);

    gtk_container_add(GTK_CONTAINER(calc_window), grid);
    gtk_widget_show_all(calc_window);
}
