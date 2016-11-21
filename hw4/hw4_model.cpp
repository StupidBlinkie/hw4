//hw4_model
////////////testing gameDef class and deserialization////////////
// #include <vector>
// #include <iostream>
// #include "hw4_model.h"

#include "hw4.h"
#include "hw4_model.h"
using namespace std;

//------for selected candy-----//
long selected_row;
long selected_col;
int selected_candy_bool = 0;
int moves_left = 30;

//-----color file names-----//


gameDef* g_def;
gameState* g_state;
candy* FIREDSPOT = new candy(-1, -1); // special candy used to fill in fired slot before applying gravity

void model_initialize(char* file){
    g_def = new gameDef();
    g_state = new gameState();

    deserialize(file);
    g_state->initialize(g_def);
}


//MODEL's INTERNAL METHODS
void deserialize2dArray(json_t *json, bool reading_first_array){
    //read rows
    cout << "deserializing first 2darray" << endl;
    json_t* json_row = json_object_get(json, "rows");
    int rows = json_integer_value(json_row); 
    //read cols
    json_t* json_col = json_object_get(json, "columns");
    int cols = json_integer_value(json_col);

    cout << "rows and cols are" << rows << " , " << cols << endl;
  
    //read json array
    json_t* json_data = json_object_get(json, "data");

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
void deserialize(char* file){

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

    g_state->initialize(g_def);
}





//game logic 


bool model_template_match(){
 
    bool find_matching = false;

    //v4  -- check 2 row is enough-----from 0 to (board height - 4 + 1) row
    for (int r = 0; r < g_state->get_rows() - 4 + 1; r++){
        for(int c = 0; c < g_state->get_cols(); c++){
            if (find_pattern_vFour(r, c)){
                cout<<"after find_pattern_vFour..r = " << r << ", c = " << c <<endl;
                g_state->update_extensionOffset(c, 4);
                find_matching = true;
            }           
        }
    }
    //h4 -- check 2 col is enough -----from 0 to (board width - 4 + 1) col
    for (int r = 0; r < g_state->get_rows(); r++){
        for(int c = 0; c < g_state->get_cols() -4 + 1; c++){
            if (find_pattern_hFour(r, c)){
                cout<<"after find_pattern_hFour..r = " << r << ", c = " << c <<endl;
                for(int count = 0 ; count < 4; count++){
                    g_state->update_extensionOffset(count + c, 1);
                }
                find_matching = true;
            }
        }
    }   
    return find_matching;
}

bool find_pattern_vFour(int row, int col){
    cout << "inside find_pattern_vFour, row = " << row << " col = " << col << endl;
    candy* curr = (candy*)g_state->get_candy_element(row, col);
    if (curr == NULL || curr->get_color() == -1){  // color = -1 means it's a firedspot
        return false;
    }

    int color = curr->get_color();
    int count = 1;

    candy* above = (candy*)g_state->get_candy_element(row + count, col);
    while (above != NULL && above->get_color() != -1 && count < 4){     
        if(above->get_color() == color){
            count++;
            above = (candy*)g_state->get_candy_element(row + count, col);
        }else{
            return false;
        }
    }

    //remove candies 
    for(int i = 0; i < count; i++){
        g_state->set_candy_element(row + i, col, FIREDSPOT); //set fired candies to FIREDSPOT in boardCandies
    }
    return true;
}
bool find_pattern_hFour(int row, int col){
    cout << "inside find_pattern_hFour, row = " << row << " col = " << col << endl;
    candy* curr = (candy*)g_state->get_candy_element(row, col);
    if (curr == NULL || curr->get_color() == -1){  // color = -1 means it's a firedspot
        return false;
    }

    int color = curr->get_color();
    int count = 1;

    candy* next = (candy*)g_state->get_candy_element(row, col + count);
    while (next != NULL && next->get_color() != -1 && count < 4){       
        if(next->get_color() == color){
            count++;
            next = (candy*)g_state->get_candy_element(row + count, col);
        }else{
            return false;
        }
    }

    //remove candies 
    for(int i = 0; i < count; i++){
        g_state->set_candy_element(row, col + i, FIREDSPOT); //set fired candies to FIREDSPOT in boardCandies
    }
    return true;
}






