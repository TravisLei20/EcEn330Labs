/*
This software is provided for student assignment use in the Department of
Electrical and Computer Engineering, Brigham Young University, Utah, USA.

Users agree to not re-host, or redistribute the software, in source or binary
form, to other persons or other institutions. Users may modify and use the
source code for personal or educational use.

For questions, contact Brad Hutchings or Jeff Goeders, https://ece.byu.edu/
*/

#include "minimax.h"
#include <stdio.h>

#define TOP 0
#define MID 1
#define BOT 2
#define LFT 0
#define RGT 2

// Test the next move code, given several boards.
// You need to also create 10 boards of your own to test.
void testBoards() {
  minimax_board_t board1; // Board 1 is the main example in the web-tutorial
                          // that I use on the web-site.
  board1.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  board1.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  board1.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  board1.squares[MID][LFT] = MINIMAX_X_SQUARE;
  board1.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  board1.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  board1.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  board1.squares[BOT][MID] = MINIMAX_O_SQUARE;
  board1.squares[BOT][RGT] = MINIMAX_O_SQUARE;

  minimax_board_t board2;
  board2.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  board2.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  board2.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  board2.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  board2.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  board2.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  board2.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  board2.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  board2.squares[BOT][RGT] = MINIMAX_O_SQUARE;

  minimax_board_t board3;
  board3.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  board3.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  board3.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  board3.squares[MID][LFT] = MINIMAX_O_SQUARE;
  board3.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  board3.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  board3.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  board3.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  board3.squares[BOT][RGT] = MINIMAX_X_SQUARE;

  minimax_board_t board4;
  board4.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  board4.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  board4.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  board4.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  board4.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  board4.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  board4.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  board4.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  board4.squares[BOT][RGT] = MINIMAX_X_SQUARE;

  minimax_board_t board5;
  board5.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  board5.squares[TOP][MID] = MINIMAX_X_SQUARE;
  board5.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  board5.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  board5.squares[MID][MID] = MINIMAX_O_SQUARE;
  board5.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  board5.squares[BOT][LFT] = MINIMAX_EMPTY_SQUARE;
  board5.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  board5.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;

  //*******************************************************************************************
  // This is my own test cases

  minimax_board_t test;
  test.squares[TOP][LFT] = MINIMAX_EMPTY_SQUARE;
  test.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  test.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test.squares[BOT][LFT] = MINIMAX_EMPTY_SQUARE;
  test.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test_x = true;

  minimax_board_t test1;
  test1.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test1.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test1.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  test1.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test1.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test1.squares[MID][RGT] = MINIMAX_O_SQUARE;
  test1.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test1.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test1.squares[BOT][RGT] = MINIMAX_O_SQUARE;
  bool test1_x = true;

  minimax_board_t test2;
  test2.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test2.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test2.squares[TOP][RGT] = MINIMAX_O_SQUARE;
  test2.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test2.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test2.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test2.squares[BOT][LFT] = MINIMAX_O_SQUARE;
  test2.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test2.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test2_x = true;

  minimax_board_t test3;
  test3.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  test3.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test3.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  test3.squares[MID][LFT] = MINIMAX_O_SQUARE;
  test3.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test3.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test3.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test3.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test3.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test3_x = true;

  minimax_board_t test4;
  test4.squares[TOP][LFT] = MINIMAX_EMPTY_SQUARE;
  test4.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test4.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  test4.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test4.squares[MID][MID] = MINIMAX_O_SQUARE;
  test4.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test4.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test4.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test4.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test4_x = false;

  minimax_board_t test5;
  test5.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test5.squares[TOP][MID] = MINIMAX_O_SQUARE;
  test5.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  test5.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test5.squares[MID][MID] = MINIMAX_O_SQUARE;
  test5.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test5.squares[BOT][LFT] = MINIMAX_EMPTY_SQUARE;
  test5.squares[BOT][MID] = MINIMAX_X_SQUARE;
  test5.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test5_x = false;

  minimax_board_t test6;
  test6.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test6.squares[TOP][MID] = MINIMAX_O_SQUARE;
  test6.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  test6.squares[MID][LFT] = MINIMAX_O_SQUARE;
  test6.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test6.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test6.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test6.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test6.squares[BOT][RGT] = MINIMAX_X_SQUARE;
  bool test6_x = false;

  minimax_board_t test7;
  test7.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test7.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test7.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  test7.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test7.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test7.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test7.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test7.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test7.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test7_x = false;

  minimax_board_t test8;
  test8.squares[TOP][LFT] = MINIMAX_EMPTY_SQUARE;
  test8.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test8.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  test8.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test8.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test8.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test8.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test8.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test8.squares[BOT][RGT] = MINIMAX_X_SQUARE;
  bool test8_x = false;

  minimax_board_t test9;
  test9.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  test9.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test9.squares[TOP][RGT] = MINIMAX_O_SQUARE;
  test9.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test9.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test9.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test9.squares[BOT][LFT] = MINIMAX_O_SQUARE;
  test9.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test9.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test9_x = true;

  minimax_board_t test10;
  test10.squares[TOP][LFT] = MINIMAX_EMPTY_SQUARE;
  test10.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test10.squares[TOP][RGT] = MINIMAX_O_SQUARE;
  test10.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test10.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test10.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test10.squares[BOT][LFT] = MINIMAX_O_SQUARE;
  test10.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test10.squares[BOT][RGT] = MINIMAX_O_SQUARE;
  bool test10_x = true;

  minimax_board_t test11;
  test11.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test11.squares[TOP][MID] = MINIMAX_X_SQUARE;
  test11.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  test11.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test11.squares[MID][MID] = MINIMAX_O_SQUARE;
  test11.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test11.squares[BOT][LFT] = MINIMAX_EMPTY_SQUARE;
  test11.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test11.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test11_x = false;

  minimax_board_t test12;
  test12.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test12.squares[TOP][MID] = MINIMAX_EMPTY_SQUARE;
  test12.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  test12.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test12.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test12.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test12.squares[BOT][LFT] = MINIMAX_EMPTY_SQUARE;
  test12.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test12.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test12_x = false;

  minimax_board_t test13;
  test13.squares[TOP][LFT] = MINIMAX_X_SQUARE;
  test13.squares[TOP][MID] = MINIMAX_O_SQUARE;
  test13.squares[TOP][RGT] = MINIMAX_X_SQUARE;
  test13.squares[MID][LFT] = MINIMAX_EMPTY_SQUARE;
  test13.squares[MID][MID] = MINIMAX_EMPTY_SQUARE;
  test13.squares[MID][RGT] = MINIMAX_O_SQUARE;
  test13.squares[BOT][LFT] = MINIMAX_X_SQUARE;
  test13.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test13.squares[BOT][RGT] = MINIMAX_O_SQUARE;
  bool test13_x = true;

  minimax_board_t test14;
  test14.squares[TOP][LFT] = MINIMAX_O_SQUARE;
  test14.squares[TOP][MID] = MINIMAX_X_SQUARE;
  test14.squares[TOP][RGT] = MINIMAX_EMPTY_SQUARE;
  test14.squares[MID][LFT] = MINIMAX_O_SQUARE;
  test14.squares[MID][MID] = MINIMAX_X_SQUARE;
  test14.squares[MID][RGT] = MINIMAX_EMPTY_SQUARE;
  test14.squares[BOT][LFT] = MINIMAX_EMPTY_SQUARE;
  test14.squares[BOT][MID] = MINIMAX_EMPTY_SQUARE;
  test14.squares[BOT][RGT] = MINIMAX_EMPTY_SQUARE;
  bool test14_x = true;

  uint8_t row, column;

  minimax_computeNextMove(&board1, true, &row,
                          &column); // true means X is current player.
  printf("next move for board1: (%d, %d)\n", row, column);

  minimax_computeNextMove(&board2, true, &row,
                          &column); // true means X is current player.
  printf("next move for board2: (%d, %d)\n", row, column);

  minimax_computeNextMove(&board3, true, &row,
                          &column); // true means X is current player.
  printf("next move for board3: (%d, %d)\n", row, column);

  minimax_computeNextMove(&board4, false, &row,
                          &column); // false means O is current player.
  printf("next move for board4: (%d, %d)\n", row, column);

  minimax_computeNextMove(&board5, false, &row,
                          &column); // false means O is current player.
  printf("next move for board5: (%d, %d)\n", row, column);

  printf("*********************************************************************"
         "* \n");
  printf("\t\tStart the tests that I wrote\n");

  minimax_computeNextMove(&test1, test1_x, &row,
                          &column); // false means O is current player.
  printf("next move for test1: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test2, test2_x, &row,
                          &column); // false means O is current player.
  printf("next move for test2: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test3, test3_x, &row,
                          &column); // false means O is current player.
  printf("next move for test3: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test4, test4_x, &row,
                          &column); // false means O is current player.
  printf("next move for test4: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test5, test5_x, &row,
                          &column); // false means O is current player.
  printf("next move for test5: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test6, test6_x, &row,
                          &column); // false means O is current player.
  printf("next move for test6: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test7, test7_x, &row,
                          &column); // false means O is current player.
  printf("next move for test7: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test8, test8_x, &row,
                          &column); // false means O is current player.
  printf("next move for test8: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test9, test9_x, &row,
                          &column); // false means O is current player.
  printf("next move for test9: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test10, test10_x, &row,
                          &column); // false means O is current player.
  printf("next move for test10: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test11, test11_x, &row,
                          &column); // false means O is current player.
  printf("next move for test11: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test12, test12_x, &row,
                          &column); // false means O is current player.
  printf("next move for test12: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test13, test13_x, &row,
                          &column); // false means O is current player.
  printf("next move for test13: (%d, %d)\n", row, column);

  minimax_computeNextMove(&test14, test14_x, &row,
                          &column); // false means O is current player.
  printf("next move for test14: (%d, %d)\n", row, column);
}
