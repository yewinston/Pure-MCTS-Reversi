#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "game.h"

bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// start game: do you want to play against a bot
// if yes -> coin flip: who goes first
// set players to colours accordingly
void set_game() {
    int game_choice = 0;
    string user_input;

    cout << "Reversi - 310 Final Project\nMarian Nguyen (@sfu.ca), Winston Ye (winstony@sfu.ca)\n";
    while(game_choice == 0) {
        cout << "Enter the number corresponding to the gamemode you wish to start:\n";
        cout << "\t1. Play against an AI without heuristics\n" << "\t2. Play against an AI with heuristics\n" << "\t3. Simulate a game (heuristic AI vs no heuristic AI)\n\n";
        cout << "> ";
        cin >> user_input;

        if(is_number(user_input)){
            game_choice = stoi(user_input);
            if((game_choice < 4) && (game_choice > 0)){
                if(game_choice == 1){
                    cout << "AI" << endl;
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
void start_game(bool sim_game, bool go_first) { 

}


bool check_end() {
    return 0;
}

void print_score() {

}

// player is asked what move they want to make
void move_input() {

}

// parses user input and determines if move is valid
// return true if valid
bool is_valid_move(vector<int> position) {
    return 0;
}

// prints score and the board
void print_status() {
    
}


int main(){
    set_game();
    return 0;
}