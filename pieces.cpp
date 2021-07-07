//
// Created by Max Van Raden on 3/27/21.
//
#include "pieces.h"

//piece class

int piece::get_value() {
    return value;
}

piece::piece() : value(0) {
    owner = 0;
}

piece::piece(int piece_value, bool owner, char icon) : value(piece_value), owner(owner), icon(icon) {
    has_moved = false;
}

//pawn class
pawn::pawn(bool owner) : piece(1, owner, 'P') {
    if(!owner)
        icon = (char) tolower(icon);
}
//knight class
knight::knight(bool owner) : piece(3, owner, 'N') {
    if(!owner)
        icon = (char) tolower(icon);
}
//bishop class
bishop::bishop(bool owner) : piece(3, owner, 'B') {
    if(!owner)
        icon = (char) tolower(icon);
}
//rook class
rook::rook(bool owner) : piece(5, owner, 'R') {
    if(!owner)
        icon = (char) tolower(icon);
}
//queen class
queen::queen(bool owner) : piece(9, owner, 'Q') {
    if(!owner)
        icon = (char) tolower(icon);
}
//king class
king::king(bool owner) : piece(999, owner, 'K') {
    if(!owner)
        icon = (char) tolower(icon);
}
