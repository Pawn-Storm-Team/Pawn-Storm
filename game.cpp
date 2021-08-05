//john bedette
//
//
//
#include "game.h"
#include <stdio.h>
#include <string>
using namespace std;

Game::Game(GameType gt, int colorSelected){
    gameType = gt;//determines build settings
    current_turn = colorSelected;//white is 0, black is 1
    game_complete = false;

    build_switch();
    action_prompt();
}
Game::~Game(){

}

int Game::build_switch(){
    switch(gameType){
        case(local)
    }
}
int Game::build_local_game(){
    return 0;
};
int Game::build_online_game(){
    return 0;
};
int Game::build_vs_AI(){
    return 0;
};

//manages the prompts each player will recieve, making it clearer who is going right now, 
//give options for who's taken what, etc
int Game::action_prompt(){
    if(game_complete){
        cout << "Somebody Wins!";
        return 0;
    }


    int check_move_placeholder = 1;
    if(check_move_placeholder){

    }
    return 0;
}
int Game::turn_prompt(int * in){

    //check member for who's turn it is, set string to white or black
    if(!current_turn){ cout << "White";
    else cout << "Black";
    cout << player << "'s turn\n" << "Format move as MyRank:MyFile,DestinationRank:DestinationFile\n$ ";

    string input = string();
    string token;
    bool valid = false;

    cin >> input;
    cin.clear();
    cin.ignore()
    size_t pos = 0;

    while((pos = input.find(",")) != std::string::npos){
       token = s.sub(0,pos)
    }
    

}