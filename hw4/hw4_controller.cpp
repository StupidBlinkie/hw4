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
   //remove current selected button's focus when selecting a new candy
   unselect_current_active_button();
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
   //int selected_candy = ((candy*)g_state->get_candy_element(selected_row, selected_col))->get_color();
   //int target_candy = ((candy*)g_state->get_candy_element(target_row, target_col))->get_color();
  
   g_state->swap_candy_elements(selected_row, selected_col, target_row, target_col); 

   if (applyTemplate()) {
      view_redraw_grid();
      selected_candy_bool = 0;
      g_state->incre_movesMade();
      view_update_moves_label();
      view_update_score_label();
   } 

   else {
      g_state->swap_candy_elements(selected_row, selected_col, target_row, target_col);
      unselect_current_active_button(); 
   }

}




// connected to up arrow button
void swap_down(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_row != 0) {
         swap_buttons(selected_row - 1, selected_col);
      }
      else{
         //unselect the button if can;t be swapped
         unselect_current_active_button();
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}

// connected to down arrow button
void swap_up(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool && moves_left > 0) {
      if (selected_row != g_state->get_rows() - 1) {
         swap_buttons(selected_row + 1, selected_col);
      }
      else{
         unselect_current_active_button();
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
         unselect_current_active_button();
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
         unselect_current_active_button();
      }
   }

   else{
      g_print("must select a candy!\n");
   }
}


void unselect_current_active_button(){
   gtk_toggle_button_set_active(
      (GtkToggleButton*)gtk_grid_get_child_at(GTK_GRID (grid), selected_col, g_state->get_rows() - 1 - selected_row), 
      false);   
}