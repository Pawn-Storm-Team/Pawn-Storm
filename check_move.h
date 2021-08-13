//forward declaration of chessboard
class chessboard;

int check_move(chessboard * game, int init_rank, int init_file, int dest_rank, int dest_file, bool player);
int agnostic_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file, bool player);

int white_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file,bool is_capture);
int black_pawn_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file,bool is_capture);
int knight_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int bishop_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int rook_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int queen_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);
int king_check(chessboard * game, int init_rank,int init_file,int dest_rank,int dest_file);