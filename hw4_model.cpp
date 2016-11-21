//hw4_model
////////////testing gameDef class and deserialization////////////
// #include <vector>
// #include <iostream>
// #include "hw4_model.h"

#include "hw4.h"
#include "hw4_model.h"
using namespace std;

//------for selected candy-----//
long selected_row;
long selected_col;
int selected_candy_bool = 0;
int moves_left = 30;

//-----color file names-----//
// const char* color_state1_files[7] = {"../images/regular/state1/blue.png", "../images/regular/state1/green.png", "../images/regular/state1/orange.png",
 //                             "../images/regular/state1/purple.png", "../images/regular/state1/red.png", "../images/regular/state1/yellow.png",
   //                           "../images/regular/state1/nocolor.png"};


gameDef* g_def;
gameState* g_state;


void model_initialize(char* file){
    g_def = new gameDef();
    g_state = new gameState();

    deserialize(file);
    g_state->initialize(g_def);
}


//MODEL's INTERNAL METHODS
void deserialize2dArray(json_t *json, bool reading_first_array){
    //read rows
    json_t* json_row = json_object_get(json, "rows");
    int rows = json_integer_value(json_row); 
    //read cols
    json_t* json_col = json_object_get(json, "columns");
    int cols = json_integer_value(json_col);
  
    //read json array
    json_t* json_data = json_object_get(json, "data");

    //store in an int array
    int* data = (int*)malloc(rows * cols *sizeof(int));
        for (size_t i = 0; i < json_array_size(json_data); i++) {
            data[i] = json_integer_value(json_array_get(json_data, i));
    }
    

    //load to different fileds of g_def
    if (reading_first_array){
      g_def->set_extensionColor(rows, cols, data);
    }
    else {
      g_def->set_boardState(rows,cols,data);
    }
    
    //g_def set functions deep copied the data, so free immediately after use
    free(data); 
}

//read json and load into 2d array arr
void deserialize(char* file){

    json_t* json = json_load_file(file, JSON_COMPACT, NULL);
    json_t* gamedef_json = json_object_get(json, "gamedef");
    if (gamedef_json == NULL) {
      cout << "did not find gamedef" << endl;
    }

    json_t *extension = json_object_get(gamedef_json, "extensioncolor");
    if (extension == NULL) {
      cout << "did not find extensioncolor" << endl;
    }
    deserialize2dArray(extension, 1); //1 and 0 to indicate if reading first or second array
    //iterate to boardstate field
    json_t *boardstate = json_object_get(gamedef_json, "boardstate");
    deserialize2dArray(boardstate, 0);
    
    //iterate to moves allowed
    int movesAllowed = json_integer_value(json_object_get(gamedef_json, "movesallowed"));

    //iterate to id
    int id = json_integer_value(json_object_get(gamedef_json, "gameid"));
    //iterate to color
    int colors = json_integer_value(json_object_get(gamedef_json, "colors"));
    json_decref(json);
    g_def->set_gameID(id);
    g_def->set_movesAllowed(movesAllowed);
    g_def->set_colors(colors);

    g_state->initialize(g_def);
}

bool applyTemplate() {
   bool possibleFire = true;
   int numberTemplatesFired = 0;
   while (possibleFire && numberTemplatesFired < 1000) {
      possibleFire = false;
      possibleFire = (VFour() || HFour() || VThree() || HThree());
      if (possibleFire) {
         numberTemplatesFired++;
         applyGravity();
      }
      
   }
   
   return (numberTemplatesFired > 0);
      
}

bool VFour() {
   bool foundFire = false;
   for (int row = 0; row <= g_state->get_rows() - 4; row++) {
      for (int col = 0; col < g_state->get_cols(); col++) {
        foundFire = foundFire || checkVFour(row, col);
         
      }
   }
   return foundFire;
}

bool checkVFour(int row, int col){
   int candy_color = g_state->get_candy_color(row, col);
   if (candy_color == -1) {
      return false;
   }
   for (int i = 1; i<4; i++){
      int curr_color = g_state->get_candy_color(row + i, col);
      if (candy_color != curr_color) {
         return false;
      }
   }
   for (int i = 0; i < 4; i++) {
      g_state->set_candy_color(row + i, col, -1);
      g_state->decrement_boardState_element(row + i, col);
   }
   return true;
}

bool HFour() {
   bool foundFire = false;
   for (int row = 0; row < g_state->get_rows(); row++) {
      for (int col = 0; col <= g_state->get_cols() - 4; col++) {
        foundFire = foundFire || checkHFour(row, col);
      }
   }
   return foundFire;
}

bool checkHFour(int row, int col){
   int candy_color = g_state->get_candy_color(row, col);
   if (candy_color == -1) {
      return false;
   }
   for (int i = 1; i<4; i++){
      int curr_color = g_state->get_candy_color(row, col + i);
      if (candy_color != curr_color) {
         return false;
      }
   }
   for (int i = 0; i < 4; i++) {
      g_state->set_candy_color(row, col + i, -1);
      g_state->decrement_boardState_element(row, col + i);
   }
   return true;
}

bool VThree() {
   bool foundFire = false;
   for (int row = 0; row <= g_state->get_rows() - 3; row++) {
      for (int col = 0; col < g_state->get_cols(); col++) {
        foundFire = foundFire || checkVThree(row, col);
      }
   }
   return foundFire;
}

bool checkVThree(int row, int col){
   int candy_color = g_state->get_candy_color(row, col);
   if (candy_color == -1) {
      return false;
   }
   for (int i = 1; i<3; i++){
      int curr_color = g_state->get_candy_color(row + i, col);
      if (candy_color != curr_color) {
         return false;
      }
   }
   for (int i = 0; i < 3; i++) {
      g_state->set_candy_color(row + i, col, -1);
      g_state->decrement_boardState_element(row + i, col);
   }
   return true;
}

bool HThree() {
   bool foundFire = false;
   for (int row = 0; row < g_state->get_rows(); row++) {
      for (int col = 0; col <= g_state->get_cols() - 3; col++) {
        foundFire = foundFire || checkHThree(row, col);
      }
   }
   return foundFire;
}

bool checkHThree(int row, int col){
   int candy_color = g_state->get_candy_color(row, col);
   if (candy_color == -1) {
      return false;
   }
   for (int i = 1; i<3; i++){
      int curr_color = g_state->get_candy_color(row, col + i);
      if (candy_color != curr_color) {
         return false;
      }
   }
   for (int i = 0; i < 3; i++) {
      g_state->set_candy_color(row, col + i, -1);
      g_state->decrement_boardState_element(row, col + i);
   }
   return true;
}

void applyGravity() {

   
   // apply gravity to all left over candies on board
   for (int col = 0; col < g_state->get_cols(); col++) {
      int lowestFiredRow = 0;
      bool foundFired = false;
      for (int row = 0;  row < g_state->get_rows(); row++) {
         if (g_state->get_candy_color(row, col) == -1 && !foundFired) {
            foundFired = true;
            lowestFiredRow = row;
         } else if (g_state->get_candy_color(row, col) != -1 && foundFired) {
            g_state->swap_candy_elements(row, col, lowestFiredRow, col);
            lowestFiredRow++;
         }
      }
         
   // all -1s should be on top. all left over candies should be on bottom
   // put candies fro extension board in -1 candies;
      cout << "column:   " << col << endl;
      if (foundFired) {
         for (int row = lowestFiredRow; row < g_state->get_rows(); row++) {
            int offset = g_state->get_extensionOffset(col) % g_def->get_extensionColor_rows();
            cout << "offset:   " << offset << endl;
            int newColor = *(int*)g_def->get_extensionColor_element(offset, col);
            cout << "new color:    " << newColor << endl;
            g_state->set_candy_color(row, col, newColor);
            int newOffset = g_state->get_extensionOffset(col) + 1;
            g_state->set_extensionOffset(col, newOffset);
            newOffset = g_state->get_extensionOffset(col) % g_def->get_extensionColor_rows();
            cout << "new offset:    " << newOffset << endl;
         }
         cout << endl << endl << endl;
      }
   }
}



