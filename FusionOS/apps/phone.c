#include "apps.h"
#include "../system/core/phone.h"

static GtkWidget *phone_stack = NULL;
static GtkWidget *dialer_view = NULL;
static GtkWidget *calls_view = NULL;
static GtkWidget *number_display = NULL;

void app_phone_launch(void) {
    if (phone_stack) {
        gtk_widget_show_all(phone_stack);
        return;
    }

    phone_stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(phone_stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    // Tuş takımı görünümü
    dialer_view = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    number_display = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(number_display), 1);
    gtk_widget_set_size_request(number_display, -1, 50);

    GtkWidget *keypad = gtk_grid_new();
    const char *buttons[] = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "*", "0", "#"
    };

    for (int i = 0; i < 12; i++) {
        GtkWidget *button = gtk_button_new_with_label(buttons[i]);
        gtk_widget_set_size_request(button, 80, 80);
        g_signal_connect(button, "clicked", G_CALLBACK(on_digit_clicked), NULL);
        gtk_grid_attach(GTK_GRID(keypad), button, i % 3, i / 3, 1, 1);
    }

    GtkWidget *call_button = gtk_button_new_with_label("🟢 Ara");
    gtk_widget_set_name(call_button, "call-button");

    gtk_box_pack_start(GTK_BOX(dialer_view), number_display, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(dialer_view), keypad, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(dialer_view), call_button, FALSE, FALSE, 5);

    // Arama geçmişi görünümü
    calls_view = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *calls_list = gtk_list_box_new();
    gtk_box_pack_start(GTK_BOX(calls_view), calls_list, TRUE, TRUE, 0);

    // Stack'e görünümleri ekle
    gtk_stack_add_titled(GTK_STACK(phone_stack), dialer_view, "dialer", "Tuş Takımı");
    gtk_stack_add_titled(GTK_STACK(phone_stack), calls_view, "calls", "Arama Geçmişi");

    // Stack switcher
    GtkWidget *stack_switcher = gtk_stack_switcher_new();
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(phone_stack));

    // Ana konteyner
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_box), stack_switcher, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_box), phone_stack, TRUE, TRUE, 0);

    // Stack'i ana stack'e ekle
    gtk_stack_add_titled(GTK_STACK(main_stack), main_box, "phone", "Telefon");
    gtk_widget_show_all(main_box);
}
