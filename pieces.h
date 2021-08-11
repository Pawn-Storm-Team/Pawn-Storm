//
// Created by Max Van Raden on 3/27/21.
//
#include <iostream>
#include <vector>
#include <string>


using namespace std;

//playing with idea of move 
struct Move{
    int a,b,x,y;
};

class Piece {
public:
    int ** move_list{};
    vector<Move> moves;
    Piece();
    Piece(int piece_value, bool owner, char icon);
    int get_value();
    int generate_moves(vector<vector<int>>,int,int);

    bool owner; //false black, true white
    const int value; //the point value of the piece
    char icon; //the icon that represents the piece on the board
    bool has_moved; //whether the piece has ever moved, important for castling
};

class Pawn : public Piece {
public:
    explicit Pawn(bool piece_owner);
    int generate_moves(vector<int[]>*,int,int);
};
class Knight : public Piece {
public:
    explicit Knight(bool piece_owner);
    int ** generate_moves();
};
class Bishop : public Piece {
public:
    explicit Bishop(bool piece_owner);
    int ** generate_moves();
};
class Rook : public Piece {
public:
    explicit Rook(bool piece_owner);
    int ** generate_moves();
};
class Queen : public Piece {
public:
    explicit Queen(bool piece_owner);
    int ** generate_moves();
};
class King : public Piece {
public:
    explicit King(bool piece_owner);
    int ** generate_moves();
};