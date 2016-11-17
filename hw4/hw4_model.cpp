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

//--------------------------------------------//




int main(int argc, char** argv){

  // std::vector<int> color;
  // std::vector<int> state;
  // color = {0, 1, 2, 3, 4, 5,
  //               0, 1, 2, 3, 4, 5,
  //               0, 1, 2, 3};
  // state = {1,1,1,1};

   g_def = new gameDef();
  

  
  deserialize(argv[1], g_def);

  for (int r = 0; r< g_def->get_extensionColor_rows(); r++){
    for (int c = 0; c< g_def->get_extensionColor_cols(); c++){
      //cout << "reteriving row: " << r << " col: " << c <<endl;
      void * temp = g_def->get_extensionColor_element(r, c);
      cout << "data: " << *(int*)temp <<endl;
    }
  }   
  cout << "-----------" <<endl;
  for (int r = 0; r< g_def->get_boardState_rows(); r++){
    for (int c = 0; c< g_def->get_boardState_cols(); c++){
      void * temp = g_def->get_boardState_element(r, c);
      cout << "boardState_data: " << *(int*)temp <<endl;
    }
  } 

  delete g_def;
  
  return 0;
}

//********......notes.....*******//
//I modified gamedef class, it should prevent leaks from deserialzation now
//however I didn't figure out how you read data from json file, I think I 
//messed up with the iterator order..
//so basically I want to read in the following order..(same as 25by5.json)
//extension color 2da --> 
// board state 2da --> 
// movesAllowed -->
// gameid -->
// colors

// Can you look at the deserialize function and modify the iterating order?
// I'm little confused. 
// the rows and cols I extract from json are both 0. I must used the jansson
// methods wrong.



void deserialize2dArray(json_t *json, bool reading_first_array){
    void * itr = json_object_iter(json);  
    //read rows
    json_t* json_row = json_object_iter_value(itr);
    int rows = json_integer_value(json_row); 
    //read cols
    itr = json_object_iter_next(json, itr);
    json_t* json_col = json_object_iter_value(itr);
    int cols = json_integer_value(json_col);

    cout << "rows and cols are" << row << ", " << col << endl;

    //read json array
    itr = json_object_iter_next(json, itr);
    json_t* json_data = json_object_iter_value(itr);

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
void deserialize(char* file, gameDef* g_def){

    json_t* json = json_load_file(file, JSON_COMPACT, NULL);
    void * itr = json_object_iter(json);


    json_t *extension = json_object_iter_value(itr);
    deserialize2dArray(extension, 1); //1 and 0 to indicate if reading first or second array

    //iterate to boardstate field
    itr = json_object_iter_next(json, itr); 
    json_t *boardstate = json_object_iter_value(itr);
    deserialize2dArray(boardstate, 0);
    
    //iterate to moves allowed
    itr = json_object_iter_next(json, itr); 
    int movesAllowed = json_integer_value(json_object_iter_value(itr));

    //iterate to id
    itr = json_object_iter_next(json, itr); 
    int id = json_integer_value(json_object_iter_value(itr));

    //iterate to color
    itr = json_object_iter_next(json, itr); 
    int colors = json_integer_value(json_object_iter_value(itr));

    g_def->set_gameID(id);
    g_def->set_movesAllowed(movesAllowed);
    g_def->set_colors(colors);
}






