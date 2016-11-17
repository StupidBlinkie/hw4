#ifndef _HW4_MODEL_H_
#define _HW4_MODEL_H_

#include <vector>
using namespace std;

 extern "C"{
	#include "../hw2/array2d.h"
   #include "../jansson/include/jansson.h"
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
 	void set_boardState(int rows, int cols,int* data_from_json);
 	void* get_extensionColor_element(int row, int col);
 	void* get_boardState_element(int row, int col);

	void free_extensionColor();
	void free_boardState();

	~gameDef(void);
};


inline void gameDef::set_extensionColor(int rows, int cols,int* data_from_json){
 	extensionColor = A2d_AllocateArray2d(rows, cols, sizeof(void*));
	//fill 2d array
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	       A2d_FillArray2d(extensionColor, r, c, &data_from_json[r * cols + c]);
	   }
	}
}

inline void gameDef::set_boardState(int rows, int cols,int* data_from_json){
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

inline void gameDef::free_extensionColor(){
  A2d_FreeArray2d(extensionColor, NULL);  //modify a2d free function?
  free(extensionColor->storage);
  free(extensionColor);
}
inline void gameDef::free_boardState(){
  A2d_FreeArray2d(extensionColor, NULL);  //modify a2d free function?
  free(boardState->storage);
  free(boardState);
}



inline gameDef::~gameDef(void){
	cout << "Object is being deleted" << endl;
	free_extensionColor();  //adding this.. 16 direct loss, 32 indirect
	free_boardState(); // adding this.. 0 lost, 0 indirect lost, still has errors
}

int* deserializeIntegerArray2d(json_t *json);
void deserialize(char* file, gameDef* g_def);

#endif // _HW4_MODEL_H_
