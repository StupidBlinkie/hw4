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

	~gameDef(void);
};


inline void gameDef::set_extensionColor(int rows, int cols,int* data_from_json){
	//deep copy data. (to-do: try std::vetor<int>? check if data is valid)
	extensionColor_row = rows;
	extensionColor_col = cols;
	internal_extencolor = (int*)malloc(rows * cols * sizeof(int));
	//cout << "allocated space for int*" << endl;
	for(int i=0; i<rows*cols; i++){
		internal_extencolor[i] = data_from_json[i];
		//cout << internal_extencolor[i];
	}
	//cout << "copied data from prev int*" << endl;
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


inline gameDef::~gameDef(void){
  cout << "gameDef Object is being deleted" << endl;
  free(extensionColor->storage);
  free(extensionColor);
  free(internal_extencolor);
  free(boardState->storage);
  free(boardState);
  free(internal_boardstate);
}



//----------------Candy Class-------------------//
class candy{
	public:
	    candy(int t, int c);
	    int get_type() const {return type;}
	    int get_color() const {return color;}
	    void set_type(int t)  { type = t;}
	    void set_color(int c) { color = c;}
	private:
		int type;
		int color;
	};
	inline candy::candy(int t, int c){
	  type = t;
	  color = c;
};




//----------------game state class-------------------//
class gameState{
	private: 
		int rows, cols;
		int gameID;
		int movesMade = 0;
		int currScore = 0;
		int* extensionOffset;

		//int* internal_extencolor; //not used
		int* internal_boardState;
		candy** internal_boardCandies; // internal candy array 

		Array2dPtr boardCandies;
		Array2dPtr boardState;
	public:
		//void set_rowsAndCols(int r, int c){rows = r; cols = c;}
		void set_gameID(int id) { gameID = id; }
		void incre_movesMade()  { movesMade += 1; }
		void incre_Score(int s) { currScore += s; }
		int get_movesMade() {return movesMade; }
		int get_currScore() {return currScore; }
		int get_gameID()	{return gameID; }	   
	    int get_rows()  const {return rows;}
	    int get_cols()  const {return cols;}
       

	    void* get_boardState_element(int row, int col);
	    void set_boardState_element(int row, int col, int value);
	      
	    void* get_candy_element(int row, int col);
	    void set_candy_element(int row, int col, void* value);
       
       int get_candy_color(int row, int col);
      void set_candy_color(int row, int col, int color);
      
      void decrement_boardState_element(int row, int col);
      
      int get_extensionOffset(int col);
      void set_extensionOffset(int col, int value);
	      
	    void swap_candy_elements(int row1, int col1, int row2, int col2);
      
		void initialize(gameDef* &g_def);	
		//void update();

		void free_gameState();
		~gameState(void);
	
};

inline void* gameState::get_boardState_element(int row, int col){
	return A2d_GetElement(boardState, row, col);
}

inline void gameState::set_boardState_element(int row, int col, int value){
		*((int*)get_boardState_element(row, col)) = value;

   //A2d_FillArray2d(boardState, row, col, value);
}

inline void* gameState::get_candy_element(int row, int col){
	return A2d_GetElement(boardCandies, row, col);
}

inline void gameState::set_candy_element(int row, int col, void* value){
	A2d_FillArray2d(boardCandies, row, col, value);
}

inline int gameState::get_candy_color(int row, int col) {
   return ((candy*)get_candy_element(row, col))->get_color();
}

inline void gameState::set_candy_color(int row, int col, int color) {
   ((candy*)get_candy_element(row, col))->set_color(color);
}

inline void gameState::decrement_boardState_element(int row, int col) {
   int num = *(int*) get_boardState_element(row, col);
   if (num > 0) {
      set_boardState_element(row, col, num - 1);
      currScore++;
   }
}

inline int gameState::get_extensionOffset(int col) {
   return extensionOffset[col];
}

inline void gameState::set_extensionOffset(int col, int value) {
   extensionOffset[col] = value;
}

inline void gameState::swap_candy_elements(int row1, int col1, int row2, int col2){
	A2d_Swap(boardCandies, row1, col1, row2, col2);
}


inline void gameState::initialize(gameDef* &g_def){
	rows = g_def->get_boardState_rows();
	cols = g_def->get_boardState_cols();

	cout << "[gameState initialize]---rows, cols .."<< rows <<", "<< cols << endl;

	//STEP 1: initialize 
	extensionOffset = (int*)malloc(rows * sizeof(int));
	internal_boardCandies = (candy**)malloc(rows * cols * sizeof(candy*));
	internal_boardState= (int*)malloc(rows * cols * sizeof(int));
   
   //STEP 1.5: set extensionOffset
   for (int i = 0; i < cols; i++) {
      extensionOffset[i] = rows;
   }

	//STEP 2: create canides and store in internal serial array storages
	for(int r=0; r<rows; r++){
		for (int c = 0; c<cols; c++){
		  int color = *(int*)g_def->get_extensionColor_element(r, c);
		  int type = *(int*)g_def->get_boardState_element(r,c);
		  
		//allocate memeory on heap for each candy, remember to free
		  internal_boardCandies[r * cols + c] = new candy(type, color); 
		  internal_boardState[r * cols + c] = type;
		  //cout << "[gameState initialize]-- internal candy array.. type & color ---" << internal_boardCandies[ r * cols + c]->get_type() << " "<< internal_boardCandies[ r * cols + c]->get_color() << endl;
		}
	}

	//STEP 3: load to boardCandies and boardState 2d arrays
	boardCandies = A2d_AllocateArray2d(rows, cols, sizeof(void*));
	boardState = A2d_AllocateArray2d(rows, cols, sizeof(void*));

	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	       A2d_FillArray2d(boardCandies, r, c, internal_boardCandies[r * cols + c]);
	       A2d_FillArray2d(boardState, r, c, &internal_boardState[r * cols + c]);
		

		//test (no need to dereference, it's already a candy pointer)
		candy* temp = (candy*)A2d_GetElement(boardCandies, r , c );
		int tem = *(int*)A2d_GetElement(boardState, r , c );
		 cout << "[gameState initialize]-- candy 2d array.. type & color ---" << temp->get_type() << " "<< temp->get_color() << endl;
		 cout << "[gameState initialize]-- state 2d array..  ---" << tem << endl;
		}
	}

}

//destructor
inline gameState::~gameState(void){
	free(extensionOffset);	

	free(boardCandies->storage);
	free(boardCandies);
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
	   //cout<< internal_boardCandies[r * cols + c]->get_type() << internal_boardCandies[r * cols + c]->get_color()<< endl;
	    //free(internal_boardCandies[r * cols + c]);
	   delete internal_boardCandies[r * cols + c];  //use delete instead of free for objects
         }
	}
	free(internal_boardCandies);
	
	free(boardState->storage);
	free(boardState);
	free(internal_boardState);
	cout << "gamestate Object is being deleted" << endl;
}




//-----------------model functions declaration---------------//
void model_initialize(char* file);
void deserialize2dArray(json_t *json, bool reading_first_array);
void deserialize(char* file);
bool applyTemplate();
bool VFour();
bool HFour();
bool VThree();
bool HThree();
bool checkVFour(int row, int col);
bool checkHFour(int row, int col);
bool checkVThree(int row, int col);
bool checkHThree(int row, int col);
void applyGravity();


#endif // _HW4_MODEL_H_