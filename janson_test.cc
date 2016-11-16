//hw4_model
#include <iostream>
#include "hw4_model.h"
using namespace std;

extern "C"{
	//#include <gtk/gtk.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	//#include "../array2d/array2d.h
	#include "../jansson/include/jansson.h"
}

// class Candy {
// private:
//    int color;
//    int type;
//    
// public:
//    Candy(int color_, int type_) {color = color_; type = type_;}
//    
//    int getColor() {return color;}
//    
//    int getType() {return type;}
// };

int *data_from_json;  //remeber to free it. on exit?
int* extensionArr;
int* initBoardStateArr;
// Candy* candyArr;
int* currBoardStateArr;

int gameID;
int movesAllowed;
int colors;
int movesMade;
int currScore;

int *extensionOffset;

int selected_row;
int selected_col;
int selected_candy_bool = 0;
const char* color_files[6] = {"../images/blue.png", "../images/green.png", "../images/orange.png",
    "../images/purple.png", "../images/red.png", "../images/yellow.png"};

int* deserializeIntegerArray2d(json_t *json){
    void * itr = json_object_iter(json);
    
    //read rows
    json_t* json_row = json_object_iter_value(itr);
    const int rows = json_integer_value(json_row);
    
    //read cols
    itr = json_object_iter_next(json, itr);
    json_t* json_col = json_object_iter_value(itr);
    const int cols = json_integer_value(json_col);
    
    //read array
    itr = json_object_iter_next(json, itr);
    json_t* json_data = json_object_iter_value(itr);
    
    int* data = (int*)malloc(rows * cols *sizeof(int));
    //store in an array
    for (size_t i = 0; i < json_array_size(json_data); i++) {
        data[i] = json_integer_value(json_array_get(json_data, i));
    }
    
    //allocate 2d array in memeory
   // arr = AllocateArray2d(rows, cols, sizeof(void*));
    
    //fill 2d array
//    for (int r=0; r<rows; r++) {
//        for (int c=0; c<cols; c++) {
//            FillArray2d(arr, r, c, &data_fr[r * cols + c]);
//        }
//    }
    return data;
}

// Candy* deserializeCandyArray2d(json_t *json) {
//    void * itr = json_object_iter(json);
//    
//    //read rows
//    json_t* json_row = json_object_iter_value(itr);
//    const int rows = json_integer_value(json_row);
//    
//    //read cols
//    itr = json_object_iter_next(json, itr);
//    json_t* json_col = json_object_iter_value(itr);
//    const int cols = json_integer_value(json_col);
//    
//    //read array
//    itr = json_object_iter_next(json, itr);
//    json_t* json_data = json_object_iter_value(itr);
//    
//    candy_data = (Candy*)malloc(rows * cols * sizeof(Candy));
//    
//    for (int i = 0; i <json_array_size(json_data); i++) {
//        json_t *json_candy = json_array_get(json_data, i);
//        void *candyItr = json_object_iter(json_candy);
//        int color = json_integer_value(json_object_itr_value(candyItr));
//        
//        candyItr = json_object_iter_next(json_candy, candyItr);
//        int type = json_integer_value(json_object_itr_value(candyItr));
//        candy_data[i] = new Candy(color, type);
//    }
//    return candy_data;
   
//    Array2dPtr candyArr = AllocateArray2d(rows, cols, sizeof(void*)); //
//    
//    for (int r=0; r<rows; r++) {
//        for (int c=0; c<cols; c++) {
//            FillArray2d(arr, r, c, &candy_data[r * cols + c]);
//        }
//    }
//    return arr;
//}

//read json and load into 2d array arr
void deserialize(char* file){
    
    json_t* json = json_load_file(file, JSON_COMPACT, NULL);
    void * itr = json_object_iter(json);
    
    json_t* gameDef = json_object_iter_value(itr);
    
    void *gameDefItr = json_object_iter(gameDef);
    gameID = json_integer_value(json_object_iter_value(gameDefItr));
    
    gameDefItr = json_object_iter_next(gameDef, gameDefItr);
    
    json_t *extension = json_object_iter_value(gameDefItr);
    extensionArr = deserializeIntegerArray2d(extension);
    
    gameDefItr = json_object_iter_next(gameDef, gameDefItr);

    json_t *initBS = json_object_iter_value(gameDefItr);
    initBoardStateArr = deserializeIntegerArray2d(initBS);
    
    gameDefItr = json_object_iter_next(gameDef, gameDefItr);
    
    movesAllowed = json_integer_value(json_object_iter_value(gameDefItr));
    
    gameDefItr = json_object_iter_next(gameDef, gameDefItr);
    
    colors = json_integer_value(json_object_iter_value(gameDefItr));
    
    itr = json_object_iter_next(json, itr);
   
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
   
   // gameStateItr = json_object_iter_next(gameState, gameStateItr);
//    extensionOffset = (int*) malloc(currBoardStateArr->cols * sizeof(int));
//    
//    json_t *extensionOffsetArr = json_object_itr_value(gameStateItr);
//    
//    for (size_t i = 0; i < json_array_size(extensionOffsetArr); i++) {
//        extensionOffset[i] = json_integer_value(json_array_get(extensionOffsetArr, i));
//    }
}


int main(int argc, char **argv){

    deserialize(argv[1]);
    cout << "id:" << gameID << endl;
    cout << "moves allowed:" << movesAllowed << endl;
    cout << "Colors:" << colors << endl;
    cout << "moves made:" << movesMade << endl;
    cout << "current score:" << currScore << endl;

    cout << "extensionColor" << endl;
    
    cout<< "extensionArr:" << endl;
    for (int i = 0; i < 16; i++) {
        cout << extensionArr[i] << endl;
    }

    cout << endl;
    
    cout << "initBoardStateArr:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << initBoardStateArr[i] << endl;
    }

    cout << endl;
    
   //  cout << "CandyArr:" << endl;
//     for (int i = 0; i < 4; i++) {
//         cout << "(" << candyArr[i].getColor() << ", " << candyArr[i],getType() << ")" << endl;
//     }
//     
//     cout << endl;

    cout << "currBoardStateArr:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << currBoardStateArr[i] << endl;
    }
    
    cout << endl;
    
  //   cout << "extensionOffset:" << endl;
//     for (int i = 0; i < 2; i++) {
//         cout << extensionOffset[i] << endl;
//     }
//	int color[16] = {0, 1, 2, 3, 4, 5,
//					    0, 1, 2, 3, 4, 5,
//					    0, 1, 2, 3};
// 	int state[4] = {1,1,1,1};
//
// 	gameDef g_def;
// 	g_def.gameID = 12345;
// 	g_def.movesAllowed = 20;
// 	g_def.colors = 6;
// 	g_def.set_extensionColor(8, 2, color);
// 	g_def.set_boardState(2,2, state);
//    
//    gameState g_state;
//    g_state.boarcandies;
//    
//
// 	cout << "id: " << g_def.gameID <<endl;
// 	cout << "colors: " << g_def.colors <<endl;
// 	cout << "moves allowed: " << g_def.movesAllowed <<endl;
//
// 	for (int r = 0; r<8; r++){
// 		for (int c = 0; c<2; c++){
// 			void * temp = g_def.get_extensionColor_element(r, c);
//			cout << "data: " << *(int*)temp <<endl;
// 		}
// 	}		
//
// 	cout << "-----------" <<endl;
//
// 	for (int r = 0; r<8; r++){
// 		for (int c = 0; c<2; c++){
// 			void * temp = g_def.get_boardState_element(r, c);
//			cout << "data: " << *(int*)temp <<endl;
// 		}
// 	}		
//
//
// 	return 0;

}



