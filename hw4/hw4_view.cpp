#include <iostream>
#include "hw4_model.h"

using namespace std;

extern "C"{
   #include <gtk/gtk.h>
}


extern gameDef* g_def;
extern gameState* g_state;
extern const char* color_state1[7]; 
extern const char* color_state0[7];


GtkWidget *grid;
GtkWidget *window;
GtkWidget *moves_label;


void activate (GtkApplication *app, gpointer user_data) {
   window = gtk_application_window_new (app);
   gtk_window_set_title (GTK_WINDOW (window), "Window");
   gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);

   grid = gtk_grid_new();
   gtk_container_add (GTK_CONTAINER (window), grid);

   GtkWidget *button;
   //load images from gameDef
   int board_rows = g_def->get_boardState_rows();
   int board_cols = g_def->get_boardState_cols();
   for (int row = 0; row < board_rows; row++) {
      for (int column = 0; column < board_cols; column++){
         button = gtk_toggle_button_new();
         int temp = *(int*) (g_def->get_boardState_element(row, column));//from gameDef 
         cout<<"I reached creating images loop in view.cpp"<<endl;
         gtk_button_set_image((GtkButton*)button, gtk_image_new_from_file(color_state1[temp])); 
         gtk_button_set_relief ((GtkButton*)button, GTK_RELIEF_NONE); //added for button style
         
         //g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) row);
         //g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) column);

         gtk_grid_attach (GTK_GRID (grid), button, column, row, 1, 1);
      }
   }


   //four control buttons + 1 quit button
   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image((GtkButton*)button, gtk_image_new_from_file ("../images/direction/up.png"));
   //g_signal_connect (button, "clicked", G_CALLBACK (swap_up), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 0, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image((GtkButton*)button, gtk_image_new_from_file ("../images/direction/down.png"));
   //g_signal_connect (button, "clicked", G_CALLBACK (swap_down), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 1, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image((GtkButton*)button, gtk_image_new_from_file ("../images/direction/left.png"));
   //g_signal_connect (button, "clicked", G_CALLBACK (swap_left), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 2, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image((GtkButton*)button, gtk_image_new_from_file ("../images/direction/right.png"));
   //g_signal_connect (button, "clicked", G_CALLBACK (swap_right), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 3, 1, 1);

   button = gtk_button_new_with_label ("Quit");
   g_signal_connect_swapped ((GtkButton*)button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 4, 1, 1);

   gtk_widget_show_all (window);
}


using namespace std;
int main (int argc, char **argv) {
   if (argc != 2) {
      printf("Missing argument!");
      return 0;
   }

   //initialize model
   model_initialize(argv[1]);

   //gtk
   GtkApplication *app;
   int status;
   app = gtk_application_new ("candy crush", G_APPLICATION_FLAGS_NONE);
   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
   status = g_application_run (G_APPLICATION (app), 0, argv);
   //model_free_func();
   g_object_unref (app);
   return status;
}