#include "ai.h"

ai_move minimax(chessboard * game, bool player, int depth) {
      //determine legal moves 
      //gen_moves
      
      //leaf
      if(depth == 0) {
        chessboard * dupe = game.duplicate();
        dupe.gen_moves(player,dupe);
        ai_move move;
        move_list move[332];
        move.state_value = game->get_value();
        for(int i = 0; i < 4; ++i) {
          move.move[i] = game->last_move[i];
        }
        return move;
      }
      //while(!game->legal_moves.empty()){
      while(!dupe->legal_moves.empty()){
        move 
      }
        /*for(all legal moves) {
            //theoretical,ai_move move_list[332], likely too high upper bound on possible moves per board state
            make the move
            move_list[i] = minimax(modified_game, !player, depth-1)
        }
        if(player){
            ai_move max;
            max.state_value = -99999;
            for(int i = 0; i < 333; ++i) {
                if(move_list[i].state_value >= max.state_value) {
                    // ask max what to do on this later max.state_value = move_list[i].statevalue
                    max.move[i] = move_list[i].move[i]
                }

            return max;
        else
            ai_move min;
            max.state_value = 99999;
            for(int i = 0; i < 333; ++i) {
                if(move_list[i].state_value <= max.state_value) {
                    max.state_value = move_list[i].statevalue
                    max.move[i] = move_list[i].move[i]
                }
            }
            return min;
