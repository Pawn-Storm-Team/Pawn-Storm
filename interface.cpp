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

    cout << "\t\t Welcome to PawnStorm! \t\t\n\n";
    intro();
    menu();
}

Interface::~Interface(){
    // if(board){
    //     delete board;
    //     board = nullptr;
    // }
};

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

int Interface::menu(){
return 0;
}

//manages the prompts each player will recieve, making it clearer who is going right now, 
//give options for who's taken what, etc
int Interface::action_prompt(){
    if(game_complete){
        cout << "Somebody Wins!";
        return 0;
    }


    int check_move_placeholder = 1;
    if(check_move_placeholder){

    }
    return 0;
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

int Interface::turn_prompt(int * in){

    //check member for who's turn it is, set string to white or black
    if(!current_turn) cout << "White";
    else cout << "Black";
    cout << "'s turn\n" << "Format move as MyRank:MyFile,DestinationRank:DestinationFile\n$ ";

    string input = string();

    cin >> input;
    cin.clear();
    cin.ignore();

    //todo sanitize further
    //glaring holes
    // - 7 digit numbers
    // - other things I haven't thought of
    while(!move_format_validator(input[0],input[2],input[4],input[6])){
        cout << "\tThis input is invalid. Please enter only digits in a:b,x:y formatting.\n\n";
        input.clear();
        cout << "\n>> ";
        cin >> input;
        cin.clear();
        cin.ignore();
    }

    //a is origin, b is dest
    int a_rank, a_file, b_rank, b_file;
    a_rank = int(input[0]);
    a_file = int(input[2]);
    b_rank = int(input[4]);
    b_file = int(input[6]);

    //for now
    return 0;
}


//man this seems just so ugly
//we're subtracting double negative from valid, so if any of these pops a "YES this DOESNT work" we get back invalid 
bool Interface::move_format_validator(char a, char b, char c, char d){
    int valid = 1;
    valid -= 0 == isdigit(a);
    valid -= 0 == isdigit(b);
    valid -= 0 == isdigit(c);
    valid -= 0 == isdigit(d);
    valid -= ( (int)a < 1 || (int)a > 8);
    valid -= ( (int)b < 1 || (int)b > 8);
    valid -= ( (int)c < 1 || (int)c > 8);
    valid -= ( (int)d < 1 || (int)d > 8);
    return valid > 0;
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