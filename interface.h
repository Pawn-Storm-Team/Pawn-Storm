//
// John Bedette
//
//
//
#include "board.h"

enum GameType{ local, whiteOnline, blackOnline, whiteAI, BlackAI};


class Interface{
        chessboard board;
        GameType gameType;
        int current_turn;
        bool game_complete;
        public:
        

        Interface();
        ~Interface();

        int intro();
        int menu();

        int build_switch();
        int build_local_game();
        int build_online_game();
        int build_vs_AI();

        int action_prompt();
        int turn_prompt();
        bool move_format_validator(char,char,char,char);
        void disp_intro_menu();
};