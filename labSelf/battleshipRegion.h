#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

int8_t battleshipRegion_computeRegionNumber(int16_t x, int16_t y);

uint8_t battleshipRegion_getColumn();

uint8_t battleshipRegion_getRow();

uint8_t battleshipRegion_getColumnFromRegion(uint16_t regionNumber);

uint8_t battleshipRegion_getRowFromRegion(uint16_t regionNumber);