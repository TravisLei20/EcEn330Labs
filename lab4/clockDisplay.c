#include "clockDisplay.h"
#include "display.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define TEXT_SIZE CLOCKDISPLAY_TEXT_SIZE
#define CURSOR_Y 100

#define TOP_TRI_COLOR DISPLAY_WHITE
#define TEXT_COLOR DISPLAY_GREEN
#define BOTTOM_TRI_COLOR DISPLAY_WHITE

#define CURSOR_X_3 90
#define TEXT_SIZE_3 3
#define SUB_NUM_3 30
#define ADD_NUM_3 10
#define LEFT_X_NUM_3 85
#define MID_X_NUM_3 30
#define RIGHT_X_NUM_3 -20
#define LEFT_X_RIGHT_NUM_3 25
#define MID_X_RIGHT_NUM_3 -30
#define RIGHT_X_RIGHT_NUM_3 -80
#define LEFT_X_TOP_3 55
#define MID_X_TOP_3 0
#define RIGHT_X_TOP_3 -52
#define TOP_Y_3 50
#define BOTTOM_Y_3 -68

#define CURSOR_X_4 60
#define TEXT_SIZE_4 4
#define SUB_NUM_4 20
#define ADD_NUM_4 10
#define LEFT_X_NUM_4 55
#define MID_X_NUM_4 20
#define RIGHT_X_NUM_4 -15
#define LEFT_X_RIGHT_NUM_4 10
#define MID_X_RIGHT_NUM_4 -30
#define RIGHT_X_RIGHT_NUM_4 -60
#define LEFT_X_TOP_4 33
#define MID_X_TOP_4 -5
#define RIGHT_X_TOP_4 -40
#define TOP_Y_4 50
#define BOTTOM_Y_4 -60

#define CURSOR_X_5 40
#define TEXT_SIZE_5 5
#define SUB_NUM_5 10
#define ADD_NUM_5 5
#define LEFT_X_NUM_5 40
#define MID_X_NUM_5 15
#define RIGHT_X_NUM_5 0
#define LEFT_X_RIGHT_NUM_5 0
#define MID_X_RIGHT_NUM_5 -20
#define RIGHT_X_RIGHT_NUM_5 -35
#define LEFT_X_TOP_5 20
#define MID_X_TOP_5 -3
#define RIGHT_X_TOP_5 -20
#define TOP_Y_5 25
#define BOTTOM_Y_5 -30

#define CURSOR_X_6 15
#define TEXT_SIZE_6 6

#define TOP_BOTTOMSIDE_Y_6 80
#define TOP_TOPSIDE_Y_6 15
#define TOP_LEFT_X_LEFTSIDE_6 5
#define TOP_LEFT_X_RIGHTSIDE_6 100
#define TOP_LEFT_X_TOPSIDE_6 53
#define TOP_MID_X_LEFTSIDE_6 110
#define TOP_MID_X_RIGHTSIDE_6 205
#define TOP_MID_X_TOPSIDE_6 158
#define TOP_RIGHT_X_LEFTSIDE_6 215
#define TOP_RIGHT_X_RIGHTSIDE_6 310
#define TOP_RIGHT_X_TOPSIDE_6 265

#define BOTTOM_BOTTOMSIDE_Y_6 160
#define BOTTOM_TOPSIDE_Y_6 225
#define BOTTOM_LEFT_X_LEFTSIDE_6 5
#define BOTTOM_LEFT_X_RIGHTSIDE_6 100
#define BOTTOM_LEFT_X_TOPSIDE_6 53
#define BOTTOM_MID_X_LEFTSIDE_6 110
#define BOTTOM_MID_X_RIGHTSIDE_6 205
#define BOTTOM_MID_X_TOPSIDE_6 158
#define BOTTOM_RIGHT_X_LEFTSIDE_6 215
#define BOTTOM_RIGHT_X_RIGHTSIDE_6 310
#define BOTTOM_RIGHT_X_TOPSIDE_6 265

#define COOL_BOTTOM_LEFT_X_LEFTSIDE_6 33
#define COOL_BOTTOM_LEFT_X_RIGHTSIDE_6 72
#define COOL_BOTTOM_LEFT_X_TOPSIDE_6 53
#define COOL_BOTTOM_MID_X_LEFTSIDE_6 138
#define COOL_BOTTOM_MID_X_RIGHTSIDE_6 177
#define COOL_BOTTOM_MID_X_TOPSIDE_6 158
#define COOL_BOTTOM_RIGHT_X_LEFTSIDE_6 243
#define COOL_BOTTOM_RIGHT_X_RIGHTSIDE_6 282
#define COOL_BOTTOM_RIGHT_X_TOPSIDE_6 265

#define MAX_HOUR 12
#define MAX_MIN 60
#define MAX_SEC 60
#define RESET_HOUR 1
#define RESET_MIN_AND_SEC 0
#define RESET_TIMER 0
#define INC_RESET_HOUR 12
#define INC_RESET_MIN_AND_SEC 59
#define INC_POINT 0

#define Y_MID_VALUE 120
#define X_HOUR 107
#define X_MIN 214

#define TEN_MILSEC_DELAY 100
#define FOUR_SEC 40
#define TEN_SEC 100

#define INDEX_0 0
#define INDEX_1 1
#define INDEX_3 3
#define INDEX_4 4
#define INDEX_6 6
#define INDEX_7 7

#define INDEX_SIZE 9

#define CHANGE_STRING_0 "%c"
#define CHANGE_STRING_1 "%2c"
#define CHANGE_STRING_3 "%4c"
#define CHANGE_STRING_4 "%5c"
#define CHANGE_STRING_6 "%7c"
#define CHANGE_STRING_7 "%8c"

// Declare and initilize hours, minutes, and seconds
int8_t hours = 12;
int8_t minutes = 59;
int8_t seconds = 59;

int16_t cursor_X;

char currentTime[INDEX_SIZE];
char previousTime[INDEX_SIZE];

// Called only once - performs any necessary inits.
// This is a good place to draw the triangles and any other
// parts of the clock display that will never change.
void clockDisplay_init() {
  // Initialize the display and set the text size and background and text color
  display_init();
  display_setTextSize(TEXT_SIZE);
  display_setTextColor(TEXT_COLOR);
  display_fillScreen(DISPLAY_BLACK);

  // The values that will determine the size of the triangle
  int8_t subtractNum = 0;
  int8_t addNum = 0;

  int8_t leftXNUM = 0;
  int8_t midXNum = 0;
  int8_t rightXNum = 0;

  int8_t leftXRightNum = 0;
  int8_t midXRightNum = 0;
  int8_t rightXRightNum = 0;

  int8_t leftXTop = 0;
  int8_t midXTop = 0;
  int8_t rightXTop = 0;

  int8_t topY = 0;
  int8_t bottomY = 0;

  // Checks the text size and appropriatly sets the cursor
  // Along with the the values that will determine the size of the triangle
  if (TEXT_SIZE == TEXT_SIZE_3) {
    display_setCursor(CURSOR_X_3, CURSOR_Y);
    subtractNum = SUB_NUM_3;
    addNum = ADD_NUM_3;

    leftXNUM = LEFT_X_NUM_3;
    midXNum = MID_X_NUM_3;
    rightXNum = RIGHT_X_NUM_3;

    leftXRightNum = LEFT_X_RIGHT_NUM_3;
    midXRightNum = MID_X_RIGHT_NUM_3;
    rightXRightNum = RIGHT_X_RIGHT_NUM_3;

    leftXTop = LEFT_X_TOP_3;
    midXTop = MID_X_TOP_3;
    rightXTop = RIGHT_X_TOP_3;

    topY = TOP_Y_3;
    bottomY = BOTTOM_Y_3;

    cursor_X = CURSOR_X_3;
  } else if (TEXT_SIZE == TEXT_SIZE_4) {
    display_setCursor(CURSOR_X_4, CURSOR_Y);
    subtractNum = SUB_NUM_4;
    addNum = ADD_NUM_4;

    leftXNUM = LEFT_X_NUM_4;
    midXNum = MID_X_NUM_4;
    rightXNum = RIGHT_X_NUM_4;

    leftXRightNum = LEFT_X_RIGHT_NUM_4;
    midXRightNum = MID_X_RIGHT_NUM_4;
    rightXRightNum = RIGHT_X_RIGHT_NUM_4;

    leftXTop = LEFT_X_TOP_4;
    midXTop = MID_X_TOP_4;
    rightXTop = RIGHT_X_TOP_4;

    topY = TOP_Y_4;
    bottomY = BOTTOM_Y_4;

    cursor_X = CURSOR_X_4;
  } else if (TEXT_SIZE == TEXT_SIZE_5) {
    display_setCursor(CURSOR_X_5, CURSOR_Y);
    subtractNum = SUB_NUM_5;
    addNum = ADD_NUM_5;

    leftXNUM = LEFT_X_NUM_5;
    midXNum = MID_X_NUM_5;
    rightXNum = RIGHT_X_NUM_5;

    leftXRightNum = LEFT_X_RIGHT_NUM_5;
    midXRightNum = MID_X_RIGHT_NUM_5;
    rightXRightNum = RIGHT_X_RIGHT_NUM_5;

    leftXTop = LEFT_X_TOP_5;
    midXTop = MID_X_TOP_5;
    rightXTop = RIGHT_X_TOP_5;

    topY = TOP_Y_5;
    bottomY = BOTTOM_Y_5;

    cursor_X = CURSOR_X_5;
  } else if (TEXT_SIZE == TEXT_SIZE_6) {
    display_setCursor(CURSOR_X_6, CURSOR_Y);
    cursor_X = CURSOR_X_6;
  }

  // Prints the main (bigger) triangle according to the text size
  display_fillTriangle(TOP_LEFT_X_LEFTSIDE_6 + leftXNUM,
                       TOP_BOTTOMSIDE_Y_6 + addNum,
                       TOP_LEFT_X_TOPSIDE_6 + leftXTop, TOP_TOPSIDE_Y_6 + topY,
                       TOP_LEFT_X_RIGHTSIDE_6 + leftXRightNum,
                       TOP_BOTTOMSIDE_Y_6 + addNum, TOP_TRI_COLOR);

  display_fillTriangle(TOP_MID_X_LEFTSIDE_6 + midXNum,
                       TOP_BOTTOMSIDE_Y_6 + addNum,
                       TOP_MID_X_TOPSIDE_6 + midXTop, TOP_TOPSIDE_Y_6 + topY,
                       TOP_MID_X_RIGHTSIDE_6 + midXRightNum,
                       TOP_BOTTOMSIDE_Y_6 + addNum, TOP_TRI_COLOR);

  display_fillTriangle(
      TOP_RIGHT_X_LEFTSIDE_6 + rightXNum, TOP_BOTTOMSIDE_Y_6 + addNum,
      TOP_RIGHT_X_TOPSIDE_6 + rightXTop, TOP_TOPSIDE_Y_6 + topY,
      TOP_RIGHT_X_RIGHTSIDE_6 + rightXRightNum, TOP_BOTTOMSIDE_Y_6 + addNum,
      TOP_TRI_COLOR);

  display_fillTriangle(
      BOTTOM_LEFT_X_LEFTSIDE_6 + leftXNUM, BOTTOM_BOTTOMSIDE_Y_6 - subtractNum,
      BOTTOM_LEFT_X_TOPSIDE_6 + leftXTop, BOTTOM_TOPSIDE_Y_6 + bottomY,
      BOTTOM_LEFT_X_RIGHTSIDE_6 + leftXRightNum,
      BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, BOTTOM_TRI_COLOR);

  display_fillTriangle(
      BOTTOM_MID_X_LEFTSIDE_6 + midXNum, BOTTOM_BOTTOMSIDE_Y_6 - subtractNum,
      BOTTOM_MID_X_TOPSIDE_6 + midXTop, BOTTOM_TOPSIDE_Y_6 + bottomY,
      BOTTOM_MID_X_RIGHTSIDE_6 + midXRightNum,
      BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, BOTTOM_TRI_COLOR);

  display_fillTriangle(
      BOTTOM_RIGHT_X_LEFTSIDE_6 + rightXNum,
      BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, BOTTOM_RIGHT_X_TOPSIDE_6 + rightXTop,
      BOTTOM_TOPSIDE_Y_6 + bottomY, BOTTOM_RIGHT_X_RIGHTSIDE_6 + rightXRightNum,
      BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, BOTTOM_TRI_COLOR);

  // Prints the smaller trangles if text size is 6
  if (TEXT_SIZE == TEXT_SIZE_6) {
    display_fillTriangle(COOL_BOTTOM_LEFT_X_LEFTSIDE_6 + leftXNUM,
                         TOP_BOTTOMSIDE_Y_6 + addNum,
                         COOL_BOTTOM_LEFT_X_TOPSIDE_6, TOP_TOPSIDE_Y_6,
                         COOL_BOTTOM_LEFT_X_RIGHTSIDE_6,
                         TOP_BOTTOMSIDE_Y_6 + addNum, TEXT_COLOR);

    display_fillTriangle(
        COOL_BOTTOM_MID_X_LEFTSIDE_6 + leftXNUM, TOP_BOTTOMSIDE_Y_6 + addNum,
        COOL_BOTTOM_MID_X_TOPSIDE_6, TOP_TOPSIDE_Y_6,
        COOL_BOTTOM_MID_X_RIGHTSIDE_6, TOP_BOTTOMSIDE_Y_6 + addNum, TEXT_COLOR);

    display_fillTriangle(COOL_BOTTOM_RIGHT_X_LEFTSIDE_6 + leftXNUM,
                         TOP_BOTTOMSIDE_Y_6 + addNum,
                         COOL_BOTTOM_RIGHT_X_TOPSIDE_6, TOP_TOPSIDE_Y_6,
                         COOL_BOTTOM_RIGHT_X_RIGHTSIDE_6,
                         TOP_BOTTOMSIDE_Y_6 + addNum, TEXT_COLOR);

    display_fillTriangle(COOL_BOTTOM_LEFT_X_LEFTSIDE_6 + leftXNUM,
                         BOTTOM_BOTTOMSIDE_Y_6 - subtractNum,
                         COOL_BOTTOM_LEFT_X_TOPSIDE_6, BOTTOM_TOPSIDE_Y_6,
                         COOL_BOTTOM_LEFT_X_RIGHTSIDE_6,
                         BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, TEXT_COLOR);

    display_fillTriangle(COOL_BOTTOM_MID_X_LEFTSIDE_6 + leftXNUM,
                         BOTTOM_BOTTOMSIDE_Y_6 - subtractNum,
                         COOL_BOTTOM_MID_X_TOPSIDE_6, BOTTOM_TOPSIDE_Y_6,
                         COOL_BOTTOM_MID_X_RIGHTSIDE_6,
                         BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, TEXT_COLOR);

    display_fillTriangle(COOL_BOTTOM_RIGHT_X_LEFTSIDE_6 + leftXNUM,
                         BOTTOM_BOTTOMSIDE_Y_6 - subtractNum,
                         COOL_BOTTOM_RIGHT_X_TOPSIDE_6, BOTTOM_TOPSIDE_Y_6,
                         COOL_BOTTOM_RIGHT_X_RIGHTSIDE_6,
                         BOTTOM_BOTTOMSIDE_Y_6 - subtractNum, TEXT_COLOR);
  }

  // Initialize the values of previousTimer and currentTime
  // Prints the default current time
  sprintf(previousTime, "%2hd:%02hd:%02hd", hours, minutes, seconds);
  sprintf(currentTime, "%2hd:%02hd:%02hd", hours, minutes, seconds);
  display_println(currentTime);
}

// Changes the time that is currently on the screen to the time
// that should be displayed on the screen
void changTime() {
  char blackOut[INDEX_SIZE];
  char correctLine[INDEX_SIZE];

  // Updates currentTime to what it needs to be
  sprintf(currentTime, "%2hd:%02hd:%02hd", hours, minutes, seconds);

  // Checks if previousTime is equal to currentTime
  if (previousTime != currentTime) {
    // Checks if index 0 is the same in previousTime and currentTime
    // If they are not equal then reset the cursor
    // write over the previous value in black
    // write the correct (new) value in text color
    if (previousTime[INDEX_0] != currentTime[INDEX_0]) {
      display_setCursor(cursor_X, CURSOR_Y);
      display_setTextColor(DISPLAY_BLACK);
      sprintf(blackOut, CHANGE_STRING_0, previousTime[INDEX_0]);
      display_println(blackOut);
      display_setTextColor(TEXT_COLOR);
      display_setCursor(cursor_X, CURSOR_Y);
      sprintf(correctLine, CHANGE_STRING_0, currentTime[INDEX_0]);
      display_println(correctLine);
    }

    // Checks if index 1 is the same in previousTime and currentTime
    // If they are not equal then reset the cursor
    // write over the previous value in black
    // write the correct (new) value in text color
    if (previousTime[INDEX_1] != currentTime[INDEX_1]) {
      display_setCursor(cursor_X, CURSOR_Y);
      display_setTextColor(DISPLAY_BLACK);
      sprintf(blackOut, CHANGE_STRING_1, previousTime[INDEX_1]);
      display_println(blackOut);
      display_setTextColor(TEXT_COLOR);
      display_setCursor(cursor_X, CURSOR_Y);
      sprintf(correctLine, CHANGE_STRING_1, currentTime[INDEX_1]);
      display_println(correctLine);
    }

    // Checks if index 3 is the same in previousTime and currentTime
    // If they are not equal then reset the cursor
    // write over the previous value in black
    // write the correct (new) value in text color
    if (previousTime[INDEX_3] != currentTime[INDEX_3]) {
      display_setCursor(cursor_X, CURSOR_Y);
      display_setTextColor(DISPLAY_BLACK);
      sprintf(blackOut, CHANGE_STRING_3, previousTime[INDEX_3]);
      display_println(blackOut);
      display_setTextColor(TEXT_COLOR);
      display_setCursor(cursor_X, CURSOR_Y);
      sprintf(correctLine, CHANGE_STRING_3, currentTime[INDEX_3]);
      display_println(correctLine);
    }

    // Checks if index 4 is the same in previousTime and currentTime
    // If they are not equal then reset the cursor
    // write over the previous value in black
    // write the correct (new) value in text color
    if (previousTime[INDEX_4] != currentTime[INDEX_4]) {
      display_setCursor(cursor_X, CURSOR_Y);
      display_setTextColor(DISPLAY_BLACK);
      sprintf(blackOut, CHANGE_STRING_4, previousTime[INDEX_4]);
      display_println(blackOut);
      display_setTextColor(TEXT_COLOR);
      display_setCursor(cursor_X, CURSOR_Y);
      sprintf(correctLine, CHANGE_STRING_4, currentTime[INDEX_4]);
      display_println(correctLine);
    }

    // Checks if index 6 is the same in previousTime and currentTime
    // If they are not equal then reset the cursor
    // write over the previous value in black
    // write the correct (new) value in text color
    if (previousTime[INDEX_6] != currentTime[INDEX_6]) {
      display_setCursor(cursor_X, CURSOR_Y);
      display_setTextColor(DISPLAY_BLACK);
      sprintf(blackOut, CHANGE_STRING_6, previousTime[INDEX_6]);
      display_println(blackOut);
      display_setTextColor(TEXT_COLOR);
      display_setCursor(cursor_X, CURSOR_Y);
      sprintf(correctLine, CHANGE_STRING_6, currentTime[INDEX_6]);
      display_println(correctLine);
    }

    // Checks if index 7 is the same in previousTime and currentTime
    // If they are not equal then reset the cursor
    // write over the previous value in black
    // write the correct (new) value in text color
    if (previousTime[INDEX_7] != currentTime[INDEX_7]) {
      display_setCursor(cursor_X, CURSOR_Y);
      display_setTextColor(DISPLAY_BLACK);
      sprintf(blackOut, CHANGE_STRING_7, previousTime[INDEX_7]);
      display_println(blackOut);
      display_setTextColor(TEXT_COLOR);
      display_setCursor(cursor_X, CURSOR_Y);
      sprintf(correctLine, CHANGE_STRING_7, currentTime[INDEX_7]);
      display_println(correctLine);
    }

    // Sets previousTime equal to currentTime
    for (uint8_t i = 0; i < strlen(currentTime); i++) {
      previousTime[i] = currentTime[i];
    }
  }
}

// Makes sure that the time isn't going out of bounds
void correctTime() {
  // Checks if seconds is greater than or equal to 60 (MAX_SEC)
  // If it is then set it to 0 (RESET_MIN_AND_SEC)
  if (seconds >= MAX_SEC) {
    seconds = RESET_MIN_AND_SEC;
  }
  // Checks if seconds is less then 0 (INC_POINT)
  // If it is then set it to 59 (INC_RESET_MIN_AND_SEC)
  else if (seconds < INC_POINT) {
    seconds = INC_RESET_MIN_AND_SEC;
  }

  // Checks if minutes is greater than or equal to 60 (MAX_SEC)
  // If it is then set it to 0 (RESET_MIN_AND_SEC)
  if (minutes >= MAX_MIN) {
    minutes = RESET_MIN_AND_SEC;
  }
  // Checks if minutes is less then 0 (INC_POINT)
  // If it is then set it to 59 (INC_RESET_MIN_AND_SEC)
  else if (minutes < INC_POINT) {
    minutes = INC_RESET_MIN_AND_SEC;
  }

  // Checks if hours is greater than 12 (MAX_HOUR)
  // If it is then set it to 1 (RESET_HOUR)
  if (hours > MAX_HOUR) {
    hours = RESET_HOUR;
  }
  // Checks if hours is 0 (INC_POINT)
  // If it is then set it to 12 (INC_RESET_HOUR)
  else if (hours == INC_POINT) {
    hours = INC_RESET_HOUR;
  }

  // Call changTimer() to update the screen
  changTime();
}

// Updates the time display with latest time, making sure to update only those
// digits that have changed since the last update. if forceUpdateAll is true,
// update all digits.
void clockDisplay_updateTimeDisplay(bool forceUpdateAll) {}

// Reads the touched coordinates and performs the increment or decrement,
// depending upon the touched region.
void clockDisplay_performIncDec() {
  int16_t x, y;
  uint8_t z;
  display_getTouchedPoint(&x, &y, &z);

  // Checks if the y coordinate is in the upper half of the screen
  if (y <= Y_MID_VALUE) {
    // checks if the x coordinate needs to increment hours, minutes, or seconds
    if (x < X_HOUR) {
      hours++;
    } else if (x < X_MIN) {
      minutes++;
    } else {
      seconds++;
    }
  }
  // Checks if the y coordinate is in the lower half of the screen
  else if (y > Y_MID_VALUE) {
    // checks if the x coordinate needs to decrement hours, minutes, or seconds
    if (x < X_HOUR) {
      hours--;
    } else if (x < X_MIN) {
      minutes--;
    } else {
      seconds--;
    }
  }

  // Calls correctTimer() to make sure the values are in bounds
  correctTime();
}

// Advances the time forward by 1 second and update the display.
void clockDisplay_advanceTimeOneSecond() {
  // Increments seconds
  seconds++;

  // Checks if seconds are equal to or greater than 60 (MAX_SEC)
  // If it is then reset the seconds to 0 and increment minutes
  if (seconds >= MAX_SEC) {
    seconds = RESET_MIN_AND_SEC;
    minutes++;
  }
  // Checks if minutes are equal to or greater than 60 (MAX_MIN)
  // If it is then reset the seconds to 0, reset the mintues to 0 and increment
  // hours
  if (minutes >= MAX_MIN) {
    seconds = RESET_MIN_AND_SEC;
    minutes = RESET_MIN_AND_SEC;
    hours++;
  }
  // Checks if hours are greater than 12 (MAX_HOUR)
  // If it is then reset the seconds to 0, reset the mintues to 0 and reset the
  // hours to 1
  if (hours > MAX_HOUR) {
    seconds = RESET_MIN_AND_SEC;
    minutes = RESET_MIN_AND_SEC;
    hours = RESET_HOUR;
  }

  correctTime();
}

// Run a test of clock-display functions.
void clockDisplay_runTest() {
  clockDisplay_init();

  uint8_t timer = RESET_TIMER;

  // Increment hours for 4 seconds
  for (timer = RESET_TIMER; timer < FOUR_SEC; timer++) {
    hours++;
    correctTime();
    utils_msDelay(TEN_MILSEC_DELAY);
  }

  // Decrement hours for 4 seconds
  for (timer = RESET_TIMER; timer < FOUR_SEC; timer++) {
    hours--;
    correctTime();
    utils_msDelay(TEN_MILSEC_DELAY);
  }

  // Increment minutes for 4 seconds
  for (timer = RESET_TIMER; timer < FOUR_SEC; timer++) {
    minutes++;
    correctTime();
    utils_msDelay(TEN_MILSEC_DELAY);
  }

  // Decrement minutes for 4 seconds
  for (timer = RESET_TIMER; timer < FOUR_SEC; timer++) {
    minutes--;
    correctTime();
    utils_msDelay(TEN_MILSEC_DELAY);
  }

  // Increment seconds for 4 seconds
  for (timer = RESET_TIMER; timer < FOUR_SEC; timer++) {
    seconds++;
    correctTime();
    utils_msDelay(TEN_MILSEC_DELAY);
  }

  // Decrement seconds for 4 seconds
  for (timer = RESET_TIMER; timer < FOUR_SEC; timer++) {
    seconds--;
    correctTime();
    utils_msDelay(TEN_MILSEC_DELAY);
  }

  // Run the timer for 10 seconds at X10 speed
  for (timer = RESET_TIMER; timer < TEN_SEC; timer++) {
    clockDisplay_advanceTimeOneSecond();
    utils_msDelay(TEN_MILSEC_DELAY);
  }
}

// ../run_elf_on_board.py lab4/lab4.elf
// ./lab4/lab4.elf