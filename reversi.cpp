#include <iostream>

#include "board.h"
#include "game.h"
#include "reversibot.h"

using namespace std;

int main(){
    int weighted_wins = 0;
    int dumb_wins = 0;
    int ties = 0;
    for(int i = 0; i < 10; i++){
        Game new_game;
        bool game_over = false;

        //std::chrono::microseconds sec(4999000);
        std::chrono::microseconds sec(2999000);
        chrono::microseconds::rep max_time = chrono::duration_cast<chrono::microseconds>(sec).count();

        //chrono::microseconds::rep max_time = 4us; 

        while(game_over == false) {
            // player code
            // new_game.print_status();
            // new_game.move_input();
            // new_game.print_status();
            // game_over = new_game.check_end();

            // random ai
            //new_game.print_status();
            ReversiBot bot_weight = ReversiBot(1, true, max_time);
            vector<vector<int>> mcts_results = bot_weight.pure_mcts(new_game.get_board());
            vector<int> weight_move = bot_weight.determine_weighted_move(mcts_results);
            new_game.ai_move(bot_weight.get_bot(), weight_move);
            //new_game.print_status();
            game_over = new_game.check_end();

            if(game_over == false){
                ReversiBot bot = ReversiBot(2, false, max_time);
                //cout << "Playout time in main: " << max_time << endl;
                vector<vector<int>> mcts_results = bot.pure_mcts(new_game.get_board());
                vector<int> best_move = bot.determine_best_move(mcts_results);
                // vector<int> best_move = bot.determine_weighted_move(mcts_results);

                // cout << "Best move:" << endl;
                // cout << "X: " << best_move[0] << ", Y:" << best_move[1] << ", Wins:" << best_move[2] <<", Loss:" << best_move[3] << ", Ties:" << best_move[4] << endl; 
                
                // cout << "board before AI makes move" << endl;
                // new_game.print_status();

                new_game.ai_move(bot.get_bot(), best_move);

                game_over = new_game.check_end();
            }
        }
        new_game.print_status();
        int end_result = new_game.get_board().check_victory(new_game.get_board().get_turn());
        cout << "results for game: " << i << endl;
        if(end_result == 1){
            cout << "X wins!" << endl;
            weighted_wins++;
        }
        else if(end_result == 2){
            cout << "O wins" << endl;
            dumb_wins++;
        }
        else if(end_result == -1){
            cout << "Tie!" << endl;
            ties++;
        }
    }
    cout << "Smart AI wins:" << weighted_wins << ", Loses: " << dumb_wins << endl;
    cout << "Dumb AI wins:" << dumb_wins << ", Loses" << weighted_wins << endl;
    cout << "Total ties:" << ties << endl;
    return 0;
}