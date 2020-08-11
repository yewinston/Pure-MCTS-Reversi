#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board{
    private:
        std::vector<std::vector<int>> game_board;
        int black_score;
        int white_score;
        int turn;
        
    public:
        // Default constructor:
        // Will create a 8x8 board that 
        Board();

        // Parameterized Constructor 
        Board(std::vector<std::vector<int>> new_board, int b_score, int w_score, int whose_turn);

        // Returns a deep copied game board
        std::vector<std::vector<int>> get_board();

        // Prints the board 
        void print_board();

        void flip_turn();
        
        // Returns the current turn order in the format:
        // 1 == black's turn (X), 2 == white's turn (O)
        int get_turn();

        // Given the player, the position, and the delta of the position, returns true if
        // the move is valid or false if it isn't.
        bool is_valid_move(int player, int delta_x, int delta_y, int x_start, int y_start);

        // Checks boundaries
        bool check_valid_line(int player, int delta_x, int delta_y, int x_start, int y_start);

        // Flips the tiles associated with a position and the player
        void flip_tiles(int player, std::vector<int> position);

        // Flips a connected line based on the player
        bool flip_line(int player, int delta_x, int delta_y, int x_start, int y_start);

        // Returns a 2D vector of all valid moves in the format:
        // [ [x1, y2], [x2, y2], ... , [xn, yn] ] 
        std::vector<std::vector<int>> valid_moves(int player);

        // Given a position and the player, the function modifies the board to make a move
        void make_move(int player, std::vector<int> position);

        // Returns a vector of the current board score in the format:
        // [black score, white score] or [X's score, O's score]
        std::vector<int> get_score();

        // Updates the current scores in the game
        void update_scores();

        // Returns an integer that represents the current state of the game in the format:
        // 0 == no victory, 1 == black (X), 2 == white (O), -1 == tie
        int check_victory(int whos_turn);
};

#endif
