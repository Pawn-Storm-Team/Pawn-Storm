/*
#include "boardh"
//TODO implement pin check
//TODO implement check check
//TODO handle en passant
//TODO handle castling
//TODO Knight, Bishop, Rook, Queen path checking
//WHEN PASSING TO FUNCTION REMEMBER THAT RANK IS PASSED BEFORE FILE, UNLIKE A CHESS SQUARE - C4 would be passed as [3,2] (with C being 2 and 4 being 3)
//This function checks the legality of a move, and returns an error code depending on why the move is illegal. Moves that would capture but are not marked
//as captures are reported as illegal.
//RETURN CODES: 0 Standard Move, 1 Capture, 2 En Passant Capture
//ERROR CODES: -1 No piece at starting square, -2 dest/init square out of bounds, -3 piece-specific move rule violation, -4 destination and initial square are the same, -5 capturing own piece, -6 path blocked by piece 

int agnostic_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file){
    if(init_rank > 7 || init_rank < 0 || init_file > 7 || init_file < 0) {//the init square do exist check
        return -2;//Out of bounds error
    }
    if(!(game->board[init_rank][init_file].piece)) {//there do be a piece check
        return -1;//No piece error
    }
    if(dest_rank > 7 || dest_rank < 0 || dest_file > 7 || dest_file < 0) {//the dest square do exist check
        return -2;//Out of bounds error
    }
    if(dest_rank == init_rank && dest_file == init_file) {//you must move to make a move
        return -4;//Literally not a move error
    }
    //This must be the last check as it returns a 1 for captures. Any checks after this may not occur
    if(game->board[dest_rank][dest_file].piece) {//there is a piece in the destination square, check for legality
        if(game->board[dest_rank][dest_file].piece->owner == game->board[init_rank][init_file].piece->owner) {//occupied by same side piece check
            return -5; //self-capture error
            } 
        if(game->board[dest_rank][dest_file].piece->owner != game->board[init_rank][init_file].piece->owner) {//occupied by an enemy piece 
            return 1; //this move is a capture
        }
    }
    else 
        return 0;//This move is so far legal, but not a capture
}

int check_move(int init_rank, int init_file, int dest_rank, int dest_file, bool is_capture, chessboard * game) {

    //breaking this out

    int a_check = agnostic_check(game,init_rank,init_file,dest_file,dest_rank);
    if(a_check < 0) return a_check;
    char icon = game->board[init_rank][init_file].piece->icon;
    bool is_capture = false;
    if(a_check == 1)
        is_capture = true;


    int result;
    switch(toupper(icon)){
        case 'P':
            if(icon == 'p') result = black_pawn_check(game, init_rank, init_file, dest_rank, dest_file, is_capture);
            else result = white_pawn_check(game, init_rank, init_file, dest_rank, dest_file, is_capture);
            break;
        case 'N':
            result = knight_check(game, init_rank, init_file, dest_rank, dest_file);
            break;
        case 'R':
            result = rook_check(game, init_rank, init_file, dest_rank, dest_file);
            break;
        case 'Q':
            result = queen_check(game, init_rank, init_file, dest_rank, dest_file);
            break;
        case 'K':
            result = king_check(game, init_rank, init_file, dest_rank, dest_file);
            break;
        default:
            return -80;//placeholder for default error
        
    }
 
}
//Individual piece move check functions 
int white_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file, bool is_capture) {
    if(!is_capture) {
        if(dest_rank != init_rank+1 || (dest_rank != init_rank+2 && init_rank == 1)) { //moving one or two squares, checking for correct rank for moving two
          return -3; //illegal piece movement
          }
            //Clear path checking
            if(dest_rank == init_rank+2) { //check for a blocking piece on the skipped square when moving two squares
                if(game->board[dest_rank-1][dest_file].piece)
                    return -6; //blocking piece
            }
    }
    else { //check for capture conditions
        if(dest_rank != init_rank+1) { 
            if(dest_file != init_file+1 && dest_file != init_file-1) {
                return -3; //illegal piece movement 
            }
        
        }
    }
    return 0; // valid move
}
int black_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file, bool is_capture) {
    if(!is_capture) { //check for non-capture conditions
        if(dest_rank != init_rank-1 || (dest_rank != init_rank-2 && init_rank == 6)) {
            return -3;//illegal piece movement
            //clear path checking
            if(dest_rank == init_rank-2) {//check for a blocking piece on the skipped square when moving two squares
                if(game->board[dest_rank+1][dest_file].piece)
                    return -6;//blocking piece
            }
        }
    }
    else { //check for capture conditions
        if(dest_rank != init_rank-1) { 
            if(dest_file != init_file+1 && dest_file != init_file-1) {
                return -3; //illegal piece movement 
            }
        
        }
    }
    return 0; // valid move
}
int knight_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    if(!(((init_rank - dest_rank == 2 || init_rank - dest_rank == -2) && (init_file - dest_file == 1 || init_file - dest_file == -1)) || 
    ((init_rank - dest_rank == 1 || init_rank - dest_rank == -1) && (init_file - dest_file == 2 || init_file - dest_file == -2)))) 
        return -3;//illegal piece movement
    
    return 0; // valid move
}
int bishop_check(chessboard * game, int init_rank, int init_file, int dest_rank, int dest_file) {
    int diff_rank = dest_rank - init_rank;
    int diff_file = dest_file - init_file;
    if(diff_rank != diff_file || diff_rank != -diff_file) {
        return -3;//illegal piece movement
    }   
    // both positive
    if(diff_rank > 0 && diff_file > 0) {
        for(int i = init_rank + 1; i < dest_rank; ++i){
            for(int k = init_file + 1; k < dest_file; ++k){
                if(!game->board[i][k].piece) {
                    return -6; //blocking piece
                }
            }
        }
    }
    // rank positive, file negative
    if(diff_rank > 0 && diff_file > 0) {
        for(int i = init_rank + 1; i < dest_rank; ++i){
            for(int k = init_file - 1; k > dest_file; --k){
                if(!game->board[i][k].piece) {
                    return -6; //blocking piece
                }
            }
        }
    }
    // rank negative, file positive
    if(diff_rank > 0 && diff_file > 0) {
        for(int i = init_rank - 1; i > dest_rank; --i){
            for(int k = init_file + 1; k < dest_file; ++k){
                if(!game->board[i][k].piece) {
                    return -6; //blocking piece
                }
            }
        }
    }
    // both negative 
    if(diff_rank > 0 && diff_file > 0) {
        for(int i = init_rank - 1; i > dest_rank; --i){
            for(int k = init_file - 1; k > dest_file; --k){
                if(!game->board[i][k].piece) {
                    return -6; //blocking piece
                }
            }
        }
    }
    return 0; // valid move
}
int rook_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    if(init_file - dest_file != 0) {//if a rook moves on a file, it cannot move on a rank, and vice versa
        if(init_rank - dest_rank != 0) {
            return -3;//illegal piece movement
        }
    }
    if(dest_file == init_file && dest_rank != init_rank) {
        if(dest_rank - init_rank > 0) {
            for(int i = init_rank + 1; i < dest_rank; ++i) {
                if(!game->board[i][init_file].piece) {
                    return -6; //blocking piece
                }
            }
        }
        else {
            for(int i = init_rank - 1; i > dest_rank; --i) {
                if(!game->board[i][init_file].piece) {
                    return -6; //blocking piece
                }
            }
        }

    }
    else if(dest_file != init_file && dest_rank == init_rank) {
        if(dest_file - init_file > 0) {
            for(int i = init_file + 1; i < dest_file; ++i) {
                if(!game->board[init_rank][i].piece) {
                    return -6; //blocking piece
                }
            }
        }
        else {
            for(int i = init_file - 1; i > dest_file; --i) {
                if(!game->board[init_rank][i].piece) {
                    return -6; //blocking piece
                }
            }
        }
    }
    else {
        return -3;//illegal piece movement
    }
    return 0; // valid move
}
int queen_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
      int i = bishop_check(game, init_rank, init_file, dest_rank, dest_file);
      if(i < 0) {
          return i; 
      }
      else {
          int k = rook_check(game, init_rank, init_file, dest_rank, dest_file);
          if(k < 0) {
              return k;
          }
      }
      return 0; // valid move
}
int king_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    if(init_rank - dest_rank > 1 || init_file - dest_file > 1) {
            return -3;//illegal piece movement
        }
        if(init_rank - dest_rank < -1 || init_file - dest_file < -1) {
            return -3;//illegal piece movement
        }
    return 0; // valid move
}

