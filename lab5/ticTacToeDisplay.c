#include "ticTacToeDisplay.h"
#include "display.h"
#include "drivers/buttons.h"
#include "drivers/switches.h"
#include "utils.h"

#define HORZ_X_START 10
#define HORZ_X_END 310
#define TOP_HORZ_Y 83
#define BOT_HORZ_Y 156

#define LEFT_VERT_X 110
#define RIGHT_VERT_X 210
#define VERT_Y_START 10
#define VERT_Y_END 230

#define O_X_LEFT 60
#define O_X_MID 160
#define O_X_RIGHT 260
#define O_Y_TOP 48
#define O_Y_MID 120
#define O_Y_BOT 195
#define RADIUS 30

#define Y_MID_OFFSET 73
#define Y_BOT_OFFSET 146

#define ROW_ZERO 0
#define ROW_ONE 1
#define ROW_TWO 2

#define COLUMN_ZERO 0
#define COLUMN_ONE 1
#define COLUMN_TWO 2

#define X_VERT_OFFSET 10
#define X_HORZ_OFFSET 20

#define TERMINATE_VAL 2
#define BTN0_VALUE 1

#define RESET_VAL 0
#define ERASE_BOOL true

#define DELAY_TIME 50

#define DRAW_BOOL false
#define SWITCH_HIGH 1

// Inits the tic-tac-toe display, draws the lines that form the board.
void ticTacToeDisplay_init() {
  display_drawLine(HORZ_X_START, TOP_HORZ_Y, HORZ_X_END, TOP_HORZ_Y,
                   DISPLAY_YELLOW);
  display_drawLine(HORZ_X_START, BOT_HORZ_Y, HORZ_X_END, BOT_HORZ_Y,
                   DISPLAY_YELLOW);
  display_drawLine(LEFT_VERT_X, VERT_Y_START, LEFT_VERT_X, VERT_Y_END,
                   DISPLAY_YELLOW);
  display_drawLine(RIGHT_VERT_X, VERT_Y_START, RIGHT_VERT_X, VERT_Y_END,
                   DISPLAY_YELLOW);
}

// Draws an X at the specified row and column.
// erase == true means to erase the X by redrawing it as background.
// erase == false, draw the X as foreground.
void ticTacToeDisplay_drawX(uint8_t row, uint8_t column, bool erase) {
  // If erase is true then erase all the Xs
  if (erase) {
    display_drawLine(HORZ_X_START + X_HORZ_OFFSET, VERT_Y_START + X_VERT_OFFSET,
                     LEFT_VERT_X - X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                     DISPLAY_BLACK);
    display_drawLine(LEFT_VERT_X - X_HORZ_OFFSET, VERT_Y_START + X_VERT_OFFSET,
                     HORZ_X_START + X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                     DISPLAY_BLACK);

    display_drawLine(LEFT_VERT_X + X_HORZ_OFFSET, VERT_Y_START + X_VERT_OFFSET,
                     RIGHT_VERT_X - X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                     DISPLAY_BLACK);
    display_drawLine(RIGHT_VERT_X - X_HORZ_OFFSET, VERT_Y_START + X_VERT_OFFSET,
                     LEFT_VERT_X + X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                     DISPLAY_BLACK);

    display_drawLine(RIGHT_VERT_X + X_HORZ_OFFSET, VERT_Y_START + X_VERT_OFFSET,
                     HORZ_X_END - X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                     DISPLAY_BLACK);
    display_drawLine(HORZ_X_END - X_HORZ_OFFSET, VERT_Y_START + X_VERT_OFFSET,
                     RIGHT_VERT_X + X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                     DISPLAY_BLACK);

    display_drawLine(HORZ_X_START + X_HORZ_OFFSET,
                     VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                     LEFT_VERT_X - X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
    display_drawLine(LEFT_VERT_X - X_HORZ_OFFSET,
                     VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                     HORZ_X_START + X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);

    display_drawLine(LEFT_VERT_X + X_HORZ_OFFSET,
                     VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                     RIGHT_VERT_X - X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
    display_drawLine(RIGHT_VERT_X - X_HORZ_OFFSET,
                     VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                     LEFT_VERT_X + X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);

    display_drawLine(RIGHT_VERT_X + X_HORZ_OFFSET,
                     VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                     HORZ_X_END - X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
    display_drawLine(HORZ_X_END - X_HORZ_OFFSET,
                     VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                     RIGHT_VERT_X + X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);

    display_drawLine(HORZ_X_START + X_HORZ_OFFSET,
                     VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                     LEFT_VERT_X - X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
    display_drawLine(LEFT_VERT_X - X_HORZ_OFFSET,
                     VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                     HORZ_X_START + X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);

    display_drawLine(LEFT_VERT_X + X_HORZ_OFFSET,
                     VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                     RIGHT_VERT_X - X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
    display_drawLine(RIGHT_VERT_X - X_HORZ_OFFSET,
                     VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                     LEFT_VERT_X + X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);

    display_drawLine(RIGHT_VERT_X + X_HORZ_OFFSET,
                     VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                     HORZ_X_END - X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
    display_drawLine(HORZ_X_END - X_HORZ_OFFSET,
                     VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                     RIGHT_VERT_X + X_HORZ_OFFSET,
                     TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET, DISPLAY_BLACK);
  }

  // If erase is not true then draw an X according to the inputs given
  else {
    // Checks if the X needs to be drawn in this row
    if (row == ROW_ZERO) {
      // Checks which column needs to be drawn and draws it.
      if (column == COLUMN_ZERO) {
        display_drawLine(HORZ_X_START + X_HORZ_OFFSET,
                         VERT_Y_START + X_VERT_OFFSET,
                         LEFT_VERT_X - X_HORZ_OFFSET,
                         TOP_HORZ_Y - X_VERT_OFFSET, DISPLAY_WHITE);
        display_drawLine(LEFT_VERT_X - X_HORZ_OFFSET,
                         VERT_Y_START + X_VERT_OFFSET,
                         HORZ_X_START + X_HORZ_OFFSET,
                         TOP_HORZ_Y - X_VERT_OFFSET, DISPLAY_WHITE);
      } else if (column == COLUMN_ONE) {
        display_drawLine(LEFT_VERT_X + X_HORZ_OFFSET,
                         VERT_Y_START + X_VERT_OFFSET,
                         RIGHT_VERT_X - X_HORZ_OFFSET,
                         TOP_HORZ_Y - X_VERT_OFFSET, DISPLAY_WHITE);
        display_drawLine(RIGHT_VERT_X - X_HORZ_OFFSET,
                         VERT_Y_START + X_VERT_OFFSET,
                         LEFT_VERT_X + X_HORZ_OFFSET,
                         TOP_HORZ_Y - X_VERT_OFFSET, DISPLAY_WHITE);
      } else if (column == COLUMN_TWO) {
        display_drawLine(RIGHT_VERT_X + X_HORZ_OFFSET,
                         VERT_Y_START + X_VERT_OFFSET,
                         HORZ_X_END - X_HORZ_OFFSET, TOP_HORZ_Y - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(HORZ_X_END - X_HORZ_OFFSET,
                         VERT_Y_START + X_VERT_OFFSET,
                         RIGHT_VERT_X + X_HORZ_OFFSET,
                         TOP_HORZ_Y - X_VERT_OFFSET, DISPLAY_WHITE);
      }
    }
    // Checks if the X needs to be drawn in this row
    else if (row == ROW_ONE) {
      // Checks which column needs to be drawn and draws it.
      if (column == COLUMN_ZERO) {
        display_drawLine(HORZ_X_START + X_HORZ_OFFSET,
                         VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                         LEFT_VERT_X - X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(LEFT_VERT_X - X_HORZ_OFFSET,
                         VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                         HORZ_X_START + X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
      } else if (column == COLUMN_ONE) {
        display_drawLine(LEFT_VERT_X + X_HORZ_OFFSET,
                         VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                         RIGHT_VERT_X - X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(RIGHT_VERT_X - X_HORZ_OFFSET,
                         VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                         LEFT_VERT_X + X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
      } else if (column == COLUMN_TWO) {
        display_drawLine(RIGHT_VERT_X + X_HORZ_OFFSET,
                         VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                         HORZ_X_END - X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(HORZ_X_END - X_HORZ_OFFSET,
                         VERT_Y_START + Y_MID_OFFSET + X_VERT_OFFSET,
                         RIGHT_VERT_X + X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_MID_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
      }
    }
    // Checks if the X needs to be drawn in this row
    else if (row == ROW_TWO) {
      // Checks which column needs to be drawn and draws it.
      if (column == COLUMN_ZERO) {
        display_drawLine(HORZ_X_START + X_HORZ_OFFSET,
                         VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                         LEFT_VERT_X - X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(LEFT_VERT_X - X_HORZ_OFFSET,
                         VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                         HORZ_X_START + X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
      } else if (column == COLUMN_ONE) {
        display_drawLine(LEFT_VERT_X + X_HORZ_OFFSET,
                         VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                         RIGHT_VERT_X - X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(RIGHT_VERT_X - X_HORZ_OFFSET,
                         VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                         LEFT_VERT_X + X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
      } else if (column == COLUMN_TWO) {
        display_drawLine(RIGHT_VERT_X + X_HORZ_OFFSET,
                         VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                         HORZ_X_END - X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
        display_drawLine(HORZ_X_END - X_HORZ_OFFSET,
                         VERT_Y_START + Y_BOT_OFFSET + X_VERT_OFFSET,
                         RIGHT_VERT_X + X_HORZ_OFFSET,
                         TOP_HORZ_Y + Y_BOT_OFFSET - X_VERT_OFFSET,
                         DISPLAY_WHITE);
      }
    }
  }
}

// Draws an O at the specified row and column.
// erase == true means to erase the X by redrawing it as background.
// erase == false, draw the X as foreground.
void ticTacToeDisplay_drawO(uint8_t row, uint8_t column, bool erase) {
  // If erase is true then erase all the Os
  if (erase) {
    display_drawCircle(O_X_LEFT, O_Y_TOP, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_MID, O_Y_TOP, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_RIGHT, O_Y_TOP, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_LEFT, O_Y_MID, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_MID, O_Y_MID, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_RIGHT, O_Y_MID, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_LEFT, O_Y_BOT, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_MID, O_Y_BOT, RADIUS, DISPLAY_BLACK);
    display_drawCircle(O_X_RIGHT, O_Y_BOT, RADIUS, DISPLAY_BLACK);
  }
  // If erase is not true then draw an O according to the inputs given
  else {
    // Checks if the O needs to be drawn in this row
    if (row == ROW_ZERO) {
      // Checks which column needs the O to be drawn in it.
      // Draws the O
      if (column == COLUMN_ZERO) {
        display_drawCircle(O_X_LEFT, O_Y_TOP, RADIUS, DISPLAY_WHITE);
      } else if (column == COLUMN_ONE) {
        display_drawCircle(O_X_MID, O_Y_TOP, RADIUS, DISPLAY_WHITE);
      } else if (column == COLUMN_TWO) {
        display_drawCircle(O_X_RIGHT, O_Y_TOP, RADIUS, DISPLAY_WHITE);
      }
    }
    // Checks if the O needs to be drawn in this row
    else if (row == ROW_ONE) {
      if (column == COLUMN_ZERO) {
        display_drawCircle(O_X_LEFT, O_Y_MID, RADIUS, DISPLAY_WHITE);
      } else if (column == COLUMN_ONE) {
        display_drawCircle(O_X_MID, O_Y_MID, RADIUS, DISPLAY_WHITE);
      } else if (column == COLUMN_TWO) {
        display_drawCircle(O_X_RIGHT, O_Y_MID, RADIUS, DISPLAY_WHITE);
      }
    }
    // Checks if the O needs to be drawn in this row
    else if (row == ROW_TWO) {
      // Checks which column needs the O to be drawn in it.
      // Draws the O
      if (column == COLUMN_ZERO) {
        display_drawCircle(O_X_LEFT, O_Y_BOT, RADIUS, DISPLAY_WHITE);
      } else if (column == COLUMN_ONE) {
        display_drawCircle(O_X_MID, O_Y_BOT, RADIUS, DISPLAY_WHITE);
      } else if (column == COLUMN_TWO) {
        display_drawCircle(O_X_RIGHT, O_Y_BOT, RADIUS, DISPLAY_WHITE);
      }
    }
  }
}

// After a touch has been detected and after the proper delay, this sets the row
// and column arguments according to where the user touched the board.
void ticTacToeDisplay_touchScreenComputeBoardRowColumn(uint8_t *row,
                                                       uint8_t *column) {
  int16_t x, y;
  uint8_t z;
  // Get the coordinates of the touched point
  display_getTouchedPoint(&x, &y, &z);
  // These sets of if statements will take the coordinates found above
  // and set row/column to the values that they need to be.
  // if the touch coordinates were found to be in the upper left cornder then
  // row and column will be set to zero to be row zero and column

  // Checks which row the coordinates will be
  if (y <= TOP_HORZ_Y) {
    *row = ROW_ZERO;
    // Checks which column the coordinates will be
    if (x <= LEFT_VERT_X) {
      *column = COLUMN_ZERO;
    } else if (x <= RIGHT_VERT_X) {
      *column = COLUMN_ONE;
    } else {
      *column = COLUMN_TWO;
    }
  }
  // Checks which row the coordinates will be
  else if (y <= BOT_HORZ_Y) {
    *row = ROW_ONE;
    // Checks which column the coordinates will be
    if (x <= LEFT_VERT_X) {
      *column = COLUMN_ZERO;
    } else if (x <= RIGHT_VERT_X) {
      *column = COLUMN_ONE;
    } else {
      *column = COLUMN_TWO;
    }
  }
  // Checks which row the coordinates will be
  else {
    *row = ROW_TWO;
    // Checks which column the coordinates will be
    if (x <= LEFT_VERT_X) {
      *column = COLUMN_ZERO;
    } else if (x <= RIGHT_VERT_X) {
      *column = COLUMN_ONE;
    } else {
      *column = COLUMN_TWO;
    }
  }
}

// Runs a test of the display. Does the following.
// Draws the board. Each time you touch one of the screen areas, the screen will
// paint an X or an O, depending on whether switch 0 (SW0) is slid up (O) or
// down (X). When BTN0 is pushed, the screen is cleared. The test terminates
// when BTN1 is pushed.
void ticTacToeDisplay_runTest() {
  // Initialize everything that needs to be initialized
  display_init();
  display_fillScreen(DISPLAY_BLACK);
  ticTacToeDisplay_init();
  buttons_init();
  switches_init();

  // Runs this while loop as long as the terminate button (BTN1) isn't set to
  // high
  while (buttons_read() != TERMINATE_VAL) {
    // If the BTN1 is set high then erase all the Xs and Os
    if (buttons_read() == BTN0_VALUE) {
      ticTacToeDisplay_drawO(RESET_VAL, RESET_VAL, ERASE_BOOL);
      ticTacToeDisplay_drawX(RESET_VAL, RESET_VAL, ERASE_BOOL);
    }
    // If the screen is touched wait 50 milliseconds
    // Collect the touch coordinates
    // Print an X or O according to the value of SW0
    else if (display_isTouched()) {
      display_clearOldTouchData();
      utils_msDelay(DELAY_TIME);
      uint8_t rowNum;
      uint8_t columnNum;
      ticTacToeDisplay_touchScreenComputeBoardRowColumn(&rowNum, &columnNum);
      // Print an X or O according to the value of SW0
      if (switches_read() == SWITCH_HIGH) {
        ticTacToeDisplay_drawO(rowNum, columnNum, DRAW_BOOL);
      } else {
        ticTacToeDisplay_drawX(rowNum, columnNum, DRAW_BOOL);
      }
    }
    // Stay in this while loop while the screen is touched so the X or O isn't
    // constantly redrawn
    while (display_isTouched()) {
    }
  }
}