//
// john bedette 
//
//
//

#include <iostream>
#include <string>
#include "interface.h"
using namespace std;

Interface::Interface(){
    //make board init values
    //board.initialize();
    gameType = local; 
    current_turn = 0;
    game_complete = false;
    //
    menu();
}

Interface::~Interface(){
};

int Interface::menu(){
    cout << "\t\t Welcome to PawnStorm! \t\t\n\n";
    //intro();
    board.initialize();
    action_prompt();
    return 0;
}
int Interface::intro() {

    string input = string();
    disp_intro_menu();

    cin >> input;
    cin.clear();
    cin.ignore();
    int choice;
    while(
        !(isdigit(input[0]) && input.length() == 1) &&   //check if input is valid - both a single character and numeric
        (choice = stoi(input)) >= 1 && choice <= 6      //by this point isdigit and input length should have guaranteed  
        ){                                              //input is a single digit integer, we assign and then check range
        cout << "\tThis input is invalid. Please enter a single digit corresponding to your desired menu choice.\n\n";
        input.clear();
        cout << "\n>> ";
        cin >> input;
        cin.clear();
        cin.ignore();
    }


    //games will be different based on local etc.
    //in a local game, distinction between black and white is unnecessary
    //online we would need to know who goes first
    //ai we would need to spool up ai and have it know its white or black
    switch(input[0]) {
        case '1':
            break;
        case '2':
            gameType = whiteOnline;
            break;
        case '3':
            gameType = blackOnline;
            break;
        case '4':
            gameType = whiteAI;
            break;
        case '5':
            gameType = BlackAI;
            break;
        case '6':
            cout << "Goodbye";
            break;
        default: 
            cout << "Invalid Choice.";
            choice = intro();//call the function again from the top, capture correct choice value from recursive response
    }
    return choice;
}


//manages the prompts each player will recieve, making it clearer who is going right now, 
//give options for who's taken what, etc
int Interface::action_prompt(){
    while(!game_complete){
      //main turn pattern
        game_complete = board.gen_moves(current_turn%2,&board);
        int error_code = turn_prompt();
        while(error_code < 0){
          error_code = turn_prompt();
          cout << "\nerr no:"<< error_code<<'\n';
        };
        cout << "\nerr no:"<< error_code<<'\n';
        ++current_turn;
    }
    if(!(current_turn % 2)){
     board.draw_board();
     cout << "Black";
    }
    else{ 
     board.draw_board();
     cout << "White";
    }
    cout << " Wins!\n";
    return -1;
}


//turn prompting
int Interface::turn_prompt(){

    //check member for who's turn it is, set string to white or black
    if(current_turn % 2){
     board.draw_board();
     cout << "Black";
    }
    else{ 
     board.draw_board();
     cout << "White";
    }
    cout << ", turn "<< current_turn  <<"\nFormat move as 1A:2B\n$ ";

    string input = string();

    cin >> input;
    cin.clear();
    cin.ignore();

    //todo sanitize further
    //glaring holes
    // - 7 digit numbers
    // - other things I haven't thought of
    int valid = 0;
    while(!(valid = move_format_validator(input[0],input[1],input[3],input[4]))){
        cout << "\tThis input is invalid. Please enter only digits in 1A:2B formatting.\n\n";
        input.clear();
        cout << "\n>> ";
        cin >> input;
        cin.clear();
        cin.ignore();
    }

    //ab is origin, xy is dest
    //by this point we know they're numbers between 1 and 8
    //subtractin char 1 and storing them in int will extract the numbers
    int a, b, x, y, out;
    a = input[0] - '1';
    b = input[1] - '1';
    x = input[3] - '1';
    y = input[4] - '1';
    return board.make_move(&board,a,b,x,y,current_turn%2);
}

//this here verifies that given char represents a number within our desired range
int range_validator(char a){
    if(isdigit(a)){
        int b = a - '0';
        if(b>=1 && b <=8) return 0;
    }
    return 1;
}

//this checks all four input values
//we're subtracting double negative from valid, so if any of these pops a "YES this DOESNT work" we get back invalid 
bool Interface::move_format_validator(char a, char b, char x, char y){
    int valid = 0;
    valid -= range_validator(a);
    valid -= range_validator(b);
    valid -= range_validator(x);
    valid -= range_validator(y);
    return valid >= 0;
}

void Interface::disp_intro_menu(){
    cout << "\t 1.\tPlay against a local opponent \t\t\n\n";
    cout << "\t 2.\tPlay a networked game as White \t\t\n\n";
    cout << "\t 3.\tPlay a networked game as Black \t\t\n\n";
    cout << "\t 4.\tPlay against the AI as White \t\t\n\n";
    cout << "\t 5.\tPlay against the AI as Black \t\t\n\n";
    cout << "\t 6.\tExit \t\t\n\n";
    cout << "\n>> ";
}

int Interface::build_local_game(){
    return 0;
};
int Interface::build_online_game(){
    return 0;
};
int Interface::build_vs_AI(){
    return 0;
};
