//
// Created by Max Van Raden on 3/27/21.
//
#include "pieces.h"
#include <vector>
#include <string>

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
    vector<Piece> taken; //vector for storing taken pieces
    int clear(); //deletes all pieces, returns quantity of pieces deleted
    int initialize(); //resets board to default configuration, can be used to reset or initialize
    int get_pieces(); //returns number of pieces on board
    void draw_board();
    int check_move(int init_rank, int init_file, int dest_rank, int dest_file, bool is_capture);
    int make_move(int,int,int,int);
    int menu();
    int generate_moves(bool);//generates all legal moves, returns 1 if no legal moves
    void test_move();
    square board[8][8]; // initializes 8 by 8 board, first dimension is rank, second is file

};

