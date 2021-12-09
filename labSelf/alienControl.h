
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

#include "buttons.h"
#include "display.h"
#include "switches.h"
#include "utils.h"

#include "alienDisplay.h"
#include "alienRegion.h"

#define BOARD_ROWS 10
#define BOARD_COLUMNS 10

typedef struct {
  uint8_t squares[BOARD_ROWS][BOARD_COLUMNS];
  uint8_t shipSquares[BOARD_ROWS][BOARD_COLUMNS];
} battle_board_t;

void alienControl_createBoard();

void alienControl_init();

// Standard tick function.
void alienControl_tick();

bool alienControl_checkAvailability(int8_t shipSize, int8_t columnNum,
                                    int8_t rowNum, bool horizontal);

void alienControl_printBoards();

void alienControl_restartGame();

void alienControl_resumeGame();
