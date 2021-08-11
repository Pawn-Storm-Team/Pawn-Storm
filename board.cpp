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
//todo
void chessboard::test_move(){
    make_move(1,2,3,4);
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
        bool color = true; 
        for(int k = 0; k < 8; ++k){
            if(i > 3) { // switch color flag to initialize black's pieces 
                color = false;
            }
            if(i == 0 || i == 7) { //rank is 1, white backrank, initialize with pieces
                if(k == 0 || k == 7) //A1 or H1, white rooks
                    board[i][k].piece = new Rook(color);
                if(k == 1 || k == 6) //B1 or G1, white knights
                    board[i][k].piece = new Knight(color);
                if(k == 2 || k == 5) //C1 or F1, white bishops
                    board[i][k].piece = new Bishop(color);
                if(k == 3) //D1, white queen
                    board[i][k].piece = new Queen(color);
                if(k == 4) //E1, white king
                    board[i][k].piece = new King(color);
            }
            if(i == 1 || i == 6) { //rank is 2, white frontrank, initialize with pawns
                board[i][k].piece = new Pawn(color);
            }
        }
    }
    //test_move();
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

//todo remove this placeholder
int check_move_placeholder(int, int, int, int){
    return 1;
}
//todo remove this placeholder

int chessboard::make_move(int a, int b, int x, int y){
    cout << "\nmake_move vals " << a << b << x << y << "\n";
    //if move is illegal, send error, redo turn
    //placeholder
    if(!check_move_placeholder(a,b,x,y)){
        cout << "Illegal move, please try again";
        return 1;
    }

    //todo, record taken piece
    //move
    board[x][y].piece = board[a][b].piece;
    board[a][b].piece = nullptr;

    return 0;
}

//interface passed color
//generate all the moves, store in legal_move vector of strings
//will be called every turn
//iterate through board
//if piece exists call generate_moves,
//capture strings of possible moves in vector,
//pass each through the move check,
//push possible moves into vector<string> of moves,
//if no possible moves, indicate to interface that game is complete
int chessboard::generate_moves(bool color){
    for(int i = 0; i < 7; ++i){
        for(int j = 0; j < 7;++j){

            Piece * curr = board[i][j].piece;
            if(curr && curr->owner == color){

                vector<vector<int>> moves;
                curr->generate_moves(&moves, i, j);


                while(!moves.empty()){
                    // move_arr[0] = (moves[moves.size()-1])[0]; 
                    // move_arr[1] = (moves[moves.size()-1])[1]; 
                    // move_arr[2] = (moves[moves.size()-1])[2]; 
                    // move_arr[3] = (moves[moves.size()-1])[3]; 
                    // if(check_move(move_vec,board)){
                    //     legal_moves.push_back(moves.pop_back());
                    // }
                    vector<int> move_vec = moves.pop_back();
                    if(check_move(&move_vec,board)){
                        legal_moves.push_back(move_vec);
                    }
                }

            }
        }
    }
    return legal_moves.size();
}


