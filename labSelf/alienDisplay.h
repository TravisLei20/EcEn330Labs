#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

#include "display.h"
#include "utils.h"

#include "alienRegion.h"

void alienDisplay_drawFire(uint8_t selected);

void alienDisplay_intro(bool erase);

void alienDisplay_init();

void alienDisplay_setRowColumn();

void alienDisplay_drawSelectedArea(bool erase);

void alienDisplay_runTest();

void alienDisplay_setRowColumnFromControl(uint8_t row, uint8_t column);

void alienDisplay_drawWaitScreen(bool erase);

void alienDisplay_drawInstructions(bool erase);

void alienDisplay_drawWin(bool erase);

void alienDisplay_drawLose(bool erase);

void alienDisplay_drawInstructionScreen(bool erase);

void alienDisplay_drawSW0Screen(bool erase, uint8_t turn);

void alienDisplay_drawSW1Screen(bool erase);

void alienDisplay_drawSW2Screen(bool erase);

void alienDisplay_drawSW3Screen(bool erase);