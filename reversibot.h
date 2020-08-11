#ifndef REVERSIBOT_H
#define REVERSIBOT_H

#include <vector>
#include <chrono>
#include "board.h"

class ReversiBot{
    private:
        // Defines the maximum playout time in microseconds
        std::chrono::microseconds::rep time_of_playouts;
        // 1 - Black (X),  2 - White (O)
        int bot_player;
        // Determines if the bot will use heuristics
        bool use_heuristics;

    public:
        // Constructor
        ReversiBot(int player, bool use_heuristic, std::chrono::microseconds::rep playout_time);
        
        // Returns bot_player, 1 - Black (X),  2 - White (O)
        int get_bot();

        // Takes a position [x,y] and returns true if the action is made
        // Returns false if action cannot be made
        bool make_action(std::vector<int> position);

        // Pure Monte-Carlo Search Tree that will perform random playouts to completion until
        // it reaches the maximum playout time. Returns a vector of positions and playout results:
        // [X, Y, Wins, Loss, Ties]
        std::vector<std::vector<int>> pure_mcts(Board game_board);

        // Returns the best move from all the positions provided from pure_mcts.
        // Resolves tie-breakers, focuses on moves that give maximum Wins or Ties.
        std::vector<int> determine_best_move(std::vector<std::vector<int>> result);

        // Static weighting heuristic that will prioritize corners and minimize moves that will 
        // allow the opponent to pick corners. Prioritizes weight, then wins + ties.
        // Returns the best move from all the positions provided from pure_mcts. 
        std::vector<int> determine_weighted_move(std::vector<std::vector<int>> result);
};

#endif