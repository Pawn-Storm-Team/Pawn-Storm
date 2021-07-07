//
// Created by Max Van Raden on 3/27/21.
//
#include <iostream>
#include <cmath>

#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H

#endif //CHESS_CHESS_H

int print();

class piece {
public:

    piece();
    piece(int piece_value, bool owner, char icon);
    int get_value();

    bool owner; //false black, true white
    const int value; //the point value of the piece
    char icon; //the icon that represents the piece on the board
    bool has_moved; //whether the piece has ever moved, important for castling
};

class pawn : public piece {
public:
    explicit pawn(bool piece_owner);
};
class knight : public piece {
public:
    explicit knight(bool piece_owner);
};
class bishop : public piece {
public:
    explicit bishop(bool piece_owner);
};
class rook : public piece {
public:
    explicit rook(bool piece_owner);
};
class queen : public piece {
public:
    explicit queen(bool piece_owner);
};
class king : public piece {
public:
    explicit king(bool piece_owner);
};