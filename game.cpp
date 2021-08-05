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
    if(!current_turn) cout << "White";
    else cout << "Black";
    cout << player << "'s turn\n" << "Format move as MyRank:MyFile,DestinationRank:DestinationFile\n$ ";

    string input = string();
    bool valid = false;

    cin >> input;
    cin.clear();
    cin.ignore()

    //todo sanitize further
    char a_rank = input[0], a_file = input[2], b_rank =input[4], b_file = input[6];
    while(move_format_validator(a_rank,a_file,b_rank,b_file)
    ){
        cout << "\tThis input is invalid. Please enter only digits in a:b,x:y formatting.\n\n";
        input.clear();
        cout << "\n>> ";
        cin >> input;
        cin.clear();
        cin.ignore();
    }



    }
}

bool move_format_validator(char a, char b, char x, char y){
    bool valid = false;
    valid = isdigit(a);
    valid = isdigit(b);
    valid = isdigit(c);
    valid = isdigit(d);
    valid = 1 <= (int)a && (int)a <= 8;
    valid = 1 <= (int)b && (int)b <= 8;
    valid = 1 <= (int)c && (int)c <= 8;
    valid = 1 <= (int)d && (int)e <= 8;
    return valid;
    /*

    //strip out white space
    size_t pos = 0; 
    while((pos = input.find(" ")) != string::npos){
       input.erase(pos,1);
    }
    //parsing input
    size_t pos = 0;
    string my_rankfile;

    //find position of delimiter ","
    //then take substring and store in my_ranfile
    //then erase the taken substring plus the delimiter
    pos = input.find(",");
    my_rankfile = input.substr(0,pos);
    input.erase(0,pos+1);

    //there should be digit:digit in both my_rankfile and input
    //sanitize 
    */


