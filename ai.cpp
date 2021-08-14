#include "ai.h"

ai_move minimax(chessboard * game, bool player, int depth) {
    if(depth != 0) {
        //determine legal moves 
        //gen_moves
        if(depth == 0) {
            ai_move move;
            move.state_value = game->get_value();
            for(int i = 0; i < 5; ++i) {
                move.move[i] = game->last_move[i];
            }
            return move;
        }
        /*for(all legal moves) {
            ai_move move_list[332]; //theoretical, likely too high upper bound on possible moves per board state
            make the move
            move_list[i] = minimax(modified_game, !player, depth-1)
        }
        if(player){
            ai_move max;
            max.state_value = -99999;
            for(int i = 0; i < 333; ++i) {
                if(move_list[i].state_value >= max.state_value) {
                    max.state_value = move_list[i].statevalue
                    max.move[i] = move_list[i].move[i]
                }
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
        */
    }
}