#include <stdio.h>

#include "flashSequence.h"
#include "globals.h"
#include "simonDisplay.h"

#define DRAW 0
#define ERASE 1

#define HIGH 1
#define LOW 0

#define WAIT_TIME 3

#define INDEX_OFFSET 1

#define DEFAULT_ERROR_MESSAGE "DEFAULT ERROR MESSAGE\n"

static bool enable = LOW;
static bool completed = LOW;

static uint8_t sequence[];
static uint16_t sequenceLength;
static uint16_t sequenceCount = LOW;
static uint8_t index = LOW;
static uint8_t regionNumber;

static uint8_t count = LOW;

// The state names in the state-machine
static enum flashSequence_st_t {
  init_st,
  flash_st,
  wait_st,
  finish_st
} currentState;

// Turns on the state machine. Part of the interlock.
void flashSequence_enable() { enable = HIGH; }

// Turns off the state machine. Part of the interlock.
void flashSequence_disable() { enable = LOW; }

// Standard init function.
void flashSequence_init() { currentState = init_st; }

// Other state machines can call this to determine if this state machine is
// finished.
bool flashSequence_isComplete() { return completed; }

// Standard tick function.
void flashSequence_tick() {

  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {

  case init_st:
    completed = LOW;
    index = LOW;
    // If enable is set high then set currentState to flash_st and get the
    // sequenceLength
    if (enable) {
      currentState = flash_st;
      count = LOW;
    }
    break;

  case flash_st:
    // Wait a specific time for the square to be drawn.
    // Then go to wait_st.
    if (count == WAIT_TIME) {
      regionNumber = globals_getSequenceValue(index);
      simonDisplay_drawSquare(regionNumber, DRAW);
      count = LOW;
      currentState = wait_st;
    }
    break;

  case wait_st:
    // Wait a specific time for the square to be erased.
    if (count == WAIT_TIME) {
      simonDisplay_drawSquare(regionNumber, ERASE);

      // If the index is equal to the iteration length minus one
      // If it is then set currentState to finish_st and completed to high.
      // If not then increment the index and set currentState to flash_st.
      if (index == globals_getSequenceIterationLength() - INDEX_OFFSET) {
        currentState = finish_st;
        completed = HIGH;
      } else {
        index++;
        currentState = flash_st;
        count = HIGH;
      }
    }
    break;

  case finish_st:
    completed = HIGH;
    // Waits in finish_st until enable is set low.
    // When it is then set currentState to init_st.
    if (!enable) {
      completed = HIGH;
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

  case flash_st:
    count++;
    break;

  case wait_st:
    count++;
    break;

  case finish_st:
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}