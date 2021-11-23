#include "switches.h"
#include "leds.h"
#include "xil_io.h"
#include "xparameters.h"

#define VALUE 0xF
#define WRITE_OFFSET 0x4
#define READ_OFFSET 0x0
#define CANCEL 0xF
#define STOP 0x0
#define DONT_TEST false

// Returns the lowest 4 bits of the button pins
// the offset parameter is the offset value from the baseaddress
int32_t switches_readGpioRegister(int32_t offset) {
  return Xil_In32(XPAR_SLIDE_SWITCHES_BASEADDR + offset);
}

// Writes a given 4 bit value to the baseaddress plus a given offset
void switches_writeGpioRegister(int32_t offset, int32_t value) {
  Xil_Out32(XPAR_SLIDE_SWITCHES_BASEADDR + offset, value);
}

// Initializes the SWITCHES driver software and hardware. Returns one of the
// STATUS values defined above.
int32_t switches_init() {
  switches_writeGpioRegister(WRITE_OFFSET, VALUE);
  return SWITCHES_INIT_STATUS_OK;
}

// Returns the current value of all 4 switches as the lower 4 bits of the
// returned value. bit3 = SW3, bit2 = SW2, bit1 = SW1, bit0 = SW0.
int32_t switches_read() { return switches_readGpioRegister(READ_OFFSET); }

// Runs a test of the switches. As you slide the switches, LEDs directly above
// the switches will illuminate. The test will run until all switches are slid
// upwards. When all 4 slide switches are slid upward, this function will
// return.
void switches_runTest() {
  switches_init();
  leds_init(DONT_TEST);
  int32_t switches = switches_read();
  // continues to test the switches until all are in the on possiton
  // at the same time it then will make all the leds turn off
  while (switches != CANCEL) {
    // switches_test();
    leds_write(switches);
    switches = switches_read();
  }
  leds_write(STOP);
}