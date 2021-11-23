#include "intervalTimer.h"
#include "xil_io.h"
#include "xparameters.h"

#define TCSR0_OFFSET 0X0
#define TCSR1_OFFSET 0X10

#define TLR0_OFFSET 0x04
#define TLR1_OFFSET 0X14

#define TCR0_OFFSET 0X08
#define TCR1_OFFSET 0X18

#define INITIALIZE_VALUE 0X000
#define INITIALIZE_VALUE_SET_CASC 0X800
#define INITIALIZE_VALUE_SET_UDT0 0XFFD

#define RESET_VALUE_TCR 0
#define RESET_VALUE_TLR 0X000

#define START_COUNT 0X080
#define STOP_COUNT 0XF7F

#define LOAD 0x020
#define STOP_LOAD 0XFDF

#define SHIFT_BITS 32

#define TIMER_FREQUENCY 100000000U

// Writes to the Gpio Register.
// timerNumber indicates which timer should be initialized.
// offset indicates what offset should be added to the base address.
// value indicates the value that will be written to the address indicated
void intervalTimer_writeGpioRegister(uint32_t timerNumber, int32_t offset,
                                     int32_t value) {
  // Check if the timerNumber is equal to one of the Timer Device IDs
  // If it is then we will write the value according to the base address
  if (timerNumber == XPAR_AXI_TIMER_0_DEVICE_ID) {
    Xil_Out32(XPAR_AXI_TIMER_0_BASEADDR + offset, value);
  } else if (timerNumber == XPAR_AXI_TIMER_1_DEVICE_ID) {
    Xil_Out32(XPAR_AXI_TIMER_1_BASEADDR + offset, value);
  } else if (timerNumber == XPAR_AXI_TIMER_2_DEVICE_ID) {
    Xil_Out32(XPAR_AXI_TIMER_2_BASEADDR + offset, value);
  }
}

// Returns the base address according to the specific timer.
// timerNumber indicates which timer should be initialized.
int32_t getBaseAddr(uint32_t timerNumber) {
  if (timerNumber == XPAR_AXI_TIMER_0_DEVICE_ID) {
    return XPAR_AXI_TIMER_0_BASEADDR;
  } else if (timerNumber == XPAR_AXI_TIMER_1_DEVICE_ID) {
    return XPAR_AXI_TIMER_1_BASEADDR;
  } else if (timerNumber == XPAR_AXI_TIMER_2_DEVICE_ID) {
    return XPAR_AXI_TIMER_2_BASEADDR;
  }
}

// We must initialize the timers before we use them the first time.
// It is generally only called once but should not cause an error if it
// is called multiple times.
// timerNumber indicates which timer should be initialized.
// returns INTERVAL_TIMER_STATUS_OK if successful, INTERVAL_TIMER_STATUS_FAIL if
// otherwise.
intervalTimer_status_t intervalTimer_init(uint32_t timerNumber) {
  // Determines if the timerNumber corresponds to one fo the timers.
  if (timerNumber == XPAR_AXI_TIMER_0_DEVICE_ID ||
      timerNumber == XPAR_AXI_TIMER_1_DEVICE_ID ||
      timerNumber == XPAR_AXI_TIMER_2_DEVICE_ID) {
    intervalTimer_writeGpioRegister(timerNumber, TCSR0_OFFSET,
                                    INITIALIZE_VALUE);
    intervalTimer_writeGpioRegister(timerNumber, TCSR1_OFFSET,
                                    INITIALIZE_VALUE);

    int32_t cascade = Xil_In32(getBaseAddr(timerNumber) + TCSR0_OFFSET) |
                      INITIALIZE_VALUE_SET_CASC;
    intervalTimer_writeGpioRegister(timerNumber, TCSR0_OFFSET, cascade);

    int32_t clearUDT0 = (Xil_In32(getBaseAddr(timerNumber) + TCSR0_OFFSET) &
                         INITIALIZE_VALUE_SET_UDT0);
    intervalTimer_writeGpioRegister(timerNumber, TCSR0_OFFSET, clearUDT0);

    return INTERVAL_TIMER_STATUS_OK;
  }

  return INTERVAL_TIMER_STATUS_FAIL;
}

// This is a convenience function that initializes all interval timers.
// Simply calls intervalTimer_init() on all timers.
// returns INTERVAL_TIMER_STATUS_OK if successful, INTERVAL_TIMER_STATUS_FAIL if
// otherwise.
intervalTimer_status_t intervalTimer_initAll() {
  // Checks if all timers are initialized successfully
  // If they are initialized successfully we return INTERVAL_TIMER_STATUS_OK
  if (intervalTimer_init(XPAR_AXI_TIMER_0_DEVICE_ID) ==
          INTERVAL_TIMER_STATUS_OK &&
      intervalTimer_init(XPAR_AXI_TIMER_1_DEVICE_ID) ==
          INTERVAL_TIMER_STATUS_OK &&
      intervalTimer_init(XPAR_AXI_TIMER_2_DEVICE_ID) ==
          INTERVAL_TIMER_STATUS_OK) {
    return INTERVAL_TIMER_STATUS_OK;
  }
  return INTERVAL_TIMER_STATUS_FAIL;
}

// This function starts the interval timer running.
// If the interval timer is already running, this function does nothing.
// timerNumber indicates which timer should start running.
void intervalTimer_start(uint32_t timerNumber) {
  intervalTimer_writeGpioRegister(
      timerNumber, TCSR0_OFFSET,
      Xil_In32(getBaseAddr(timerNumber) + TCSR0_OFFSET) | START_COUNT);
}

// This function stops a running interval timer.
// If the interval time is currently stopped, this function does nothing.
// timerNumber indicates which timer should stop running.
void intervalTimer_stop(uint32_t timerNumber) {
  intervalTimer_writeGpioRegister(
      timerNumber, TCSR0_OFFSET,
      Xil_In32(getBaseAddr(timerNumber) + TCSR0_OFFSET) & STOP_COUNT);
}

// This function is called whenever we want to reuse an interval timer.
// For example, say the interval timer has been used in the past, the user
// will call intervalTimer_reset() prior to calling intervalTimer_start().
// timerNumber indicates which timer should reset.
void intervalTimer_reset(uint32_t timerNumber) {
  // Stop the counter
  intervalTimer_stop(timerNumber);

  // Initialize
  intervalTimer_init(timerNumber);

  // Set the 32-bit TLR value to zeros
  intervalTimer_writeGpioRegister(timerNumber, TLR0_OFFSET, RESET_VALUE_TLR);
  intervalTimer_writeGpioRegister(timerNumber, TLR1_OFFSET, RESET_VALUE_TLR);

  // Load the values that are in TLR and then stop loading them
  // Load
  intervalTimer_writeGpioRegister(
      timerNumber, TCSR0_OFFSET,
      Xil_In32(getBaseAddr(timerNumber) + TCSR0_OFFSET) | LOAD);
  intervalTimer_writeGpioRegister(
      timerNumber, TCSR1_OFFSET,
      Xil_In32(getBaseAddr(timerNumber) + TCSR1_OFFSET) | LOAD);
  // Stop-load
  intervalTimer_writeGpioRegister(
      timerNumber, TCSR0_OFFSET,
      Xil_In32(getBaseAddr(timerNumber) + TCSR0_OFFSET) & STOP_LOAD);
  intervalTimer_writeGpioRegister(
      timerNumber, TCSR1_OFFSET,
      Xil_In32(getBaseAddr(timerNumber) + TCSR1_OFFSET) & STOP_LOAD);
}

// Convenience function for intervalTimer_reset().
// Simply calls intervalTimer_reset() on all timers.
void intervalTimer_resetAll() {
  intervalTimer_reset(XPAR_AXI_TIMER_0_DEVICE_ID);
  intervalTimer_reset(XPAR_AXI_TIMER_1_DEVICE_ID);
  intervalTimer_reset(XPAR_AXI_TIMER_2_DEVICE_ID);
}

// Use this function to ascertain how long a given timer has been running.
// Note that it should not be an error to call this function on a running timer
// though it usually makes more sense to call this after intervalTimer_stop()
// has been called.
// The timerNumber argument determines which timer is read.
double intervalTimer_getTotalDurationInSeconds(uint32_t timerNumber) {
  double total;
  uint64_t count;

  count = Xil_In32(getBaseAddr(timerNumber) + TCR1_OFFSET);
  count = count << SHIFT_BITS;
  count = count + Xil_In32(getBaseAddr(timerNumber) + TCR0_OFFSET);
  total = count;
  return total / TIMER_FREQUENCY;
}