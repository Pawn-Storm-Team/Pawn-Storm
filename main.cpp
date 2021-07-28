#include <iostream>
//#include "pieces.h"
#include "board.h"

int main() {
    //pawn test_pawn = pawn(false);
    //std::cout << "A pawn's value is " << test_pawn.get_value();
    /*chessboard board = chessboard();
    cout << "\nPieces on board after creation: " << board.get_pieces();
    board.initialize();
    cout << "\nPieces on board after initialization: " << board.get_pieces();
    board.draw_board();
    cout << "\nNumber of pieces on board after " << board.clear() << " pieces were cleared: " << board.get_pieces();
    */
    invalid_choice:
    char choice = menu()[0];
    switch(choice) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        default: 
            goto invalid_choice;
    }
    return 0;
}

string menu() {
    string input = string();
    cout << "\t\t Welcome to PawnStorm! \t\t\n\n";
    cout << "\t 1.\tPlay a local game as White \t\t\n\n";
    cout << "\t 2.\tPlay a local game as Black \t\t\n\n";
    cout << "\t 3.\tPlay a networked game as White \t\t\n\n";
    cout << "\t 4.\tPlay a networked game as Black \t\t\n\n";
    cout << "\t 5.\tPlay against the AI as White \t\t\n\n";
    cout << "\t 6.\tPlay against the AI as Black \t\t\n\n";
    cout << "\t 7.\tExit \t\t\n\n";
    cout << "\n>> ";
    cin >> input;
    cin.clear();
    cin.ignore();

    while(!(isdigit(input[0]) && input.length() == 1)) { //check if input is valid - both a single character and numeric
        cout << "\tThis input is invalid. Please enter a single digit corresponding to your desired menu choice.\n\n";
        input.clear();
        cout << "\n>> ";
        cin >> input;
        cin.clear();
        cin.ignore();
        

    }
    return input;
}
