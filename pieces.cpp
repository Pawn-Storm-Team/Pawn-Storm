//
// Created by Max Van Raden on 3/27/21.
//
#include "pieces.h"

//piece class

int Piece::get_value() {
    return value;
}

Piece::Piece() : value(0) {
    owner = 0;
}
Piece::~Piece(){};

Piece::Piece(int piece_value, bool owner, char icon) : value(piece_value), owner(owner), icon(icon) {
    has_moved = false;
}

//pawn class
Pawn::Pawn(bool owner) : Piece(1, owner, 'P') {
    if(!owner)
        icon = (char) tolower(icon);
}
//knight class
Knight::Knight(bool owner) : Piece(3, owner, 'N') {
    if(!owner)
        icon = (char) tolower(icon);
}
//bishop class
Bishop::Bishop(bool owner) : Piece(3, owner, 'B') {
    if(!owner)
        icon = (char) tolower(icon);
}
//rook class
Rook::Rook(bool owner) : Piece(5, owner, 'R') {
    if(!owner)
        icon = (char) tolower(icon);
}
//queen class
Queen::Queen(bool owner) : Piece(9, owner, 'Q') {
    if(!owner)
        icon = (char) tolower(icon);
}
//king class
King::King(bool owner) : Piece(999, owner, 'K') {
    if(!owner)
        icon = (char) tolower(icon);
}



void Pawn::generate_moves(vector<vector<int>> & moves,int a, int b) { //a == init rank, b == init file
// int Pawn::generate_moves(vector<vector<int>> *& moves,int a, int b) { //a == init rank, b == init file
    
    int z; //used to modify function for black/white
    vector<int> out (4,-1);
    out[0] = a;
    out[1] = b;

    //flips movement based on black or white
    owner ? z = 1 : z = -1;

    //pawn moves forward 1
    out[3] = b;
    out[2] = a + (1*z);
    moves.push_back(out);

    //pawn moves forward 2
    out[3] = b;
    out[2] = a + (2 * z);
    moves.push_back(out);

    //pawn take diag
    out[3] = b - 1;
    out[2] = a + (1*z);
    moves.push_back(out);

    //pawn takes other diag
    out[3] = b + 1;
    out[2] = a + (1*z);
    moves.push_back(out);

};
void Bishop::generate_moves(vector<vector<int>> & moves,int a, int b) {
    
    vector<int> out (4,-1);
    out[0] = a;
    out[1] = b;
    //one loop for each diagonal direction
    for(int i = a+1, j = b+1; i <= 7 && j <= 7; ++i, ++j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    for(int i = a+1, j = b-1; i <= 7 && j >= 0; ++i, --j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    for(int i = a-1, j = b+1; i >= 7 && j <= 7; --i, ++j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    for(int i = a-1, j = b-1; i >= 7 && j >= 7; --i, --j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
};
void Knight::generate_moves(vector<vector<int>> & moves,int a, int b) {
    vector<int> out (4,-1);
    out[0] = a;
    out[1] = b;

    out[2] = a+2;
    out[3] = b+1;
    moves.push_back(out);

    out[2] = a-2;
    out[3] = b+1;
    moves.push_back(out);

    out[2] = a+2;
    out[3] = b-1;
    moves.push_back(out);

    out[2] = a-2;
    out[3] = b-1;
    moves.push_back(out);

    out[2] = a+1;
    out[3] = b+2;
    moves.push_back(out);

    out[2] = a-1;
    out[3] = b+2;
    moves.push_back(out);

    out[2] = a+1;
    out[3] = b-2;
    moves.push_back(out);

    out[2] = a-1;
    out[3] = b-2;
    moves.push_back(out);

};
void Rook::generate_moves(vector<vector<int>> & moves,int a, int b) {
    vector<int> out (4,-1);
    out[0] = a;
    out[1] = b;

    for(int i = a+1; i <=7; ++i) {
        out[2] = i;
        out[3] = b;
        moves.push_back(out);
    }
    for(int i = a-1; i >=0; --i) {
        out[2] = i;
        out[3] = b;
        moves.push_back(out);
    }
    for(int i = b+1; i <=7; ++i) {
        out[2] = a;
        out[3] = i;
        moves.push_back(out);
    }
    for(int i = a-1; i >=0; --i) {
        out[2] = a;
        out[3] = i;
        moves.push_back(out);
    }

};
void Queen::generate_moves(vector<vector<int>> & moves,int a, int b){
    //Code of rook and bishop combined 
    
    vector<int> out (4,-1);
    out[0] = a;
    out[1] = b;
    
    //Bishop
    //one loop for each diagonal direction
    for(int i = a+1, j = b+1; i <= 7 && j <= 7; ++i, ++j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    for(int i = a+1, j = b-1; i <= 7 && j >= 0; ++i, --j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    for(int i = a-1, j = b+1; i >= 7 && j <= 7; --i, ++j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    for(int i = a-1,  j = b-1; i >= 7 && j >= 7; --i, --j) {
        out[2] = i;
        out[3] = j;
        moves.push_back(out);
    }
    
    //Rook 
    for(int i = a+1; i <=7; ++i) {
        out[2] = i;
        out[3] = b;
        moves.push_back(out);
    }
    for(int i = a-1; i >=0; --i) {
        out[2] = i;
        out[3] = b;
        moves.push_back(out);
    }
    for(int i = b+1; i <=7; ++i) {
        out[2] = a;
        out[3] = i;
        moves.push_back(out);
    }
    for(int i = a-1; i >=0; --i) {
        out[2] = a;
        out[3] = i;
        moves.push_back(out);
    }
};
void King::generate_moves(vector<vector<int>> & moves,int a, int b) {
    vector<int> out (4,-1);
    out[0] = a;
    out[1] = b;

    out[2] = a+1;
    out[3] = b;
    moves.push_back(out);

    out[2] = a+1;
    out[3] = b+1;
    moves.push_back(out);

    out[2] = a-1;
    out[3] = b;
    moves.push_back(out);

    out[2] = a-1;
    out[3] = b+1;
    moves.push_back(out);

    out[2] = a-1;
    out[3] = b-1;
    moves.push_back(out);

    out[2] = a+1;
    out[3] = b-1;
    moves.push_back(out);

    out[2] = a;
    out[3] = b+1;
    moves.push_back(out);

    out[2] = a;
    out[3] = b-1;
    moves.push_back(out);

};

