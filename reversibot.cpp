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
    vector<vector<int>> result;

    // determine valid moves
    vector<vector<int>> valid = game_board.valid_moves(bot_player);
    bool initial_move = true;

    for(int j = 0; j < valid.size(); j++){
        vector<int> stat{valid[j][0], valid[j][1], 0, 0, 0};
        result.push_back(stat);
    }

    int playouts = 10;

    for(int m = 0; m < playouts; m++){
        // perform random playouts on valid moves, stop when reach max playout time
        for(int i = 0; i < valid.size(); i++){
            // get a temporary, deep copied board to work with
            vector<int> score = game_board.get_score();
            Board temp_board(game_board.get_board(), score[0], score[1], game_board.get_turn());

            while(temp_board.check_victory(temp_board.get_turn()) == 0){
                if(initial_move){
                    cout << "initial move" << endl;
                    temp_board.make_move(bot_player, valid[i]);
                    initial_move = false;
                }
                else{
                    vector<vector<int>> next_moves = temp_board.valid_moves(temp_board.get_turn());
                    // cout << "Printing valid MCTS moves:" << endl;
                    // for(int i = 0; i < next_moves.size(); i++){
                    //     cout << "X:" << next_moves[i][0] << " Y: " << next_moves[i][1] << endl;
                    // }
                    srand(time(0)); // seed random number generator
                    vector<int> rand_position = next_moves[rand() % next_moves.size()];
                    temp_board.make_move(temp_board.get_turn(), rand_position);
                }
                temp_board.print_board();
            }
            // -1 = tie, 1 = black win, 2 = white win
            int game_result = temp_board.check_victory(temp_board.get_turn());
            
            // [x, y, Win (2), Loss (3), Ties (4)]
            // If the AI wins
            if(game_result == bot_player){
                result[i][2] += 1;
            }
            // If the AI ties
            else if(game_result == -1){
                result[i][4] += 1;
            }
            // If the AI loses
            else{
                result[i][3] += 1;
            }
        }

        for(int k = 0; k < result.size(); k++){
            cout << "X: " << result[k][0] << " Y:" << result[k][1] << endl;
            cout << "Wins: " << result[k][2] << ", Losses: " << result[k][3] << ", Ties: " << result[k][4] << endl;

        }
        for (int i = 0; i < result.size(); i++) {
            vector<int> best_move;
            best_move.push_back(result[i][2]);
            for (int k = i + 1; k < result.size(); k++) {
                if (result[i][2] > result[k][2]) {
                    cout << "bigger" << endl;
                }
                else {
                    cout << "smaller" << endl;
                }
            }
        }
    
    }

    return result;
}

vector<int> determine_best_move(vector<vector<int>> result) {
    vector<int> best_move;

    

    return best_move;
}

vector<vector<int>> ReversiBot::heuristics(Board game_board) {

    // get list of valid moves
    vector<vector<int>> valid = game_board.valid_moves(bot_player);

    // always go for a corner piece if available
    // [0,0] [0,7] [7,0] [7,7]
    

    
    // find the highest scoring move possible
    vector<int> best_score;
    // make a temp board
    vector<int> score = game_board.get_score();
    Board temp_board(game_board.get_board(), score[0], score[1], game_board.get_turn());

    // make move from valid moves
    for(int i = 0; i < valid.size(); i++) {
        temp_board.make_move(bot_player, valid[i]);
        // get score of board after move was taken
        vector<int> temp_score = temp_board.get_score();
        // compare the scores
        if(temp_score > best_score) {
            best_score = temp_score;
        }
    }

}