#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "board.h"
#include "reversibot.h"

class Game {
    private:
        // 1 - black,  2 - white, 0 - empty
        int turn;

        Board game_board;

    public:
        // start game: do you want to play against a bot
        // if yes -> coin flip: who goes first
        // set players to colours accordingly
        void set_game();
        
        // sim_game - simulate game against 2 bots
        // go_first - does player want to go first?
        void start_game(bool sim_game, bool go_first);
        
        bool check_end(Board the_board);

        void print_score(Board the_board);

        // player is asked what move they want to make
        void move_input();

        // parses user input and determines if move is valid
        // return true if valid
        bool is_valid_move(std::vector<int> position);

        // prints score and the board
        void print_status(Board the_board);
};

#endif
