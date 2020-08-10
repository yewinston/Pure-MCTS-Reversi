#ifndef REVERSIBOT_H
#define REVERSIBOT_H

#include <vector>
#include "board.h"

class ReversiBot{
    private:
        // max playout time in ms
        int playout_time;

        // 1 - black,  2 - white
        int bot_player;

        bool use_heuristics;

        // [[Wins, Loss, Ties], ...,[Wins, Loss, Ties]]
        // for each valid move the AI can make
        std::vector<std::vector<int>> result;

    public:
        ReversiBot(int player, bool use_heuristic, int playout_time);

        // Takes a position [x,y] and returns true if action is made
        // Returns false if action cannot be made
        bool make_action(std::vector<int> position);

        // determine heuristic later, just a placeholder
        std::vector<std::vector<int>> pure_mcts(Board game_board);

        // determine best move, used after pure_mcts
        // resolves tie-breakers, focuses on Wins and Ties
        std::vector<int> determine_best_move(std::vector<std::vector<int>>);
};

#endif