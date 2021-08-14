# Pawn Storm
Max Van Raden and John Bedette, 2021

Command Line Chess App with a chess engine opponent in C++

Pawn Storm is a command line chess app written in C++. It contains a from scratch implementation
of the game itself (some code of which was originally written in javascript for a separate
project and translated), and a basic AI that is capable of playing the game against the player,
as well as the option for two players to play a game against each other locally. The AI is written
from scratch, and is implemented using the minimax algorithm.

## Running the app
Clone the repository to a local directory
Run from the root of the directory: g++ *.cpp
Run: ./a.out (or, if on Windows, ./a.exe)

## Screenshot of game in progress

## Acknowledgements 

The minimax algorithm was leveraged to creat the AI, and previous work and code used for other
implementations of chess by Max Van Raden was utilized during this project. 

## License

Our project is licensed under the MIT open source license. Our license can be found [here](../blob/main/LICENSE)



## Roadmap
- Week 1 : Basic board with pieces moving
- Week 2 : (Prototype Complete) Correct Chess rules and local multiplayer
- Week 3 : Starting on engine and general sprucing up of things
- Week 4 : (MVP Complete) Finish work on chess engine
- Week 5 : Add algebraic notation parsing
- Week 6 : Quashing of the bugs

## Project Goals
- Command line interface 
- Full implementation of the chess ruleset
- Board display from perspective of black or white
- Local play, swap player/board view per move 
- AI player for singleplayer mode
- Output game as PGN file 
- Take move input as algebraic chess notation

### MVP Goals
- Command line interface 
- Full implementation of ruleset
- Local play, swap board
- Board display from black or white
- AI play
- Move input in A3B4 format

### Prototype Goals
- CLI
- Ruleset
- Local play
- Board display
- Move input A3B4 format



