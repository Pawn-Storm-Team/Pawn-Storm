#include <iostream>
#include <string>
#include "interface.h"
using namespace std;

Interface(){
    //make board init values
    board.initialize();
    gameType = local; 
    white = black = mult = false;
    //


    char choice = '\0';

    menu();
}

~Interface(){
    if(board){
        delete board;
        board = nullptr;
    }
};

int interface::intro() {

    cout << "\t\t Welcome to PawnStorm! \t\t\n\n";
    cout << "\t 1.\tPlay against a local opponent \t\t\n\n";
    cout << "\t 2.\tPlay a networked game as White \t\t\n\n";
    cout << "\t 3.\tPlay a networked game as Black \t\t\n\n";
    cout << "\t 4.\tPlay against the AI as White \t\t\n\n";
    cout << "\t 5.\tPlay against the AI as Black \t\t\n\n";
    cout << "\t 6.\tExit \t\t\n\n";
    cout << "\n>> ";

    cin >> input;
    cin.clear();
    cin.ignore();

        while(!(isdigit(input[0]) && input.length() == 1 && parseInt(input[0]) >= 1  && parseInt(input[0] <=6)) { //check if input is valid - both a single character and numeric
            cout << "\tThis input is invalid. Please enter a single digit corresponding to your desired menu choice.\n\n";
            input.clear();
            cout << "\n>> ";
            cin >> input;
            cin.clear();
            cin.ignore();
        }
    int choice = parseInt(input[0]);

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
            cout << "."
            goto invalid_choice; //if the menu isn't selected, restart the process
    }
    return choice;
}

int Interface::menu(){

}
/*


    switch(input[0]) {
        case '1':
            white = true;
            black = true;
            break;
        case '2':
            white = true;
            mult = true;
            break;
        case '3':
            black = true;
            mult = true;
            break;
        case '4':
            white = true;
            break;
        case '5':
            black = true;
            break;
        case '6':
            cout << "Goodbye";
            return;
        default: 
            cout << "Something has gone badly wrong, restarting,"
            goto invalid_choice; //if the menu isn't selected, restart the process
    }
    */