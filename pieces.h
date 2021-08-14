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
    ~Piece();
    Piece(int piece_value, bool owner, char icon);
    int get_value();
    virtual void generate_moves(vector<vector<int>> &,int,int) = 0;
    int duplicate(Piece *);

    bool owner; //false black, true white
    const int value; //the point value of the piece
    char icon; //the icon that represents the piece on the board
    bool has_moved; //whether the piece has ever moved, important for castling
};

class Pawn : public Piece {
public:
    ~Pawn();
    explicit Pawn(bool piece_owner);
    void generate_moves(vector<vector<int>> &, int, int);
    // void generate_moves(int *, int, int);
};
class Knight : public Piece {
public:
    ~Knight();
    explicit Knight(bool piece_owner);
    void generate_moves(vector<vector<int>> & moves,int a, int b);
    // void generate_moves(int *,int a, int b);
};
class Bishop : public Piece {
public:
    ~Bishop();
    explicit Bishop(bool piece_owner);
    void generate_moves(vector<vector<int>> & moves,int a, int b);
    // void generate_moves(vector<vector<int>> *& moves,int a, int b);
};
class Rook : public Piece {
public:
    ~Rook();
    explicit Rook(bool piece_owner);
    void generate_moves(vector<vector<int>> & moves,int a, int b);
    // void generate_moves(vector<vector<int>> *& moves,int a, int b);
};
class Queen : public Piece {
public:
    ~Queen();
    explicit Queen(bool piece_owner);
    void generate_moves(vector<vector<int>> & moves,int a, int b);
    // void generate_moves(vector<vector<int>> *& moves,int a, int b);
};
class King : public Piece {
public:
    ~King();
    explicit King(bool piece_owner);
    void generate_moves(vector<vector<int>> & moves,int a, int b);
    // void generate_moves(vector<vector<int>> *& moves,int a, int b);
};
