#include "ticTacToeControl.h"
#include "display.h"
#include "drivers/buttons.h"
#include "intervalTimer.h"
#include "minimax.h"
#include "stdio.h"
#include "ticTacToeDisplay.h"
#include "xparameters.h"

#define SPACE_NOT_EMPTY false
#define SPACE_FILLED true

#define BTN0_VALUE 1
#define RESET_VAL 0

#define ERASE_BOOL true
#define DRAW_BOOL false

#define INITIAL_WAIT 60

#define GAME_ON true
#define GAME_OFF false

#define PLAYX true
#define PLAYO false

#define THROW_AWAY 1
#define DISPLAYED true
#define LINE1_X 35
#define LINE2_X 120
#define LINE3_X 35
#define LINE4_X 100
#define LINES_START_Y 50
#define LINES2_START_Y 75
#define LINES3_START_Y 100
#define LINES4_START_Y 125
#define TEXT_SIZE 2
#define LINE1 "Touch board to play X"
#define LINE2 "--or--"
#define LINE3 "wait for the computer"
#define LINE4 "and play O"

#define MAX_DELAY                                                              \
  "\nThe worse case scenario has time duration of: %6.2e seconds.\n\n"

// the gloval rows and columns
static uint8_t rowNum;
static uint8_t columnNum;

// Represents if the player(human) is playing as X or O
static bool playerIsX = false;
static bool startPlaying = false;

// The counter to keep track of the time
static uint8_t counter = 0;
static bool introDisplayed = false;

// The TicTacToe board that we will be playing on
static minimax_board_t playingBoard;

// Will hold the duration values for the various timers.
static double worseCaseTime;

// The state names in the state-machine
enum ticTacToeControl_st_t {
  init_st,
  intro_st,
  waiting_for_initial_touch_st,
  opponent_turn_st,
  player_turn_st,
  waiting_for_touch_st,
  confirm_touch_st,
  game_finished_st
} currentState;

// The draws introduction screen before the game begins
void ticTacToeControl_introduction(bool erase) {
  // If erase is true then set the text color to black to erase the
  // instructions. If erase is false then set the text color to white to draw
  // the instructions.
  if (erase) {
    display_setTextColor(DISPLAY_BLACK);
  } else {
    display_setTextColor(DISPLAY_WHITE);
  }
  display_setTextSize(TEXT_SIZE);
  display_setCursor(LINE1_X, LINES_START_Y);
  display_println(LINE1);
  display_setCursor(LINE2_X, LINES2_START_Y);
  display_println(LINE2);
  display_setCursor(LINE3_X, LINES3_START_Y);
  display_println(LINE3);
  display_setCursor(LINE4_X, LINES4_START_Y);
  display_println(LINE4);
}

// Clears all the values on the board both on the display and the playingBoard
void ticTacToeControl_clearBoard() {
  minimax_initBoard(&playingBoard);
  ticTacToeDisplay_drawO(RESET_VAL, RESET_VAL, ERASE_BOOL);
  ticTacToeDisplay_drawX(RESET_VAL, RESET_VAL, ERASE_BOOL);
}

// Updates the board according to the specified row and column
// If the row and column on the board is already occupied then return false and
// do not update
bool ticTacToeControl_updateBoard(minimax_board_t *board, bool player_is_x,
                                  uint8_t row, uint8_t column) {
  // Checks if the space is empty or not
  // If it is not then return false
  if (board->squares[row][column] != MINIMAX_EMPTY_SQUARE) {
    return SPACE_NOT_EMPTY;
  }
  // Fills the specified row and column according to the value of player_is_x
  if (player_is_x) {
    board->squares[row][column] = MINIMAX_X_SQUARE;
  } else {
    board->squares[row][column] = MINIMAX_O_SQUARE;
  }
  return SPACE_FILLED;
}

// Initialize the tic-tac-toe conroller state machine
// Initializes the playingBoard
// Sets the counter to zero
void ticTacToeControl_init() {
  uint8_t throwAway = THROW_AWAY;
  currentState = init_st;
  display_init();
  intervalTimer_init(XPAR_AXI_TIMER_0_DEVICE_ID);  // init the interval timers.
  intervalTimer_reset(XPAR_AXI_TIMER_0_DEVICE_ID); // reset the interval timers.
  minimax_initBoard(&playingBoard);
  // start timer
  intervalTimer_start(INTERVAL_TIMER_TIMER_0);
  // minimax on empty board to get worse case
  minimax_computeNextMove(&playingBoard, throwAway, &throwAway, &throwAway);
  // stop timer
  intervalTimer_stop(INTERVAL_TIMER_TIMER_0);
  // Get the duration values for the timer.
  worseCaseTime =
      intervalTimer_getTotalDurationInSeconds(INTERVAL_TIMER_TIMER_0);
  intervalTimer_reset(INTERVAL_TIMER_TIMER_0);
  // Print the duration value for the timer.
  // print out saying worse case
  printf(MAX_DELAY, worseCaseTime);
  counter = RESET_VAL;
  display_fillScreen(DISPLAY_BLACK);
  ticTacToeControl_introduction(DRAW_BOOL);
}

// Calles the draw function found in ticTacToeDisplay.h
// draws an X_or_O accordingto the value of X_or_O
// row and column are given to specify which square will drawn in
void ticTacToeControl_draw(uint8_t row, uint8_t column, bool X_or_O) {
  // draws an X or O according to the value of X_or_O
  if (X_or_O) {
    ticTacToeDisplay_drawX(row, column, DRAW_BOOL);
  } else {
    ticTacToeDisplay_drawO(row, column, DRAW_BOOL);
  }
}

// Tick the tic-tac-toe conroller state machine
void ticTacToeControl_tick() {
  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {
  // Sets the currentState to intro_st
  case init_st:
    currentState = intro_st;
    break;

  case intro_st:
    // If the counter has reached 3 seconds then sets currentState to
    // waiting_for_initial_touch_st counter gets reset to zero erase the words
    // of the intro message initialize the ticTacToeDisplay board
    if (counter == INITIAL_WAIT) {
      currentState = waiting_for_initial_touch_st;
      counter = RESET_VAL;
      ticTacToeControl_introduction(ERASE_BOOL);
      ticTacToeDisplay_init();
    }
    break;

  // Waits for 3 seconds for the user to play as X
  // If user doesn't play then the computer will play as X and go first
  case waiting_for_initial_touch_st:
    // If the user toucheds the screen then playerIsX set to true
    // currentState will be set to confirm_touch_st
    if (display_isTouched()) {
      currentState = confirm_touch_st;
      playerIsX = PLAYX;
    }
    // If 3 seconds is reached without the user touching the screen then
    // currentState state will be set to opponent_turn_st so the computer will
    // play as X
    else if (counter == INITIAL_WAIT) {
      currentState = opponent_turn_st;
      playerIsX = PLAYO;
    }
    break;

  // A state to confrim that the screen was indeed touched
  case confirm_touch_st:
    // if the screen is still touched then set currentState to player_turn_st
    if (display_isTouched()) {
      currentState = player_turn_st;
      startPlaying = GAME_ON;
    }
    // if the game has already started and the screen is no longer being touched
    // then set currentState to waiting_for_touch_st
    else if (startPlaying) {
      currentState = waiting_for_touch_st;
    }
    // if the game hasn't started and the screen is no longer being touched then
    // set currentState to waiting_for_initial_touch_st
    else {
      currentState = waiting_for_initial_touch_st;
    }
    break;

  // This the when the computer takes a turn
  case opponent_turn_st:
    // The computer will first call computer next move to get the best square to
    // play in This gets the row and column value with those values the board
    // and display will be updated Afterward, currentState is set to
    // waiting_for_touch_st
    minimax_computeNextMove(&playingBoard, !playerIsX, &rowNum, &columnNum);
    ticTacToeControl_updateBoard(&playingBoard, !playerIsX, rowNum, columnNum);
    ticTacToeControl_draw(rowNum, columnNum, !playerIsX);
    currentState = waiting_for_touch_st;

    break;

  // This is after the player as selected a square to play in
  case player_turn_st:
    // Gets the row and column values from the screen coordinates
    ticTacToeDisplay_touchScreenComputeBoardRowColumn(&rowNum, &columnNum);
    // If the square wasn't empty then currentState will return to
    // waiting_for_touch_st without changing the board
    if (!ticTacToeControl_updateBoard(&playingBoard, playerIsX, rowNum,
                                      columnNum)) {
      currentState = waiting_for_touch_st;
    }
    // If is was empty then the board will be updated and currentState will be
    // moved to the opponenet_turn_st
    else {
      ticTacToeControl_draw(rowNum, columnNum, playerIsX);
      currentState = opponent_turn_st;
    }

    break;

  // This is were the game waits for the user to select a square on the screen
  // It is also where the game can be determined as finished
  // It is also where the game can be reset by hitting BTN0
  case waiting_for_touch_st:
    // If the score shows that the game is over then currentState is set to
    // game_finished_st
    if (minimax_computeBoardScore(&playingBoard, playerIsX) !=
        MINIMAX_NOT_ENDGAME) {
      currentState = game_finished_st;
    }
    // if BTN0 is set high then the game will reset and currentState will be set
    // to waiting_for_initial_touch_st
    else if (buttons_read() == BTN0_VALUE) {
      currentState = waiting_for_initial_touch_st;
      playerIsX = PLAYO;
      ticTacToeControl_clearBoard();
    }
    // If the screen is touched then currentState is set confirm_touch_st
    else if (display_isTouched()) {
      currentState = confirm_touch_st;
    }
    break;

  // This is where the game is finished and can be reset with BTN0 being set to
  // high
  case game_finished_st:
    // If BTN0 is set to high then the game is reset and currentState is set to
    // waiting_for_initial_touch_st
    if (buttons_read() == BTN0_VALUE) {
      currentState = waiting_for_initial_touch_st;
      playerIsX = PLAYO;
      ticTacToeControl_clearBoard();
    }
    break;

  // Prints a default error message
  default:
    printf("DEFAULT_ERROR_MEALY_MSG\n");
    break;
  }

  // Perform state action next.
  // Perform the Moore actions base on currentState
  switch (currentState) {
  case init_st:
    break;

  // This is where the intro message is displayed and the counter is
  // incremented.
  case intro_st:
    counter++;
    break;

  // counter is incremented to wait 3 seconds
  case waiting_for_initial_touch_st:
    counter++;
    break;

  case opponent_turn_st:
    break;

  // The moore action of display_clearOldTouchData will be performed
  case confirm_touch_st:
    display_clearOldTouchData();
    break;

  case player_turn_st:
    break;

  case waiting_for_touch_st:
    break;

  // the counter value will be reset
  case game_finished_st:
    counter = RESET_VAL;
    break;

  // Prints a default error message
  default:
    printf("DEFAULT_ERROR_MOORE_MSG\n");
    break;
  }
}