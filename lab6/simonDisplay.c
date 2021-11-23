#include "simonDisplay.h"
#include "display.h"

#define BUTTON_X 50
#define BUTTON_Y 30
#define BUTTON_RIGHT_X_OFFSET 160
#define BUTTON_BOTTOM_Y_OFFSET 120

#define SQUARE_X 20
#define SQUARE_Y 0
#define SQUARE_RIGHT_X_OFFSET 190
#define SQUARE_BOTTOM_Y_OFFSET 120

#define MID_X 160
#define MID_Y 120

// Computes the region according to the x and y coordinates of the screen.
int8_t simonDisplay_computeRegionNumber(int16_t x, int16_t y) {
  // Checks if the x coordinate is on the left side of the screen.
  if (x < MID_X) {
    // Checks if the y coordinate is on the top of the screen.
    if (y < MID_Y) {
      return SIMON_DISPLAY_REGION_0;
    }
    // y coordinate is on the button of the screen.
    else {
      return SIMON_DISPLAY_REGION_2;
    }
  }
  // x coordinate is on the right side of the screen.
  else {
    if (y < MID_Y) {
      return SIMON_DISPLAY_REGION_1;
    }
    // y coordinate is on the button of the screen.
    else {
      return SIMON_DISPLAY_REGION_3;
    }
  }
}

// Draws a colored "button" that the user can touch.
// The colored button is centered in the region but does not fill the region.
// If erase argument is true, draws the button as black background to erase it.
void simonDisplay_drawButton(uint8_t regionNo, bool erase) {
  // Checks if erase is high
  if (erase) {
    // Checks which region is being erased according to regionNo
    if (regionNo == SIMON_DISPLAY_REGION_0) {
      display_fillRect(BUTTON_X, BUTTON_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
    } else if (regionNo == SIMON_DISPLAY_REGION_1) {
      display_fillRect(BUTTON_X + BUTTON_RIGHT_X_OFFSET, BUTTON_Y,
                       SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                       DISPLAY_BLACK);
    } else if (regionNo == SIMON_DISPLAY_REGION_2) {
      display_fillRect(BUTTON_X, BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                       DISPLAY_BLACK);
    } else if (regionNo == SIMON_DISPLAY_REGION_3) {
      display_fillRect(BUTTON_X + BUTTON_RIGHT_X_OFFSET,
                       BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                       DISPLAY_BLACK);
    }
  }
  // erase is low so a button will be drawn
  else {
    // Checks which region is being drawn according to regionNo
    if (regionNo == SIMON_DISPLAY_REGION_0) {
      display_fillRect(BUTTON_X, BUTTON_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                       SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_RED);
    } else if (regionNo == SIMON_DISPLAY_REGION_1) {
      display_fillRect(BUTTON_X + BUTTON_RIGHT_X_OFFSET, BUTTON_Y,
                       SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                       DISPLAY_YELLOW);
    } else if (regionNo == SIMON_DISPLAY_REGION_2) {
      display_fillRect(BUTTON_X, BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                       DISPLAY_BLUE);
    } else if (regionNo == SIMON_DISPLAY_REGION_3) {
      display_fillRect(BUTTON_X + BUTTON_RIGHT_X_OFFSET,
                       BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                       DISPLAY_GREEN);
    }
  }
}

// Convenience function that draws all of the buttons.
void simonDisplay_drawAllButtons() {
  display_fillRect(BUTTON_X, BUTTON_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                   SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_RED);
  display_fillRect(BUTTON_X + BUTTON_RIGHT_X_OFFSET, BUTTON_Y,
                   SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                   DISPLAY_YELLOW);
  display_fillRect(BUTTON_X, BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
                   SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                   DISPLAY_BLUE);
  display_fillRect(
      BUTTON_X + BUTTON_RIGHT_X_OFFSET, BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
      SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_GREEN);
}

// Convenience function that erases all of the buttons.
void simonDisplay_eraseAllButtons() {
  display_fillRect(BUTTON_X, BUTTON_Y, SIMON_DISPLAY_BUTTON_WIDTH,
                   SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
  display_fillRect(BUTTON_X + BUTTON_RIGHT_X_OFFSET, BUTTON_Y,
                   SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                   DISPLAY_BLACK);
  display_fillRect(BUTTON_X, BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
                   SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT,
                   DISPLAY_BLACK);
  display_fillRect(
      BUTTON_X + BUTTON_RIGHT_X_OFFSET, BUTTON_Y + BUTTON_BOTTOM_Y_OFFSET,
      SIMON_DISPLAY_BUTTON_WIDTH, SIMON_DISPLAY_BUTTON_HEIGHT, DISPLAY_BLACK);
}

// Draws a bigger square that completely fills the region.
// If the erase argument is true, it draws the square as black background to
// "erase" it.
void simonDisplay_drawSquare(uint8_t regionNo, bool erase) {
  // Checks if erase is high
  if (erase) {
    // Checks which region is being erased according to regionNo
    if (regionNo == SIMON_DISPLAY_REGION_0) {
      display_fillRect(SQUARE_X, SQUARE_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
    } else if (regionNo == SIMON_DISPLAY_REGION_1) {
      display_fillRect(SQUARE_X + SQUARE_RIGHT_X_OFFSET, SQUARE_Y,
                       SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                       DISPLAY_BLACK);
    } else if (regionNo == SIMON_DISPLAY_REGION_2) {
      display_fillRect(SQUARE_X, SQUARE_Y + SQUARE_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                       DISPLAY_BLACK);
    } else if (regionNo == SIMON_DISPLAY_REGION_3) {
      display_fillRect(SQUARE_X + SQUARE_RIGHT_X_OFFSET,
                       SQUARE_Y + SQUARE_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                       DISPLAY_BLACK);
    }
  }
  // erase is low so a square will be drawn
  else {
    // Checks which region is being drawn according to regionNo
    if (regionNo == SIMON_DISPLAY_REGION_0) {
      display_fillRect(SQUARE_X, SQUARE_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                       SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_RED);
    } else if (regionNo == SIMON_DISPLAY_REGION_1) {
      display_fillRect(SQUARE_X + SQUARE_RIGHT_X_OFFSET, SQUARE_Y,
                       SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                       DISPLAY_YELLOW);
    } else if (regionNo == SIMON_DISPLAY_REGION_2) {
      display_fillRect(SQUARE_X, SQUARE_Y + SQUARE_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                       DISPLAY_BLUE);
    } else if (regionNo == SIMON_DISPLAY_REGION_3) {
      display_fillRect(SQUARE_X + SQUARE_RIGHT_X_OFFSET,
                       SQUARE_Y + SQUARE_BOTTOM_Y_OFFSET,
                       SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                       DISPLAY_GREEN);
    }
  }
}

// Convenience function that erases all of the squares.
void simonDisplay_eraseAllSquares() {
  display_fillRect(SQUARE_X, SQUARE_Y, SIMON_DISPLAY_SQUARE_WIDTH,
                   SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
  display_fillRect(SQUARE_X + SQUARE_RIGHT_X_OFFSET, SQUARE_Y,
                   SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                   DISPLAY_BLACK);
  display_fillRect(SQUARE_X, SQUARE_Y + SQUARE_BOTTOM_Y_OFFSET,
                   SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT,
                   DISPLAY_BLACK);
  display_fillRect(
      SQUARE_X + SQUARE_RIGHT_X_OFFSET, SQUARE_Y + SQUARE_BOTTOM_Y_OFFSET,
      SIMON_DISPLAY_SQUARE_WIDTH, SIMON_DISPLAY_SQUARE_HEIGHT, DISPLAY_BLACK);
}

// Runs a brief demonstration of how buttons can be pressed and squares lit up
// to implement the user interface of the Simon game. The routine will continue
// to run until the touchCount has been reached, e.g., the user has touched the
// pad touchCount times.

// I used a busy-wait delay (utils_msDelay) that uses a for-loop and just blocks
// until the time has passed. When you implement the game, you CANNOT use this
// function as we discussed in class. Implement the delay using the non-blocking
// state-machine approach discussed in class.
void simonDisplay_runTest(uint16_t touchCount) {}