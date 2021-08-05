// John Bedette
//
// Game class will handle non-board specific game states
// eg: who's turn is it, game type [local play, vs ai, online]
//
// TODO I thought about putting this into interface,
// but though it best to keep it separate for now. 

enum GameType{ local, whiteOnline, blackOnline, whiteAI, BlackAI};

class Game{
    Game(GameType,int);
    ~Game();

    GameType gameType;
    int current_turn;
    bool game_complete;

    int build_switch();
    int build_local_game();
    int build_online_game();
    int build_vs_AI();

    int action_prompt();
    int turn_prompt(int[]) 
}