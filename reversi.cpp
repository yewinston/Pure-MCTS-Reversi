#include <iostream>

#include "board.h"
#include "game.h"

using namespace std;

int main(){
    // Board new_board;

    // // vector<vector<int>> w_moves = new_board.valid_moves(2);
    // vector<vector<int>> b_moves = new_board.valid_moves(1);

    // // for(int i = 0; i < w_moves.size(); i++){
    // //     cout << "White, X: " << w_moves[i][0] << " Y: " << w_moves[i][1] << endl;

    // // }

    // for(int j = 0; j < b_moves.size(); j++){
    //     cout << "Black, X: " << b_moves[j][0] << " Y: " << b_moves[j][1] << endl;
    // }

    // new_board.print_board();
    
    Game new_game;

    new_game.print_status();

    new_game.move_input();

    new_game.print_status();
    // new_game.move_input();
    //new_game.set_game();
    return 0;
}