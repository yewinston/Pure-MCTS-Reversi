#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board{
    private:
        std::vector<std::vector<int>> game_board;
        int black_score;
        int white_score;
    public:
        // Default constructor
        Board();

        // Parameterized Constructor 
        Board(std::vector<std::vector<int>> new_board, int white_score, int black_score);

        void print_board();

        // 1 - black, 2 - white
        int whos_turn();

        // returns all valid moves
        // [ [x1, y2], [x2, y2], ... ,[xn, yn] ] 
        std::vector<int> valid_moves();

        // [black score, white score]
        std::vector<int> get_score();

        int check_victory();

        void make_move(int player, std::vector<int> position);
};

#endif
