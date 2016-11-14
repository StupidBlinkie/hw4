//hw4_model
#include <iostream>
#include "hw4_model.h"
using namespace std;

extern "C"{
	//#include <gtk/gtk.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include "../array2d/array2d.h"
	//#include "../jansson/include/jansson.h"
}


int main(){

	int color[16] = {0, 1, 2, 3, 4, 5,
					    0, 1, 2, 3, 4, 5,
					    0, 1, 2, 3};
 	int state[4] = {1,1,1,1};

 	gameDef g_def;
 	g_def.gameID = 12345;
 	g_def.movesAllowed = 20;
 	g_def.colors = 6;
 	g_def.set_extensionColor(8, 2, color);
 	g_def.set_boardState(2,2, state);

 	cout << "id: " << g_def.gameID <<endl;
 	cout << "colors: " << g_def.colors <<endl;
 	cout << "moves allowed: " << g_def.movesAllowed <<endl;

 	for (int r = 0; r<8; r++){
 		for (int c = 0; c<2; c++){
 			void * temp = g_def.get_extensionColor_element(r, c);
			cout << "data: " << *(int*)temp <<endl;
 		}
 	}		

 	cout << "-----------" <<endl;

 	for (int r = 0; r<8; r++){
 		for (int c = 0; c<2; c++){
 			void * temp = g_def.get_boardState_element(r, c);
			cout << "data: " << *(int*)temp <<endl;
 		}
 	}		


 	return 0;

}



