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
        // Default constructor
        Board();

        // Parameterized Constructor 
        Board(std::vector<std::vector<int>> new_board, int b_score, int w_score, int whose_turn);

        // might need a better name, returns a copied board
        std::vector<std::vector<int>> get_board();

        void print_board();

        void flip_turn();
        
        // 1 - black, 2 - white
        int get_turn();

        bool is_valid_move(int player, int delta_x, int delta_y, int x_start, int y_start);

        bool check_valid_line(int player, int delta_x, int delta_y, int x_start, int y_start);

        void flip_tiles(int player, std::vector<int> position);

        bool flip_line(int player, int delta_x, int delta_y, int x_start, int y_start);

        // returns all valid moves
        // [ [x1, y2], [x2, y2], ... ,[xn, yn] ] 
        std::vector<std::vector<int>> valid_moves(int player);

        void make_move(int player, std::vector<int> position);

        bool flip_board(int player, int row, int col);

        // [black score, white score]
        std::vector<int> get_score();

        void update_scores();

        // 0 - no victory, 1 - black, 2 - white
        int check_victory(int whos_turn);
};

#endif
