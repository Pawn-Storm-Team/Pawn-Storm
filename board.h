//
// Created by Max Van Raden on 3/27/21.
//
#include "pieces.h"
#include <vector>
#include <string>
using namespace std;

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#endif //CHESS_BOARD_H


class square {
public:
    square();
    ~square();
    Piece * piece;
};

class chessboard {
public:
    vector<vector<int>> legal_moves;
    int clear(); //deletes all pieces, returns quantity of pieces deleted
    int initialize(); //resets board to default configuration, can be used to reset or initialize
    int get_pieces(); //returns number of pieces on board
    void draw_board();

    int make_move(chessboard *,int,int,int,int,bool);
    int menu();
    bool gen_moves(bool, chessboard *);//generates all legal moves, returns 1 if no legal moves
    void test_move();
    square board[8][8]; // initializes 8 by 8 board, first dimension is rank, second is file
    int last_move [4] = {-1, -1, -1, -1};

};


