//hw4_model
#include <iostream>
#include "hw4_model.h"
using namespace std;


int*color;
int*state;

int main(){


  color = (int*)malloc(sizeof(int)*16);
  for(int i = 0; i<16; i++){
    color[i] = i;
  }

  state = (int*)malloc(sizeof(int)*4);
  for (int i =0; i<4;i++){
      state[i] = 1;
  }


 	gameDef g_def;
 	g_def.set_gameID(12345);
 	g_def.movesAllowed = 20;
 	g_def.colors = 6;

	
 	g_def.set_extensionColor(8, 2, color);
 	g_def.set_boardState(2,2, state);

 	cout << "id: " << g_def.gameID <<endl;
 	cout << "colors: " << g_def.colors <<endl;
 	cout << "moves allowed: " << g_def.movesAllowed <<endl;

 	for (int r = 0; r<8; r++){
 		for (int c = 0; c<2; c++){
		  //cout << "reteriving row: " << r << " col: " << c <<endl;
 			void * temp = g_def.get_extensionColor_element(r, c);
			cout << "data: " << *(int*)temp <<endl;
 		}
 	}		

 	cout << "-----------" <<endl;


 	for (int r = 0; r<2; r++){
 		for (int c = 0; c<2; c++){
 			void * temp = g_def.get_boardState_element(r, c);
			cout << "boardState_data: " << *(int*)temp <<endl;
 		}
 	}	

 	return 0;

}



