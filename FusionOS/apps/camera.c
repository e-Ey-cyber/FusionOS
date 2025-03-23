#include "apps.h"

static GtkWidget *camera_view = NULL;
static GtkWidget *preview_area = NULL;

void app_camera_launch(void) {
    if (camera_view) {
        gtk_widget_show_all(camera_view);
        return;
    }

    camera_view = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(camera_view, "camera-view");

    // Kamera önizleme alanı
    preview_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(preview_area, 320, 480);

    // Kamera kontrolleri
    GtkWidget *controls = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_top(controls, 10);
    gtk_widget_set_margin_bottom(controls, 10);

    GtkWidget *switch_cam = gtk_button_new_from_icon_name("camera-switch", GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkWidget *capture = gtk_button_new_from_icon_name("camera-photo", GTK_ICON_SIZE_LARGE_TOOLBAR);
    GtkWidget *video = gtk_button_new_from_icon_name("camera-video", GTK_ICON_SIZE_LARGE_TOOLBAR);

    gtk_box_pack_start(GTK_BOX(controls), switch_cam, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(controls), capture, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(controls), video, TRUE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(camera_view), preview_area, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(camera_view), controls, FALSE, FALSE, 0);

    gtk_stack_add_titled(GTK_STACK(main_stack), camera_view, "camera", "Kamera");
    gtk_widget_show_all(camera_view);
}
