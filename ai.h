class chessboard;


/*
Step 1: pass in current board state, current player, and depth to go to, and int [] for the move to be played
Step 2: find all valid moves in current board state, make all current moves as recursive calls, switching current player and decrementing depth
Step 3: if depth is still not zero, repeat step 2
Step 4: once depth is zero, return max/min board state value (and set the move) depending on current player
Step 5: unravel and return ultimate result
*/
struct ai_move {
    int state_value = 0; //the value of the board state
    int move [4] = {-1, -1, -1, -1};
};

ai_move minimax(chessboard * game, bool player, int depth);
