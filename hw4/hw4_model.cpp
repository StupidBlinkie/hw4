//hw4_model
////////////testing gameDef class and deserialization////////////
#include <vector>
#include <iostream>
#include "hw4_model.h"
using namespace std;


//Global temp data for deserialize
//-------goes to gamedef object
int* extensionArr;
std::vector<int> extensionColor;
int* initBoardStateArr;
int gameID;
int movesAllowed;
int colors;
int row, col;

//-----goes to gamestate object-------------//
int movesMade;
int currScore;
int *extensionOffset;
int* currBoardStateArr;

gameDef* g_def;
gameState* g_state;

//--------------------------------------------//




int main(int argc, char** argv){

  // std::vector<int> color;
  // std::vector<int> state;
  // color = {0, 1, 2, 3, 4, 5,
  //               0, 1, 2, 3, 4, 5,
  //               0, 1, 2, 3};
  // state = {1,1,1,1};

   g_def = new gameDef();
   g_state = new gameState();
   g_state->initialize(g_def);



   cout<< c->get_type() << c->get_color() << endl;


   
  delete g_def;
  delete c;
  return 0;
}

void deserialize2dArray(json_t *json, bool reading_first_array){
    //read rows
  json_t* json_row = json_object_get(json, "rows");
    int rows = json_integer_value(json_row); 
    //read cols
    json_t* json_col = json_object_get(json, "columns");
    int cols = json_integer_value(json_col);

    cout << "rows and cols are" << rows << ", " << cols << endl;

    //read json array
    json_t* json_data = json_object_get(json, "data");

    //store in an int array
    int* data = (int*)malloc(rows * cols *sizeof(int));
        for (size_t i = 0; i < json_array_size(json_data); i++) {
            data[i] = json_integer_value(json_array_get(json_data, i));
    }
	cout << "made it past for loop" << endl;
    //load to different fileds of g_def
    if (reading_first_array){
      g_def->set_extensionColor(rows, cols, data);
    }
    else {
      g_def->set_boardState(rows,cols,data);
    }
    cout << "made it past if else" << endl;
    
    //g_def set functions deep copied the data, so free immediately after use
    free(data); 
}


//read json and load into 2d array arr
void deserialize(char* file, gameDef* g_def){

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
}






