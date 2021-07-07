#include <iostream>
//#include "pieces.h"
#include "board.h"

int main() {
    //pawn test_pawn = pawn(false);
    //std::cout << "A pawn's value is " << test_pawn.get_value();
    chessboard board = chessboard();
    std::cout << "\nPieces on board after creation: " << board.get_pieces();
    board.initialize();
    std::cout << "\nPieces on board after initialization: " << board.get_pieces();
    board.draw_board();
    std::cout << "\nNumber of pieces on board after " << board.clear() << " pieces were cleared: " << board.get_pieces();

    return 0;
}
