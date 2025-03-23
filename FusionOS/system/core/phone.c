#include "phone.h"
#include <stdio.h>

static GtkWidget *dialer_entry;
static GtkWidget *call_button;
static GtkWidget *end_button;

void gui_create_phone_dialer(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *grid = gtk_grid_new();
    
    // Numara gösterge alanı
    dialer_entry = gtk_entry_new();
    gtk_entry_set_alignment(GTK_ENTRY(dialer_entry), 1);
    gtk_widget_set_size_request(dialer_entry, 300, 50);
    
    // Numara tuşları
    const char* buttons[] = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "*", "0", "#"
    };
    
    for (int i = 0; i < 12; i++) {
        GtkWidget *button = gtk_button_new_with_label(buttons[i]);
        gtk_widget_set_size_request(button, 80, 80);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);
        
        g_signal_connect(button, "clicked", G_CALLBACK(on_digit_clicked), (gpointer)buttons[i]);
    }
    
    // Arama ve sonlandırma düğmeleri
    call_button = gtk_button_new_with_label("📞 Ara");
    gtk_widget_set_size_request(call_button, 100, 50);
    end_button = gtk_button_new_with_label("🔴 Bitir");
    gtk_widget_set_size_request(end_button, 100, 50);
    
    // Widget'ları yerleştir
    gtk_box_pack_start(GTK_BOX(box), dialer_entry, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(box), call_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), end_button, FALSE, FALSE, 5);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "phone", "Telefon");
}

void on_digit_clicked(GtkButton *button, gpointer data) {
    (void)button; // Suppress unused parameter warning
    const char* digit = (const char*)data;
    const char* current = gtk_entry_get_text(GTK_ENTRY(dialer_entry));
    char* new_text = g_strdup_printf("%s%s", current, digit);
    gtk_entry_set_text(GTK_ENTRY(dialer_entry), new_text);
    g_free(new_text);
}

void gui_create_contacts_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *toolbar = gtk_toolbar_new();
    GtkWidget *contact_list = gtk_list_box_new();
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    
    // Araç çubuğu düğmeleri
    GtkToolItem *add_contact = gtk_tool_button_new(NULL, "Yeni Kişi");
    GtkToolItem *import_contacts = gtk_tool_button_new(NULL, "İçe Aktar");
    
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), add_contact, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), import_contacts, -1);
    
    gtk_container_add(GTK_CONTAINER(scroll), contact_list);
    
    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "contacts", "Kişiler");
}

void gui_create_messages_page(void) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    
    // Mesaj listesi
    GtkWidget *message_list = gtk_list_box_new();
    GtkWidget *list_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(list_scroll), message_list);
    
    // Mesaj içeriği
    GtkWidget *message_view = gtk_text_view_new();
    GtkWidget *view_scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(view_scroll), message_view);
    
    gtk_paned_add1(GTK_PANED(paned), list_scroll);
    gtk_paned_add2(GTK_PANED(paned), view_scroll);
    
    gtk_box_pack_start(GTK_BOX(box), paned, TRUE, TRUE, 0);
    
    // Yeni mesaj girişi
    GtkWidget *entry_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *message_entry = gtk_entry_new();
    GtkWidget *send_button = gtk_button_new_with_label("Gönder");
    
    gtk_box_pack_start(GTK_BOX(entry_box), message_entry, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(entry_box), send_button, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_box, FALSE, FALSE, 5);
    
    gtk_stack_add_titled(GTK_STACK(main_stack), box, "messages", "Mesajlar");
}
