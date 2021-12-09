
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

#include "buttons.h"
#include "display.h"
#include "switches.h"
#include "utils.h"

#include "battleshipDisplay.h"
#include "battleshipRegion.h"

#define BOARD_ROWS 10
#define BOARD_COLUMNS 10

typedef struct {
  uint8_t squares[BOARD_ROWS][BOARD_COLUMNS];
  uint8_t shipSquares[BOARD_ROWS][BOARD_COLUMNS];
} battle_board_t;

void battleshipControl_createBoard();

void battleshipControl_init();

// Standard tick function.
void battleshipControl_tick();

bool battleshipControl_checkAvailability(int8_t shipSize, int8_t columnNum,
                                         int8_t rowNum, bool horizontal);

void battleshipControl_printBoards();

void battleshipControl_restartGame();

void battleshipControl_resumeGame();
