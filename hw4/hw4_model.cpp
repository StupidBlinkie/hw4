//hw4_model
////////////testing gameDef class and deserialization////////////
#include <vector>
#include <iostream>
#include "hw4_model.h"
using namespace std;


//Global temp data for deserialize
//-------goes to gamedef object
int* extensionArr;
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



  for (int r = 0; r<8; r++){
    for (int c = 0; c<2; c++){
      //cout << "reteriving row: " << r << " col: " << c <<endl;
      void * temp = g_def->get_extensionColor_element(r, c);
      cout << "data: " << *(int*)temp <<endl;
    }
  }   
  cout << "-----------" <<endl;
  for (int r = 0; r<2; r++){
    for (int c = 0; c<2; c++){
      void * temp = g_def->get_boardState_element(r, c);
      cout << "boardState_data: " << *(int*)temp <<endl;
    }
  } 

  delete g_def;
  
  return 0;
}



int* deserializeIntegerArray2d(json_t *json){
    void * itr = json_object_iter(json);
    
    //read rows
    json_t* json_row = json_object_iter_value(itr);
    int rows = json_integer_value(json_row);
    row = rows;
    
    //read cols
    itr = json_object_iter_next(json, itr);
    json_t* json_col = json_object_iter_value(itr);
    int cols = json_integer_value(json_col);
    col = cols;
    //  cout << "rows and cols are" << *row << ", " << *col << endl;

    //read array
    itr = json_object_iter_next(json, itr);
    json_t* json_data = json_object_iter_value(itr);


    
    int* data = (int*)malloc(rows * cols *sizeof(int));
    //store in an array
    for (size_t i = 0; i < json_array_size(json_data); i++) {
        data[i] = json_integer_value(json_array_get(json_data, i));
    }
    
    return data;
}


//read json and load into 2d array arr
void deserialize(char* file, gameDef* g_def){

    json_t* json = json_load_file(file, JSON_COMPACT, NULL);
    void * itr = json_object_iter(json);
    
    json_t* gameDef = json_object_iter_value(itr);
    
    void *gameDefItr = json_object_iter(gameDef);
    gameID = json_integer_value(json_object_iter_value(gameDefItr));
    
    gameDefItr = json_object_iter_next(gameDef, gameDefItr);
    
    json_t *extension = json_object_iter_value(gameDefItr);
    extensionArr = deserializeIntegerArray2d(extension);
    
    cout << "before set extension color.. row, col are " << row << " "<< col <<endl; 
    g_def->set_extensionColor(row, col, extensionArr);
    ////////////////////////
    
    gameDefItr = json_object_iter_next(gameDef, gameDefItr);
    json_t *initBS = json_object_iter_value(gameDefItr);
    initBoardStateArr = deserializeIntegerArray2d(initBS);  
    gameDefItr = json_object_iter_next(gameDef, gameDefItr); 
    movesAllowed = json_integer_value(json_object_iter_value(gameDefItr));
    gameDefItr = json_object_iter_next(gameDef, gameDefItr); 
    colors = json_integer_value(json_object_iter_value(gameDefItr));
    itr = json_object_iter_next(json, itr);


    cout << "before set board state.. row, col are " << row << " "<< col <<endl; 
    g_def->set_boardState(row, col, initBoardStateArr);


   json_t *gameState = json_object_iter_value(itr);
   void *gameStateItr = json_object_iter(gameState);
   
  // json_t *boardcandies = json_object_itr_value(gameStateItr);
  // candyArr = deserializeCandyArray2d(boardcandies);
   
   gameStateItr = json_object_iter_next(gameState, gameStateItr);
   json_t *currentBS = json_object_iter_value(gameStateItr);
   currBoardStateArr = deserializeIntegerArray2d(currentBS);
   gameStateItr = json_object_iter_next(gameState, gameStateItr);
   movesMade =json_integer_value(json_object_iter_value(gameStateItr));
   gameStateItr = json_object_iter_next(gameState, gameStateItr); 
   currScore =json_integer_value(json_object_iter_value(gameStateItr));
   
   g_def->set_gameID(gameID);
   g_def->set_movesAllowed(movesAllowed);
   g_def->set_colors(colors);
   // gameStateItr = json_object_iter_next(gameState, gameStateItr);
//    extensionOffset = (int*) malloc(currBoardStateArr->cols * sizeof(int));
//    
//    json_t *extensionOffsetArr = json_object_itr_value(gameStateItr);
//    
//    for (size_t i = 0; i < json_array_size(extensionOffsetArr); i++) {
//        extensionOffset[i] = json_integer_value(json_array_get(extensionOffsetArr, i));
//    }
}






