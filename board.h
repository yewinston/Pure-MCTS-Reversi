#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

using namespace std;

class Board{
    private:

    public:
        vector<vector<int>> board;

        void print_board();

        // 1 - black, 2 - white
        int whos_turn();

        // returns all valid moves
        // [ [x1, y2], [x2, y2], ... ,[xn, yn] ] 
        vector<int> valid_moves();

        // [black score, white score]
        vector<int> get_score();

        int check_victory();

        void make_move(int player, vector<int> position);
        
};

#endif
