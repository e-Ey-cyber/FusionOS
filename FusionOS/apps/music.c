#include "apps.h"

static GtkWidget *music_view = NULL;
static GtkWidget *progress_bar = NULL;
static GtkWidget *play_button = NULL;

void app_music_launch(void) {
    if (music_view) {
        gtk_widget_show_all(music_view);
        return;
    }

    music_view = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(music_view, "music-view");

    // Şarkı listesi
    GtkWidget *playlist = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), playlist);

    // Çalma kontrolleri
    GtkWidget *controls = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_margin_top(controls, 10);
    gtk_widget_set_margin_bottom(controls, 10);

    progress_bar = gtk_progress_bar_new();
    
    GtkWidget *buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *prev = gtk_button_new_from_icon_name("media-skip-backward", GTK_ICON_SIZE_LARGE_TOOLBAR);
    play_button = gtk_button_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkWidget *next = gtk_button_new_from_icon_name("media-skip-forward", GTK_ICON_SIZE_LARGE_TOOLBAR);

    gtk_box_pack_start(GTK_BOX(buttons), prev, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(buttons), play_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(buttons), next, TRUE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(controls), progress_bar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(controls), buttons, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(music_view), scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(music_view), controls, FALSE, FALSE, 0);

    gtk_stack_add_titled(GTK_STACK(main_stack), music_view, "music", "Müzik");
    gtk_widget_show_all(music_view);
}
