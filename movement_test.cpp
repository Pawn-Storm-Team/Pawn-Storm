#include "board.h"
#include <iostream>

using namespace std;


int move_test(chessboard * game){
  int result = 0;
  result = pawn_test();
  result = rook_test();
  result = knight_test();
  result = bishop_test();
  result = queen_test();
  result = king_test();

  return result;
}

int pawn_test(chessboard * game){
  int result = 0;
  cout << "\nmove 2A white pawn 3C, want valid: " << game.make_move(game,2,1,3,1, true);  
  cout << "move 2B white pawn 4B, want valid: " << game.make_move(game,2,2,4,2, true); 
  cout << "move 2C white pawn 5C, want invalid: " << game.make_move(game,2,1,5,1, true);
  cout << "move 2D white pawn to 4C, want invalid: "<< game.make_move(game,2,1,3,1, true);  
  cout << "move 2E white pawn to 3F, want invalid: " << game.make_move(game,2,1,3,1, true);
  cout << "game.display
  cout << "move game.make_move(game,2,1,3,1, true);
  result = game.make_move(game,2,1,3,1, true);
  result = game.make_move(game,2,1,3,1, true);
  return result;
}

int main(){
chessboard game = initialize();
movetest(&game);

}
