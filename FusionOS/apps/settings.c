#include "apps.h"

static void on_theme_changed(GtkComboBox *widget, gpointer user_data) {
    (void)user_data;
    gint active = gtk_combo_box_get_active(widget);
    
    if (active == 0) {
        apply_theme("light");
    } else {
        apply_theme("dark");
    }
}

void app_settings_launch(void) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sistem Ayarları");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);
    
    GtkWidget *notebook = gtk_notebook_new();
    
    // Ağ Ayarları Sayfası
    GtkWidget *network_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *wifi_frame = gtk_frame_new("WiFi Ayarları");
    GtkWidget *wifi_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    GtkWidget *wifi_switch = gtk_switch_new();
    GtkWidget *wifi_label = gtk_label_new("WiFi");
    GtkWidget *wifi_list = gtk_list_box_new();
    
    gtk_box_pack_start(GTK_BOX(wifi_box), wifi_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(wifi_box), wifi_switch, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(wifi_box), wifi_list, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(wifi_frame), wifi_box);
    
    // Bluetooth Ayarları
    GtkWidget *bt_frame = gtk_frame_new("Bluetooth Ayarları");
    GtkWidget *bt_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *bt_switch = gtk_switch_new();
    GtkWidget *bt_label = gtk_label_new("Bluetooth");
    
    gtk_box_pack_start(GTK_BOX(bt_box), bt_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(bt_box), bt_switch, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(bt_frame), bt_box);
    
    // SIM Kart Ayarları
    GtkWidget *sim_frame = gtk_frame_new("SIM Kart Ayarları");
    GtkWidget *sim_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    GtkWidget *sim_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sim_combo), "SIM1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(sim_combo), "SIM2");
    
    GtkWidget *data_switch = gtk_switch_new();
    GtkWidget *data_label = gtk_label_new("Mobil Veri");
    
    gtk_box_pack_start(GTK_BOX(sim_box), gtk_label_new("Aktif SIM"), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(sim_box), sim_combo, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(sim_box), data_label, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(sim_box), data_switch, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(sim_frame), sim_box);
    
    // Görünüm Ayarları
    GtkWidget *appearance_frame = gtk_frame_new("Görünüm Ayarları");
    GtkWidget *appearance_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    GtkWidget *theme_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(theme_combo), "Açık Tema");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(theme_combo), "Koyu Tema");
    
    GtkWidget *font_button = gtk_font_button_new();
    GtkWidget *icon_combo = gtk_combo_box_text_new();
    
    gtk_box_pack_start(GTK_BOX(appearance_box), gtk_label_new("Tema"), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(appearance_box), theme_combo, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(appearance_box), gtk_label_new("Yazı Tipi"), FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(appearance_box), font_button, FALSE, FALSE, 5);
    gtk_container_add(GTK_CONTAINER(appearance_frame), appearance_box);
    
    // Tüm frame'leri sayfaya ekle
    gtk_box_pack_start(GTK_BOX(network_page), wifi_frame, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(network_page), bt_frame, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(network_page), sim_frame, FALSE, FALSE, 5);
    
    // Sayfaları notebook'a ekle
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), network_page, gtk_label_new("Ağ ve SIM"));
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), appearance_frame, gtk_label_new("Görünüm"));
    
    // Tema değişikliği sinyalini bağla
    g_signal_connect(theme_combo, "changed", G_CALLBACK(on_theme_changed), NULL);
    
    gtk_container_add(GTK_CONTAINER(window), notebook);
    gtk_widget_show_all(window);
}
