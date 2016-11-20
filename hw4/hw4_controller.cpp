<<<<<<< HEAD
// #include "hw3.h"
// #include "hw3_view.h"

#include "hw4.h"
#include "hw4_model.h"
#include "hw4_controller.h"
#include "hw4_view.h"

extern gameDef* g_def;
extern gameState* g_state;
extern long selected_row; // change to be int later
extern long selected_col;
extern int selected_candy_bool;
extern int moves_left;
extern const char* color_state1_files[7];
extern GtkWidget *grid;
extern GtkWidget *window;


// connected to each candy to set the row
void set_row(GtkWidget *widget, gpointer  data) {
   selected_row = (long) data;
}

// connected to each candy to set col
void set_col(GtkWidget *widget, gpointer  data) {
   selected_col = (long) data;
   selected_candy_bool = 1;
   //printf("%d, %d\n", selected_row, selected_col);
}


void swap_buttons(int target_row, int target_col) {
   // get the indexes for the candies in temp_data
   int selected_candy = ((candy*)g_state->get_candy_element(selected_row, selected_col))->get_color();
   int target_candy = ((candy*)g_state->get_candy_element(target_row, target_col))->get_color();

   
   cout << "selected color:   " << selected_row << ", " << selected_col << endl;
   cout << "target color:     " << target_row << ", " << target_col << endl;
   
   g_state->swap_candy_elements(selected_row, selected_col, target_row, target_col); 
   if (applyTemplate()) {
      view_redraw_grid();
      selected_candy_bool = 0;
      moves_left--;
      view_update_moves_label();
   } else {
      g_state->swap_candy_elements(selected_row, selected_col, target_row, target_col); 
   }
   //update view
  // view_destroy_candy(selected_col, selected_row);
  // view_destroy_candy(target_col, target_row);

   //create target candy in selected slot, and selected candy in target solt
   //view_create_candy(selected_candy, target_row, target_col);
   //view_create_candy(target_candy, selected_row, selected_col);
}




// connected to up arrow button
void swap_up(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_row != g_state->get_rows() - 1) {
         swap_buttons(selected_row + 1, selected_col);  //passing target candy coordinates
      }
      else{
         //unselect the button if can't be swapped

         gtk_toggle_button_set_active 
            ((GtkToggleButton*)gtk_grid_get_child_at(GTK_GRID (grid), selected_col, g_state->get_rows() - 1 - selected_row),
            false);
         g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to down arrow button
void swap_down(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_row != 0) {
         swap_buttons(selected_row - 1, selected_col);
      }
      else{
         gtk_toggle_button_set_active 
            ((GtkToggleButton*) gtk_grid_get_child_at(GTK_GRID (grid), selected_col, g_state->get_rows() - 1 - selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to left arrow button
void swap_left(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_col != 0) {
         swap_buttons(selected_row, selected_col - 1);
      }
      else{
         gtk_toggle_button_set_active 
            ((GtkToggleButton*) gtk_grid_get_child_at(GTK_GRID (grid), selected_col, g_state->get_rows() - 1 - selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to right arrow button
void swap_right(GtkWidget *widget, gpointer  data){
  if (selected_candy_bool && moves_left > 0) {
      if (selected_col != g_state->get_cols() - 1) {
         swap_buttons(selected_row, selected_col + 1);
      }
      else{
         gtk_toggle_button_set_active 
            ((GtkToggleButton*) gtk_grid_get_child_at(GTK_GRID (grid), selected_col, g_state->get_rows() - 1 - selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
=======
// #include "hw3.h"
// #include "hw3_view.h"

#include "hw4.h"
#include "hw4_model.h"
#include "hw4_controller.h"
#include "hw4_view.h"

extern gameDef* g_def;
extern gameState* g_state;
extern long selected_row; // change to be int later
extern long selected_col;
extern int selected_candy_bool;
extern int moves_left;
extern const char* color_state1_files[7];
extern GtkWidget *grid;
extern GtkWidget *window;


// connected to each candy to set the row
void set_row(GtkWidget *widget, gpointer  data) {
   selected_row = (long) data;
}

// connected to each candy to set col
void set_col(GtkWidget *widget, gpointer  data) {
   selected_col = (long) data;
   selected_candy_bool = 1;
   //printf("%d, %d\n", selected_row, selected_col);
}


void swap_buttons(int target_row, int target_col) {

   // printf("selected: %d, %d\n", selected_row, selected_col);
   // printf("to be swapped with: %d, %d\n", target_row, target_col);
   cout << "target color:   " << target_row << ", " << target_col << endl;

   // get the indexes for the candies in temp_data
   int selected_candy = ((candy*)g_state->get_candy_element(selected_row, selected_col))->get_color();
   int target_candy = ((candy*)g_state->get_candy_element(target_row, target_col))->get_color();

   
   //update arr (2d array swap function, could make a swap function in model)
   
   cout << "selected color:   " << selected_row << ", " << selected_col << endl;
   cout << "target color:     " << target_row << ", " << target_col << endl;
   g_state->swap_candy_elements(selected_row, selected_col, target_row, target_col); 
   if (applyTemplate()) {
      view_redraw_grid();
      selected_candy_bool = 0;
      moves_left--;
      view_update_moves_label();
   } else {
      g_state->swap_candy_elements(selected_row, selected_col, target_row, target_col); 
   }
   //update view
  // view_destroy_candy(selected_col, selected_row);
  // view_destroy_candy(target_col, target_row);

   //create target candy in selected slot, and selected candy in target solt
   //view_create_candy(selected_candy, target_row, target_col);
   //view_create_candy(target_candy, selected_row, selected_col);
}




// connected to up arrow button
void swap_up(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_row != 0) {
         swap_buttons(selected_row - 1, selected_col);
      }
      else{
         //unselect the button if can;t be swapped
         gtk_toggle_button_set_active 
            ((GtkToggleButton*)gtk_grid_get_child_at(GTK_GRID (grid), selected_col, selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to down arrow button
void swap_down(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_row != g_state->get_rows() - 1) {
         swap_buttons(selected_row + 1, selected_col);
    //      selected_candy_bool = 0;
//          moves_left--;
//          view_update_moves_label();
      }
      else{
         gtk_toggle_button_set_active 
            ((GtkToggleButton*) gtk_grid_get_child_at(GTK_GRID (grid), selected_col, selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to left arrow button
void swap_left(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_col != 0) {
         swap_buttons(selected_row, selected_col - 1);
      //    selected_candy_bool = 0;
//          moves_left--;
//          view_update_moves_label();
      }
      else{
         gtk_toggle_button_set_active 
            ((GtkToggleButton*) gtk_grid_get_child_at(GTK_GRID (grid), selected_col, selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to right arrow button
void swap_right(GtkWidget *widget, gpointer  data){
  if (selected_candy_bool && moves_left > 0) {
      if (selected_col != g_state->get_cols() - 1) {
         swap_buttons(selected_row, selected_col + 1);
       //   selected_candy_bool = 0;
//          moves_left--;
//          view_update_moves_label();
      }
      else{
         gtk_toggle_button_set_active 
            ((GtkToggleButton*) gtk_grid_get_child_at(GTK_GRID (grid), selected_col, selected_row),
            false);
         //g_print ("can't swap\n");
      }
   }

   else{
      g_print("must select a candy!\n");
   }
>>>>>>> origin/master
}