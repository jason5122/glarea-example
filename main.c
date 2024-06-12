#include <epoxy/gl.h>
#include <gtk/gtk.h>
#include <stdio.h>

static gboolean realize(GtkGLArea* self, gpointer user_data) {
    gtk_gl_area_make_current(self);

    GLuint tex_id;
    glGenTextures(1, &tex_id);
    fprintf(stderr, "tex_id: %d\n", tex_id);
}

static GtkWidget* create_window(GtkApplication* app) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    GtkWidget* gl_area = gtk_gl_area_new();
    gtk_container_add(GTK_CONTAINER(window), gl_area);
    g_signal_connect(gl_area, "realize", G_CALLBACK(realize), NULL);
    return window;
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window1 = create_window(app);
    GtkWidget* window2 = create_window(app);

    gtk_widget_show_all(window1);
    gtk_widget_show_all(window2);
}

int main(int argc, char** argv) {
    GtkApplication* app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
