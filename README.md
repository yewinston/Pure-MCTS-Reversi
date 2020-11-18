# Pure MCTS Reversi
An implementation of Reversi where you can play against an AI that utilizes a [pure Monte Carlo tree search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search#Pure_Monte_Carlo_game_search) to determine the next possible move. A more difficult AI is also implemented that utilizes a [static weighting heuristic](https://courses.cs.washington.edu/courses/cse573/04au/Project/mini1/RUSSIA/Final_Paper.pdf) to determine a more informed move. Users can also simulate games between the two AIs.

## Pre-requisites
- GNU compiler tools
- make (optional)

## Installation
- Clone the reposistory using:
    - `git clone https://github.com/yewinston/Pure-MCTS-Reversi.git`
- In a terminal, use **one** of the following commands to build the application:
    - `make` 
    - `g++ board.cpp game.cpp reversibot.cpp reversi.cpp -o reversi`
- Run the application with the following command: 
    - `./reversi`

## How to play
- Pick option 1 to play against a Pure MCTS AI with no heuristics
- Pick option 2 to play against a Pure MCTS AI with a static weighting heuristic
- Pick option 3 to simulate a game between Pure MCTS AI with no heuristics vs Pure MCTS AI with static weighting heuristic

## Making a move during a game
- Pick a position that is marked by an asterisk (*). 
- Input the position by inputting a position within the following format: “[A-H][0-7]”
    - where the X-axis is the first character and the Y-axis is the second character
- Example, to pick the top-left corner: the user would have to input “A1”

## Team
- Check out our GitHub's here:
    - [Marian Nguyen](https://github.com/nguyenmar)
    - [Winston Ye](https://github.com/yewinston)