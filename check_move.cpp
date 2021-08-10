#include "board.h"
//TODO implement pin check
//TODO implement check check
//TODO handle en passant
//TODO handle castling
//TODO Knight, Bishop, Rook, Queen path checking
//WHEN PASSING TO FUNCTION REMEMBER THAT RANK IS PASSED BEFORE FILE, UNLIKE A CHESS SQUARE - C4 would be passed as [3,2] (with C being 2 and 4 being 3)
//This function checks the legality of a move, and returns an error code depending on why the move is illegal. Moves that would capture but are not marked
//as captures are reported as illegal.

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
    
}
int knight_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    if(!(((init_rank - dest_rank == 2 || init_rank - dest_rank == -2) && (init_file - dest_file == 1 || init_file - dest_file == -1)) || 
    ((init_rank - dest_rank == 1 || init_rank - dest_rank == -1) && (init_file - dest_file == 2 || init_file - dest_file == -2)))) 
        return -3;//illegal piece movement
}
int bishop_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
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
    
}
int rook_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    if(init_file - dest_file != 0) {//if a rook moves on a file, it cannot move on a rank, and vice versa
        if(init_rank - dest_rank != 0) {
            return -3;//illegal piece movement
        }
    }
}
int queen_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    bool legal_move = true;

        //bishop component of queen movement check
        int x = init_rank - dest_rank;
        if (init_file - dest_file != x || init_file - dest_file != -x)
            legal_move = false;

        //rook component of queen movement check
        if (!legal_move) {//only check the rook component if bishop component was false
            if(init_file - dest_file != 0 && init_rank - dest_rank == 0) {
                legal_move = true;
                }
            if(!legal_move) {//only check for other direction of rook movement if necessary
                if (init_rank - dest_rank != 0 && init_file - dest_file == 0)
                    legal_move = true;
            }
        }
        if(!legal_move)
            return -3;//illegal piece movement  
}
int king_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file) {
    if(init_rank - dest_rank > 1 || init_file - dest_file > 1) {
            return -3;//illegal piece movement
        }
        if(init_rank - dest_rank < -1 || init_file - dest_file < -1) {
            return -3;//illegal piece movement
        }
}

/*    
    //
    //PIECE MOVEMENT RULES
    //
    if(icon == 'P') {//white pawn move rules - no capture yet
        if(dest_rank != init_rank+1 || (dest_rank != init_rank+2 && init_rank == 1)) {
            return -3;//illegal piece movement
        }
        //Clear path checking
        if(dest_rank == init_rank+2) {//check for a blocking piece on the skipped square when moving two squares
            if(game->board[dest_rank-1][dest_file].piece)
                return -6;//blocking piece
        }
    }

    if(icon == 'p') {//black pawn move rules - no capture yet
        if(dest_rank != init_rank-1 || (dest_rank != init_rank-2 && init_rank == 6))
            return -3;//illegal piece movement
        //clear path checking
        if(dest_rank == init_rank-2) {//check for a blocking piece on the skipped square when moving two squares
            if(game->board[dest_rank+1][dest_file].piece)
                return -6;//blocking piece
        }
    }
    //no path checking necessary as the horsey bois hop
    if(game->board[init_rank][init_file].piece->icon == 'N' || game->board[init_rank][init_file].piece->icon == 'n') {//knight moves, not to be confused with Night Moves by bob seger
        if(!(((init_rank - dest_rank == 2 || init_rank - dest_rank == -2) && (init_file - dest_file == 1 || init_file - dest_file == -1)) 
        || ((init_rank - dest_rank == 1 || init_rank - dest_rank == -1) && (init_file - dest_file == 2 || init_file - dest_file == -2)))) //Jesus christ I hope this is correct
            return -3;//illegal piece movement
    }

    if(game->board[init_rank][init_file].piece->icon == 'B' || game->board[init_rank][init_file].piece->icon == 'b') {//bishop move rules
        int x = init_rank - dest_rank;
        if(init_file - dest_file != x || init_file - dest_file != -x)
            return -3;//illegal piece movement
    }

    if(toupper(icon) == 'R') {//rook movement rules
        if(init_file - dest_file != 0) {//if a rook moves on a file, it cannot move on a rank, and vice versa
            if(init_rank - dest_rank != 0) {
                return -3;//illegal piece movement
            }
        }

        if(init_rank - dest_rank != 0) {
            if (init_file - dest_file != 0) {
                return -3;//illegal piece movement
            }
        }
    }

    if(toupper(icon) == 'Q') {//queen move rules
        bool legal_move = true;

        //bishop component of queen movement check
        int x = init_rank - dest_rank;
        if (init_file - dest_file != x || init_file - dest_file != -x)
            legal_move = false;

        //rook component of queen movement check
        if (!legal_move) {//only check the rook component if bishop component was false
            if(init_file - dest_file != 0 && init_rank - dest_rank == 0) {
                legal_move = true;
                }
            if(!legal_move) {//only check for other direction of rook movement if necessary
                if (init_rank - dest_rank != 0 && init_file - dest_file == 0)
                    legal_move = true;
            }
        }
        if(!legal_move)
            return -3;//illegal piece movement
    }
    if(game->board[init_rank][init_file].piece->icon == 'K' || game->board[init_rank][init_file].piece->icon == 'k') {//king move rules
        if(init_rank - dest_rank > 1 || init_file - dest_file > 1) {
            return -3;//illegal piece movement
        }
        if(init_rank - dest_rank < -1 || init_file - dest_file < -1) {
            return -3;//illegal piece movement
        }

    }

    return 0;//legal piece movement
    */