#ifndef _HW4_MODEL_H_
#define _HW4_MODEL_H_

#include <vector>
using namespace std;

extern "C"{
	#include "../hw2/array2d.h"
    #include "../jansson/include/jansson.h"
}






class gameDef{
 private:
 	//gameDefinition();
 	int gameID;
	int movesAllowed;
 	int colors;

 	int* internal_extencolor; //copies data read from json
 	int* internal_boardstate; //copies data read from json
 	Array2dPtr extensionColor; // collection of pointers to internal data storage
	Array2dPtr boardState;
	int extensionColor_row, extensionColor_col;
	int boardState_row, boardState_col;

 public:
 	//simple get/set
	void set_gameID(int id){gameID = id;}
	void set_movesAllowed(int m) {movesAllowed = m;}
	void set_colors(int c) {colors = c;}
	int get_gameID(){return gameID;}
	int get_movesAllowed(){return movesAllowed;}
	int get_colors(){return colors;}
	int get_extensionColor_rows(){return extensionColor_row;}
 	int get_extensionColor_cols(){return extensionColor_col;}
 	int get_boardState_rows(){return boardState_row;}
 	int get_boardState_cols(){return boardState_col;}
 	
 	//long get/set, defined below with inline
 	void set_extensionColor(int rows, int cols, int* data_from_json);
 	void set_boardState(int rows, int cols,int* data_from_json);
 	void* get_extensionColor_element(int row, int col);
 	void* get_boardState_element(int row, int col);

	void free_extensionColor();
	void free_boardState();

	~gameDef(void);
};


inline void gameDef::set_extensionColor(int rows, int cols,int* data_from_json){
	//deep copy data. (to-do: try std::vetor<int>? check if data is valid)
	extensionColor_row = rows;
	extensionColor_col = cols;
	internal_extencolor = (int*)malloc(rows * cols * sizeof(int));
	cout << "allocated space for int*" << endl;
	for(int i=0; i<rows*cols; i++){
		internal_extencolor[i] = data_from_json[i];
		cout << internal_extencolor[i];
	}
	cout << "copied data from prev int*" << endl;
	//free(data_from_json);

	//fill 2d array
	extensionColor = A2d_AllocateArray2d(rows, cols, sizeof(void*));
	
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	       A2d_FillArray2d(extensionColor, r, c, &internal_extencolor[r * cols + c]);
	   }
	}
}

inline void gameDef::set_boardState(int rows, int cols,int* data_from_json){
	boardState_row = rows;
	boardState_col = cols;
	internal_boardstate = (int*)malloc(rows * cols * sizeof(int));

	for(int i=0; i<rows*cols; i++){
		internal_boardstate[i] = data_from_json[i];
	}
	//free(data_from_json);

	boardState = A2d_AllocateArray2d(rows, cols, sizeof(void*));
	
	//fill 2d array
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	       A2d_FillArray2d(boardState, r, c, &internal_boardstate[r * cols + c]);
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
  free(internal_extencolor);
}
inline void gameDef::free_boardState(){
  A2d_FreeArray2d(extensionColor, NULL);  //modify a2d free function?
  free(boardState->storage);
  free(boardState);
  free(internal_boardstate);
}



inline gameDef::~gameDef(void){
	cout << "Object is being deleted" << endl;
	free_extensionColor();  //adding this.. 16 direct loss, 32 indirect
	free_boardState(); // adding this.. 0 lost, 0 indirect lost, still has errors
}

void deserialize2dArray(json_t *json, bool reading_first_array);
void deserialize(char* file, gameDef* g_def);

#endif // _HW4_MODEL_H_
