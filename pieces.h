//
// Created by Max Van Raden on 3/27/21.
//
#include <iostream>


using namespace std;


class Piece {
public:

    Piece();
    Piece(int piece_value, bool owner, char icon);
    int get_value();

    bool owner; //false black, true white
    const int value; //the point value of the piece
    char icon; //the icon that represents the piece on the board
    bool has_moved; //whether the piece has ever moved, important for castling
};

class Pawn : public Piece {
public:
    explicit Pawn(bool piece_owner);
};
class Knight : public Piece {
public:
    explicit Knight(bool piece_owner);
};
class Bishop : public Piece {
public:
    explicit Bishop(bool piece_owner);
};
class Rook : public Piece {
public:
    explicit Rook(bool piece_owner);
};
class Queen : public Piece {
public:
    explicit Queen(bool piece_owner);
};
class King : public Piece {
public:
    explicit King(bool piece_owner);
};