#include "check_move.h"
#include "board.h"
//TODO implement pin check
//TODO implement check check
//TODO handle en passant
//TODO handle castling
//TODO Knight, Bishop, Rook, Queen path checking
//WHEN PASSING TO FUNCTION REMEMBER THAT RANK IS PASSED BEFORE FILE, UNLIKE A CHESS SQUARE - C4 would be passed as [3,2] (with C being 2 and 4 being 3)
//This function checks the legality of a move, and returns an error code depending on why the move is illegal. Moves that would capture but are not marked
//as captures are reported as illegal.
//RETURN CODES: 0 Standard Move, 1 Capture, 2 En Passant Capture
//ERROR CODES: -1 No piece at starting square, -2 dest/init square out of bounds, -3 piece-specific move rule violation, 
//-4 destination and initial square are the same, -5 capturing own piece, -6 path blocked by piece, -7 trying to move the other player's piece 

int agnostic_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file, bool player){
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
    if(game->board[init_rank][init_file].piece->owner != player) {
        return -7; //cannot move other players piece
    }
    //This must be the last check as it returns a 1 for captures. Any checks after this may not occur
    if(game->board[dest_rank][dest_file].piece) {//there is a piece in the destination square, check for legality
        if(game->board[dest_rank][dest_file].piece->owner == game->board[init_rank][init_file].piece->owner) {//occupied by same side piece check
            return -5; //self-capture error
            } 
        else {//occupied by an enemy piece 
            return 1; //this move is a capture
        }
    }
    else 
        return 0;//This move is so far legal, but not a capture
}

int check_move(chessboard * game, int init_rank, int init_file, int dest_rank, int dest_file, bool player) {


    // int init_rank = move[0];
    // int init_file = move[1];
    // int dest_rank = move[2];
    // int dest_file = move[3];

    int a_check = agnostic_check(game, init_rank, init_file, dest_file, dest_rank, player);
    if(a_check < 0) return a_check;
    char icon = (game->board[init_rank])[init_file].piece->icon;
    bool is_capture = false;
    if(a_check == 1)
        is_capture = true;


    int result;
    switch(toupper(icon)){
        case 'P':
            if(icon == 'p') result = black_pawn_check(game, init_rank, init_file, dest_rank, dest_file, is_capture, player);
            else result = white_pawn_check(game, init_rank, init_file, dest_rank, dest_file, is_capture, player);
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
    return result;
}
/*
int is_in_check(chessboard * game, int init_rank, int init_file, int dest_rank, int dest_file, bool is_capture, bool player) {
    int king_rank = -1;
    int king_file = -1; 
    int is_king = 0; //if the king is the piece moving, we can just check the destination square without "moving" pieces to see if the king would be in check
    int in_check = 0; //This flag is used to track if the king is in check so that the temporary movement can be undone

    if(game->board[init_rank][init_file].piece->icon == 'k' || game->board[init_rank][init_file].piece->icon == 'K') {
        king_rank = dest_rank;
        king_file = dest_file; 
        is_king = 1;
    }
}
*/
//Individual piece move check functions 
int white_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file, bool is_capture, bool player) {
    int legality = 0;
    if(!is_capture) {
        if(dest_rank == init_rank+1 && dest_file == init_file) { //moving one square 
            legality = 0; //valid move
        }
        if(dest_rank == init_rank+2 && init_rank == 1 && dest_file == init_file) { //check for a blocking piece on the skipped square when moving two squares
            if(game->board[dest_rank-1][dest_file].piece) {
                legality = -6; //blocking piece
            }
            else {
                legality = 0; //valid move 
            }
        }
        //En Passant capture check section - in this section because the ag check will not determine that this move is a capture due to an empty destination square 
        //En Passant check - to the right
        if(dest_file == init_file+1 && //correct file for en passant right
        dest_rank == init_rank-1 && //moved one square down the board 
        !game->board[init_rank-1][init_file+1].piece && // the destination square is empty
        game->board[init_rank][init_file+1].piece && // there is a piece directly to the right of the moving pawn
        game->board[init_rank][init_file+1].piece->owner != player && // it is not owned by the player
        toupper(game->board[init_rank][init_file+1].piece->icon) == 'P' && // it is also a pawn
        game->last_move[0]+2 == game->last_move[2] && //white piece moved two squares up last move
        game->last_move[2] == init_rank && game->last_move[3] == init_file+1 //The last move ended on the coordinates directly adjacent to the moving pawn
        ) {
            legality = 2; // valid en passant capture, will require special handling
        }
        //En passant check - to the left
        else if(dest_file == init_file-1 && //correct file for en passant left
        dest_rank == init_rank-1 && //moved one square down the board 
        !game->board[init_rank-1][init_file-1].piece && // the destination square is empty
        game->board[init_rank][init_file-1].piece && // there is a piece directly to the left of the moving pawn
        game->board[init_rank][init_file-1].piece->owner != player && // it is not owned by the player
        toupper(game->board[init_rank][init_file-1].piece->icon) == 'P' && // it is also a pawn
        game->last_move[0]+2 == game->last_move[2] && //White piece moved two squares up last move
        game->last_move[2] == init_rank && game->last_move[3] == init_file-1 //The last move ended on the coordinates directly adjacent to the moving pawn
        ) {
            legality = 2; // valid en passant capture, will require special handling
        }
        else {
            legality = -3; //illegal piece movement 
        }
    }
    else { //check for capture conditions
        if(dest_rank != init_rank+1) { 
            if(dest_file != init_file+1 && dest_file != init_file-1) {
                legality = -3; //illegal piece movement 
            }
        }
    }
    return legality; // valid move
}
int black_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file, bool is_capture, bool player) {\
    int legality = 0;
    if(!is_capture) { //check for non-capture conditions and en passant 
        if(dest_rank != init_rank-1 || (dest_rank != init_rank-2 && init_rank == 6)) {
            legality = -3;//illegal piece movement
            //clear path checking
            if(dest_rank == init_rank-2) {//check for a blocking piece on the skipped square when moving two squares
                if(game->board[dest_rank+1][dest_file].piece)
                   legality = -6;//blocking piece
            }
        }
        //En Passant capture check section - in this section because the ag check will not determine that this move is a capture due to an empty destination square 
        //En Passant check - to the right
        if(dest_file == init_file+1 && //correct file for en passant right
        dest_rank == init_rank+1 && //moved one square up the board 
        !game->board[init_rank+1][init_file+1].piece && // the destination square is empty
        game->board[init_rank][init_file+1].piece && // there is a piece directly to the right of the moving pawn
        game->board[init_rank][init_file+1].piece->owner != player && // it is not owned by the player
        toupper(game->board[init_rank][init_file+1].piece->icon) == 'P' && // it is also a pawn
        game->last_move[0]-2 == game->last_move[2] && //Black piece moved two squares down last move
        game->last_move[2] == init_rank && game->last_move[3] == init_file+1 //The last move ended on the coordinates directly adjacent to the moving pawn
        ) {
            legality = 2; // valid en passant capture, will require special handling
        }
        //En passant check - to the left
        else if(dest_file == init_file-1 && //correct file for en passant left
        dest_rank == init_rank+1 && //moved one square up the board 
        !game->board[init_rank+1][init_file-1].piece && // the destination square is empty
        game->board[init_rank][init_file-1].piece && // there is a piece directly to the left of the moving pawn
        game->board[init_rank][init_file-1].piece->owner != player && // it is not owned by the player
        toupper(game->board[init_rank][init_file-1].piece->icon) == 'P' && // it is also a pawn
        game->last_move[0]-2 == game->last_move[2] && //Black piece moved two squares down last move
        game->last_move[2] == init_rank && game->last_move[3] == init_file-1 //The last move ended on the coordinates directly adjacent to the moving pawn
        ) {
            legality = 2; // valid en passant capture, will require special handling
        }
        else {
            legality = -3; //illegal piece movement 
        }
    }
    else { //check for capture conditions
        if(dest_rank != init_rank-1) { 
            if(dest_file != init_file+1 && dest_file != init_file-1) {
                legality = -3; //illegal piece movement 
            }
        
        }
    }
    return legality; // valid move
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

//
//Function to determine whether the move would put the same-side king in check




//Max Van Raden
//TEST to see if I can directly convert the Java version instead of rewriting it
//This function was originally written in Java by me for a separate project, and was translated to C++ for use in this project, it is wholly my original work
int is_in_check(chessboard * game, int init_rank, int init_file, int dest_rank, int dest_file, bool is_capture, bool player) {
    int king_rank = -1;
          int king_file = -1;
          int isKing = 0;
          int inCheck = 0; //tracks whether or not the king is in check, needed because the board is set to a temporary state and returning early would prevent me from correcting that
          Piece * temp = NULL;
          Piece * temp2 = NULL;
          if(toupper(game->board[init_rank][init_file].piece->icon) == 'K'){
              king_rank = dest_rank;
              king_file = dest_file;
              isKing = 1;
          }
          else{
            for(int i = 0; i < 8; i++) { //Step one, locate the same side king by iterating through board
                for(int k = 0; k < 8; k++) {
                    if(game->board[i][k].piece != NULL){
                        if((toupper(toupper(game->board[i][k].piece->icon) == 'K')) && game->board[i][k].piece->owner == player) { //locate same side king 
                            king_rank = i;
                            king_file = k; 
                            break;       
                        }
                    }
                }
                if(king_file != -1) {//stop looping once king is found
                    break;
                }
            }
          }
          if(!isKing) { //move the pieces temporarily so that we can check the proposed board state to see if the king is still in check
            temp =  game->board[init_rank][init_file].piece;
            temp2 = game->board[dest_rank][dest_file].piece;
            game->board[dest_rank][dest_file].piece = NULL;
            game->board[dest_rank][dest_file].piece = game->board[init_rank][init_file].piece;
            game->board[init_rank][init_file].piece = NULL;
          }

          //check for knights, includes checks for out of bounds and existing pieces to prevent NULL dereferences
          if(king_rank+2 <= 7 && king_file+1 <= 7 ) {
            if(game->board[king_rank+2][king_file+1].piece != NULL && toupper(game->board[king_rank+2][king_file+1].piece->icon) == 'N' && game->board[king_rank+2][king_file+1].piece->owner != player) {
                inCheck = 1; //king is in check
            }
          }   
          if(king_rank+2 <= 7 && king_file-1 >= 0 ) {
             if(game->board[king_rank+2][king_file-1].piece != NULL && toupper(game->board[king_rank+2][king_file-1].piece->icon) == 'N' && game->board[king_rank+2][king_file-1].piece->owner != player) {
                inCheck = 1; //king is in check
             }
          }
          if(king_rank-2 >= 0 && king_file+1 <= 7) { 
             if(game->board[king_rank-2][king_file+1].piece != NULL && toupper(game->board[king_rank-2][king_file+1].piece->icon) == 'N' && game->board[king_rank-2][king_file+1].piece->owner != player) {
                inCheck = 1; //king is in check
             }
          }
          if(king_rank-2 >= 0 && king_file-1 >= 0 ) {
            if(game->board[king_rank-2][king_file-1].piece != NULL && toupper(game->board[king_rank-2][king_file-1].piece->icon) == 'N' && game->board[king_rank-2][king_file-1].piece->owner != player) {
                 inCheck = 1; //king is in check
            }
          }
          if(king_rank+1 <= 7 && king_file+2 <= 7) {
            if(game->board[king_rank+1][king_file+2].piece != NULL && toupper(game->board[king_rank+1][king_file+2].piece->icon) == 'N' && game->board[king_rank+1][king_file+2].piece->owner != player) {
                inCheck = 1; //king is in check
            }
          }
          if(king_rank+1 <= 7 && king_file-2 >= 0 ) {
            if(game->board[king_rank+1][king_file-2].piece != NULL && toupper(game->board[king_rank+1][king_file-2].piece->icon) == 'N' && game->board[king_rank+1][king_file-2].piece->owner != player) {
                inCheck = 1; //king is in check
            }
          }
          if(king_rank-1 >= 0 && king_file+2 <= 7 ) {
            if(game->board[king_rank-1][king_file+2].piece != NULL && toupper(game->board[king_rank-1][king_file+2].piece->icon) == 'N' && game->board[king_rank-1][king_file+2].piece->owner != player) {
                  inCheck = 1; //king is in check
            }
          } 
          if(king_rank-1 >= 0 && king_file-2 >= 0 ) {
            if(game->board[king_rank-1][king_file-2].piece != NULL && toupper(game->board[king_rank-1][king_file-2].piece->icon) == 'N' && game->board[king_rank-1][king_file-2].piece->owner != player) {
                inCheck = 1; //king is in check
            }
          }
          

          //check the rank and file directions (horizontal and vertical lines for check threats)
          for(int i = king_rank+1; i < 8; ++i) {
              if(game->board[i][king_file].piece != NULL) {
                  if((toupper(game->board[i][king_file].piece->icon) == 'R' || toupper(game->board[i][king_file].piece->icon) == 'Q') && game->board[i][king_file].piece->owner != player) {
                      inCheck = 1; //king is in check 
                  }
                  else {//king is not in check in this direction
                      break;
                  }
              }
          }
          for(int i = king_rank-1; i >= 0; --i) {
              if(game->board[i][king_file].piece != NULL) {
                  if((toupper(game->board[i][king_file].piece->icon) == 'R' || toupper(game->board[i][king_file].piece->icon) == 'Q') && game->board[i][king_file].piece->owner != player) {
                      inCheck = 1; //king is in check 
                  }
                  else {//king is not in check in this direction
                      break;
                  }
              }
          }
          for(int i = king_file+1; i < 8; ++i) {
              if(game->board[king_rank][i].piece != NULL) {
                  if((toupper(game->board[king_rank][i].piece->icon) == 'R' || toupper(game->board[king_rank][i].piece->icon) == 'Q') && game->board[king_rank][i].piece->owner != player) {
                      inCheck = 1; //king is in check 
                  }
                  else {//king is not in check in this direction
                      break;
                  }
              }
          }
          for(int i = king_file-1; i >= 0; --i) {
              if(game->board[king_rank][i].piece != NULL) {
                  if((toupper(game->board[king_rank][i].piece->icon) == 'R' || toupper(game->board[king_rank][i].piece->icon) == 'Q') && game->board[king_rank][i].piece->owner != player) {
                      inCheck = 1; //king is in check 
                  }
                  else {//king is not in check in this direction
                      break;
                  }
              }
          }

          //Check the diagonals 
          for(int i = king_rank+1; i < 8; ++i){
              int notSafe = 1;
              for(int k = king_file+1; k < 8; ++k) {
                  if(abs(king_rank - i) == abs(king_file - k)){
                    if(game->board[i][k].piece != NULL) {
                      if((toupper(toupper(game->board[i][k].piece->icon)) == 'B' || toupper(toupper(game->board[i][k].piece->icon)) == 'Q') && game->board[i][k].piece->owner != player) {
                        inCheck = 1; //king is in check 
                      }
                      //black pawn check
                      else if(toupper(toupper(game->board[i][k].piece->icon)) == 'P' && game->board[i][k].piece->owner != player && player == true && i == king_rank+1 && (k == king_file+1 || k == king_file-1)) {
                        inCheck = 1; //king is in check
                      }
                      //white pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == false && i == king_rank-1 && (k == king_file+1 || k == king_file-1)) {
                        inCheck = 1; //king is in check
                      }
                      else {//king is not in check in this direction
                          notSafe = 0;
                          break;
                      }
                  }
                }
              }
              if(notSafe == 0) {
                  break;
              }
          }
          for(int i = king_rank-1; i >= 0; --i){
            int notSafe = 1;
              for(int k = king_file+1; k < 8; ++k) {
                if(abs(king_rank - i) == abs(king_file - k)){
                  if(game->board[i][k].piece != NULL ) {
                      if((toupper(game->board[i][k].piece->icon) == 'B' || toupper(game->board[i][k].piece->icon) == 'Q') && game->board[i][k].piece->owner != player) {
                          inCheck = 1; //king is in check 
                      }
                      //black pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == true && i == king_rank+1 && (k == king_file+1 || k == king_file-1)) {
                          inCheck = 1; //king is in check
                      }
                      //white pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == false && i == king_rank-1 && (k == king_file+1 || k == king_file-1)) {
                          inCheck = 1; //king is in check
                      }
                      else {//king is not in check in this direction
                          notSafe = 0;
                          break;
                      }
                  }
                }
              }
              if(notSafe == 0) {
                break;
              }
          }
          for(int i = king_rank+1; i < 8; ++i){
            int notSafe = 1;
              for(int k = king_file-1; k >= 0; --k) {
                if(abs(king_rank - i) == abs(king_file - k)){
                  if(game->board[i][k].piece != NULL) {
                      if((toupper(game->board[i][k].piece->icon) == 'B' || toupper(game->board[i][k].piece->icon) == 'Q') && game->board[i][k].piece->owner != player) {
                          inCheck = 1; //king is in check 
                      }
                      //black pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == true && i == king_rank+1 && (k == king_file+1 || k == king_file-1)) {
                          inCheck = 1; //king is in check
                      }
                      //white pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == false && i == king_rank-1 && (k == king_file+1 || k == king_file-1)) {
                          inCheck = 1; //king is in check
                      }
                      else {//king is not in check in this direction
                        notSafe = 0;  
                        break;
                      }
                  }
                }
              }
              if(notSafe == 0) {
                break;
              }
          }
          for(int i = king_rank-1; i >= 0; --i){
            int notSafe = 1;
              for(int k = king_file-1; k >= 0; --k) {
                if(abs(king_rank - i) == abs(king_file - k)){
                  if(game->board[i][k].piece != NULL) {
                      if((toupper(game->board[i][k].piece->icon) == 'B' || toupper(game->board[i][k].piece->icon) == 'Q') && game->board[i][k].piece->owner != player) {
                          inCheck = 1; //king is in check 
                      }
                      //black pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == true && i == king_rank+1 && (k == king_file+1 || k == king_file-1)) {
                          inCheck = 1; //king is in check
                      }
                      //white pawn check
                      else if(toupper(game->board[i][k].piece->icon) == 'P' && game->board[i][k].piece->owner != player && player == false && i == king_rank-1 && (k == king_file+1 || k == king_file-1)) {
                          inCheck = 1; //king is in check
                      }
                      else {//king is not in check in this direction
                        notSafe = 0;  
                        break;
                      }
                  }
                }
              }
              if(notSafe == 0) {
                break;
              }
          }
          //Check for the other king putting the king in check - super gross but frankly not where I want to spend my time right now
          if((king_rank+1 <= 7 && king_file+1 <= 7 && game->board[king_rank+1][king_file+1].piece && toupper(game->board[king_rank+1][king_file+1].piece->icon) == 'K' && game->board[king_rank+1][king_file+1].piece->owner != player) ||
             (king_rank+1 <= 7 && king_file-1 >= 0 && game->board[king_rank+1][king_file-1].piece && toupper(game->board[king_rank+1][king_file-1].piece->icon) == 'K' && game->board[king_rank+1][king_file-1].piece->owner != player) ||
             (king_rank+1 <= 7 && game->board[king_rank+1][king_file].piece && toupper(game->board[king_rank+1][king_file].piece->icon) == 'K' && game->board[king_rank+1][king_file].piece->owner != player) ||
             (king_rank-1 >= 0 && game->board[king_rank-1][king_file].piece && toupper(game->board[king_rank-1][king_file].piece->icon) == 'K' && game->board[king_rank-1][king_file].piece->owner != player) ||
             (king_rank-1 >= 0 && king_file+1 <= 7 && game->board[king_rank-1][king_file+1].piece && toupper(game->board[king_rank-1][king_file+1].piece->icon) == 'K' && game->board[king_rank-1][king_file+1].piece->owner != player) ||
             (king_rank-1 >= 0 && king_file-1 >= 0 && game->board[king_rank-1][king_file-1].piece && toupper(game->board[king_rank-1][king_file-1].piece->icon) == 'K' && game->board[king_rank-1][king_file-1].piece->owner != player) ||
             (king_file+1 <= 7 && game->board[king_rank][king_file+1].piece && toupper(game->board[king_rank][king_file+1].piece->icon) == 'K' && game->board[king_rank][king_file+1].piece->owner != player) || 
             (king_file-1 >= 0 && game->board[king_rank][king_file-1].piece && toupper(game->board[king_rank][king_file-1].piece->icon) == 'K' && game->board[king_rank][king_file-1].piece->owner != player)) {
                 inCheck = 1;
             }
          //reset board to original position
          if(!isKing) {
            game->board[init_rank][init_file].piece = temp;
            game->board[dest_rank][dest_file].piece = temp2;
          }
          if(inCheck) {
              return -8; //The king is in check
          }
}