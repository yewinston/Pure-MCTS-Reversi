#include <iostream>

#include "board.h"
#include "game.h"
#include "reversibot.h"

using namespace std;

int main(){
    // Maximum Time for playouts
    std::chrono::microseconds sec(4999000);
    // std::chrono::microseconds sec(2999000);
    chrono::microseconds::rep max_time = chrono::duration_cast<chrono::microseconds>(sec).count();

    Game new_game;
    bool game_over = false;

    // Start by asking user what they want to do
    // Pure MCTS AI - Go first (1), Go second (2)
    // MCTS + weights - Go first (3), Go second (4)
    // Simulate AI - MCTS first (5), Static Weights first (6)
    int game_type = new_game.set_game();
    bool use_heuristic = false;

    if((game_type == 3)||(game_type == 4)){
        use_heuristic = true;
    }

    // Player goes first against AI
    if((game_type == 1)||(game_type == 3)){
        while(!game_over){
            // Player 
            new_game.print_status();
            new_game.move_input();
            new_game.print_status();
            game_over = new_game.check_end();

            // Pure MCTS AI
            if(game_over == false){
                ReversiBot bot = ReversiBot(2, max_time);
                cout << "AI is thinking..." << endl;
                vector<vector<int>> mcts_results = bot.pure_mcts(new_game.get_board());
                vector<int> best_move;

                if(use_heuristic){
                     best_move = bot.determine_best_move(mcts_results);
                }
                else{
                    best_move = bot.determine_weighted_move(mcts_results);
                }
                cout << "AI has made a move!" << endl;
                new_game.ai_move(bot.get_bot(), best_move);
                game_over = new_game.check_end();
            }
        }
    }

    // Player goes second against AI
    else if((game_type == 2)||(game_type == 4)){
        while(!game_over){
            new_game.print_status();

            // Pure MCTS AI
            ReversiBot bot = ReversiBot(1, max_time);
            cout << "AI is thinking..." << endl;
            vector<vector<int>> mcts_results = bot.pure_mcts(new_game.get_board());
            vector<int> best_move;

            if(use_heuristic){
                best_move = bot.determine_best_move(mcts_results);
            }
            else{
                best_move = bot.determine_weighted_move(mcts_results);
            }
            new_game.ai_move(bot.get_bot(), best_move);
            cout << "AI has made a move!" << endl;
            game_over = new_game.check_end();

            // Player 
            if(game_over == false){
                new_game.print_status();
                new_game.move_input();
                game_over = new_game.check_end();
            }
        }
    }
    
    // AI without heuristics goes first
    else if(game_type == 5){
        while(!game_over){
            new_game.print_status();

            // AI without heuristics
            ReversiBot bot = ReversiBot(1, max_time);

            cout << "AI without heuristics is thinking..." << endl;
            vector<vector<int>> mcts_results = bot.pure_mcts(new_game.get_board());
            vector<int> best_move = bot.determine_best_move(mcts_results);

            cout << "AI without heuristics made a move!" << endl;
            new_game.ai_move(bot.get_bot(), best_move);
            game_over = new_game.check_end();

            // AI with heuristics
            if(game_over == false){
                new_game.print_status();

                ReversiBot w_bot = ReversiBot(2, max_time);

                cout << "AI with static weights is thinking..." << endl;
                vector<vector<int>> mcts_results = w_bot.pure_mcts(new_game.get_board());
                vector<int> weight_move = w_bot.determine_weighted_move(mcts_results);

                cout << "AI with static weights made a move!" << endl;
                new_game.ai_move(w_bot.get_bot(), weight_move);
                game_over = new_game.check_end();
            }
        }
    }

    // AI with heuristics goes first
    else if(game_type == 6){
        while(!game_over){
            new_game.print_status();

            ReversiBot w_bot = ReversiBot(2, max_time);
            cout << "AI with static weights is thinking..." << endl;
            vector<vector<int>> mcts_results = w_bot.pure_mcts(new_game.get_board());
            vector<int> weight_move = w_bot.determine_weighted_move(mcts_results);

            cout << "AI with static weights made a move!" << endl;
            new_game.ai_move(w_bot.get_bot(), weight_move);
            game_over = new_game.check_end();

            // AI with heuristics
            if(game_over == false){
                new_game.print_status();

                // AI without heuristics
                ReversiBot bot = ReversiBot(1, max_time);

                cout << "AI without heuristics is thinking..." << endl;
                vector<vector<int>> mcts_results = bot.pure_mcts(new_game.get_board());
                vector<int> best_move = bot.determine_best_move(mcts_results);

                cout << "AI without heuristics made a move!" << endl;
                new_game.ai_move(bot.get_bot(), best_move);
                game_over = new_game.check_end();
            }
        }
    }

    new_game.print_status();
    int end_result = new_game.get_board().check_victory(new_game.get_board().get_turn());

    if(end_result == 1){
        cout << "X wins!" << endl;
    }
    else if(end_result == 2){
        cout << "O wins!" << endl;
    }
    else if(end_result == -1){
        cout << "Tie!" << endl;
    }

    return 0;
}