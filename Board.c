#include <stdbool.h>

#include <avr/io.h>

#include <util/delay.h>

extern int turn;
extern int board[9];
extern int keypad;
extern red();
extern zero();

bool checkMove(int drag);
int convertToKeypad(int n);
int convertFromKeypad(int n);
int checkWin(int board[9]);

// Sets the DDR for a specific pixel
void setDDR(int pixel)
{

  switch (pixel)
  {

  case 4:

    DDRD = 0b00000100;
    DDRB = 0b00000000;

    break;

  case 6:

    DDRD = 0b00000010;
    DDRB = 0b00000000;

    break;

  case 7:

    DDRD = 0b00000001;
    DDRB = 0b00000000;

    break;

  case 8:

    DDRD = 0b00100000;
    DDRB = 0b00000000;

    break;

  case 11:

    DDRD = 0b00001000;
    DDRB = 0b00000000;

    break;

  case 10:

    DDRD = 0b00010000;
    DDRB = 0b00000000;

    break;

  case 15:

    DDRD = 0b01000000;
    DDRB = 0b00000000;

    break;

  case 14:

    DDRB = 0b00000001;
    DDRD = 0b00000000;

    break;

  case 12:

    DDRB = 0b00000010;
    DDRD = 0b00000000;

    break;
  }
}
// Converts and returns the vector value to the keypad value
int convertToKeypad(int n)
{
  int newN;
  if (n == 0)
  {
    newN = 12;
  }
  else if (n == 1)
  {
    newN = 14;
  }
  else if (n == 2)
  {
    newN = 15;
  }
  else if (n == 3)
  {
    newN = 8;
  }
  else if (n == 4)
  {
    newN = 10;
  }
  else if (n == 5)
  {
    newN = 11;
  }
  else if (n == 6)
  {
    newN = 4;
  }
  else if (n == 7)
  {
    newN = 6;
  }
  else if (n == 8)
  {
    newN = 7;
  }
  return newN;
}
// Converts the keypad value to vector value
int convertFromKeypad(int n)
{
  int newN;
  if (n == 12)
  {
    newN = 0;
  }
  else if (n == 14)
  {
    newN = 1;
  }
  else if (n == 15)
  {
    newN = 2;
  }
  else if (n == 8)
  {
    newN = 3;
  }
  else if (n == 10)
  {
    newN = 4;
  }
  else if (n == 11)
  {
    newN = 5;
  }
  else if (n == 4)
  {
    newN = 6;
  }
  else if (n == 6)
  {
    newN = 7;
  }
  else if (n == 7)
  {
    newN = 8;
  }
  return newN;
}
// Plays a move (input is keypad value)
void playMove(int location)
{

  board[convertFromKeypad(location)] = turn;

  setDDR(location);

  if (turn == 1)
  {
    blue();
  }
  else if (turn == 2)
  {
    green();
  }

  int winner = checkWin(board);

  if (winner != 0)
  {
    winAnimation(winner);
  }
}

// Changes the color of all pixels and flashes them, depending on who won
void winAnimation(int winner)
{

  DDRB = 0b00000011;
  DDRD = 0b01111111;

  if (winner == 2)
  {
    while (PINA != 3)
    {
      green();
      _delay_ms(1000);
      zero();
      _delay_ms(1000);
    }
  }
  else if (winner == 1)
  {
    while (PINA != 3)
    {
      blue();
      _delay_ms(1000);
      zero();
      _delay_ms(1000);
    }
  }
  else if (winner == -1)
  {
    while (PINA != 3)
    {
      red();
      _delay_ms(1000);
      zero();
      _delay_ms(1000);
    }
  }
  DDRB = 0b00000011;
  DDRD = 0b01111111;
  zero();
  DDRD = 0b00000000;
  DDRB = 0b00000100;
  red();
}

// Checks if someone has won and if so returs who. If someone is yet to win, 0 is returned
int checkWin(int board[9])
{

  for (int x = 0; x <= 2; x++)
  {
    if (board[3 * x] != 0 && board[3 * x] == board[3 * x + 1] && board[3 * x] == board[3 * x + 2])
    {
      return board[3 * x];
    }
  }

  for (int y = 0; y <= 2; y++)
  {
    if (board[y] != 0 && board[y] == board[y + 3] && board[y] == board[y + 6])
    {
      return board[y];
    }
  }

  if (board[0] != 0 && board[0] == board[4] && board[0] == board[8])
  {
    return board[0];
  }
  else if (board[2] != 0 && board[2] == board[4] && board[2] == board[6])
  {
    return board[2];
  }

  int cot = 0;
  for (int i = 0; i <= 8; i++)
  {
    if (board[i] != 0)
    {
      cot++;
    }
  }

  if (cot == 9)
  {
    return -1;
  }

  return 0;
}

// Checks the lagality of the move and returns a boolean
bool checkMove(int drag)
{
  if (board[drag] == 0)
  {
    return true;
  }
  return false;
}

// Switches the turn for the players
void switchTurn()
{
  DDRD = 0b00000000;
  DDRB = 0b00000100;
  if (turn == 1)
  {
    turn = 2;
    green();
  }
  else if (turn == 2)
  {
    turn = 1;
    blue();
  }
}

// Resets the physical- and logical boards
void resetBoard()
{

  DDRB = 0b00000011;
  DDRD = 0b01111111;
  zero();

  for (int i = 0; i <= 8; i++)
  {
    board[i] = 0;
  }
}

// Initiates the pins
void init()
{
  DDRA = 0b11110000;
  DDRB = 0b00000000;
  DDRC |= 0b00111100;
  DDRD = 0b00000000;
  PORTA = 0x00;
  PORTB = 0x00;
  PORTC = 0b00111100; // JTAG
  PORTD = 0b11111000;
}