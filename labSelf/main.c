#include <stdint.h>
#include <stdio.h>
#include <xparameters.h>

#include "buttons.h"
#include "drivers/buttons.h"
#include "drivers/switches.h"

#include "battleshipControl.h"
#include "battleshipDisplay.h"
#include "battleshipRegion.h"

int main() {
  display_init();
  display_fillScreen(DISPLAY_BLACK);
  buttons_init();
  switches_init();
  battleshipControl_init();

  while (1) {
    battleshipControl_tick();
    utils_sleep();
  }

  return 0;
}

// Interrupt routine
void isr_function() {
  // Empty for flag method (flag set elsewhere)
}