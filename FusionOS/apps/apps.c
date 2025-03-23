#include "apps.h"

// Temel uygulama başlatıcılar
void app_phone_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Telefon");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 500);
    gtk_widget_show_all(window);
}

void app_messages_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mesajlar");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 500);
    gtk_widget_show_all(window);
}

void app_contacts_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kişiler");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 500);
    gtk_widget_show_all(window);
}

void app_calendar_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Takvim");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 500);
    gtk_widget_show_all(window);
}

void app_gallery_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Galeri");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_widget_show_all(window);
}

void app_camera_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Kamera");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_widget_show_all(window);
}

void app_music_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Müzik");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_widget_show_all(window);
}

void app_files_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Dosyalar");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);
    gtk_widget_show_all(window);
}

void app_settings_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ayarlar");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
    gtk_widget_show_all(window);
}

void app_security_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Güvenlik");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
    gtk_widget_show_all(window);
}
