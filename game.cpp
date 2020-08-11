#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "board.h"
#include "game.h"

using namespace std;

bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

Board Game::get_board(){
    return game_board;
}

// start game: do you want to play against a bot
// if yes -> coin flip: who goes first
// set players to colours accordingly
void Game::set_game() {
    int game_choice = 0;
    string user_input;

    cout << "Reversi - 310 Final Project\nMarian Nguyen (mna68@sfu.ca), Winston Ye (winstony@sfu.ca)\n";
    while(game_choice == 0) {
        cout << "Enter the number corresponding to the gamemode you wish to start:\n";
        cout << "\t1. Play against an AI without heuristics\n" << "\t2. Play against an AI with heuristics\n" << "\t3. Simulate a game (heuristic AI vs no heuristic AI)\n\n";
        cout << "> ";
        cin >> user_input;

        if(is_number(user_input)){
            game_choice = stoi(user_input);
            if((game_choice < 4) && (game_choice > 0)){
                if(game_choice == 1){

                    cout << "Would you like to go first? (Y/N) ";
                    cin >> user_input;
                    if (user_input == "Y" | user_input == "y")
                        cout << "Player wants to go first" << endl;
                    else if (user_input == "N" | user_input == "n")
                        cout << "Player wants to go second" << endl;
                    else {
                        // cout << "Invalid Input.." << endl;
                        // cout << "Would you like to go first? (Y/N) ";
                        // cin >> user_input;
                    }
                    
                }
                else if(game_choice == 2){
                    cout << "harder AI" << endl;
                }
                else if(game_choice == 3){
                    cout << "sim game" << endl;
                }
            }
            else{
                cout << "Error: input is not an option from (1-3)\n";
                game_choice = 0;
            }
        }
        else{
            cout << "Error: expected a number, input is not a valid.\n";
        }
    }
}

// sim_game - simulate game against 2 bots
// go_first - does player want to go first?
void Game::start_game(bool sim_game, bool go_first) { 

}

bool Game::check_end() {
    vector<vector<int>> moves_left = game_board.valid_moves(game_board.get_turn());
    
    if(moves_left.size() == 0){
        return true;
    }
    return false;
}

void Game::print_score(Board the_board) {
    vector<int> scores = the_board.get_score();
    cout << "Black score (X): " << scores[0] << endl;
    cout << "White score (O): " << scores[1] << endl;
}


// player is asked what move they want to make
void Game::move_input() {
    string user_input;
    vector<char> valid_alpha{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    bool valid_input = false;
    
    cout << "It's your turn! Type a coordinate in the format '[A-H][0-7]':" << endl;
    
    // parse user_input;
    while(!valid_input){
        cin >> user_input;

        // check if input is correct length
        if(user_input.size() != 2){
            cout << "Error: expected input of length 2, received input of length " << user_input.size() << endl;
        }
        
        // check if first character is alphabetical
        else if(!isalpha(user_input[0])){
            cout << "Error: first character '" << user_input[0] << "' is not alphabetical." << endl;
        }
        // if first character is alphabetical, change it to uppercase
        else{
            user_input[0] = toupper(user_input[0]);
            vector<char>::iterator find_char;

            find_char = find(valid_alpha.begin(), valid_alpha.end(), user_input[0]);

            // if the first character is found within our valid_alpha vector
            if(find_char != valid_alpha.end()){
                char test_num = user_input[1];
                if(isdigit(test_num)){
                    int y_pos = (test_num - '0') % 48;
                    if((y_pos >= 0) && (y_pos < 8)){
                        //cout << "valid input! X:" << find_char - valid_alpha.begin() << " Y: " << y_pos << endl;
                        
                        int x_pos = find_char - valid_alpha.begin();
                        vector<int> position{x_pos, y_pos};

                        bool valid_move = move_validate(position);
                        
                        if(valid_move){
                            game_board.make_move(1, position);
                            valid_input = true;
                        }
                        else{
                            cout << "Error: invalid position" << endl;
                        }
                    }
                    else{
                        cout << "Error: second character '" << user_input[1] << "' is not in range (0-7)" << endl;
                    }
                }
                else{
                    cout << "Error: second character '" << user_input[1] << "' is not a digit" << endl;
                }
            }
            else{
                cout << "Error: first character '" << user_input[0] << "' is not in alphabet range of [A-H]." << endl;
            }
        }
    }
}

void Game::ai_move(int bot_player, vector<int> position){
    game_board.make_move(bot_player, position);
}

// parses user input and determines if move is valid
// return true if valid
bool Game::move_validate(vector<int> position) {
    vector<vector<int>> valid_moves = game_board.valid_moves(1);

    for(int i = 0; i < valid_moves.size(); i++){
        if(valid_moves[i][0] == position[0]){
            if(valid_moves[i][1] == position[1]){
                return true;
            }
        }
    }

    return false;
}

// prints score and the board
void Game::print_status() {
    // print_score(the_board);
    game_board.print_board();
    cout << endl;
}