#include <gtk/gtk.h>

int
main(int argc, char **argv)
{
  GtkWidget *win;
  gtk_init(&argc, &argv);

  /* make a window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  gtk_main();
  return 0;
}
