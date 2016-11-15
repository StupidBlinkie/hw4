#ifndef _HW4_MODEL_H_
#define _HW4_MODEL_H_
using namespace std;
 extern "C"{
	#include "../hw2/array2d.h"
 }


class gameDef{
 public:
 	//gameDefinition();

 	int gameID;
 	Array2dPtr extensionColor;
	Array2dPtr boardState;
	int movesAllowed;
 	int colors;

	void set_gameID(int id){gameID = id;}
	void set_movesAllowed(int m) {movesAllowed = m;}
	void set_colors(int c) {colors = c;}
 	
 	void set_extensionColor(int rows, int cols, int* data_from_json);
 	void set_boardState(int rows, int cols, int* data_from_json);
 	void* get_extensionColor_element(int row, int col);
 	void* get_boardState_element(int row, int col);
	
};


inline void gameDef::set_extensionColor(int rows, int cols, int* data_from_json){
 	extensionColor = A2d_AllocateArray2d(rows, cols, sizeof(void*));
	//fill 2d array
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	       A2d_FillArray2d(extensionColor, r, c, &data_from_json[r * cols + c]);
	   }
	}
}

inline void gameDef::set_boardState(int rows, int cols, int* data_from_json){
	boardState = A2d_AllocateArray2d(rows, cols, sizeof(void*));
	//fill 2d array
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	       A2d_FillArray2d(boardState, r, c, &data_from_json[r * cols + c]);
	      
	   }
	}
}

inline void* gameDef::get_extensionColor_element(int row, int col){
	return A2d_GetElement(extensionColor, row, col);
}
inline void* gameDef::get_boardState_element(int row, int col){
	return A2d_GetElement(boardState, row, col);
}


#endif // _HW4_MODEL_H_
