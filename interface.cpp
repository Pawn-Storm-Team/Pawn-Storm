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
    white = black = mult = false;
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
    dispIntroMenu();

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

void dispIntroMenu(){
    cout << "\t 1.\tPlay against a local opponent \t\t\n\n";
    cout << "\t 2.\tPlay a networked game as White \t\t\n\n";
    cout << "\t 3.\tPlay a networked game as Black \t\t\n\n";
    cout << "\t 4.\tPlay against the AI as White \t\t\n\n";
    cout << "\t 5.\tPlay against the AI as Black \t\t\n\n";
    cout << "\t 6.\tExit \t\t\n\n";
    cout << "\n>> ";

}