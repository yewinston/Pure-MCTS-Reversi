#include <iostream>

#include "board.h"
#include "game.h"
#include "reversibot.h"

using namespace std;

int main(){
    Game new_game;
    
    new_game.move_input();

    new_game.print_status();

    ReversiBot bot = ReversiBot(2, false, 100);

    bot.pure_mcts(new_game.get_board());

    return 0;
}