/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

// Print out "hello world" on both the console and the LCD screen.

#include "display.h"

#define TEXT_SIZE 2

#define LINE_ONE_START_XY 0
#define LINES_END_OF_X 320
#define LINE_ONE_END_AND_LINE_TWO_START_Y 240

#define LINE_TWO_START_X 0
#define LINE_TWO_END_Y 0

#define GREEN 0x07E0
#define RED 0xF800
#define YELLOW 0xFFE0

#define FILL_TRI_BOTTOM_X 160
#define FILL_TRI_BOTTOM_Y 90
#define FILL_TRI_LEFT_X 130
#define FILL_TRI_LEFT_AND_RIGHT_Y 30
#define FILL_TRI_RIGHT_X 190

#define DRAW_TRI_TOP_X 160
#define DRAW_TRI_TOP_Y 150
#define DRAW_TRI_LEFT_X 130
#define DRAW_TRI_LEFT_AND_RIGHT_Y 210
#define DRAW_TRI_RIGHT_X 190

#define FILL_CIR_X 235
#define FILL_CIR_Y 120
#define FILL_CIR_R 30

#define DRAW_CIR_X 85
#define DRAW_CIR_Y 120
#define DRAW_CIR_R 30

#include <stdio.h>
int main() {
  display_init(); // Must init all of the software and underlying hardware for

  display_fillScreen(DISPLAY_BLACK);

  display_drawLine(LINE_ONE_START_XY, LINE_ONE_START_XY, LINES_END_OF_X,
                   LINE_ONE_END_AND_LINE_TWO_START_Y, GREEN);
  display_drawLine(LINE_TWO_START_X, LINE_ONE_END_AND_LINE_TWO_START_Y,
                   LINES_END_OF_X, LINE_TWO_END_Y, GREEN);

  display_fillTriangle(FILL_TRI_BOTTOM_X, FILL_TRI_BOTTOM_Y, FILL_TRI_LEFT_X,
                       FILL_TRI_LEFT_AND_RIGHT_Y, FILL_TRI_RIGHT_X,
                       FILL_TRI_LEFT_AND_RIGHT_Y, YELLOW);
  display_drawTriangle(DRAW_TRI_TOP_X, DRAW_TRI_TOP_Y, DRAW_TRI_LEFT_X,
                       DRAW_TRI_LEFT_AND_RIGHT_Y, DRAW_TRI_RIGHT_X,
                       DRAW_TRI_LEFT_AND_RIGHT_Y, YELLOW);

  display_fillCircle(FILL_CIR_X, FILL_CIR_Y, FILL_CIR_R, RED);
  display_drawCircle(DRAW_CIR_X, DRAW_CIR_Y, DRAW_CIR_R, RED);

  return 0;
}

// This function must be defined but can be left empty for now.
// You will use this function in a later lab.
// It is called in the timer interrupt service routine (see interrupts.c in
// supportFiles).
void isr_function() {
  // Empty for now.
}