/*
#include "board.h"
#include <iostream>
using namespace std;

//check if in check via pieces
//check if check can be blocked
void board::check_test(){
  //chk 1 
  chessboard * a = new chessboard();
  a->board[4][4].piece = new King(0);
  a->board[5][5].piece = new Rook(1);
  a->board[3][3].piece = new Rook(1);
  int err_1 = make_move(a, 4,4,5,4,0);
  a->board[5][4].piece = nullptr;
  a->board[4][4].piece = new King(0);
  a->board[5][5].piece = nullptr;
  a->board[3][3].piece = nullptr;
  int suc_1 = make_move(a, 4,4,5,4,0);
  
  cout << "\n chk1: " << err_1 << ' ' << suc_1;
}
*/
