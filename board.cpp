//
// Created by Max Van Raden on 3/27/21.
//
#include "board.h"

square::square() {
    piece = nullptr;
}

square::~square() {
    if(piece) {
        delete piece;
        piece = nullptr;
    }

}
//Adds the pieces for a standard ascii-chess game to the board
int chessboard::initialize() { //can be used to reset or initialize the board
    for(int i = 0; i < 8; ++i) { //wipes the board clean, no pieces
        for(int k = 0; k < 8; ++k){
            if(board[i][k].piece != nullptr){
                delete board[i][k].piece;
                board[i][k].piece = nullptr;
            }
        }
    }
    for(int i = 0; i < 8; ++i) {
        for(int k = 0; k < 8; ++k){
            if(i == 0) { //rank is 1, white backrank, initialize with pieces
                if(k == 0 || k == 7) //A1 or H1, white rooks
                    board[i][k].piece = new rook(true);
                if(k == 1 || k == 6) //B1 or G1, white knights
                    board[i][k].piece = new knight(true);
                if(k == 2 || k == 5) //C1 or F1, white bishops
                    board[i][k].piece = new bishop(true);
                if(k == 3) //D1, white queen
                    board[i][k].piece = new queen(true);
                if(k == 4) //E1, white king
                    board[i][k].piece = new king(true);
            }
            if(i == 1) { //rank is 2, white frontrank, initialize with pawns
                board[i][k].piece = new pawn(true);
            }
            if(i == 6) { //rank is 7, black frontrank, initialize with pawns
                board[i][k].piece = new pawn(false);
            }
            if(i == 7) { //rank is 8, black backrank, initialize with pieces
                if(k == 0 || k == 7) //A8 or H8, black rooks
                    board[i][k].piece = new rook(false);
                if(k == 1 || k == 6) //B1 or G1, white knights
                    board[i][k].piece = new knight(false);
                if(k == 2 || k == 5) //C1 or F1, white bishops
                    board[i][k].piece = new bishop(false);
                if(k == 3) //D1, white queen
                    board[i][k].piece = new queen(false);
                if(k == 4) //E1, white king
                    board[i][k].piece = new king(false);
            }

        }
    }
    return 0;
}
//frees memory allocated during piece creation
int chessboard::clear() {
    int count = 0;
    for(int i = 0; i < 8; ++i) { //wipes the board clean, no pieces
        for(int k = 0; k < 8; ++k){
            if(board[i][k].piece != nullptr){
                delete board[i][k].piece;
                board[i][k].piece = nullptr;
                ++count;
            }
        }
    }
    return count;
}

int chessboard::get_pieces() {
    int count = 0;
    for(int i = 0; i < 8; ++i) {
        for(int k = 0; k < 8; ++k){
            if(board[i][k].piece)
                ++count;
        }
    }
    return count;
}

void chessboard::draw_board() {
    std::cout << "\n\n";
    std::cout << "\t   A     B     C     D     E     F     G     H"<< std::endl;
    for(int i = 7; i >= 0; --i) { //print from white's perspective, so first square printed will be A8, so ranks count backwards
        std::cout << "\t   -     -     -     -     -     -     -     -" << std::endl;
        std::cout << i+1 << "\t";
        for(int k = 0; k < 8; ++k) {
            if(board[i][k].piece)
                //std::cout << "| P ";
                std::cout << "|  " << board[i][k].piece->icon << "  ";
            else
                std::cout << "|     ";
        }
        std::cout << "|\t" << i+1 << std::endl;
    }
    std::cout << "\t   -     -     -     -     -     -     -     -" << std::endl;
    std::cout << "\t   A     B     C     D     E     F     G     H"<< std::endl;
}
//TODO implement pin check
//TODO implement check check
//TODO handle en passant
//TODO handle castling
//TODO Knight, Bishop, Rook, Queen path checking
//WHEN PASSING TO FUNCTION REMEMBER THAT RANK IS PASSED BEFORE FILE, UNLIKE A CHESS SQUARE - C4 would be passed as [3,2] (with C being 2 and 4 being 3)
//This function checks the legality of a move, and returns an error code depending on why the move is illegal. Moves that would capture but are not marked
//as captures are reported as illegal.
int chessboard::check_move(int init_rank, int init_file, int dest_rank, int dest_file, bool is_capture) {

    if(!board[init_rank][init_file].piece) {//there do be a piece check
        return -1;//No piece error
    }
    if(dest_rank > 7 || dest_rank < 0 || dest_file > 7 || dest_file < 0) {//the dest square do exist check
        return -2;//Out of bounds error
    }
    if(dest_rank == init_rank && dest_file == init_file) {//you must move to make a move
        return -4;//Literally not a move error
    }
    if(board[dest_rank][dest_file].piece->owner == board[init_rank][init_file].piece->owner) {//occupied by same side piece check
        return -5;//Self-capture error
    }

    //
    //PIECE MOVEMENT RULES
    //
    if(board[init_rank][init_file].piece->icon == 'P') {//white pawn move rules - no capture yet
        if(dest_rank != init_rank+1 || (dest_rank != init_rank+2 && init_rank == 1)) {
            return -3;//illegal piece movement
        }
        //Clear path checking
        if(dest_rank == init_rank+2) {//check for a blocking piece on the skipped square when moving two squares
            if(board[dest_rank-1][dest_file].piece)
                return -6;//blocking piece
        }
    }

    if(board[init_rank][init_file].piece->icon == 'p') {//black pawn move rules - no capture yet
        if(dest_rank != init_rank-1 || (dest_rank != init_rank-2 && init_rank == 6))
            return -3;//illegal piece movement
        //clear path checking
        if(dest_rank == init_rank-2) {//check for a blocking piece on the skipped square when moving two squares
            if(board[dest_rank+1][dest_file].piece)
                return -6;//blocking piece
        }
    }
    //no path checking necessary as the horsey bois hop
    if(board[init_rank][init_file].piece->icon == 'N' || board[init_rank][init_file].piece->icon == 'n') {//knight moves, not to be confused with Night Moves by bob seger
        if(!(((init_rank - dest_rank == 2 || init_rank - dest_rank == -2) && (init_file - dest_file == 1 || init_file - dest_file == -1)) || ((init_rank - dest_rank == 1 || init_rank - dest_rank == -1) && (init_file - dest_file == 2 || init_file - dest_file == -2))))//Jesus christ I hope this is correct
            return -3;//illegal piece movement
    }

    if(board[init_rank][init_file].piece->icon == 'B' || board[init_rank][init_file].piece->icon == 'b') {//bishop move rules
        int x = init_rank - dest_rank;
        if(init_file - dest_file != x || init_file - dest_file != -x)
            return -3;//illegal piece movement
    }

    if(board[init_rank][init_file].piece->icon == 'R' || board[init_rank][init_file].piece->icon == 'r') {//rook movement rules
        if(init_file - dest_file != 0) {//if a rook moves on a file, it cannot move on a rank, and vice versa
            if(init_rank - dest_rank != 0) {
                return -3;//illegal piece movement
            }
        }

        if(init_rank - dest_rank != 0) {
            if (init_file - dest_file != 0) {
                return -3;//illegal piece movement
            }
        }
    }

    if(board[init_rank][init_file].piece->icon == 'Q' || board[init_rank][init_file].piece->icon == 'q') {//queen move rules
        bool legal_move = true;

        //bishop component of queen movement check
        int x = init_rank - dest_rank;
        if (init_file - dest_file != x || init_file - dest_file != -x)
            legal_move = false;

        //rook component of queen movement check
        if (!legal_move) {//only check the rook component if bishop component was false
            if(init_file - dest_file != 0 && init_rank - dest_rank == 0) {
                legal_move = true;
                }
            if(!legal_move) {//only check for other direction of rook movement if necessary
                if (init_rank - dest_rank != 0 && init_file - dest_file == 0)
                    legal_move = true;
            }
        }
        if(!legal_move)
            return -3;//illegal piece movement
    }
    if(board[init_rank][init_file].piece->icon == 'K' || board[init_rank][init_file].piece->icon == 'k') {//king move rules
        if(init_rank - dest_rank > 1 || init_file - dest_file > 1) {
            return -3;//illegal piece movement
        }
        if(init_rank - dest_rank < -1 || init_file - dest_file < -1) {
            return -3;//illegal piece movement
        }

    }

    return 0;//legal piece movement
}

