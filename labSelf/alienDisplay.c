#include "alienDisplay.h"

#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

#include "display.h"
#include "leds.h"
#include "utils.h"
#include "xparameters.h"

#include "alienRegion.h"

#define MISS 0
#define SPLASH 1
#define HIT 2
#define SUNK 3

static uint8_t rowNum = 0;
static uint8_t columnNum = 0;

// Sets the row and column that is needed in control
void alienDisplay_setRowColumnFromControl(uint8_t row, uint8_t column) {
  rowNum = row;
  columnNum = column;
}

// Draws the correct square according selected action
void alienDisplay_drawFire(uint8_t selected) {
  if (selected == MISS) {
    display_fillRect((32 * columnNum) + 1, (24 * rowNum) + 1, 30, 22,
                     DISPLAY_BLUE);
  } else if (selected == SPLASH) {
    display_fillRect((32 * columnNum) + 1, (24 * rowNum) + 1, 30, 22,
                     DISPLAY_YELLOW);
  } else if (selected == HIT) {
    display_fillRect((32 * columnNum) + 1, (24 * rowNum) + 1, 30, 22,
                     DISPLAY_RED);
  } else if (selected == SUNK) {
    display_fillRect((32 * columnNum) + 1, (24 * rowNum) + 1, 30, 22,
                     DISPLAY_GRAY);
  }
}

// The intro "Battleship" screen
void alienDisplay_intro(bool erase) {
  if (erase) {
    display_fillRect(0, 0, 320, 80, DISPLAY_BLACK);
    display_fillRect(0, 80, 320, 80, DISPLAY_BLACK);
    display_fillRect(0, 160, 320, 80, DISPLAY_BLACK);
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_fillRect(0, 0, 320, 80, DISPLAY_RED);
    display_fillRect(0, 80, 320, 80, DISPLAY_WHITE);
    display_fillRect(0, 160, 320, 80, DISPLAY_BLUE);
    display_setTextColor(DISPLAY_DARK_BLUE);
  }
  display_setCursor(10, 100);
  display_setTextSize(5);
  display_println("Battleship");
}

// The instruction screen with multiple switches high
void alienDisplay_drawInstructionScreen(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(2);

  display_setCursor(35, 30);
  display_println("SW0 Shows Turn Number");
  display_setCursor(38, 60);
  display_println("SW1 is Splash Rules");
  display_setCursor(35, 90);
  display_println("SW2 is General Rules");
  display_setCursor(5, 120);
  display_println("SW3 is Button Instructions");
  display_setCursor(10, 170);
  display_println("Switch Multiple Switches");
  display_setCursor(5, 200);
  display_println("To See Switch Instructions");
}

// The info displayed by SW0
void alienDisplay_drawSW0Screen(bool erase, uint8_t turn) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(2);

  char string[25];
  sprintf(string, "You Have %d Turns Left", turn);

  display_setCursor(25, 50);
  display_println(string);

  display_setCursor(20, 100);
  display_println("Every Time You Sink an");
  display_setCursor(90, 130);
  display_println("Enemy Ship");
  display_setCursor(10, 160);
  display_println("You Will Receive 10 Turns");
}

// The info displayed by SW1
void alienDisplay_drawSW1Screen(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(2);

  display_setCursor(55, 30);
  display_println("A Splash is When");
  display_setCursor(25, 60);
  display_println("You Fire Next to a Ship.");
  display_setCursor(30, 90);
  display_println("Diagonal Shots are NOT");
  display_setCursor(35, 120);
  display_println("Considered a Splash");
}

// The info displayed by SW2
void alienDisplay_drawSW2Screen(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(2);

  display_setCursor(30, 20);
  display_println("Sink All Enemy Ships");
  display_setCursor(28, 50);
  display_println("Before You Run Out of");
  display_setCursor(28, 80);
  display_println("Turns to Win the Game.");
  display_setCursor(30, 120);
  display_println("Blue Shots Mean Miss");
  display_setCursor(40, 150);
  display_println("Red Shots Mean Hit");
  display_setCursor(15, 180);
  display_println("Yellow Shots Mean Splash");
  display_setCursor(30, 210);
  display_println("Gray Shots Mean Sunk");
}

// The info displayed by SW3
void alienDisplay_drawSW3Screen(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(2);

  display_setCursor(2, 30);
  display_println("Press BTN0 to Confirm Fire");
  display_setCursor(2, 60);
  display_println("Press BTN3 to Restart Game");

  display_setCursor(10, 100);
  display_println("There is one 5 wide ship");
  display_setCursor(10, 130);
  display_println("There is one 4 wide ship");
  display_setCursor(10, 160);
  display_println("There is one 3 wide ship");
  display_setCursor(10, 190);
  display_println("There is one 2 wide ship");
  display_setCursor(10, 220);
  display_println("There is one 1 wide ship");
}

// The info displayed by the initial wait screen
void alienDisplay_drawWaitScreen(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(2);

  display_setCursor(30, 30);
  display_println("Touch Screen to Start");
  display_setCursor(2, 60);
  display_println("Press BTN0 to Confirm Fire");
  display_setCursor(2, 90);
  display_println("Press BTN3 to Restart Game");

  display_setCursor(15, 150);
  display_println("Switch Multiple Switches");

  display_setCursor(120, 180);
  display_println("To See");

  display_setCursor(10, 210);
  display_println("Game General Instructions");
}

// init function
void alienDisplay_init() {
  for (int8_t i = 0; i < 10; i++) {
    display_drawLine(i * 32, 0, i * 32, 240, DISPLAY_WHITE);
    display_drawLine(0, i * 24, 320, i * 24, DISPLAY_WHITE);
  }
}

// Set the rows and colums from region
void alienDisplay_setRowColumn() {
  rowNum = alienRegion_getRow();
  columnNum = alienRegion_getColumn();
}

// Display the little red square on the touched region of the screen
void alienDisplay_drawSelectedArea(bool erase) {
  alienDisplay_setRowColumn();
  if (erase) {
    display_drawRect((32 * columnNum) + 1, (24 * rowNum) + 1, 30, 22,
                     DISPLAY_BLACK);
  } else {
    display_drawRect((32 * columnNum) + 1, (24 * rowNum) + 1, 30, 22,
                     DISPLAY_RED);
  }
}

// Draw the win screen
void alienDisplay_drawWin(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setCursor(15, 80);
  display_setTextSize(7);
  display_println("Victory");
}

// Draw the lose screen
void alienDisplay_drawLose(bool erase) {
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setCursor(10, 80);
  display_setTextSize(8);
  display_println("Defeat");
}

// This was a function that I ran when I was first making this lab so I could
// see what was going on
void alienDisplay_runTest() {
  alienDisplay_init();
  for (int8_t i = 0; i < 10; i++) {
    for (int8_t j = 0; j < 10; j++) {
      rowNum = j;
      columnNum = i;
      alienDisplay_drawSelectedArea(0);
      utils_msDelay(100);
      alienDisplay_drawFire(j % 3);
      alienDisplay_drawSelectedArea(1);
    }
  }
}

// ./labSelf/labSelf.elf
// ../run_elf_on_board.py labSelf/labSelf.elf