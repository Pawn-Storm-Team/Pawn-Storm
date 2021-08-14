//
// Created by Max Van Raden on 3/27/21.
//
#include "board.h"
#include "check_move.h"
#include <vector>
using namespace std;
square::square() {
  piece = nullptr;
}

square::~square() {
  if(piece) {
    delete piece;
    piece = nullptr;
  }

}

//Adds the pieces for a standard ascii-chess game to the board
int chessboard::initialize() { //can be used to reset or initialize the board
  for(int i = 0; i < 8; ++i) { //wipes the board clean, no pieces
    for(int k = 0; k < 8; ++k){
      if(board[i][k].piece != nullptr){
        delete board[i][k].piece;
        board[i][k].piece = nullptr;
      }
    }
  }
  for(int i = 0; i < 8; ++i) {
    bool color = true; 
    for(int k = 0; k < 8; ++k){
      if(i > 3) { // switch color flag to initialize black's pieces 
        color = false;
      }
      if(i == 0 || i == 7) { //rank is 1, white backrank, initialize with pieces
        if(k == 0 || k == 7) //A1 or H1, white rooks
          board[i][k].piece = new Rook(color);
        if(k == 1 || k == 6) //B1 or G1, white knights
          board[i][k].piece = new Knight(color);
        if(k == 2 || k == 5) //C1 or F1, white bishops
          board[i][k].piece = new Bishop(color);
        if(k == 3) //D1, white queen
          board[i][k].piece = new Queen(color);
        if(k == 4) //E1, white king
          board[i][k].piece = new King(color);
      }
      if(i == 1 || i == 6) { //rank is 2, white frontrank, initialize with pawns
        board[i][k].piece = new Pawn(color);
      }
    }
  }
  //test_move();
  return 0;
}
//frees memory allocated during piece creation
int chessboard::clear() {
  int count = 0;
  for(int i = 0; i < 8; ++i) { //wipes the board clean, no pieces
    for(int k = 0; k < 8; ++k){
      if(board[i][k].piece != nullptr){
        delete board[i][k].piece;
        board[i][k].piece = nullptr;
        ++count;
      }
    }
  }
  return count;
}

int chessboard::get_pieces() {
  int count = 0;
  for(int i = 0; i < 8; ++i) {
    for(int k = 0; k < 8; ++k){
      if(board[i][k].piece)
        ++count;
    }
  }
  return count;
}

void chessboard::draw_board() {
  std::cout << "\n\n";
  std::cout << "\t   A     B     C     D     E     F     G     H"<< std::endl;
  for(int i = 7; i >= 0; --i) { //print from white's perspective, so first square printed will be A8, so ranks count backwards
    std::cout << "\t   -     -     -     -     -     -     -     -" << std::endl;
    std::cout << i+1 << "\t";
    for(int k = 0; k < 8; ++k) {
      if(board[i][k].piece)
        //std::cout << "| P ";
        std::cout << "|  " << board[i][k].piece->icon << "  ";
      else
        std::cout << "|     ";
    }
    std::cout << "|\t" << i+1 << std::endl;
  }
  std::cout << "\t   -     -     -     -     -     -     -     -" << std::endl;
  std::cout << "\t   A     B     C     D     E     F     G     H"<< std::endl;
}


void chessboard::draw_board_black() {
    std::cout << "\n\n";
    std::cout << "\t   H     G     F     E     D     C     B     A"<< std::endl;
    for(int i = 0; i <= 7; ++i) { //print from black's perspective, so first square printed will be H1, so ranks count forward
        std::cout << "\t   -     -     -     -     -     -     -     -" << std::endl;
        std::cout << i+1 << "\t";
        for(int k = 7; k >= 0; --k) { //print from black's perspective, so first file is H
            if(board[i][k].piece)
                std::cout << "|  " << board[i][k].piece->icon << "  ";
            else
                std::cout << "|     ";
        }
        std::cout << "|\t" << i+1 << std::endl;
    }
    std::cout << "\t   -     -     -     -     -     -     -     -" << std::endl;
    std::cout << "\t   H     G     F     E     D     C     B     A"<< std::endl;
}



int chessboard::make_move(chessboard * game,int a, int b, int x, int y, bool color){
  //if move is illegal, send error, redo turn
  if(check_move(game,a,b,x,y,!color)< 0){

    cout << "Illegal move, please try again";
    return 1;
  }

  board[x][y].piece = board[a][b].piece;
  board[a][b].piece = nullptr;
  //populate last move
  last_move[0] = a;
  last_move[1] = b;
  last_move[2] = x;
  last_move[3] = y;

  return 0;
}

//interface passed color
//generate all the moves, store in legal_move vector of strings
//will be called every turn
//iterate through board
//if piece exists call generate_moves,
//capture strings of possible moves in vector,
//pass each through the move check,
//push possible moves into vector<string> of moves,
//if no possible moves, indicate to interface that game is complete
bool chessboard::gen_moves(bool color, chessboard * game){
  for(int i = 0; i < 7; ++i){
    for(int j = 0; j < 7;++j){

      Piece * curr = board[i][j].piece;
      if(curr && curr->owner == color){

        vector<vector<int>> moves;
        curr->generate_moves(moves, i, j);


        while(!moves.empty()){
          vector<int> move_vec (4,-1);
          copy(moves[moves.size()-1].begin(),moves[moves.size()-1].end(),move_vec.begin());
          moves.pop_back();
          if(check_move(game,move_vec[0],move_vec[1],move_vec[2],move_vec[3],!color)){
            legal_moves.push_back(move_vec);
          }
        }

      }
    }
  }
  return legal_moves.empty();
}
//iterates throught the board, incrementing/decrementing
//the total board state value based on the owner and type of piece
int chessboard::get_value() { 
  int state_value = 0; 
  for(int i = 0; i < 8; ++i) {
    for(int k = 0; k < 8; ++k){
      if(board[i][k].piece) {
        if(board[i][k].piece->owner) {
          state_value += board[i][k].piece->value;
        }
        else {
          state_value -= board[i][k].piece->value;
        }
      }     
    }
  }
  return state_value;
}

//deep copy board for ai simming
chessboard * chessboard::duplicate(){
  chessboard * dupe = new chessboard();
  //get last move
  for (int k = 0; k < 4;++k){
    dupe->last_move[k] = last_move[k];
  }
  //copy legal_moves
  dupe->legal_moves = legal_moves;

  //copy board
  for(int i = 0; i < 8; ++i){
    for(int j = 0; j < 8; ++j){
      Piece * p = board[i][j].piece;
      if(p){
        char icon = p->icon;
        bool color = p->owner;
        if (toupper(icon) == 'P'){
          dupe->board[i][j].piece = new Pawn(color);
        }
        else if (toupper(icon) == 'R'){
          dupe->board[i][j].piece = new Rook(color);
        }
        else if (toupper(icon) == 'N'){
          dupe->board[i][j].piece = new Knight(color);
        }
        else if (toupper(icon) == 'B'){
          dupe->board[i][j].piece = new Bishop(color);
        }
        else if (toupper(icon) == 'Q'){
          dupe->board[i][j].piece = new Queen(color);
        }
        else if (toupper(icon) == 'K'){
          dupe->board[i][j].piece = new King(color);
        }
      }
    }
  }
  return dupe;
}








