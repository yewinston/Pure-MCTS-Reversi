#include <iostream>
#include <vector>
#include <string>

#include "board.h"

using namespace std;

// Default constructor
Board::Board(){
    cout << "Default board being made\n";
    // X = columns
    // Y = rows
    
    vector<vector<int>> new_board({{0, 0, 0, 0, 0, 0, 0, 0 }, 
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 1, 2, 0, 0, 0 },
                                    {0, 0, 0, 2, 1, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 },
                                    {0, 0, 0, 0, 0, 0, 0, 0 } });
    // vector<vector<int>> new_board({{0, 0, 0, 0, 0, 0, 0, 0 }, 
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 2, 1, 0, 0, 0 },
    //                             {0, 0, 2, 1, 2, 0, 0, 0 },
    //                             {0, 0, 2, 0, 0, 0, 0, 0 },
    //                             {0, 0, 2, 0, 0, 0, 0, 0 },
    //                             {0, 0, 0, 0, 0, 0, 0, 0 } });
    game_board = new_board;
    black_score = 0;
    white_score = 0;
}

Board::Board(vector<vector<int>> new_board, int b_score, int w_score){
    cout << "Using a pre-made board\n";
    game_board = new_board;
    white_score = w_score;
    black_score = b_score;
}

void Board::print_board() {
    int n = 8; 
    int m = 8;

    bool debug = true;

    cout << "\n    A   B   C   D   E   F   G   H" << endl;
    cout << "\n    0   1   2   3   4   5   6   7" << endl;

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

bool Board::check_valid_line(int player, int delta_x, int delta_y, int x_start, int y_start){
    
    if (game_board[x_start][y_start] == player) {
        return true;
    } 

    if (game_board[x_start][y_start] == 0){
        return false;
    }

    if ((x_start + delta_x < 0) || (x_start + delta_x > 7)){
        return false;
    }

    if ((y_start + delta_y < 0) || (y_start + delta_y > 7)){
        return false;
    }

    return check_valid_line(player, delta_x, delta_y, x_start + delta_x, y_start + delta_y); 
}

bool Board::is_valid_move(int player, int delta_x, int delta_y, int x_start, int y_start){
    
    int other_player;


    if (player == 1) {
        other_player = 2;
    }
    else if (player == 2) {
        other_player = 1;
    }
    else {
        cout << "error" << endl;
        return false;
    }
    
    // checks if the piece moves off the board
    if ((x_start + delta_x < 0) || (x_start + delta_x > 7)){
        return false;
    }

    if ((y_start + delta_y < 0) || (y_start + delta_y > 7)){
        return false;
    }
    // check if it is touching the other players piece
    if (game_board[x_start + delta_x][y_start + delta_y] != other_player){
        return false;
    }
    return check_valid_line(player, delta_x, delta_y, x_start + delta_x + delta_x, y_start + delta_y + delta_y); 
}

// returns all valid moves
// [ [x1, y2], [x2, y2], ... ,[xn, yn] ] 
// new_game.legal_moves = valid_moves('1/2 player', board)
vector<vector<int>> Board::valid_moves(int player) {
    vector<vector<int>> valid;

    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (game_board[y][x] == 0) {
                bool north_west = is_valid_move(player, -1, -1, y, x);
                bool north = is_valid_move(player, -1, 0, y, x);
                bool north_east = is_valid_move(player, -1, 1, y, x);

                bool west = is_valid_move(player, 0, -1, y, x);
                bool east = is_valid_move(player, 0, 1, y, x);

                bool south_west = is_valid_move(player, 1, -1, y, x);
                bool south = is_valid_move(player, 1, 0, y, x);
                bool south_east = is_valid_move(player, 1, 1, y, x);

                if (north_west || north || north_east || west || east || south_west || south || south_east){
                    vector<int> position;         
                    position.push_back(x);
                    position.push_back(y);
                    valid.push_back(position);
                }
            }
        }
    }
    return valid;
}

void Board::make_move(int player, vector<int> position){
    // TODO: NEEDS ERROR CHECKING

    cout << "player number is: " << player << endl;
    cout << " x: " << position[0] << "y: " << position[1] << endl;

    game_board[position[1]][position[0]] = player;

    cout << game_board[position[1]][position[0]] << endl;

    return;
}

void Board::flip_tiles(int player, vector<int> position) {
    int x = position[0];
    int y = position[1];

    flip_line(player, -1, -1, y, x);
    flip_line(player, -1, 0, y, x);
    flip_line(player, -1, 1, y, x);

    flip_line(player, 0, -1, y, x);
    flip_line(player, 0, 1, y, x);

    flip_line(player, 1, -1, y, x);
    flip_line(player, 1, 0, y, x);
    flip_line(player, 1, 1, y, x);

    return;
}

bool Board::flip_line(int player, int delta_x, int delta_y, int x_start, int y_start) {

    if ((x_start + delta_x < 0) || (x_start + delta_x > 7)){
        return false;
    }

    if ((y_start + delta_y < 0) || (y_start + delta_y > 7)){
        return false;
    }

    if (game_board[x_start + delta_x][y_start + delta_y] == 0) {
        return false;
    }

    if (game_board[x_start + delta_x][y_start + delta_y] == player) {
        return true;
    }
    else {
        if (flip_line(player, delta_x, delta_y, x_start + delta_x, y_start + delta_y)){
            game_board[x_start + delta_x][y_start + delta_y] = player;
            return true;
        }
        else {
            return false;
        }
    }
}



vector<int> Board::get_score() {
    vector<int> scores;
    return scores;
};