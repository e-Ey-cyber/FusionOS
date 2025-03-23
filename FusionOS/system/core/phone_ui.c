#include "phone_ui.h"
#include <time.h>
#include <locale.h>
#include "app_manager.h" // Add this include

static GtkWidget *home_screen;
static GtkWidget *lock_screen;
static GtkWidget *status_bar;
static GtkWidget *clock_label;
static GtkWidget *pin_entry;
static const char* correct_pin = "1234"; // Gerçek uygulamada güvenli bir şekilde saklanmalı

// Define global variables
GtkWidget *status_bar_signal_icon;
GtkWidget *status_bar_battery_icon;
GtkWidget *status_bar_battery_label;

// Remove static global declaration since we're using extern
extern GtkWidget *main_stack;

// Fonksiyon prototipini en üste ekleyelim
GtkWidget* create_customizable_dock(void);
static void update_clock_label(GtkWidget *label);

static const DockItem default_dock_items[] = {
    {"phone", "phone_app", "Telefon"},
    {"chat", "messages_app", "Mesajlar"},
    {"contact-new", "contacts_app", "Kişiler"},
    {"web-browser", "browser_app", "Tarayıcı"}
};

void create_info_bar(void) {
    GtkWidget *info_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_name(info_bar, "info-bar");
    
    // Sol taraf - Sinyal ve operatör
    GtkWidget *left_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *signal_icon = gtk_image_new_from_icon_name("network-wireless", GTK_ICON_SIZE_MENU);
    GtkWidget *carrier_label = gtk_label_new("FusionOS");
    gtk_box_pack_start(GTK_BOX(left_box), signal_icon, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(left_box), carrier_label, FALSE, FALSE, 2);
    
    // Orta - Saat
    GtkWidget *time_label = gtk_label_new(NULL);
    update_clock_label(time_label);
    
    // Sağ taraf - Pil ve bildirimler
    GtkWidget *right_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    GtkWidget *battery_icon = gtk_image_new_from_icon_name("battery-full", GTK_ICON_SIZE_MENU);
    GtkWidget *battery_label = gtk_label_new("100%");
    gtk_box_pack_end(GTK_BOX(right_box), battery_label, FALSE, FALSE, 2);
    gtk_box_pack_end(GTK_BOX(right_box), battery_icon, FALSE, FALSE, 2);
    
    gtk_box_pack_start(GTK_BOX(info_bar), left_box, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(info_bar), time_label, TRUE, TRUE, 5);
    gtk_box_pack_end(GTK_BOX(info_bar), right_box, TRUE, TRUE, 5);
    
    gtk_box_pack_start(GTK_BOX(home_screen), info_bar, FALSE, FALSE, 0);
}

void create_bottom_dock(void) {
    GtkWidget *dock = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(dock, "bottom-dock");
    
    for (size_t i = 0; i < G_N_ELEMENTS(default_dock_items); i++) {
        GtkWidget *button = gtk_button_new();
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
        GtkWidget *icon = gtk_image_new_from_icon_name(
            default_dock_items[i].icon_name, GTK_ICON_SIZE_LARGE_TOOLBAR);
        GtkWidget *label = gtk_label_new(default_dock_items[i].label);
        
        gtk_box_pack_start(GTK_BOX(box), icon, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
        gtk_container_add(GTK_CONTAINER(button), box);
        
        gtk_widget_set_name(button, "dock-button");
        g_signal_connect_swapped(button, "clicked", 
            G_CALLBACK(app_manager_launch), (gpointer)default_dock_items[i].app_id);
        
        gtk_box_pack_start(GTK_BOX(dock), button, TRUE, TRUE, 0);
    }
    
    gtk_box_pack_end(GTK_BOX(home_screen), dock, FALSE, FALSE, 0);
}

static void update_clock(void) {
    time_t now = time(NULL);
    char hour_str[3];
    char min_str[3];
    
    strftime(hour_str, sizeof(hour_str), "%H", localtime(&now));
    strftime(min_str, sizeof(min_str), "%M", localtime(&now));
    
    char *markup = g_markup_printf_escaped(
        "<span font='64' weight='bold'>%s:%s</span>",
        hour_str, min_str
    );
    gtk_label_set_markup(GTK_LABEL(clock_label), markup);
    g_free(markup);
}

static gboolean update_status_bar(gpointer data) {
    (void)data; // Suppress unused parameter warning
    SystemStatus* status = fusion_get_system_status();
    
    // Pil durumu güncelleme
    char battery_icon[32];
    if (status->battery_level > 80)
        g_strlcpy(battery_icon, "battery-full", sizeof(battery_icon));
    else if (status->battery_level > 50)
        snprintf(battery_icon, sizeof(battery_icon), "battery-good");
    else if (status->battery_level > 20)
        snprintf(battery_icon, sizeof(battery_icon), "battery-low");
    else
        snprintf(battery_icon, sizeof(battery_icon), "battery-empty");

    char battery_text[32];
    snprintf(battery_text, sizeof(battery_text), "%d%%", status->battery_level);
    
    gtk_image_set_from_icon_name(GTK_IMAGE(status_bar_battery_icon), battery_icon, GTK_ICON_SIZE_MENU);
    gtk_label_set_text(GTK_LABEL(status_bar_battery_label), battery_text);
    
    // Sinyal durumu güncelleme
    char signal_icon[64]; // Increased buffer size
    if (status->network_signal > 80)
        g_strlcpy(signal_icon, "network-wireless-signal-excellent", sizeof(signal_icon));
    else if (status->network_signal > 50)
        snprintf(signal_icon, sizeof(signal_icon), "network-wireless-signal-good");
    else if (status->network_signal > 20)
        snprintf(signal_icon, sizeof(signal_icon), "network-wireless-signal-weak");
    else
        snprintf(signal_icon, sizeof(signal_icon), "network-wireless-signal-none");
    
    gtk_image_set_from_icon_name(GTK_IMAGE(status_bar_signal_icon), signal_icon, GTK_ICON_SIZE_MENU);
    
    // Her 30 saniyede bir güncelle
    return G_SOURCE_CONTINUE;
}

static void on_unlock_clicked(GtkButton *button, gpointer data) {
    (void)button;
    (void)data;
    
    const char* entered_pin = gtk_entry_get_text(GTK_ENTRY(pin_entry));
    if (g_strcmp0(entered_pin, correct_pin) == 0) {
        // Kilit ekranını gizle
        gtk_widget_hide(lock_screen);
        
        // Ana ekranı göster (eğer yoksa oluştur)
        if (!home_screen) {
            home_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
            gtk_widget_set_name(home_screen, "home-screen");
            
            // Status bar oluştur
            status_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            gtk_widget_set_name(status_bar, "status-bar");
            gtk_box_pack_start(GTK_BOX(home_screen), status_bar, FALSE, FALSE, 0);
            
            // Uygulama ızgarasını ekle
            GtkWidget *app_scroll = create_scrollable_app_grid();
            gtk_box_pack_start(GTK_BOX(home_screen), app_scroll, TRUE, TRUE, 0);
            
            // Ana ekranı stack'e ekle
            gtk_stack_add_titled(GTK_STACK(main_stack), home_screen, "home", "Ana Ekran");
        }

        // Stack'i ana ekrana geçir ve göster
        gtk_stack_set_visible_child_name(GTK_STACK(main_stack), "home");
        gtk_widget_show_all(home_screen);
        
        // PIN giriş alanını temizle
        gtk_entry_set_text(GTK_ENTRY(pin_entry), "");
        
        // Durum çubuğunu güncelle
        update_status_bar(NULL);
    } else {
        // Show error dialog
        GtkWidget *dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(pin_entry)),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Yanlış PIN kodu!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_entry_set_text(GTK_ENTRY(pin_entry), "");
    }
}

void phone_ui_show_lock_screen(void) {
    // Check if main_stack is initialized
    if (!main_stack) {
        g_error("main_stack is not initialized!");
        return;
    }
    
    lock_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_name(lock_screen, "lock-screen");
    
    // Arkaplan resmi ayarla
    GtkStyleContext *style_context = gtk_widget_get_style_context(lock_screen);
    gtk_style_context_add_class(style_context, "lock-screen-background");
    
    // Saat ve tarih bölümü için container
    GtkWidget *clock_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_name(clock_box, "clock-box");
    
    // Saat etiketi - büyük boyut
    clock_label = gtk_label_new(NULL);
    gtk_widget_set_name(clock_label, "clock-label");
    gtk_label_set_markup(GTK_LABEL(clock_label), 
        "<span font='64' weight='bold'>00:00</span>");
    update_clock();
    
    // Tarih etiketi
    time_t now = time(NULL);
    char date_str[128];
    setlocale(LC_TIME, "tr_TR.UTF-8"); // Türkçe tarih formatı için
    strftime(date_str, sizeof(date_str), "%A, %d %B %Y", localtime(&now));
    GtkWidget *date_label = gtk_label_new(date_str);
    gtk_widget_set_name(date_label, "date-label");
    
    // Saat ve tarih bileşenlerini yerleştir
    gtk_box_pack_start(GTK_BOX(clock_box), clock_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(clock_box), date_label, FALSE, FALSE, 5);
    
    // PIN girişi ve diğer bileşenler
    GtkWidget *login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(login_box, "login-box");
    
    pin_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(pin_entry), FALSE);
    gtk_entry_set_max_length(GTK_ENTRY(pin_entry), 4);
    gtk_widget_set_size_request(pin_entry, 250, 50);
    gtk_entry_set_placeholder_text(GTK_ENTRY(pin_entry), "PIN: 1234");
    
    // Giriş yap butonu
    GtkWidget *login_button = gtk_button_new_with_label("Giriş Yap");
    gtk_widget_set_name(login_button, "login-button");
    gtk_widget_set_size_request(login_button, 250, 50);
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_unlock_clicked), NULL);
    
    gtk_box_pack_start(GTK_BOX(login_box), pin_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(login_box), login_button, FALSE, FALSE, 5);

    // Acil arama butonu yerine metin etiketi
    GtkWidget *emergency_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(emergency_box, "emergency-box");
    
    GtkWidget *emergency_label = gtk_label_new("Acil Aramalar");
    gtk_widget_set_name(emergency_label, "emergency-label");
    gtk_box_pack_start(GTK_BOX(emergency_box), emergency_label, FALSE, FALSE, 0);
    
    // Durum çubuğu
    status_bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(status_bar, "status-bar");
    
    // Sol taraf için konteyner (WiFi)
    GtkWidget *left_items = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_widget_set_name(left_items, "left-items");
    
    status_bar_signal_icon = gtk_image_new();
    gtk_box_pack_start(GTK_BOX(left_items), status_bar_signal_icon, FALSE, FALSE, 0);
    
    // Sağ taraf için konteyner (Pil)
    GtkWidget *right_items = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    gtk_widget_set_name(right_items, "right-items");
    
    GtkWidget *battery_info = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4);
    gtk_widget_set_name(battery_info, "battery-info");
    
    status_bar_battery_icon = gtk_image_new();
    status_bar_battery_label = gtk_label_new("");
    
    gtk_box_pack_start(GTK_BOX(battery_info), status_bar_battery_icon, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(battery_info), status_bar_battery_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right_items), battery_info, FALSE, FALSE, 0);
    
    // Status bar'a yerleştir
    gtk_box_pack_start(GTK_BOX(status_bar), left_items, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(status_bar), right_items, TRUE, TRUE, 0);
    
    // Status bar'ı ekle
    gtk_box_pack_start(GTK_BOX(lock_screen), status_bar, FALSE, FALSE, 0);
    
    // Ana container'a bileşenleri yerleştir
    gtk_box_pack_start(GTK_BOX(lock_screen), clock_box, FALSE, FALSE, 20);
    gtk_box_pack_start(GTK_BOX(lock_screen), login_box, FALSE, FALSE, 20);
    gtk_box_pack_end(GTK_BOX(lock_screen), emergency_box, FALSE, FALSE, 20);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), lock_screen, "lock", "Lock Screen");
    gtk_widget_show_all(lock_screen);
    
    // Otomatik saat güncellemesi için timer
    g_timeout_add(60000, (GSourceFunc)update_clock, NULL);
    
    // Durum çubuğu güncellemesi için timer
    g_timeout_add_seconds(30, update_status_bar, NULL);
}

void phone_ui_show_home_screen(void) {
    if (!home_screen) {
        home_screen = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        gtk_widget_set_name(home_screen, "home-screen");
        
        // Bilgi çubuğunu ekle
        create_info_bar();
        
        // Uygulama ızgarası
        GtkWidget *app_scroll = create_scrollable_app_grid();
        gtk_box_pack_start(GTK_BOX(home_screen), app_scroll, TRUE, TRUE, 0);
        
        // Alt dock'u ekle
        create_bottom_dock();
        
        gtk_stack_add_titled(GTK_STACK(main_stack), home_screen, "home", "Ana Ekran");
    }
    
    // Ana ekranın görünürlüğünü garantile
    if (!gtk_widget_get_visible(home_screen)) {
        gtk_widget_show_all(home_screen);
    }
    
    update_status_bar(NULL); // Durum çubuğunu hemen güncelle
}

void apply_theme(const char* theme_name) {
    GtkSettings *settings = gtk_settings_get_default();
    
    if (g_strcmp0(theme_name, "dark") == 0) {
        g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
        g_object_set(settings, "gtk-theme-name", "Adwaita-dark", NULL);
    } else {
        g_object_set(settings, "gtk-application-prefer-dark-theme", FALSE, NULL);
        g_object_set(settings, "gtk-theme-name", "Adwaita", NULL);
    }
}

void update_datetime_labels(GtkWidget *time_label, GtkWidget *date_label) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    char time_str[32];
    char date_str[32];
    
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
    strftime(date_str, sizeof(date_str), "%d.%m.%Y", tm_info);
    
    gtk_label_set_text(GTK_LABEL(time_label), time_str);
    gtk_label_set_text(GTK_LABEL(date_label), date_str);
}

GtkWidget* create_customizable_dock(void) {
    GtkWidget *dock = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(dock, "dock");
    
    // Load dock apps from settings
    const char *dock_apps[][2] = {
        {"phone", "Telefon"},
        {"chat", "Mesajlar"},
        {"contact-new", "Kişiler"},
        {"web-browser", "Tarayıcı"}
    };
    
    for (int i = 0; i < 4; i++) {
        GtkWidget *button = gtk_button_new();
        GtkWidget *icon = gtk_image_new_from_icon_name(dock_apps[i][0], 
            GTK_ICON_SIZE_LARGE_TOOLBAR);
        gtk_button_set_image(GTK_BUTTON(button), icon);
        gtk_widget_set_tooltip_text(button, dock_apps[i][1]);
        gtk_widget_set_name(button, "dock-button");
        
        // Make dock buttons draggable
        gtk_drag_source_set(button, GDK_BUTTON1_MASK,
            NULL, 0, GDK_ACTION_MOVE);
        gtk_drag_dest_set(button, GTK_DEST_DEFAULT_ALL,
            NULL, 0, GDK_ACTION_MOVE);
            
        gtk_box_pack_start(GTK_BOX(dock), button, TRUE, TRUE, 0);
    }
    
    return dock;
}

static void update_clock_label(GtkWidget *label) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char time_str[32];
    strftime(time_str, sizeof(time_str), "%H:%M", tm_info);
    gtk_label_set_text(GTK_LABEL(label), time_str);
}

static gboolean periodic_clock_update(gpointer user_data) {
    GtkWidget *label = GTK_WIDGET(user_data);
    update_clock_label(label);
    return G_SOURCE_CONTINUE;
}
