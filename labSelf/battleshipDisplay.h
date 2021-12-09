#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

#include "display.h"
#include "utils.h"

#include "battleshipRegion.h"

void battleshipDisplay_drawFire(uint8_t selected);

void battleshipDisplay_intro(bool erase);

void battleshipDisplay_init();

void battleshipDisplay_setRowColumn();

void battleshipDisplay_drawSelectedArea(bool erase);

void battleshipDisplay_runTest();

void battleshipDisplay_setRowColumnFromControl(uint8_t row, uint8_t column);

void battleshipDisplay_drawWaitScreen(bool erase);

void battleshipDisplay_drawInstructions(bool erase);

void battleshipDisplay_drawWin(bool erase);

void battleshipDisplay_drawLose(bool erase);

void battleshipDisplay_drawInstructionScreen(bool erase);

void battleshipDisplay_drawSW0Screen(bool erase, uint8_t turn);

void battleshipDisplay_drawSW1Screen(bool erase);

void battleshipDisplay_drawSW2Screen(bool erase);

void battleshipDisplay_drawSW3Screen(bool erase);