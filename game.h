#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

#include "board.h"
#include "reversibot.h"

class Game {
    private:
        Board game_board;
        int player;

    public:
        // Returns the game_board, shallow copy
        Board get_board();

        // Set's the game up by receiving user input. Determines who goes first as well as
        // if a game is being played or if simulations will be done.
        int set_game();
        
        // Returns true if game is over, which is when the current player has no longer
        // has any more moves left. Returns false otherwise.
        bool check_end();

        // Receives the user's input for a game move and validates if it is correct
        void move_input();

        // Parses the user input and determines if the input and move is valid
        // Returns true if valid, false otherwise
        bool move_validate(std::vector<int> position);

        // Given the bot_player (1/2) and a position [x, y], makes the move on the board
        void ai_move(int bot_player, std::vector<int> position);

        // Prints the current game score
        void print_score(Board the_board);

        // Prints the score and the board
        void print_status();
};

#endif
