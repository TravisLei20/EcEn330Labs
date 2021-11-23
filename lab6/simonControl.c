#include "simonControl.h"
#include "display.h"
#include "flashSequence.h"
#include "globals.h"
#include "simonDisplay.h"
#include "verifySequence.h"
#include <stdio.h>
#include <time.h>

#define INDEX_SIZE 100

#define SIMON_CURSOR_X 85
#define SIMON_CURSOR_Y 50
#define SIMON_TEXT_SIZE 5

#define INSTRUCTIONS_X 40
#define INSTRUCTIONS_Y 110
#define INSTRUCTIONS_TEXT_SIZE 3

#define INTRO_LENGTH_X 75
#define INTRO_LENGTH_Y 150

#define SIMON_TEXT "SIMON"
#define INSTRUCTIONS_TEXT "Touch to Play"
#define INTRO_TEXT "Length: 4"

#define FAIL_MESSAGE "EPIC FAIL"
#define SUCCESS_MESSAGE "EPIC SUCCESS"

#define SCORE_MESSAGE "Your score %d/%d"

#define CONTINUE_MESSAGE "Tap to Continue"

#define WAIT_TIME 30

#define STRING_SIZE 20

#define DRAW 0
#define ERASE 1

#define HIGH 1
#define LOW 0

#define ORIGINAL_SEQUENCE_LENGTH 4

#define DEFAULT_ERROR_MESSAGE "DEFAULT ERROR MESSAGE\n"

#define SEED NULL

static bool enable = LOW;
static bool losted = LOW;

static uint8_t count = LOW;

static uint8_t thisSequence[INDEX_SIZE];
static uint16_t sequenceLength = ORIGINAL_SEQUENCE_LENGTH;
static uint16_t iterationLength = HIGH;

static uint16_t success = LOW;

// The state names in the state-machine
static enum simonControl_st_t {
  init_st,
  start_st,
  waiting_for_touch_st,
  flash_st,
  verify_st,
  results_st,
  score_st
} currentState;

// Creates a random sequence according to a length that is passed in.
void createSequence(uint16_t length) {
  srand(time(SEED));
  // Assigns the sequence with random numbers according to the given length.
  for (uint16_t i = LOW; i < length; i++) {
    thisSequence[i] = rand() % ORIGINAL_SEQUENCE_LENGTH;
  }
  globals_setSequence(thisSequence, length);
}

// Prints or eraseds the instructions according to the given erase value.
void instructions(bool erase) {
  // If erase is set high then set the text color to black to erase the words.
  // if erase is set low then set the text color to white to draw the words.
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(SIMON_TEXT_SIZE);
  display_setCursor(SIMON_CURSOR_X, SIMON_CURSOR_Y);
  display_println(SIMON_TEXT);

  display_setTextSize(INSTRUCTIONS_TEXT_SIZE);
  display_setCursor(INSTRUCTIONS_X, INSTRUCTIONS_Y);
  display_println(INSTRUCTIONS_TEXT);

  display_setCursor(INTRO_LENGTH_X, INTRO_LENGTH_Y);
  display_println(INTRO_TEXT);
}

// Draw or erase the messge of success or failure on the screen according to the
// given erase value.
void drawSuccessOrFail(bool erase) {
  // If erase is set high then set the text color to black to erase the words.
  // if erase is set low then set the text color to white to draw the words.
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(INSTRUCTIONS_TEXT_SIZE);
  display_setCursor(INSTRUCTIONS_X, INSTRUCTIONS_Y);
  // If losted is set high then write the fail message to the screen.
  // if losted is set low then write the success message to the screen.
  if (losted) {
    display_println(FAIL_MESSAGE);
  } else {
    display_println(SUCCESS_MESSAGE);
  }
}

// Draw or erase user score on the screen according to the given erase value.
void drawScore(bool erase) {
  // If erase is set high then set the text color to black to erase the words.
  // if erase is set low then set the text color to white to draw the words.
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(INSTRUCTIONS_TEXT_SIZE);
  display_setCursor(INSTRUCTIONS_X, INSTRUCTIONS_Y);
  char string[STRING_SIZE];
  sprintf(string, SCORE_MESSAGE, success, sequenceLength);
  display_println(string);
}

// Draw or erase the continue game message on the screen according to the given
// erase value.
void drawContinue(bool erase) {
  // If erase is set high then set the text color to black to erase the words.
  // if erase is set low then set the text color to white to draw the words.
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(INSTRUCTIONS_TEXT_SIZE);
  display_setCursor(INSTRUCTIONS_X, INSTRUCTIONS_Y);
  display_println(CONTINUE_MESSAGE);
}

// Used to init the state machine. Always provided though it may not be
// necessary.
void simonControl_init() { currentState = init_st; }

// Enables the control state machine.
void simonControl_enable() { enable = HIGH; }

// Disables the controll state machine.
void simonControl_disable() { enable = LOW; }

// This tells if the game is over is terms of if the game has timed out or the
// user input is wrong.
bool simonControl_isGameOver() {
  return verifySequence_isTimeOutError() || verifySequence_isUserInputError();
}

// Use this to set the sequence length. This the sequence set by this function
// will only be recognized when the controller passes through its init state.
void simonControl_setSequenceLength(uint16_t length) {}

// Standard tick function.
void simonControl_tick() {
  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {

  case init_st:
    // If enabled is set high then set currentState to start_st.
    // Reset losted, count, success, iterationLength and sequenceLength.
    // Create new sequence and set it and the iteration length.
    // Draw the instructions.
    if (enable) {
      currentState = start_st;
      losted = LOW;
      count = LOW;
      success = LOW;
      sequenceLength = ORIGINAL_SEQUENCE_LENGTH;
      iterationLength = HIGH;
      createSequence(sequenceLength);
      globals_setSequence(thisSequence, sequenceLength);
      globals_setSequenceIterationLength(iterationLength);
      instructions(DRAW);
    }
    break;

  case start_st:
    // When the display is touched then erase the instructions
    // erase all the buttons enable flashSequence and disable verifySequence.
    // Set currentState to flash_st.
    if (display_isTouched()) {
      instructions(ERASE);
      simonDisplay_eraseAllButtons();
      flashSequence_enable();
      verifySequence_disable();
      currentState = flash_st;
    }
    break;

  case flash_st:
    // If the flashSequence is complete then draw all the buttons, disable
    // flashSequence, enable verifySequence and set currentState to verify_st.
    if (flashSequence_isComplete()) {
      simonDisplay_drawAllButtons();
      flashSequence_disable();
      verifySequence_enable();
      currentState = verify_st;
    }
    break;

  case verify_st:
    // If verifySequence is completed then do one of three actions
    if (verifySequence_isComplete()) {
      // If the game is over as in the user input incorrectly or the game timed
      // out then set losted to high disable both flashSequence and
      // verifySequence_disable erase all buttons and draw the fail message
      // reset count and set currentState to result_st.
      if (simonControl_isGameOver()) {
        losted = HIGH;
        currentState = results_st;
        flashSequence_disable();
        verifySequence_disable();
        simonDisplay_eraseAllButtons();
        drawSuccessOrFail(DRAW);
        count = LOW;

      }
      // If the iterationLength is equal to sequenceLength then increment
      // success set currentState to result_st disable both flashSequence and
      // verifySequence_disable erase all buttons and draw the success message
      // reset count.
      else if (iterationLength == sequenceLength) {
        success++;
        currentState = results_st;
        flashSequence_disable();
        verifySequence_disable();
        simonDisplay_eraseAllButtons();
        drawSuccessOrFail(DRAW);
        count = LOW;
      }
      // else increment success
      // set currentState to flash_st and start over
      // enable flashSequence and disable verifySequence
      // increment iterationLength and set the global iterationLength
      // erase all buttons.
      else {
        success++;
        currentState = flash_st;
        flashSequence_enable();
        verifySequence_disable();
        globals_setSequenceIterationLength(++iterationLength);
        simonDisplay_eraseAllButtons();
      }
    }
    break;

  case results_st:
    // If count equals WAIT_TIME
    // then reset count and erase the success or fail message
    if (count == WAIT_TIME) {
      count = LOW;
      drawSuccessOrFail(ERASE);
      // If losted is set high then set currentState to score_st and draw the
      // score.
      if (losted) {
        currentState = score_st;
        drawScore(DRAW);
      }
      // else set currentState to waiting_for_touch_st and draw the continue
      // message
      else {
        currentState = waiting_for_touch_st;
        drawContinue(DRAW);
      }
    }
    break;

  case score_st:
    // If count equals WAIT_TIME then erase the score message and set
    // currentState to init_st.
    if (count == WAIT_TIME) {
      drawScore(ERASE);
      currentState = init_st;
    }
    break;

  case waiting_for_touch_st:
    // If count equals WAIT_TIME the reset count and set currentState to
    // score_st. erase the continue message and draw the score message. This is
    // if the play has been successful but decides that he/she dosen't want to
    // continue to play.
    if (count == WAIT_TIME) {
      count = LOW;
      currentState = score_st;
      drawContinue(ERASE);
      drawScore(DRAW);
    }
    // If player decides to continue to play then he/she will touch screen.
    // If the screen is touched then reset the iterationLength to one.
    // reset success to zero erase the continue message
    // create a new sequence according to the incremented sequenceLength
    // set the global iterationLength, sequenceLength, and sequence
    // erase all buttons and disable verifySequence and enable flashSequence.
    // set currentState to flash_st.
    else if (display_isTouched()) {
      iterationLength = HIGH;
      success = LOW;
      drawContinue(ERASE);
      createSequence(++sequenceLength);
      globals_setSequenceIterationLength(iterationLength);
      globals_setSequence(thisSequence, sequenceLength);
      simonDisplay_eraseAllButtons();
      flashSequence_enable();
      verifySequence_disable();
      currentState = flash_st;
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

  case start_st:
    break;

  case flash_st:
    break;

  case verify_st:
    break;

  case results_st:
    count++;
    break;

  case score_st:
    count++;
    break;

  case waiting_for_touch_st:
    count++;
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}