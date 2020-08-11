#ifndef REVERSIBOT_H
#define REVERSIBOT_H

#include <vector>
#include <chrono>
#include "board.h"

class ReversiBot{
    private:
        // max playout time in ms
        std::chrono::microseconds::rep time_of_playouts;

        // 1 - black,  2 - white
        int bot_player;

        bool use_heuristics;

    public:
        ReversiBot(int player, bool use_heuristic, std::chrono::microseconds::rep playout_time);

        int get_bot();

        // Takes a position [x,y] and returns true if action is made
        // Returns false if action cannot be made
        bool make_action(std::vector<int> position);

        // determine heuristic later, just a placeholder
        std::vector<std::vector<int>> pure_mcts(Board game_board);
        std::vector<std::vector<int>> heuristics(Board game_board);

        // determine best move, used after pure_mcts
        // resolves tie-breakers, focuses on Wins and Ties
        std::vector<int> determine_best_move(std::vector<std::vector<int>> result);

        std::vector<int> determine_weighted_move(std::vector<std::vector<int>> result);
};

#endif