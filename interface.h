//
// John Bedette
//
//
//
#include "board.h"

enum GameType{ local, whiteOnline, blackOnline, whiteAI, BlackAI}


class Interface{
        chessboard board;
        bool white, black, mult;
        GameType gameType;
        int intro();
        int menu();

    public:
        Interface();
        ~Interface();
};