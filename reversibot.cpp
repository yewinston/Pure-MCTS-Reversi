#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "reversibot.h"
#include "board.h"

using namespace std;

ReversiBot::ReversiBot(int player, bool heuristic, int playout_time){
    bot_player = player;
    use_heuristics = heuristic;
}

// Pure MCTS
vector<vector<int>> ReversiBot::pure_mcts(Board game_board){
    // determine valid moves
    vector<vector<int>> valid = game_board.valid_moves(bot_player);
    bool initial_move = true;

    // perform random playouts on valid moves, stop when reach max playout time
    for(int i = 0; i < 1; i++){
        // get a temporary, deep copied board to work with
        vector<int> score = game_board.get_score();
        Board temp_board(game_board.get_board(), score[0], score[1], game_board.get_turn());



        while(temp_board.check_victory(game_board.get_turn()) == 0){
            if(initial_move){
                cout << "initial move" << endl;
                temp_board.make_move(bot_player, valid[i]);
                initial_move = false;
            }
            else{
                cout << "turn: " << temp_board.get_turn() << endl;
                vector<vector<int>> next_moves = temp_board.valid_moves(temp_board.get_turn());
                srand(time(0)); // seed random number generator
                vector<int> rand_position = next_moves[rand() % next_moves.size()];
                temp_board.make_move(temp_board.get_turn(), rand_position);
            }

            temp_board.print_board();
        }

        cout << temp_board.check_victory(temp_board.get_turn()) << endl;
    }
    return result;
}