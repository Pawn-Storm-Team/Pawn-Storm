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



int Pawn::generate_moves(vector<int[4]> moves,int a, int b){
    //dest rank, file, owernership mulitplier
    int x, y, z;

    //flips movement based on black or white
    owner ? z = 1 : z = -1;

    //pawn moves forward 1
    y = b + (1*z);
    moves.push([a,b,x,y]);

    //pawn moves forward 2
    y = b + (2 * z);
    moves.push([a,b,x,y]);

    //pawn take diag
    x = a - 1;
    y = b + (1*z);
    moves.push([a,b,x,y]);

    //pawn takes other diag
    x = a + 1;
    y = b + (1*z);
    moves.push([a,b,x,y]);

    return 0;
};
// int ** Bishop::generate_moves(){};
// int ** Knight::generate_moves(){};
// int ** Rook::generate_moves(){};
// int ** Queen::generate_moves(){};
// int ** King::generate_moves(){};

