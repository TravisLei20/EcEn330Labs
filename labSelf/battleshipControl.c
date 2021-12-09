#include "battleshipControl.h"

#define DEFAULT_ERROR_MESSAGE "DEFAULT ERROR MESSAGE\n"

#define MISS 0
#define SPLASH 1
#define HIT 2
#define SUNK 3
#define EMPTY 4
#define FULL 5
#define NEXT_TO_SHIP 6

#define START_VALUE 8

#define SHIP_NUM_1 11
#define SHIP_NUM_2 12
#define SHIP_NUM_3 13
#define SHIP_NUM_4 14
#define SHIP_NUM_5 15
#define SUNK_SHIP_NUM_1 21
#define SUNK_SHIP_NUM_2 22
#define SUNK_SHIP_NUM_3 23
#define SUNK_SHIP_NUM_4 24
#define SUNK_SHIP_NUM_5 25

#define WAIT_TIME 15000000

#define DRAW 0
#define ERASE 1

static uint32_t counter = 0;

static int16_t x = 0, y = 0;
static uint8_t z = 0;

static uint8_t regionNumber = 0;

static battle_board_t battleBoard = {};

static uint64_t seed = 16;

static uint16_t turn = 10;

static bool switchOn = false;

static bool btnOn = false;

static uint8_t lastSwitch = 0;

// The state names in the state-machine
static enum battleshipControl_st_t {
  init_st,
  intro_st,
  waiting_for_initial_touch_st,
  waiting_for_touch_st,
  waiting_for_release_st,
  confirm_touch_st,
  gameplay_st,
  final_result_st,
  instructions_st,
  release_btn_st
} currentState,
    resumeState;

// This function checks if the given ship is sunk
// if it is then change the red squares on the display to gray
void battleshipControl_checkIfSunk(uint8_t shipNum) {
  bool sunk = true;
  // Checks if there is any remaining ship squares not hit
  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 10; j++) {
      if (battleBoard.shipSquares[i][j] == shipNum) {
        sunk = false;
      }
    }
  }
  // If it is sunk then turn it gray on the display
  if (sunk) {
    turn += 10;
    for (uint8_t i = 0; i < 10; i++) {
      for (uint8_t j = 0; j < 10; j++) {
        if (battleBoard.shipSquares[i][j] == (shipNum + 10)) {
          battleBoard.squares[i][j] = SUNK;
          battleshipDisplay_setRowColumnFromControl(j, i);
          battleshipDisplay_drawFire(SUNK);
        }
      }
    }
  }
}

// Checks if all the ships have been sunk
bool battleshipControl_checkGameOver() {
  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 10; j++) {
      if (battleBoard.shipSquares[i][j] == SHIP_NUM_1 ||
          battleBoard.shipSquares[i][j] == SHIP_NUM_2 ||
          battleBoard.shipSquares[i][j] == SHIP_NUM_3 ||
          battleBoard.shipSquares[i][j] == SHIP_NUM_4 ||
          battleBoard.shipSquares[i][j] == SHIP_NUM_5) {
        return false;
      }
    }
  }
  return true;
}

// Creates the playing board
void battleshipControl_createBoard() {
  // Empties the board
  for (int8_t i = 0; i < 10; i++) {
    for (int8_t j = 0; j < 10; j++) {
      battleBoard.squares[i][j] = EMPTY;
      battleBoard.shipSquares[i][j] = EMPTY;
    }
  }
  srand(seed);

  int8_t column = 0;
  int8_t row = 0;
  bool outOfRange;
  int8_t currentShipSize = 5;
  int8_t currentOffset = 4;

  // Places all the ships on the board
  while (currentShipSize != 0) {
    do {
      outOfRange = true;
      column = rand() % 10;
      row = rand() % 10;
      if (rand() % 2) {
        if ((column + currentOffset) < 10 &&
            battleshipControl_checkAvailability(currentShipSize, column, row,
                                                true)) {
          for (int8_t i = 0; i < currentShipSize; i++) {
            battleBoard.squares[column + i][row] = FULL;
            battleBoard.shipSquares[column + i][row] = currentShipSize + 10;
          }
          outOfRange = false;
        } else if ((row + currentOffset) < 10 &&
                   battleshipControl_checkAvailability(currentShipSize, column,
                                                       row, false)) {
          for (int8_t i = 0; i < currentShipSize; i++) {
            battleBoard.squares[column][row + i] = FULL;
            battleBoard.shipSquares[column][row + i] = currentShipSize + 10;
          }
          outOfRange = false;
        }
      } else {
        if ((row + currentOffset) < 10 &&
            battleshipControl_checkAvailability(currentShipSize, column, row,
                                                false)) {
          for (int8_t i = 0; i < currentShipSize; i++) {
            battleBoard.squares[column][row + i] = FULL;
            battleBoard.shipSquares[column][row + i] = currentShipSize + 10;
          }
          outOfRange = false;
        } else if ((column + currentOffset) < 10 &&
                   battleshipControl_checkAvailability(currentShipSize, column,
                                                       row, true)) {
          for (int8_t i = 0; i < currentShipSize; i++) {
            battleBoard.squares[column + i][row] = FULL;
            battleBoard.shipSquares[column + i][row] = currentShipSize + 10;
          }
          outOfRange = false;
        }
      }
    } while (outOfRange);
    currentOffset--;
    currentShipSize--;
  }

  // Creates the splash squares
  for (int8_t i = 0; i < 10; i++) {
    for (int8_t j = 0; j < 10; j++) {
      if (battleBoard.squares[i][j] == EMPTY &&
          ((battleBoard.squares[i + 1][j] == FULL && ((i + 1) != (10))) ||
           (battleBoard.squares[i - 1][j] == FULL && ((i - 1) != (-1))) ||
           (battleBoard.squares[i][j + 1] == FULL && ((j + 1) != (10))) ||
           (battleBoard.squares[i][j - 1] == FULL && ((j - 1) != (-1))))) {
        battleBoard.squares[i][j] = NEXT_TO_SHIP;
      }
    }
  }

  // battleshipControl_printBoards();
}

// Prints both boards
void battleshipControl_printBoards() {
  printf("---------------------------\n");
  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 10; j++) {
      printf("%d ", battleBoard.squares[j][i]);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 10; j++) {
      printf("%d ", battleBoard.shipSquares[j][i]);
    }
    printf("\n");
  }
}

// Checks if the space is available for the ship to go on those spaces
bool battleshipControl_checkAvailability(int8_t shipSize, int8_t columnNum,
                                         int8_t rowNum, bool horizontal) {
  for (int8_t i = 0; i < shipSize; i++) {
    if (horizontal) {
      if (battleBoard.squares[columnNum + i][rowNum] == FULL) {
        return false;
      }
    } else {
      if (battleBoard.squares[columnNum][rowNum + i] == FULL) {
        return false;
      }
    }
  }
  return true;
}

// Standard init function, sets currentState to initial state
void battleshipControl_init() {
  currentState = init_st;
  battleshipControl_createBoard();
}

// Restarts the game and clears the screen and creates a new board
void battleshipControl_restartGame() {
  counter = 0;
  turn = 10;
  display_fillScreen(DISPLAY_BLACK);
  battleshipDisplay_init();
  battleshipControl_createBoard();
}

// Changes the square according to the board
// If it is a valid shot then return true
// If not then return false
bool battleshipControl_confirmFire() {
  uint8_t shipNum = 0;
  if (battleBoard.squares[battleshipRegion_getColumn()]
                         [battleshipRegion_getRow()] == EMPTY) {
    battleBoard
        .squares[battleshipRegion_getColumn()][battleshipRegion_getRow()] =
        MISS;
    battleBoard
        .shipSquares[battleshipRegion_getColumn()][battleshipRegion_getRow()] =
        MISS;
    battleshipDisplay_drawFire(MISS);
  }

  else if (battleBoard.squares[battleshipRegion_getColumn()]
                              [battleshipRegion_getRow()] == FULL) {
    battleBoard
        .squares[battleshipRegion_getColumn()][battleshipRegion_getRow()] = HIT;
    shipNum = battleBoard.shipSquares[battleshipRegion_getColumn()]
                                     [battleshipRegion_getRow()];
    battleBoard
        .shipSquares[battleshipRegion_getColumn()][battleshipRegion_getRow()] =
        battleBoard.shipSquares[battleshipRegion_getColumn()]
                               [battleshipRegion_getRow()] +
        10;
    battleshipDisplay_drawFire(HIT);
    battleshipControl_checkIfSunk(shipNum);
  }

  else if (battleBoard.squares[battleshipRegion_getColumn()]
                              [battleshipRegion_getRow()] == NEXT_TO_SHIP) {
    battleBoard
        .squares[battleshipRegion_getColumn()][battleshipRegion_getRow()] =
        SPLASH;
    battleBoard
        .shipSquares[battleshipRegion_getColumn()][battleshipRegion_getRow()] =
        SPLASH;
    battleshipDisplay_drawFire(SPLASH);
  }

  else {

    return false;
  }

  return true;
}

// Resumes the game after all the switches have been turned off.
void battleshipControl_resumeGame() {
  display_fillScreen(DISPLAY_BLACK);
  battleshipDisplay_init();
  counter = 0;
  bool array[10];
  bool sunk = true;

  // Which ships are sunk
  for (int8_t ship = 11; ship < 16; ship++) {
    sunk = true;
    for (uint8_t i = 0; i < 10; i++) {
      for (uint8_t j = 0; j < 10; j++) {
        if (battleBoard.shipSquares[i][j] == ship) {
          sunk = false;
        }
      }
    }
    array[ship - 11] = sunk;
  }

  // Prints the MISS and Splash squares
  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 10; j++) {

      battleshipDisplay_setRowColumnFromControl(j, i);
      battleshipDisplay_drawFire(battleBoard.shipSquares[i][j]);
    }
  }

  // Prints the Hits or Sunk squares
  for (uint8_t i = 0; i < 10; i++) {
    for (uint8_t j = 0; j < 10; j++) {
      if (battleBoard.shipSquares[i][j] != 4 &&
          battleBoard.shipSquares[i][j] != 1 &&
          battleBoard.shipSquares[i][j] != 0 &&
          battleBoard.shipSquares[i][j] != 11 &&
          battleBoard.shipSquares[i][j] != 12 &&
          battleBoard.shipSquares[i][j] != 13 &&
          battleBoard.shipSquares[i][j] != 14 &&
          battleBoard.shipSquares[i][j] != 15) {
        uint8_t ship = battleBoard.shipSquares[i][j] % 20;
        battleshipDisplay_setRowColumnFromControl(j, i);
        if (array[ship - 1]) {
          battleshipDisplay_drawFire(SUNK);
        } else {
          battleshipDisplay_drawFire(HIT);
        }
      }
    }
  }
}

// Standard tick function.
void battleshipControl_tick() {
  seed++;
  // If BTN3 is hit at any time then restart the game
  // Unless a switch is high
  if (buttons_read() == 0x8 && !switchOn && !btnOn) {
    battleshipControl_restartGame();
    btnOn = true;
    currentState = release_btn_st;
  }
  // If Switches are hit anytime during the game then show the instructions
  // Unless BTN3 is pressed
  else if (switches_read() != 0x0 && !switchOn && !btnOn) {
    resumeState = currentState;
    currentState = instructions_st;
    display_fillScreen(DISPLAY_BLACK);
    switchOn = true;
  }

  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {
  // Initial state
  case init_st:
    currentState = intro_st;
    battleshipDisplay_intro(DRAW);
    break;

  // Intro screen
  case intro_st:
    if (counter == WAIT_TIME) {
      currentState = waiting_for_initial_touch_st;
      battleshipDisplay_intro(ERASE);
      battleshipDisplay_drawWaitScreen(DRAW);
      counter = 0;
    }
    break;

  // Waits for a touch to start the game
  case waiting_for_initial_touch_st:
    if (display_isTouched()) {
      currentState = waiting_for_touch_st;
      battleshipControl_createBoard();
      battleshipDisplay_drawWaitScreen(ERASE);
      battleshipDisplay_init();
      turn = 10;
    }
    break;

  // Wait to select a region of the board
  case waiting_for_touch_st:
    if (display_isTouched()) {
      display_clearOldTouchData();
      currentState = waiting_for_release_st;
    }
    break;

  // Wait to release touch
  case waiting_for_release_st:
    display_getTouchedPoint(&x, &y, &z);
    if (!display_isTouched()) {
      currentState = confirm_touch_st;
      regionNumber = battleshipRegion_computeRegionNumber(x, y);
      battleshipDisplay_drawSelectedArea(DRAW);
      break;
    }
    break;

  // Waits to touch another region or confirm the shot with BTN0
  case confirm_touch_st:
    if (buttons_read() == 0x1) {
      if (battleshipControl_confirmFire()) {
        currentState = gameplay_st;
        battleshipDisplay_drawSelectedArea(ERASE);
        turn--;
        battleshipControl_printBoards();

      } else {
        currentState = waiting_for_touch_st;
        battleshipDisplay_drawSelectedArea(ERASE);
      }

    } else if (display_isTouched()) {
      currentState = waiting_for_touch_st;
      battleshipDisplay_drawSelectedArea(ERASE);
    }
    break;

  // Checks if the game is over
  case gameplay_st:
    if (turn != 0 && !battleshipControl_checkGameOver()) {
      currentState = waiting_for_touch_st;
    }

    else {
      display_fillScreen(DISPLAY_BLACK);
      if (battleshipControl_checkGameOver()) {
        battleshipDisplay_drawWin(DRAW);
      } else {
        battleshipDisplay_drawLose(DRAW);
      }
      currentState = final_result_st;
    }
    break;

  // Prints the result of the game
  case final_result_st:
    if (counter == WAIT_TIME) {
      if (battleshipControl_checkGameOver()) {
        battleshipDisplay_drawWin(ERASE);
      } else {
        battleshipDisplay_drawLose(ERASE);
      }
      currentState = waiting_for_initial_touch_st;
      display_fillScreen(DISPLAY_BLACK);
      battleshipDisplay_drawWaitScreen(DRAW);
      counter = 0;
    }
    break;

  // Display the instructions according to switch_read() state
  case instructions_st:

    if (lastSwitch != switches_read()) {
      if (lastSwitch == 0x1) {
        battleshipDisplay_drawSW0Screen(ERASE, turn);
      } else if (lastSwitch == 0x2) {
        battleshipDisplay_drawSW1Screen(ERASE);
      } else if (lastSwitch == 0x4) {
        battleshipDisplay_drawSW2Screen(ERASE);
      } else if (lastSwitch == 0x8) {
        battleshipDisplay_drawSW3Screen(ERASE);
      } else {
        battleshipDisplay_drawInstructionScreen(ERASE);
      }
    }

    lastSwitch = switches_read();

    if (switches_read() == 0x1) {
      battleshipDisplay_drawSW0Screen(DRAW, turn);
    } else if (switches_read() == 0x2) {
      battleshipDisplay_drawSW1Screen(DRAW);
    } else if (switches_read() == 0x4) {
      battleshipDisplay_drawSW2Screen(DRAW);
    } else if (switches_read() == 0x8) {
      battleshipDisplay_drawSW3Screen(DRAW);
    } else if (switches_read() != 0x0) {
      battleshipDisplay_drawInstructionScreen(DRAW);
    }

    if (switches_read() == 0x0) {
      currentState = resumeState;
      switchOn = false;
      counter = 0;

      battleshipDisplay_drawSW0Screen(ERASE, turn);
      battleshipDisplay_drawSW1Screen(ERASE);
      battleshipDisplay_drawSW2Screen(ERASE);
      battleshipDisplay_drawSW3Screen(ERASE);
      battleshipDisplay_drawInstructionScreen(ERASE);

      if (currentState == waiting_for_touch_st ||
          currentState == confirm_touch_st) {
        battleshipControl_resumeGame();
      }

      else if (currentState == waiting_for_initial_touch_st) {
        battleshipDisplay_drawWaitScreen(DRAW);
      }

      else if (currentState == intro_st) {
        currentState = waiting_for_initial_touch_st;
        battleshipDisplay_drawWaitScreen(DRAW);
      } else if (currentState == final_result_st) {
        currentState = waiting_for_initial_touch_st;
        battleshipDisplay_drawWaitScreen(DRAW);
      }
    }
    break;

  // Waits for the BTN3 to be released
  case release_btn_st:
    if (buttons_read() == 0x0) {
      currentState = waiting_for_touch_st;
      btnOn = false;
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

  case intro_st:
    counter++;
    break;

  case waiting_for_initial_touch_st:
    seed++;
    break;

  case waiting_for_touch_st:
    seed++;
    break;

  case waiting_for_release_st:
    break;

  case confirm_touch_st:
    break;

  case gameplay_st:
    break;

  case final_result_st:
    counter++;
    break;

  case instructions_st:
    break;

  case release_btn_st:
    break;

  // Prints a default error message
  default:
    printf(DEFAULT_ERROR_MESSAGE);
    break;
  }
}
