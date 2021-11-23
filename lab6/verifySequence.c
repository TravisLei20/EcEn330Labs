#include <stdio.h>

#include "buttonHandler.h"
#include "globals.h"
#include "simonDisplay.h"
#include "verifySequence.h"

#include "display.h"

#define TIME_OUT 30

#define DRAW 0
#define ERASE 1

#define HIGH 1
#define LOW 0

#define DEFAULT_ERROR_MESSAGE "DEFAULT ERROR MESSAGE\n"

static bool enable = LOW;
static bool completed = LOW;
static bool timedOut = LOW;
static bool inputError = LOW;

static uint8_t sequence[];
static uint16_t sequenceLength = LOW;

static uint8_t index = LOW;
static uint8_t regionNumber = LOW;

static uint8_t count = LOW;

// The state names in the state-machine
static enum verifySequence_st_t {
  init_st,
  waiting_for_input_st,
  verify_st,
  wait_st,
  finish_st
} currentState;

// State machine will run when enabled.
void verifySequence_enable() { enable = HIGH; }

// This is part of the interlock. You disable the state-machine and then enable
// it again.
void verifySequence_disable() { enable = LOW; }

// Standard init function.
void verifySequence_init() { currentState = init_st; }

// Used to detect if there has been a time-out error.
bool verifySequence_isTimeOutError() { return timedOut; }

// Used to detect if the user tapped the incorrect sequence.
bool verifySequence_isUserInputError() { return inputError; }

// Used to detect if the verifySequence state machine has finished verifying.
bool verifySequence_isComplete() { return completed; }

// Standard tick function.
void verifySequence_tick() {
  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {
  // Sets the currentState to intro_st
  case init_st:
    completed = LOW;
    inputError = LOW;
    timedOut = LOW;
    // If enable is set high then set currentState to waiting_for_input_st
    // resets count and index to zero
    // get the sequence length from globals.
    if (enable) {
      currentState = waiting_for_input_st;
      count = LOW;
      index = LOW;
      sequenceLength = globals_getSequenceIterationLength();
    }
    break;

  case waiting_for_input_st:
    buttonHandler_enable();
    // If a release is detected then set currentState to verify_st.
    if (buttonHandler_releaseDetected()) {
      currentState = verify_st;
    }
    // If count equals TIME_OUT meaning the user took to long to answer then
    // set completed and timedOut high
    // disable buttoneHandler
    // erase the square and draw the button of the touched region.
    // set currentState to finish_st.
    else if (count == TIME_OUT) {
      timedOut = HIGH;
      completed = HIGH;
      buttonHandler_disable();
      simonDisplay_drawSquare(buttonHandler_getRegionNumber(), ERASE);
      simonDisplay_drawButton(buttonHandler_getRegionNumber(), DRAW);
      currentState = finish_st;
    }
    break;

  case verify_st:
    // If the user inputs the correct region then do one of two things
    if (globals_getSequenceValue(index) == buttonHandler_getRegionNumber()) {
      // If the input is the last region in the sequence then set completed to
      // high and set currentState to finish_st.
      if (index == sequenceLength - HIGH) {
        completed = HIGH;
        currentState = finish_st;
      }
      // If it isn't the last then increment index, reset count and set
      // currentState to wait_st.
      else {
        index++;
        currentState = wait_st;
        count = LOW;
      }
    }
    // If the user input incorrectly then set inputError and completed high and
    // currentState to finish_st.
    else {
      inputError = HIGH;
      completed = HIGH;
      currentState = finish_st;
    }
    break;

  case wait_st:
    // If the buttonHandler is completed then disable it and set currentState to
    // waiting_for_input_st.
    if (buttonHandler_isComplete()) {
      buttonHandler_disable();
      currentState = waiting_for_input_st;
    }

    break;

  case finish_st:
    // Wait until buttonHandler is completed then disable it.
    if (buttonHandler_isComplete()) {
      buttonHandler_disable();
      // When enable is set low then return to init_st.
      if (!enable) {
        currentState = init_st;
      }
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

  case waiting_for_input_st:
    count++;
    break;

  case verify_st:
    break;

  case wait_st:
    break;

  case finish_st:
    completed = HIGH;
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}