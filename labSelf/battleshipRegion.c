#include "battleshipRegion.h"

#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

// Region Numbers
#define REGION_0_0 0
#define REGION_0_1 1
#define REGION_0_2 2
#define REGION_0_3 3
#define REGION_0_4 4
#define REGION_0_5 5
#define REGION_0_6 6
#define REGION_0_7 7
#define REGION_0_8 8
#define REGION_0_9 9

#define REGION_1_0 10
#define REGION_1_1 11
#define REGION_1_2 12
#define REGION_1_3 13
#define REGION_1_4 14
#define REGION_1_5 15
#define REGION_1_6 16
#define REGION_1_7 17
#define REGION_1_8 18
#define REGION_1_9 19

#define REGION_2_0 20
#define REGION_2_1 21
#define REGION_2_2 22
#define REGION_2_3 23
#define REGION_2_4 24
#define REGION_2_5 25
#define REGION_2_6 26
#define REGION_2_7 27
#define REGION_2_8 28
#define REGION_2_9 29

#define REGION_3_0 30
#define REGION_3_1 31
#define REGION_3_2 32
#define REGION_3_3 33
#define REGION_3_4 34
#define REGION_3_5 35
#define REGION_3_6 36
#define REGION_3_7 37
#define REGION_3_8 38
#define REGION_3_9 39

#define REGION_4_0 40
#define REGION_4_1 41
#define REGION_4_2 42
#define REGION_4_3 43
#define REGION_4_4 44
#define REGION_4_5 45
#define REGION_4_6 46
#define REGION_4_7 47
#define REGION_4_8 48
#define REGION_4_9 49

#define REGION_5_0 50
#define REGION_5_1 51
#define REGION_5_2 52
#define REGION_5_3 53
#define REGION_5_4 54
#define REGION_5_5 55
#define REGION_5_6 56
#define REGION_5_7 57
#define REGION_5_8 58
#define REGION_5_9 59

#define REGION_6_0 60
#define REGION_6_1 61
#define REGION_6_2 62
#define REGION_6_3 63
#define REGION_6_4 64
#define REGION_6_5 65
#define REGION_6_6 66
#define REGION_6_7 67
#define REGION_6_8 68
#define REGION_6_9 69

#define REGION_7_0 70
#define REGION_7_1 71
#define REGION_7_2 72
#define REGION_7_3 73
#define REGION_7_4 74
#define REGION_7_5 75
#define REGION_7_6 76
#define REGION_7_7 77
#define REGION_7_8 78
#define REGION_7_9 79

#define REGION_8_0 80
#define REGION_8_1 81
#define REGION_8_2 82
#define REGION_8_3 83
#define REGION_8_4 84
#define REGION_8_5 85
#define REGION_8_6 86
#define REGION_8_7 87
#define REGION_8_8 88
#define REGION_8_9 89

#define REGION_9_0 90
#define REGION_9_1 91
#define REGION_9_2 92
#define REGION_9_3 93
#define REGION_9_4 94
#define REGION_9_5 95
#define REGION_9_6 96
#define REGION_9_7 97
#define REGION_9_8 98
#define REGION_9_9 99

#define X_OFFSET 32
#define Y_OFFSET 24

static uint8_t rowNum = 0;
static uint8_t columnNum = 0;

// Determines the row and column and region according to the x and y coordinates
int8_t battleshipRegion_computeRegionNumber(int16_t x, int16_t y) {
  if (x < X_OFFSET) {
    columnNum = 0;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_0_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_0_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_0_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_0_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_0_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_0_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_0_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_0_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_0_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_0_9;
    }
  } else if (x < X_OFFSET * 2) {
    columnNum = 1;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_1_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_1_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_1_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_1_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_1_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_1_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_1_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_1_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_1_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_1_9;
    }
  } else if (x < X_OFFSET * 3) {
    columnNum = 2;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_2_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_2_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_2_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_2_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_2_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_2_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_2_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_2_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_2_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_2_9;
    }
  } else if (x < X_OFFSET * 4) {
    columnNum = 3;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_3_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_3_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_3_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_3_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_3_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_3_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_3_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_3_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_3_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_3_9;
    }
  } else if (x < X_OFFSET * 5) {
    columnNum = 4;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_4_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_4_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_4_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_4_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_4_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_4_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_4_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_4_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_4_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_4_9;
    }
  } else if (x < X_OFFSET * 6) {
    columnNum = 5;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_5_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_5_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_5_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_5_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_5_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_5_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_5_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_5_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_5_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_5_9;
    }
  } else if (x < X_OFFSET * 7) {
    columnNum = 6;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_6_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_6_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_6_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_6_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_6_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_6_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_6_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_6_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_6_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_6_9;
    }
  } else if (x < X_OFFSET * 8) {
    columnNum = 7;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_7_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_7_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_7_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_7_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_7_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_7_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_7_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_7_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_7_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_7_9;
    }
  } else if (x < X_OFFSET * 9) {
    columnNum = 8;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_8_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_8_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_8_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_8_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_8_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_8_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_8_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_8_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_8_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_8_9;
    }
  } else if (x < X_OFFSET * 10) {
    columnNum = 9;
    if (y < Y_OFFSET) {
      rowNum = 0;
      return REGION_9_0;
    } else if (y < Y_OFFSET * 2) {
      rowNum = 1;
      return REGION_9_1;
    } else if (y < Y_OFFSET * 3) {
      rowNum = 2;
      return REGION_9_2;
    } else if (y < Y_OFFSET * 4) {
      rowNum = 3;
      return REGION_9_3;
    } else if (y < Y_OFFSET * 5) {
      rowNum = 4;
      return REGION_9_4;
    } else if (y < Y_OFFSET * 6) {
      rowNum = 5;
      return REGION_9_5;
    } else if (y < Y_OFFSET * 7) {
      rowNum = 6;
      return REGION_9_6;
    } else if (y < Y_OFFSET * 8) {
      rowNum = 7;
      return REGION_9_7;
    } else if (y < Y_OFFSET * 9) {
      rowNum = 8;
      return REGION_9_8;
    } else if (y < Y_OFFSET * 10) {
      rowNum = 9;
      return REGION_9_9;
    }
  }
}

uint8_t battleshipRegion_getColumn() { return columnNum; }

uint8_t battleshipRegion_getRow() { return rowNum; }

uint8_t battleshipRegion_getColumnFromRegion(uint16_t regionNumber) {
  return regionNumber / 10;
}

uint8_t battleshipRegion_getRowFromRegion(uint16_t regionNumber) {
  return regionNumber % 10;
}