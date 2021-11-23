#include "buttons.h"
#include "display.h"
#include "xil_io.h"
#include "xparameters.h"

#define VALUE 0xF
#define WRITE_OFFSET 0x4
#define READ_OFFSET 0x0
#define CANCEL 0xF
#define INITIALIZE_ITERATION 0x0

#define GREEN 0x07E0
#define RED 0xF800
#define YELLOW 0xFFE0
#define BLACK 0x0000
#define BLUE 0x001F

#define BTN3_RECT_X_START 0
#define BTN2_RECT_X_START 80
#define BTN1_RECT_X_START 160
#define BTN0_RECT_X_START 240
#define BTN_RECT_Y_START 0

#define RECT_WIDTH 80
#define RECT_HEIGHT 120

#define BTN3_CURSOR_X 15
#define BTN2_CURSOR_X 95
#define BTN1_CURSOR_X 175
#define BTN0_CURSOR_X 255
#define BTN_CURSOR_Y 50

#define BTN_TEXT_SIZE 2

#define BTN3_TEXT "BTN3"
#define BTN2_TEXT "BTN2"
#define BTN1_TEXT "BTN1"
#define BTN0_TEXT "BTN0"

int32_t lastIteration = INITIALIZE_ITERATION;

// Tests the buttons to see if there is a difference between
// iterations. If there is differences then the difference will
// be found and the appropriate display will be changed.
// The parameter of currentIteration comes from the current value of
// the buttons taken from buttons_read().
void buttons_test(int32_t currentIteration) {
  display_setTextColor(BLACK);
  display_setTextSize(BTN_TEXT_SIZE);

  // testing to determine if there is any difference between
  // the current and last iteration
  if (currentIteration != lastIteration) {
    // test to determine if there is the found difference
    // is the 0 bit
    if ((lastIteration & BUTTONS_BTN0_MASK) !=
        (currentIteration & BUTTONS_BTN0_MASK)) {
      // determine if the button is pressed or not
      if ((currentIteration & BUTTONS_BTN0_MASK) == BUTTONS_BTN0_MASK) {
        display_fillRect(BTN0_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, YELLOW);
        display_setCursor(BTN0_CURSOR_X, BTN_CURSOR_Y);
        display_println(BTN0_TEXT);
      } else {
        display_fillRect(BTN0_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, BLACK);
      }
    }

    // test to determine if there is the found difference
    // is the 1st bit
    if ((lastIteration & BUTTONS_BTN1_MASK) !=
        (currentIteration & BUTTONS_BTN1_MASK)) {
      // determine if the button is pressed or not
      if ((currentIteration & BUTTONS_BTN1_MASK) == BUTTONS_BTN1_MASK) {
        display_fillRect(BTN1_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, GREEN);
        display_setCursor(BTN1_CURSOR_X, BTN_CURSOR_Y);
        display_println(BTN1_TEXT);
      } else {
        display_fillRect(BTN1_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, BLACK);
      }
    }

    // test to determine if there is the found difference
    // is the 2nd bit
    if ((lastIteration & BUTTONS_BTN2_MASK) !=
        (currentIteration & BUTTONS_BTN2_MASK)) {
      // determine if the button is pressed or not
      if ((currentIteration & BUTTONS_BTN2_MASK) == BUTTONS_BTN2_MASK) {
        display_fillRect(BTN2_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, RED);
        display_setCursor(BTN2_CURSOR_X, BTN_CURSOR_Y);
        display_println(BTN2_TEXT);
      } else {
        display_fillRect(BTN2_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, BLACK);
      }
    }

    // test to determine if there is the found difference
    // is the 3rd bit
    if ((lastIteration & BUTTONS_BTN3_MASK) !=
        (currentIteration & BUTTONS_BTN3_MASK)) {
      // determine if the button is pressed or not
      if ((currentIteration & BUTTONS_BTN3_MASK) == BUTTONS_BTN3_MASK) {
        display_fillRect(BTN3_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, BLUE);
        display_setCursor(BTN3_CURSOR_X, BTN_CURSOR_Y);
        display_println(BTN3_TEXT);
      } else {
        display_fillRect(BTN3_RECT_X_START, BTN_RECT_Y_START, RECT_WIDTH,
                         RECT_HEIGHT, BLACK);
      }
    }
    lastIteration = currentIteration;
  }
}

// Returns the lowest 4 bits of the button pins
// the offset parameter is the offset value from the baseaddress
int32_t buttons_readGpioRegister(int32_t offset) {
  return Xil_In32(XPAR_PUSH_BUTTONS_BASEADDR + offset);
}

// Writes a given 4 bit value to the baseaddress plus a given offset
void buttons_writeGpioRegister(int32_t offset, int32_t value) {
  Xil_Out32(XPAR_PUSH_BUTTONS_BASEADDR + offset, value);
}

// Initializes the button driver software and hardware. Returns one of the
// defined status values (above).
int32_t buttons_init() {
  buttons_writeGpioRegister(WRITE_OFFSET, VALUE);
  return BUTTONS_INIT_STATUS_OK;
}

// Returns the current value of all 4 buttons as the lower 4 bits of the
// returned value. bit3 = BTN3, bit2 = BTN2, bit1 = BTN1, bit0 = BTN0.
int32_t buttons_read() { return buttons_readGpioRegister(READ_OFFSET); }

// Runs a test of the buttons. As you push the buttons, graphics and messages
// will be written to the LCD panel. The test will until all 4 pushbuttons are
// simultaneously pressed.
void buttons_runTest() {
  display_init();
  buttons_init();
  display_fillScreen(BLACK);

  // continues to test the buttons until all buttons are pressed at the same
  // time it then will make the screen all black
  while (buttons_read() != CANCEL) {
    buttons_test(buttons_read());
  }
  display_fillScreen(BLACK);
}