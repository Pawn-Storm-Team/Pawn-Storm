//
// Created by Max Van Raden on 3/27/21.
//
#include "pieces.h"

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#endif //CHESS_BOARD_H

class square {
public:
    square();
    ~square();
    piece * piece;
};

class chessboard {
public:
    int clear(); //deletes all pieces, returns quantity of pieces deleted
    int initialize(); //resets board to default configuration, can be used to reset or initialize
    int get_pieces(); //returns number of pieces on board
    void draw_board();

    square board[8][8]; // initializes 8 by 8 board, first dimension is rank, second is file
};


