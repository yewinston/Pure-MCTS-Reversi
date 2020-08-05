#ifndef REVERSIBOT_H
#define REVERSIBOT_H

#include <vector>
#include "board.h"

using namespace std;

class ReversiBot{
    private:
        int num_playouts;

        // 1 - black,  2 - white
        int player;

        // [[Wins, Loss, Ties], ...,[Wins, Loss, Ties]]
        // for each valid move the AI can make
        vector<vector<int>> result;

    public:
        Board get_board();

        // Takes a position [x,y] and returns true if action is made
        // Returns false if action cannot be made
        bool make_action(vector<int> position);

        // determine heuristic later, just a placeholder
        int determine_best_move(int heuristic);
        

        
};

#endif