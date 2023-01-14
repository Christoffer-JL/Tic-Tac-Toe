#include <util/delay.h>

#include <stdbool.h>

extern int board[];
extern int difficulty;
extern int tur;
extern int keypad;
extern int convertToCase(int n);
extern int checkWin(int board[9]);
extern int findTopMove(int board[9]);
extern bool checkMove(int move);
extern void switchTurn();
extern void playMove();

int easy();
int normal();
void playAIMove();

// Easy difficulty. Computer tries to make a random move and places it if it doesn't win the game. Returns the move played
int easy()
{

  int move;
  int board2[9];

  for (int i = 0; i <= 8; i++)
  {
    board2[i] = board[i];
  }

  int failSafe = 0;

  while (1)
  {
    failSafe++;
    move = rand() % 9;

    while (!checkMove(move))
    {
      move = rand() % 9;
    }

    board2[move] = turn;

    if (checkWin(board2) == 0)
    {
      board2[move] == 0;
      return move;
    }

    board2[move] == 0;

    if (failSafe == 50)
    {
      return normal();
    }
  }
}

// Normal difficulty, places a random move and returns the move played
int normal()
{

  while (1)
  {

    int move = rand() % 9;
    if (checkMove(move))
    {
      return move;
    }
  }
}

// Calls the play class for the chosen difficulty
void playAIMove()
{
  int move;
  if (grad == 1)
  {
    move = easy();
  }
  else if (grad == 2)
  {
    move = normal();
  }
  else if (grad == 3)
  {
    move = hittaTopMove(board);
  }

  playMove(convertToCase(move));

  switchTurn();
}