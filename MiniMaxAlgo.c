#include <avr/io.h>

#include <stdlib.h>

#include <stdio.h>

#include <time.h>

#include <stdbool.h>

extern void switchTurn();
extern int turn;
extern int checkWin(int board[9]);
extern int board[9];

int findTopMove(int board[9]);
int max(int a, int b);
int min(int a, int b);
int miniMax(int board[9], int depth, bool isMax);

// returns the max integer out of the two parameters
int max(int a, int b)
{
  if (a < b)
  {
    return b;
  }
  else if (a > b)
  {
    return a;
  }

  return a;
}

// returns the min integer out of the two parameters
int min(int a, int b)
{
  if (a < b)
  {
    return a;
  }
  else if (a > b)
  {
    return b;
  }

  return a;
}
// A recursive miniMax algorythm used to find the best move for hard difficulty
int miniMax(int board[9], int depth, bool isMax)
{
  int p = checkWin(board);

  if (p != 0)
  {
    return p;
  }

  if (isMax)
  {
    int top = -1000;

    for (int i = 0; i <= 8; i++)
    {
      if (board[i] == 0)
      {
        board[i] = 1;
        top = max(top, miniMax(board, depth + 1, !isMax));
        board[i] = 0;
      }
    }
    return top;
  }
  else
  {
    int top = 1000;

    for (int i = 0; i <= 8; i++)
    {
      if (board[i] == 0)
      {
        board[i] = 2;
        top = min(top, miniMax(board, depth + 1, !isMax));
        board[i] = 0;
      }
    }
    return top;
  }
}

// Recursive call to the miniMax method and modifications to find top move
int findTopMove(int board[9])
{

  int c = 0;
  for (int i = 0; i <= 8; i++)
  {
    if (board[i] != 0)
    {
      c++;
    }
  }
  if (c == 0)
  {
    while (true)
    {
      int move = rand() % 9;

      if (move == 0 || move == 2 || move == 6 || move == 8)
      {
        return move;
      }
    }
  }

  int board2[9];

  for (int i = 0; i <= 8; i++)
  {
    board2[i] = board[i];
  }

  for (int i = 0; i <= 8; i++)
  {
    if (checkMove(i))
    {
      board2[i] = tur;
      if (checkWin(board2) == tur)
      {

        return i;
      }

      board2[i] = 0;
    }
  }

  for (int i = 0; i <= 8; i++)
  {
    board2[i] = board[i];
  }

  for (int i = 0; i <= 8; i++)
  {
    if (checkMove(i))
    {
      board2[i] = 2;
      if (checkWin(board2) == 2)
      {

        return i;
      }

      board2[i] = 0;
    }
  }

  int topVal = -1000;
  int topMove = -1;
  for (int i = 0; i <= 8; i++)
  {
    if (board[i] == 0)
    {
      board[i] = turn;
      int moveVal = miniMax(board, 0, false);
      board[i] = 0;

      if (moveVal > topVal)
      {
        topMove = i;
        topVal = moveVal;
      }
    }
  }
  return topMove;
}