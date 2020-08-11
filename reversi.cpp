#include <iostream>

#include "board.h"
#include "game.h"
#include "reversibot.h"

using namespace std;

int main(){
    Game new_game;
    bool game_over = false;

    std::chrono::microseconds sec(4999000);
    chrono::microseconds::rep max_time = chrono::duration_cast<chrono::microseconds>(sec).count();

    //chrono::microseconds::rep max_time = 4us; 

    while(game_over == false) {
        new_game.print_status();
        new_game.move_input();
        new_game.print_status();

        game_over = new_game.check_end();

        if(game_over == false){
            ReversiBot bot = ReversiBot(2, false, max_time);
            //cout << "Playout time in main: " << max_time << endl;
            vector<vector<int>> mcts_results = bot.pure_mcts(new_game.get_board());
            vector<int> best_move = bot.determine_best_move(mcts_results);

            cout << "Best move:" << endl;
            cout << "X: " << best_move[0] << ", Y:" << best_move[1] << ", Wins:" << best_move[2] <<", Loss:" << best_move[3] << ", Ties:" << best_move[4] << endl; 
            
            // cout << "board before AI makes move" << endl;
            // new_game.print_status();

            new_game.ai_move(bot.get_bot(), best_move);

            game_over = new_game.check_end();
        }
    }
    
    int end_result = new_game.get_board().check_victory(new_game.get_board().get_turn());

    if(end_result == 1){
        cout << "X wins!" << endl;
    }
    else if(end_result == 2){
        cout << "O wins" << endl;
    }
    else if(end_result == -1){
        cout << "Tie!" << endl;
    }

    return 0;
}