CMPT 310 - Reversi Final Project 
Marian Nguyen (mna68@sfu.ca)
Winston Ye (winstony@sfu.ca)

Pre-requisites:
    - GNU compiler tools

Installation:
    - Unzip contents
    - In a terminal, use ONE of the following commands to build the application:
        - make
        - g++ board.cpp game.cpp reversibot.cpp reversi.cpp -o reversi
    - Run the application with the following command:
        - ./reversi

How to play:
    - Pick option 1 to play against a Pure MCTS AI with no heuristics
    - Pick option 2 to play against a Pure MCTS AI with static weighting heuristic
    - Pick option 3 to simulate a game between Pure MCTS AI with no heuristics vs Pure MCTS AI with static weighting heuristic

Making a move during a game:
    - Pick a position that is marked by an asterisk (*). 
    - Input the position by inputting a position within the following format: “[A-H][0-7]”
        - where the X-axis is the first character and the Y-axis is the second character
    - Example, to pick the top-left corner: the user would have to input “A1”
    