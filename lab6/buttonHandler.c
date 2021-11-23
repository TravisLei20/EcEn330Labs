#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "buttonHandler.h"
#include "display.h"
#include "simonDisplay.h"
#include "verifySequence.h"
#include "xparameters.h"

#define DRAW 0
#define ERASE 1

#define HIGH 1
#define LOW 0

#define DEFAULT_ERROR_MESSAGE "DEFAULT ERROS MESSAGE\n"

static bool enable = LOW;
static bool completed = LOW;
static bool released = LOW;
static bool timedOut = LOW;

static int16_t x = LOW;
static int16_t y = LOW;
static uint8_t z = LOW;

static uint8_t regionNumber;

// The state names in the state-machine
static enum buttonHandler_st_t {
  init_st,
  waiting_for_touch_st,
  draw_st,
  waiting_for_release_st,
  finish_st
} currentState;

// Get the simon region numbers. See the source code for the region numbering
// scheme.
uint8_t buttonHandler_getRegionNumber() { return regionNumber; }

// Turn on the state machine. Part of the interlock. Set enable high.
void buttonHandler_enable() { enable = HIGH; }

// Turn off the state machine. Part of the interlock. Set enable low.
void buttonHandler_disable() { enable = LOW; }

// Standard init function. Sets currentState to init_st.
void buttonHandler_init() { currentState = init_st; }

// The only thing this function does is return a boolean flag set by the
// buttonHandler state machine. To wit: Once enable, the buttonHandler
// state-machine first waits for a touch. Once a touch is detected, the
// buttonHandler state-machine computes the region-number for the touched area.
// Next, the buttonHandler state-machine waits until the player removes their
// finger. At this point, the state-machine should set a bool flag that
// indicates the the player has removed their finger. Once the buttonHandler()
// state-machine is disabled, it should clear this flag.
// All buttonHandler_releasedDetected() does is return the value of this flag.
// As such, the body of this function should only contain a single line of code.
// If this function does more than return a boolean set by the buttonHandler
// state machine, you are going about this incorrectly.
bool buttonHandler_releaseDetected() { return released; }

// Let's you know that the buttonHander is waiting in the interlock state.
bool buttonHandler_isComplete() { return completed; }

// Allows an external controller to notify the buttonHandler that a time-out has
// occurred.
void buttonHandler_timeOutOccurred() {
  timedOut = verifySequence_isTimeOutError();
}

// Standard tick function.
void buttonHandler_tick() {
  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {

  case init_st:
    completed = LOW;
    released = LOW;
    timedOut = LOW;
    // If enable is set high then set currentState to waiting_for_touch_st.
    if (enable) {
      currentState = waiting_for_touch_st;
    }
    break;

  case waiting_for_touch_st:
    buttonHandler_timeOutOccurred();
    // If the user took too long and the program timed out then set complete to
    // high and set currentState to finish_st.
    if (timedOut) {
      completed = HIGH;
      currentState = finish_st;
      break;
    }

    // If the display is still touched then set currentState to draw_st and
    // clear the old touch data.
    if (display_isTouched()) {
      currentState = draw_st;
      display_clearOldTouchData();
    }
    break;

  case draw_st:
    display_getTouchedPoint(&x, &y, &z);
    regionNumber = simonDisplay_computeRegionNumber(x, y);
    simonDisplay_drawSquare(regionNumber, DRAW);
    currentState = waiting_for_release_st;
    break;

  case waiting_for_release_st:
    // When the display is released then set released and completed to high and
    // currentState to finish_st. This will also erase the square and redraw the
    // button of the touched region.
    if (!display_isTouched()) {
      released = HIGH;
      completed = HIGH;
      currentState = finish_st;
      simonDisplay_drawSquare(regionNumber, ERASE);
      simonDisplay_drawButton(regionNumber, DRAW);
    }
    // If enable is set low or timedOut is set high then set completed to high
    // and currentState to finish_st.
    else if (!enable || timedOut) {
      completed = HIGH;
      currentState = finish_st;
    }
    break;

  case finish_st:
    // Waits in finish_st until enable is set low.
    // When it is then set currentState to init_st.
    if (!enable) {
      completed = HIGH;
      timedOut = LOW;
      released = LOW;
      currentState = init_st;
    }
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }

  // Perform state action next.
  // Perform the Moore actions base on currentState
  switch (currentState) {

  case init_st:
    break;

  case waiting_for_touch_st:
    break;

  case draw_st:
    break;

  case waiting_for_release_st:
    break;

  case finish_st:
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}

// ./lab6/lab6.elf