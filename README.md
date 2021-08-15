# Pawn Storm
Max Van Raden and John Bedette, 2021

Command Line Chess App with a chess engine opponent in C++

Pawn Storm is a command line chess app written in C++. It contains a from scratch implementation
of the game itself (some code of which was originally written in javascript for a separate
project and translated), and a basic AI that is capable of playing the game against the player,
as well as the option for two players to play a game against each other locally. The AI is written
from scratch, and is implemented using the minimax algorithm.

## Running the app
1. Clone the repository to a local directory
2. Run from the root of the directory: `g++ *.cpp`
3. Run: `./a.out` (or, if on Windows, `./a.exe`)

## Screenshot of game in progress
![alt text](https://github.com/Pawn-Storm-Team/Pawn-Storm/blob/dev/Screenshot.PNG)
## Acknowledgements 

The minimax algorithm was leveraged to create the AI, though the implementation is original and not based off an existing implementation or guide. 
Previous work and code used for other implementations of chess written by Max Van Raden, specifically a javascript webapp project, was utilized 
during this project. 

Though it has not been written into the project at this time, the use of Alpha-Beta pruning for searching efficiency is a long-term project goal.

## License

Our project is licensed under the MIT open source license. Our license can be found [here](https://github.com/Pawn-Storm-Team/Pawn-Storm/blob/main/LICENSE)

## Video

 The video for our project can be found [here](https://www.youtube.com/watch?v=KQBZ4I96eAs)
 
## Work Summary

  Max Van Raden wrote the AI and wrote the piece check functions, the agnostic check functions, and the function for determining
  whether or not the king is check. He also wrote the generate_moves function for each piece, which returns the legal moves an
  individual piece can make and is used as part of the larger gen_moves function
  
  John Bedette wrote the interface, designed the game loop and developed associated functionality, and 
  worked on the piece check functions and the king check function. He also wrote the gen_moves function that creates 
  a vector list of all legal moves in a given board state, which is needed both for the AI and to determine checkmate.
  
  Development was done largely in tandem, and both team members participated in bug fixing, testing, and developing
  beyond what is listed above. 



## Roadmap
- Week 1 : Basic board with pieces moving
- Week 2 : (Prototype Complete) Correct Chess rules and local multiplayer
- Week 3 : Starting on engine and general sprucing up of things
- Week 4 : (MVP Complete) Finish work on chess engine
- Week 5 : Add algebraic notation parsing
- Week 6 : Quashing of the bugs

## Project Goals
- Command line interface  - COMPLETED
- Full implementation of the chess ruleset - 90% - missing castling
- Board display from perspective of black or white  - COMPLETED
- Local play, swap player/board view per move  - COMPLETED
- AI player for singleplayer mode - 90% - written but not successfully linked to interface
- Output game as PGN file - INCOMPLETE 
- Take move input as algebraic chess notation - INCOMPLETE

### MVP Goals
- Command line interface  - COMPLETED
- Full implementation of ruleset - 90% - missing castling 
- Local play, swap board - COMPLETED
- Board display from black or white - COMPLETED
- AI play - 90% - written but not successfully linked to interface
- Move input in A3B4 format - COMPLETED

### Prototype Goals
- CLI - COMPLETED
- Ruleset - COMPLETED
- Local play - COMPLETED
- Board display - COMPLETED
- Move input A3B4 format - COMPLETED



