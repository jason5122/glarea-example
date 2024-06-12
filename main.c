// https://stackoverflow.com/questions/46548553/c-setenv-implicit-declaration
#define _POSIX_C_SOURCE 200112L
#include <stdlib.h>

#include <epoxy/gl.h>
#include <gtk/gtk.h>
#include <stdio.h>

static gboolean realize(GtkGLArea* self, gpointer user_data) {
    gtk_gl_area_make_current(self);

    GLuint tex_id;
    glGenTextures(1, &tex_id);
    fprintf(stderr, "tex_id: %d\n", tex_id);
}

static gboolean render(GtkGLArea* self, GdkGLContext* context, gpointer user_data) {
    gtk_gl_area_make_current(self);

    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw commands are flushed after returning.
    return true;
}

static GtkWidget* create_window(GtkApplication* app) {
    GtkWidget* window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    GtkWidget* gtk_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), gtk_box);

    GtkWidget* gl_area = gtk_gl_area_new();
    gtk_widget_set_hexpand(gl_area, TRUE);
    gtk_widget_set_vexpand(gl_area, TRUE);
    gtk_box_append(GTK_BOX(gtk_box), gl_area);
    g_signal_connect(gl_area, "realize", G_CALLBACK(realize), NULL);
    g_signal_connect(gl_area, "render", G_CALLBACK(render), NULL);

    return window;
}

static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget* window1 = create_window(app);
    GtkWidget* window2 = create_window(app);

    gtk_window_present(GTK_WINDOW(window1));
    gtk_window_present(GTK_WINDOW(window2));
}

int main(int argc, char** argv) {
    // TODO: Remove this once OpenGL backend starts up faster.
    //       Also, consider allowing users to override `GSK_RENDERER` (change 1 to 0).
    setenv("GSK_RENDERER", "cairo", 1);

    GtkApplication* app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
