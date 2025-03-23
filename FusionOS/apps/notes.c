#include "apps.h"

static GtkWidget *notes_window = NULL;

void app_notes_launch(void) {
    if (notes_window) {
        gtk_window_present(GTK_WINDOW(notes_window));
        return;
    }

    notes_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(notes_window), "Notlar");
    gtk_window_set_default_size(GTK_WINDOW(notes_window), 400, 500);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    GtkWidget *toolbar = gtk_toolbar_new();
    GtkToolItem *new_note = gtk_tool_button_new(NULL, "Yeni");
    GtkToolItem *save_note = gtk_tool_button_new(NULL, "Kaydet");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_note, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save_note, -1);

    GtkWidget *text_view = gtk_text_view_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), text_view);

    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(notes_window), box);
    gtk_widget_show_all(notes_window);
}
