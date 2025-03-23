#ifndef FUSION_PHONE_H
#define FUSION_PHONE_H

#include <gtk/gtk.h>
#include <stdbool.h>
#include "types.h"
#include "init.h"  // For SystemStatus definition

extern GtkWidget *main_stack;  // Add this line

typedef struct {
    char* number;
    char* name;
    char* timestamp;
    int duration;
    int type; // 1: gelen, 2: giden, 3: cevapsız
} CallRecord;

// Phone status
typedef struct {
    bool in_call;
    bool is_ringing;
    char* current_number;
    int call_duration;
    int missed_calls;
    int unread_messages;
} PhoneStatus;

// Phone functions
void phone_init(void);
int phone_dial(const char* number);
int phone_answer(void);
int phone_end_call(void);
int phone_send_sms(const char* number, const char* message);

// Add new functions
PhoneStatus* phone_get_status(void);
void phone_set_ringtone(const char* path);
void phone_set_vibration(bool enabled);
void phone_emergency_call(void);

// Contact management
void contact_add(const char* name, const char* number);
void contact_delete(const char* number);
void contact_edit(const char* old_number, const char* new_number, const char* new_name);

// GUI components
void gui_create_phone_dialer(void);
void gui_create_contacts_page(void);
void gui_create_call_history(void);
void gui_create_messages_page(void);

// Signal handlers
void on_digit_clicked(GtkButton *button, gpointer data);  // Add this line

#endif
