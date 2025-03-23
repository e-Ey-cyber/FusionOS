#ifndef FUSION_APPS_H
#define FUSION_APPS_H

#include <gtk/gtk.h>
#include "../system/core/init.h"

extern GtkWidget *main_stack;

// Uygulama fonksiyonları
void app_phone_launch(void);
void app_messages_launch(void);
void app_contacts_launch(void);
void app_calendar_launch(void);
void app_calculator_launch(void);
void app_notes_launch(void);
void app_gallery_launch(void);
void app_camera_launch(void);
void app_music_launch(void);
void app_files_launch(void);
void app_settings_launch(void);
void app_security_launch(void);

#endif
