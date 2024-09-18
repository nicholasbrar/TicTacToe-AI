#include <iostream>

using namespace std;

class TicTacToe {
  public: char board[3][3];
  char turn = 'X';
  TicTacToe() {
    initializeBoard();
  }

  void initializeBoard() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        board[i][j] = ' ';
      }
    }
  }

  void printBoard() {
    cout << "----------\n";
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        cout << "| " << board[i][j];
      }
      cout << "|\n----------\n";
    }
  }

  bool boardFull() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == ' ') { // Returns false if there's an empty square
          return false;
        }
      }
    }
    return true;
  }

  bool isValidMove(int r, int c){
    return(r >= 0 && r < 3 && c >= 0 && c < 3 && board[r][c] == ' ');
  }

  void makeMove(int row, int col) {
    if(isValidMove(row, col)){
      board[row][col] = turn;
      return;
    }
  }

  void getMove() {
    int row, col;

    cout << "Enter move(row , column): ";
    cin >> row >> col;
    makeMove(row - 1, col - 1);
  }

  int evaluateBoard() {
    for (int row = 0; row < 3; row++) {
      if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
        if (board[row][0] == 'X')
          return 10;
        else if (board[row][0] == 'O')
          return -10;
      }
    }
    for (int col = 0; col < 3; col++) {
      if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
        if (board[0][col] == 'X')
          return 10;
        else if (board[0][col] == 'O')
          return -10;
      }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
      if (board[0][0] == 'X')
        return 10;
      else if (board[0][0] == 'O')
        return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
      if (board[0][2] == 'X')
        return 10;
      else if (board[0][2] == 'O')
        return -10;
    }
    return 0;
  }

  int minimax(int depth, bool isMaximizing) {
    int score = evaluateBoard();

    if (score == 10) {
      return score;
    }
    if (score == -10) {
      return score;
    }
    if (boardFull()) {
      return 0;
    }
    if (!isMaximizing) { // Minimizing player
      int bestScore = 1000; 
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (board[i][j] == ' ') {
            board[i][j] = 'O';
            int score = minimax(depth + 1, !isMaximizing); 
            board[i][j] = ' ';
            bestScore = min(score, bestScore);
          }

        }

      }
      return bestScore;

    } else { // Maximizing player
      int bestScore = -1000;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          if (board[i][j] == ' ') {
            board[i][j] = 'X';
            int score = minimax(depth + 1, !isMaximizing);
            board[i][j] = ' ';
            bestScore = max(score, bestScore);
          }
        }
      }
      return bestScore;
    }
  }
  int findBestMove() {
    int placeholder = -100; 
    int row = -1, col = -1;  

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (board[i][j] == ' ') {
          board[i][j] = 'X';
          int moveEvaluation = minimax(0, false); // Calculate evaluation of a move
          board[i][j] = ' ';

          if (moveEvaluation > placeholder) { // If the move is better than the current best move, update the best move
            placeholder = moveEvaluation;
            row = i;
            col = j;
          }
        }
      }
    }
    makeMove(row, col);
    return 0;
  }
  void play() {
    cout << "-- TICTACTOE --\n" << endl;

    while (!boardFull() && evaluateBoard() == 0) { 
      if (turn == 'X') { // Computer's turn
        findBestMove();
      } else { 
        getMove(); // Human's turn
      }

      printBoard();
      
      if (evaluateBoard() == 0) { // If there is no winner
        turn = (turn == 'X' ? 'O' : 'X');
      } else { // If there is a winner
        printBoard();
        char winner = (evaluateBoard() == 10 ? 'X' : 'O');
        cout << "Winner is " << winner << endl;
        return;
      }
    }
    if (boardFull() && evaluateBoard() == 0) { // If there is no winner and board is full, then drawn game
      printBoard();
      cout << "It's a draw\n";
    }
  }
};

int main() {
  TicTacToe game;
  game.play();
}
