#include <iostream>
#include <vector>
#include <string>

#include "board.h"

using namespace std;

// Default constructor
Board::Board(){
    cout << "Default board being made\n";
    vector<vector<int>> new_board({{0, 0, 0, 0, 0, 0, 0, 0 }, 
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 1, 2, 0, 0, 0 },
                                    {0, 0, 0, 2, 1, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 } });
    game_board = new_board;
    black_score = 0;
    white_score = 0;
}

Board::Board(vector<vector<int>> new_board, int w_score, int b_score){
    cout << "Using a pre-made board\n";
    game_board = new_board;
    white_score = w_score;
    black_score = b_score;
}

void Board::print_board() {
    int n = 8; 
    int m = 8;

    bool debug = false;

    cout << "\n    A   B   C   D   E   F   G   H" << endl;
    for (int i = 0; i < n; i++) { 
        cout <<"   -------------------------------- "<< endl;
        cout << i << " ";
        
        for (int j = 0; j < m; j++) {
            if(debug){
                cout << "| " << game_board[i][j] << " ";
            }
            else{
                if(game_board[i][j] == 0){
                    cout << "|   ";
                }
                else if(game_board[i][j] == 1){
                    cout << "| X ";
                }
                else if(game_board[i][j] == 2){
                    cout << "| O ";
                }
            }
        }
        cout << "| \n"; 
    } 
    cout <<"   -------------------------------- " << endl;
} 

vector<int> Board::valid_moves() {
    vector<int> valid;
    return valid;
}

vector<int> Board::get_score() {
    vector<int> scores;
    return scores;
};