//
// john bedette 
//
//
//

#include <iostream>
#include <string>
#include "interface.h"
using namespace std;

Interface::Interface(){

  //check_test();
  //make board init values
  //board.initialize();
  gameType = local; 
  current_turn = 0;
  game_complete = false;
  //
  menu();
}

Interface::~Interface(){
};

int Interface::menu(){
  cout << "\t\t Welcome to PawnStorm! \t\t\n\n";
  //intro();
  board.initialize();
  action_prompt();
  return 0;
}
int Interface::intro() {

  string input = string();
  disp_intro_menu();

  cin >> input;
  cin.clear();
  cin.ignore();
  int choice;
  while(
      !(isdigit(input[0]) && input.length() == 1) &&   //check if input is valid - both a single character and numeric
      (choice = stoi(input)) >= 1 && choice <= 6      //by this point isdigit and input length should have guaranteed  
      ){                                              //input is a single digit integer, we assign and then check range
    cout << "\tThis input is invalid. Please enter a single digit corresponding to your desired menu choice.\n\n";
    input.clear();
    cout << "\n>> ";
    cin >> input;
    cin.clear();
    cin.ignore();
  }


  //games will be different based on local etc.
  //in a local game, distinction between black and white is unnecessary
  //online we would need to know who goes first
  //ai we would need to spool up ai and have it know its white or black
  switch(input[0]) {
    case '1':
      break;
    case '2':
      gameType = whiteAI;
      break;
    case '3':
      gameType = blackAI;
      break;
    case '4':
      cout << "Goodbye";
      break;
    default: 
      cout << "Invalid Choice.";
      choice = intro();//call the function again from the top, capture correct choice value from recursive response
  }
  return choice;
}


//manages the prompts each player will recieve, making it clearer who is going right now, 
//give options for who's taken what, etc
int Interface::action_prompt(){

  while(!game_complete){
    //main turn pattern
    if(gameType == whiteAI){
      ai_turn();
      ++current_turn;
    }
    else {
      int error_code = turn_prompt();
      while(error_code < 0){
        cout << "Illegal move, try again, error code: " << error_code;
        error_code = turn_prompt();
      };
    }
    if(gameType == blackAI){
      ++current_turn;
      ai_turn();
    }
    ++current_turn;
    game_complete = board.gen_moves(current_turn%2,&board);
  }
  if(!(current_turn % 2)){
    board.draw_board();
    cout << "White";
  }
  else{ 
    board.draw_board();
    cout << "Black";
  }
  cout << " Wins!\n";
  return -1;
}



//turn prompting
int Interface::turn_prompt(){

  //check member for who's turn it is, set string to white or black
  if(current_turn % 2){
    board.draw_board_black();
    cout << "Black";
  }
  else{ 
    board.draw_board();
    cout << "White";
  }
  cout << ", turn "<< current_turn  <<"\nFormat move as A1:B2\n$ ";

  string input = string();

  cin >> input;
  cin.clear();
  cin.ignore();
  input = convert_input(input);
  //todo sanitize further
  //glaring holes
  // - 7 digit numbers
  // - other things I haven't thought of

  int valid = 0;
  while(!(valid = move_format_validator(input[0],input[1],input[3],input[4]))){
    cout << "\tThis input is invalid. Please enter only digits in A1:B2 formatting.\n\n";
    input.clear();
    cout << "\n>> ";
    cin >> input;
    input = convert_input(input);
    cin.clear();
    cin.ignore();
  }

  //ab is origin, xy is dest
  //by this point we know they're numbers between 1 and 8
  //subtractin char 1 and storing them in int will extract the numbers
  int a, b, x, y, out;
  a = input[0] - '1';
  b = input[1] - '1';
  x = input[3] - '1';
  y = input[4] - '1';
  out = board.make_move(&board,a,b,x,y,current_turn%2);
  /*
  //testing
  cout << "/n>>>>>>>testing board dup\n";
  chessboard * dupe = board.duplicate();
  cout << "/n>>>>>>> dup draw\n";
  dupe->draw_board();
  */
  return board.make_move(&board,b,a,y,x,current_turn%2); //order changed so that file, rank input can be translated to rank, file format for throughput 
}

//this here verifies that given char represents a number within our desired range
int range_validator(char a){
  if(isdigit(a)){
    int b = a - '0';
    if(b>=1 && b <=8) return 0;
  }
  return 1;
}

//this checks all four input values
//we're subtracting double negative from valid, so if any of these pops a "YES this DOESNT work" we get back invalid 
bool Interface::move_format_validator(char a, char b, char x, char y){
  int valid = 0;
  valid -= range_validator(a);
  valid -= range_validator(b);
  valid -= range_validator(x);
  valid -= range_validator(y);
  return valid >= 0;
}

void Interface::disp_intro_menu(){
  cout << "\t 1.\tPlay against a local opponent \t\t\n\n";

  cout << "\t 2.\tPlay against the AI as White \t\t\n\n";
  cout << "\t 3.\tPlay against the AI as Black \t\t\n\n";
  cout << "\t 4.\tExit \t\t\n\n";
  cout << "\n>> ";
}

int Interface::build_local_game(){
  return 0;
};
int Interface::build_online_game(){
  return 0;
};
int Interface::build_vs_AI(){
  return 0;
};

string Interface::convert_input(string input) {
  for(int i = 0; i < 6; ++i) {
    if(i != 2) {
      if(toupper(input[i]) == 'A') {
        input[i] = '1'; 
      }
      if(toupper(input[i]) == 'B') {
        input[i] = '2'; 
      }
      if(toupper(input[i]) == 'C') {
        input[i] = '3'; 
      }
      if(toupper(input[i]) == 'D') {
        input[i] = '4'; 
      }
      if(toupper(input[i]) == 'E') {
        input[i] = '5'; 
      }
      if(toupper(input[i]) == 'F') {
        input[i] = '6'; 
      }
      if(toupper(input[i]) == 'G') {
        input[i] = '7'; 
      }
      if(toupper(input[i]) == 'H') {
        input[i] = '8'; 
      }
    }
  }
  return input;
}

//check if in check via pieces
//check if check can be blocked
void Interface::check_test(){
  //chk 1 
  chessboard * a = new chessboard();
  a->board[4][4].piece = new King(1);
  a->board[5][5].piece = new Rook(0);
  a->board[3][3].piece = new Rook(0);
  int err_1 = a->make_move(a, 4,4,5,4,0);
  a->draw_board();
  a->board[5][4].piece = nullptr;
  a->board[4][4].piece = new King(0);
  a->board[5][5].piece = nullptr;
  a->board[3][3].piece = nullptr;
  int suc_1 = a->make_move(a, 4,4,5,4,0);
  a->draw_board();

  cout << "\n chk1: " << err_1 << ' ' << suc_1;
}

void Interface::ai_turn() {
    ai_move move;
    move = minimax(&board,current_turn%2, 3);
    board.ai_move(move.move[0], move.move[1], move.move[2], move.move[3]);
    return;
}
