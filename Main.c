// CPU clocked to 8MHz
#define F_CPU 8000000 UL

#include <util/delay.h>

#include <avr/io.h>

#include <stdlib.h>

#include <stdio.h>

#include <time.h>

#include <stdbool.h>

extern void blue();
extern void green();
extern void zero();
extern void ret();
extern void playMove(int location);
extern void winAnimation(char winner);
extern void switchTurn();
extern void resetBoard();
extern void init();
extern void playAIMove();
extern char checkWin(int board[9]);
extern int convertFromCase(int n);
extern bool checkMove(int move);

int turn = 1;
int board[9] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0};

// 0 = human, 1 = easy bot, 2 = normal bot, 3 = hard/miniMax
int difficulty = 0;

// Keypad value used for user inpout detection
int keypad = 100;

//  KEYPAD            |  PIXELS
//  13 12 14 15       |  1  2  3
//  9  8 10  11       |  4  5  6    10
//  5  4  6  7        |  7  8  9
//  1  0  2  3        |
// P1: DDRD=0b01000000, P2: DDRD=0b00100000, P3: DDRD=0b00010000, P4: DDRD=0b00001000, P5: DDRD=0b00000100,
// P6: DDRD=0b00000010,  P7: DDRD=0b00000001, P8: DDRB= 0b00000001, P9: DDRB=0b00000010, P10: DRRB=0b00000100

int main(void)
{

  init();

  DDRD = 0b00000000;
  DDRB = 0b00000100;
  blue();

  while (1)
  {

    if (PINA != keypad)
    {

      keypad = PINA;

      switch (keypad)
      {

        // buttons 4, 6, 7, 8, 10, 11, 12, 14, 15 represents move options (see commented section from before for physical locations)
        // value 12 representents button 0, 14 = 1, 15 = 2, 8 = 3, 10 = 4, 11 = 5, 4 = 6, 6 = 7 and 7 = 8
      case 4:
      case 6:
      case 7:
      case 8:
      case 10:
      case 11:
      case 12:
      case 14:
      case 15:

        if (checkMove(convertFromCase(keypad)))
        {
          playMove(keypad);
          switchTurn();

          if (difficulty != 0)
          {
            _delay_ms(1000);
            playAIMove();
          }
        }

        break;

        // RESET
      case 3:
        resetBoard();
        DDRD = 0b00000000;
        DDRB = 0b00000100;
        zero();
        blue();
        turn = 1;
        difficulty = 0;
        break;

        // pvp
      case 13:
        difficulty = 0;
        break;

        // easy difficulty
      case 9:
        difficulty = 1;
        playAIMove();
        break;
        // normal difficulty
      case 5:
        difficulty = 2;
        playAIMove();
        break;
        // hard difficulty
      case 1:
        difficulty = 3;
        playAIMove();
        break;
      }
    }
  }
}