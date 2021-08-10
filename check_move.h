#include "board.h"

int agnostic_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int white_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int black_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int knight_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int bishop_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int rook_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int queen_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int king_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);