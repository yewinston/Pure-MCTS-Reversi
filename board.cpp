 #include <iostream>
#include <vector>
#include <string>

#include "board.h"

using namespace std;

// Default constructor
Board::Board(){
    // cout << "Default board being made\n";
    // X = columns
    // Y = rows
    
    vector<vector<int>> new_board({ {0, 0, 0, 0, 0, 0, 0, 0 }, 
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
    turn = 1; // temporary
}

Board::Board(vector<vector<int>> new_board, int b_score, int w_score, int whose_turn){
    // cout << "Using a pre-made board\n";
    game_board = new_board;
    white_score = w_score;
    black_score = b_score;
    turn = whose_turn;
}

vector<vector<int>> Board::get_board(){
    vector<vector<int>> copy_board(game_board.size());
    copy(game_board.begin(), game_board.end(), copy_board.begin());
    return game_board;
}

void Board::print_board() {
    int n = 8; 
    bool debug = false;
    
    vector<vector<int>> moves = valid_moves(turn);
    vector<vector<char>> moves_board(n, vector<char>(n, '0'));

    for(int i = 0; i < moves.size(); i++){
        moves_board[moves[i][1]][moves[i][0]] = '#';
    }

    cout << endl << "\n    A   B   C   D   E   F   G   H" << endl;
    cout << "\n    0   1   2   3   4   5   6   7" << endl;

    for (int i = 0; i < n; i++) { 
        cout << "   -------------------------------- "<< endl;
        cout << i << " ";
        
        for (int j = 0; j < n; j++) {
            if(debug){
                cout << "| " << game_board[i][j] << " ";
            }
            else{
                if(moves_board[i][j] == '#'){
                    cout << "| * ";
                }
                else if(game_board[i][j] == 0){
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
    cout << "   -------------------------------- " << endl;
} 

int Board::get_turn(){
    return turn;
}

void Board::flip_turn(){
    if(turn == 1){
        turn = 2;
    }
    else{
        turn = 1;
    }
}

bool Board::check_valid_line(int player, int delta_x, int delta_y, int x_start, int y_start){
    //cout << "check_valid_line function starts" << endl;

    //cout << "x-start: " << x_start << " y-start: " << y_start << endl;

    if ((x_start + delta_x < 0) || (x_start + delta_x > 7)){

        return false;
    }

    if ((y_start + delta_y < 0) || (y_start + delta_y > 7)){
        return false;
    }

    if (game_board[x_start][y_start] == player) {
        //cout << "game board[x][y] == player returns true" << endl;
        return true;
    } 

    if (game_board[x_start][y_start] == 0){
        //cout << "game board[x][y] == 0 returns false" << endl;
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
        cout << "player == "<< player << endl;
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

    //cout << "Player: " << player  << " made move: " << "X: " << position[0] << " Y: " << position[1] << endl;
    // if (player == 2)
    // {
    //     cout << "Player: " << player  << " made move: " << "X: " << position[0] << " Y: " << position[1] << endl;
    // }
    
    game_board[position[1]][position[0]] = player;
    flip_tiles(player, position);
    flip_turn();
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
    update_scores();
    vector<int> scores{black_score, white_score};
    return scores;
};

void Board::update_scores() {
    int b_score = 0;
    int w_score = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(game_board[i][j] == 1){
                b_score += 1;
            }
            else if(game_board[i][j] == 2){
                w_score += 1;
            }
        }
    }
    black_score = b_score;
    white_score = w_score;
}

int Board::check_victory(int whos_turn){
    update_scores();

    vector<vector<int>> moves = valid_moves(whos_turn);
    // cout << "Black score: " << black_score << " White score: " << white_score << endl;
    // cout << "Moves left for " << whos_turn << ": " << moves.size() << endl;
    if(moves.size() == 0){
        if(black_score > white_score){
            // cout << "Black wins" << endl;
            return 1;
        }
        else if(black_score < white_score){
            // cout << "White wins" << endl;
            return 2;
        }
        else if(black_score == white_score){
            // cout << "Tie" << endl;
            return -1;
        }
    }
    return 0;
}