#include <vector>
#include <string>
#include <iostream>
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

bool Game::check_end(Board the_board) {
    vector<int> moves_left = the_board.valid_moves();
    
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

}

// parses user input and determines if move is valid
// return true if valid
bool Game::is_valid_move(vector<int> position) {
    return 0;
}

// prints score and the board
void Game::print_status(Board the_board) {
    print_score(the_board);
    the_board.print_board();
    cout << endl;
}