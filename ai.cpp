#include "ai.h"
#include "board.h"

//
chessboard * dup_helper(chessboard * board, int a, int b, int x, int y){
  board->ai_move(a,b,x,y);
  return board;
}
ai_move minimax(chessboard * game, bool player, int depth) {
      //determine legal moves
      //gen_moves
      
      //base case, the tree is at a leaf and will not go any further. Return current state value and last_move coordinates 
      if(depth == 0) {
        ai_move move;
        move.state_value = game->get_value();
        for(int i = 0; i < 4; ++i) {
          move.move[i] = game->last_move[i];
        }
        return move;
      }
      //Meat of the recursion
      //list of ai_move structs sized at theoretical maximum legal moves
      game->gen_moves(player, game);//generate all legal moves for the current player in the current board state
      cerr << "\n array setting:" << game->legal_moves.size()-1;
      ai_move * move_list = new ai_move[game->legal_moves.size()-1];

      for(int i = 0; i < game->legal_moves.size(); ++i) {
        //chessboard * temp = game->duplicate();
        //temp->ai_move(temp->legal_moves[i][0],temp->legal_moves[i][1],temp->legal_moves[i][2],temp->legal_moves[i][3]);
        move_list[i] = minimax(dup_helper(game,game->legal_moves[i][0], game->legal_moves[i][1],game->legal_moves[i][2],game->legal_moves[i][3]),!player, depth-1); //Call with the duplicated, changed board, the opposite of the current player flag, and decremented depth
        //cerr << "\n1st" << i;
        //delete temp;
        //cerr << " Post 1st" << '\n';
      }
      if(player){
          ai_move max;
          max.state_value = -99999;
          for(int i = 0; i < game->legal_moves.size(); ++i) {
              if(move_list[i].state_value > max.state_value) {                    
                  max.state_value = move_list[i].state_value;
                  for(int k = 0; k < 4; k++) {//loop to populate the four move coordinates 
                    max.move[k] = move_list[i].move[k]; 
                  }
              }
          //cerr << "\n2nd" << i << '\n';
          }
          delete move_list;
          return max;
      }
      else {
            ai_move min;
            min.state_value = 99999;
            for(int i = 0; i < game->legal_moves.size(); ++i) {
              if(move_list[i].state_value < min.state_value) {                    
                  min.state_value = move_list[i].state_value;
                  for(int k = 0; k < 4; k++) {//loop to populate the four move coordinates 
                    min.move[k] = move_list[i].move[k]; 
                  }
              }
          //cerr << "\n3rd" << i << '\n';
          }
          delete move_list;
          return min;   
      }
}
