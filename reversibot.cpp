#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <stdlib.h>

#include "reversibot.h"
#include "board.h"

using namespace std;

ReversiBot::ReversiBot(int player, chrono::microseconds::rep playout_time){
    bot_player = player;
    time_of_playouts = playout_time;
}

int ReversiBot::get_bot(){
    return bot_player;
}

// Pure MCTS
vector<vector<int>> ReversiBot::pure_mcts(Board game_board){
    chrono::microseconds::rep time_playouts = time_of_playouts;
    bool initial_move = true;
    bool times_up = false;
    // int playouts = 0;

    // Determine valid moves
    vector<vector<int>> valid = game_board.valid_moves(bot_player);
    // Holds the result of the valid move in the format: [X, Y, Wins, Loss, Ties]
    vector<vector<int>> result;

    for(int j = 0; j < valid.size(); j++){
        vector<int> stat{valid[j][0], valid[j][1], 0, 0, 0};
        result.push_back(stat);
    }

    chrono::steady_clock::time_point playout_begin = std::chrono::steady_clock::now();

    while(!times_up){
        // Perform random playouts on valid moves, stop when reach max playout time
        for(int i = 0; i < valid.size(); i++){
            // Get a temporary, deep copied board to work with
            vector<int> score = game_board.get_score();
            Board temp_board(game_board.get_board(), score[0], score[1], game_board.get_turn());

            while(temp_board.check_victory(temp_board.get_turn()) == 0){
                if(initial_move){
                    // cout << "initial move" << endl;
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
                // temp_board.print_board();
            }
            // -1 = tie, 1 = black win, 2 = white win
            int game_result = temp_board.check_victory(temp_board.get_turn());
            
            // [X, Y, Win (2), Loss (3), Ties (4)]
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
            
            // check clock, time elapsed > max time
            chrono::steady_clock::time_point playout_end = std::chrono::steady_clock::now();
            chrono::microseconds::rep duration = chrono::duration_cast<chrono::microseconds>(playout_end - playout_begin).count();
            //cout << "Duration: " << duration << endl;
            //cout << "Playout time at end of loop: " << time_of_playouts << endl;
            if(duration >= time_of_playouts){
                //cout << "Total duration: " << duration << endl;
                times_up = true;
            }
        }
        // playouts++;
    }
    //cout << "Total number of playouts: " << playouts << endl;
    return result;
}

// Sorts the result vector in descending order, based on wins, then ties, then loses
bool win_sort(vector<int> a, vector<int> b){
    // If wins are the same, prioritze most ties
    if(a[2] == b[2]){
        // If ties are the same, prioritize least loses
        if(a[4] == b[4]){
            return(a[3] < b[3]);
        }
        // Prioritize ties
        else{
            return(a[4] > b[4]);
        }
    }
    // Prioritize wins
    return (a[2] > b[2]);
}

// Sorts the result vector in descending order, based on weight, then wins + ties
bool weight_sort(vector<int> a, vector<int> b){
    // If weights are the same, prioritize wins + ties
    if(a[2] == b[2]){
        return(a[3] > b[3]);
    }
    // Prioritze weights
    return (a[2] > b[2]);
}

vector<int> ReversiBot::determine_best_move(vector<vector<int>> result) {
    vector<int> best_move;
    vector<vector<int>> tie_breaker;
    int win_max;

    sort(result.begin(), result.end(), win_sort);

    win_max = result[0][2];
    tie_breaker.push_back(result[0]);

    // Find all positions that have wins == win_max
    // Solves case where all positions have a win == 0
    for(int i = 1; i < result.size(); i++){
        if(win_max == result[i][2]){
            tie_breaker.push_back(result[i]);
        }
    }

    // If there are multiple positions with same number of wins, pick a random one among them
    if(tie_breaker.size() > 1){
        srand(time(0));
        best_move = tie_breaker[rand() % tie_breaker.size()];
    }
    else{
        best_move = result[0];
    }

    return best_move;
}

vector<int> ReversiBot::determine_weighted_move(vector<vector<int>> result){
    vector<vector<int>> weight_board({ {4, -3, 2, 2, 2, 2, -3, 4}, 
                                    {-3, -4, -1, -1, -1, -1, -4, -3},
                                    {2, -1, 1, 0, 0, 1, -1, 2},
                                    {2, -1, 0, 1, 1, 0, -1, 2},
                                    {2, -1, 0, 1, 1, 0, -1, 2},
                                    {2, -1, 1, 0, 0, 1, -1, 2},
                                    {-3, -4, -1, -1, -1, -1, -4, -3},
                                    {4, -3, 2, 2, 2, 2, -3, 4} });

    vector<vector<int>> weighted_result;

    for(int i = 0; i < result.size(); i++){
        int weight = weight_board[result[i][1]][result[i][0]]; 
        vector<int> weighted_position{result[i][0], result[i][1], weight, result[i][2] + result[i][3]};

        weighted_result.push_back(weighted_position);
    }

    sort(weighted_result.begin(), weighted_result.end(), weight_sort);

    return weighted_result[0];
}