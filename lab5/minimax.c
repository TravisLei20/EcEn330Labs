#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "minimax.h"

#define TOP 0
#define MID 1
#define BOT 2
#define LFT 0
#define RGT 2

#define FIRST_INDEX 0
#define SECOND_INDEX 1

#define INITIALIZE_ITERATION 0

#define GAME_ON false
#define GAME_OFF true

#define ARRAY_SIZE 10

#define INDEX_START 0
#define ERROR -1

// Declaring choice
static minimax_move_t choice = {};

// Determine if the game is over by looking at the score that is passed into it.
bool minimax_isGameOver(minimax_score_t score) {
  // Checks if score is the same as MINIMAX_NOT_ENDGAME.
  // If it is then return GAME_ON
  if (score == MINIMAX_NOT_ENDGAME) {
    return GAME_ON;
  }
  // If not then return GAME_OFF
  else {
    return GAME_OFF;
  }
}

// Returns the score of the board, based upon the player turn and the board.
// This returns one of 4 values: MINIMAX_X_WINNING_SCORE,
// MINIMAX_O_WINNING_SCORE, MINIMAX_DRAW_SCORE, MINIMAX_NOT_ENDGAME
minimax_score_t minimax_computeBoardScore(minimax_board_t *board,
                                          bool player_is_x) {
  // Checks all the cases to see if X wins
  // case 1
  if (board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
      board->squares[TOP][MID] == MINIMAX_X_SQUARE &&
      board->squares[TOP][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 2
  else if (board->squares[MID][LFT] == MINIMAX_X_SQUARE &&
           board->squares[MID][MID] == MINIMAX_X_SQUARE &&
           board->squares[MID][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 3
  else if (board->squares[BOT][LFT] == MINIMAX_X_SQUARE &&
           board->squares[BOT][MID] == MINIMAX_X_SQUARE &&
           board->squares[BOT][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 4
  else if (board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
           board->squares[MID][LFT] == MINIMAX_X_SQUARE &&
           board->squares[BOT][LFT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 5
  else if (board->squares[TOP][MID] == MINIMAX_X_SQUARE &&
           board->squares[MID][MID] == MINIMAX_X_SQUARE &&
           board->squares[BOT][MID] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 6
  else if (board->squares[TOP][RGT] == MINIMAX_X_SQUARE &&
           board->squares[MID][RGT] == MINIMAX_X_SQUARE &&
           board->squares[BOT][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 7
  else if (board->squares[TOP][LFT] == MINIMAX_X_SQUARE &&
           board->squares[MID][MID] == MINIMAX_X_SQUARE &&
           board->squares[BOT][RGT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }
  // case 8
  else if (board->squares[TOP][RGT] == MINIMAX_X_SQUARE &&
           board->squares[MID][MID] == MINIMAX_X_SQUARE &&
           board->squares[BOT][LFT] == MINIMAX_X_SQUARE) {
    return MINIMAX_X_WINNING_SCORE;
  }

  // Checks all the cases to see if O wins
  // case 1
  if (board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
      board->squares[TOP][MID] == MINIMAX_O_SQUARE &&
      board->squares[TOP][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 2
  else if (board->squares[MID][LFT] == MINIMAX_O_SQUARE &&
           board->squares[MID][MID] == MINIMAX_O_SQUARE &&
           board->squares[MID][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 3
  else if (board->squares[BOT][LFT] == MINIMAX_O_SQUARE &&
           board->squares[BOT][MID] == MINIMAX_O_SQUARE &&
           board->squares[BOT][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 4
  else if (board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
           board->squares[MID][LFT] == MINIMAX_O_SQUARE &&
           board->squares[BOT][LFT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 5
  else if (board->squares[TOP][MID] == MINIMAX_O_SQUARE &&
           board->squares[MID][MID] == MINIMAX_O_SQUARE &&
           board->squares[BOT][MID] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 6
  else if (board->squares[TOP][RGT] == MINIMAX_O_SQUARE &&
           board->squares[MID][RGT] == MINIMAX_O_SQUARE &&
           board->squares[BOT][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 7
  else if (board->squares[TOP][LFT] == MINIMAX_O_SQUARE &&
           board->squares[MID][MID] == MINIMAX_O_SQUARE &&
           board->squares[BOT][RGT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }
  // case 8
  else if (board->squares[TOP][RGT] == MINIMAX_O_SQUARE &&
           board->squares[MID][MID] == MINIMAX_O_SQUARE &&
           board->squares[BOT][LFT] == MINIMAX_O_SQUARE) {
    return MINIMAX_O_WINNING_SCORE;
  }

  // Checks if there is any empty spaces left.
  // If there is then return MINIMAX_NOT_ENDGAME
  // This loop loops through the number of rows
  for (int8_t row = INITIALIZE_ITERATION; row < MINIMAX_BOARD_ROWS; row++) {
    // This loop loops through the number of columns
    for (int8_t column = INITIALIZE_ITERATION; column < MINIMAX_BOARD_COLUMNS;
         column++) {
      // Checks if the specified squre is empty
      // If it is then return that the isn't finished
      if (board->squares[row][column] == MINIMAX_EMPTY_SQUARE) {
        return MINIMAX_NOT_ENDGAME;
      }
    }
  }
  // If no one one with the 16 cases above and there are no more spaces left
  // then the game ends in a draw
  return MINIMAX_DRAW_SCORE;
}

// Initializes the board to all empty squares.
void minimax_initBoard(minimax_board_t *board) {
  // Interates through all the rows and columns and sets it to
  // MINIMAX_EMPTY_SQUARE This loop loops through the number of rows
  for (int8_t rowNum = INITIALIZE_ITERATION; rowNum < MINIMAX_BOARD_ROWS;
       rowNum++) {
    // This loop loops through the number of columns
    for (int8_t columnNum = INITIALIZE_ITERATION;
         columnNum < MINIMAX_BOARD_COLUMNS; columnNum++) {
      board->squares[rowNum][columnNum] = MINIMAX_EMPTY_SQUARE;
    }
  }
}

// A function that prints the board that is passed into it.
// Used for debugging
void minimax_printBoard(minimax_board_t *board) {
  // Interates through all the rows and columns to print the current board
  // This for loop loops through the number of rows
  for (int8_t rowNum = INITIALIZE_ITERATION; rowNum < MINIMAX_BOARD_ROWS;
       rowNum++) {
    // This loop loops through the number of columns
    for (int8_t columnNum = INITIALIZE_ITERATION;
         columnNum < MINIMAX_BOARD_COLUMNS; columnNum++) {
      int8_t num = board->squares[rowNum][columnNum];

      // if num equals MINIMAX_X_SQUARE then print X
      if (num == MINIMAX_X_SQUARE) {
        printf("X ");
      }
      // if num equals MINIMAX_O_SQUARE then print O
      else if (num == MINIMAX_O_SQUARE) {
        printf("O ");
      }
      // If the space isn't either MINIMAX_X_SQUARE or MINIMAX_O_SQUARE the
      // print a space
      else {
        printf("  ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

// calculates the best move using recursion.
// using the given board and the current player's turn to find the best move
minimax_score_t minimax(minimax_board_t *board, bool current_player_is_x) {
  // Declare the score array
  minimax_score_t scores[ARRAY_SIZE] = {};
  // Declare the move array
  minimax_move_t move[ARRAY_SIZE] = {};

  uint8_t index = INDEX_START;

  // Checks if the game is finished
  // If the game is finished then returns the score of the given board
  // Recursion base case, there has been a win or a draw.
  if (minimax_isGameOver(
          minimax_computeBoardScore(board, current_player_is_x))) {
    return minimax_computeBoardScore(board, current_player_is_x);
  }

  // This loop will generate all possible boards by iterating through all the
  // rows and columns This loop loops through the number of rows
  for (uint8_t rowNum = INITIALIZE_ITERATION; rowNum < MINIMAX_BOARD_ROWS;
       rowNum++) {
    // This loop loops through the number of rows
    for (uint8_t columnNum = INITIALIZE_ITERATION;
         columnNum < MINIMAX_BOARD_COLUMNS; columnNum++) {
      // If the square is empty then assign it a value based on the current_player_is_x value.\
        // If not then skip over it
      if (board->squares[rowNum][columnNum] == MINIMAX_EMPTY_SQUARE) {
        // Assign the square to 'X'or O' based on the current_player_is_x value.
        if (current_player_is_x) {
          board->squares[rowNum][columnNum] = MINIMAX_X_SQUARE;
        } else {
          board->squares[rowNum][columnNum] = MINIMAX_O_SQUARE;
        }
        // Record the score and move
        scores[index] = minimax(board, !current_player_is_x);
        move[index].row = rowNum;
        move[index].column = columnNum;

        // Set the square to empty again
        board->squares[rowNum][columnNum] = MINIMAX_EMPTY_SQUARE;

        // Increment the index
        index++;
      }
    }
  }

  // Return the score depending upon whether you are computing min or max.
  // Return the max if current_player_is_x is true.
  // Return the min if current_player_is_x is false.
  if (current_player_is_x) {
    // Set the max to the first index value and then interate through the rest
    // of the array comparing the values with the max
    minimax_score_t maxValue = scores[FIRST_INDEX];
    choice = move[FIRST_INDEX];
    // Starts the iteration at index one
    for (uint8_t i = SECOND_INDEX; i < index; i++) {
      // if the value in the current index is greater than maxValue then store
      // it in choice and maxValue
      if (maxValue < scores[i]) {
        maxValue = scores[i];
        choice = move[i];
      }
    }
    return maxValue;
  } else {
    // Set the min to the first index value and then interate through the rest
    // of the array comparing the values with the min
    minimax_score_t minValue = scores[FIRST_INDEX];
    choice = move[FIRST_INDEX];
    // Starts the iteration at index one
    for (uint8_t i = SECOND_INDEX; i < index; i++) {
      // if the value in the current index is greater than maxValue then store
      // it in choice and maxValue
      if (minValue > scores[i]) {
        minValue = scores[i];
        choice = move[i];
      }
    }
    return minValue;
  }
  // Return -1 if an error occured
  return ERROR;
}

// This routine is not recursive but will invoke the recursive minimax function.
// You will call this function from the controlling state machine that you will
// implement in ticTacToeControl.c. It computes the row and column of the next
// move based upon: the current board, the player. true means the computer is X.
// false means the computer is O. When called from the controlling state
// machine, you will call this function as follows:
// 1. If the computer is playing as X, you will call this function with
// current_player_is_x = true.
// 2. If the computer is playing as O, you will call this function with
// current_player_is_x = false. minimax_computeNextMove directly passes the
// current_player_is_x argument into the minimax() (helper) function. To assign
// values to the row and column arguments, you must use the following syntax in
// the body of the function: *row = move_row; *column = move_column; (for
// example).
void minimax_computeNextMove(minimax_board_t *board, bool current_player_is_x,
                             uint8_t *row, uint8_t *column) {
  minimax(board, current_player_is_x);
  *row = choice.row;
  *column = choice.column;
}