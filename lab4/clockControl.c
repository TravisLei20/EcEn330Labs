#include "clockControl.h"
#include "clockDisplay.h"
#include "display.h"
#include "stdio.h"

// All printed messages for states are provided here.
#define INIT_ST_MSG "init state\n"
#define NEVER_TOUCHED_ST_MSG "never_touched_st\n"
#define WAITING_FOR_TOUCH_ST_MSG "waiting for touch_st\n"
#define AD_TIMER_RUNNING_ST_MSG "ad_timer_running_st\n"
#define AUTO_TIMER_RUNNING_ST_MSG "auto_timer_running_st\n"
#define RATE_TIMER_RUNNING_ST_MSG "rate_timer_running_st\n"
#define RATE_TIMER_EXPIRED_ST_MSG "rate_timer_expired_st\n"

#define DEFAULT_ERROR_MEALY_MSG "Error occurred in mealy machine\n"
#define DEFAULT_ERROR_MOORE_MSG "Error occurred in moore machine\n"

#define ADC_COUNTER_MAX_VALUE 1
#define AUTO_COUNTER_MAX_VALUE 10
#define RATE_COUNTER_MAX_VALUE 2
#define ADVANCE_ONE_SEC_INTERVAL 20
#define RESET_VALUE 0

uint64_t adcCounter, autoCounter, rateCounter;
bool startTime;
uint8_t timer;

// States for the controller state machine.
enum clockControl_st_t {
  init_st, // Start here, transition out of this state on the first tick.
  never_touched_st, // Wait here until the first touch - clock is disabled until
                    // set.
  waiting_for_touch_st,  // waiting for touch, clock is enabled and running.
  ad_timer_running_st,   // waiting for the touch-controller ADC to settle.
  auto_timer_running_st, // waiting for the auto-update delay to expire
                         // (user is holding down button for auto-inc/dec)
  rate_timer_running_st, // waiting for the rate-timer to expire to know when to
                         // perform the auto inc/dec.
  rate_timer_expired_st, // when the rate-timer expires, perform the inc/dec
                         // function.
  add_second_to_clock_st // add a second to the clock time and reset the ms
                         // counter.
} currentState;

// This is a debug state print routine. It will print the names of the states
// each time tick() is called. It only prints states if they are different than
// the previous state.
void debugStatePrint() {
  static enum clockControl_st_t previousState;
  static bool firstPass = true;
  // Only print the message if:
  // 1. This the first pass and the value for previousState is unknown.
  // 2. previousState != currentState - this prevents reprinting the same state
  // name over and over.
  if (previousState != currentState || firstPass) {
    firstPass = false; // previousState will be defined, firstPass is false.
    previousState =
        currentState;       // keep track of the last state that you were in.
    switch (currentState) { // This prints messages based upon the state that
                            // you were in.
    case init_st:
      printf(INIT_ST_MSG);
      break;
    case never_touched_st:
      printf(NEVER_TOUCHED_ST_MSG);
      break;
    case waiting_for_touch_st:
      printf(WAITING_FOR_TOUCH_ST_MSG);
      break;
    case ad_timer_running_st:
      printf(AD_TIMER_RUNNING_ST_MSG);
      break;
    case auto_timer_running_st:
      printf(AUTO_TIMER_RUNNING_ST_MSG);
      break;
    case rate_timer_running_st:
      printf(RATE_TIMER_RUNNING_ST_MSG);
      break;
    case rate_timer_expired_st:
      printf(RATE_TIMER_EXPIRED_ST_MSG);
      break;
    }
  }
}

// Call this before you call clockControl_tick().
void clockControl_init() {
  currentState = init_st;
  startTime = false;
  timer = 0;
  debugStatePrint();
}

// Performs the Mealy and Moore actions according to the appropriate current
// state machine position
void clockControl_tick() {
  // After the screen is touched once then the timer will start
  if (startTime) {
    // If the screen is not being touched then the timer will run
    if (!display_isTouched()) {
      // If the timer has reached 20 (ADVANCE_ONE_SEC_INTERVAL) then call
      // clockDisplay_advanceTimeOneSecond() and reset it If it has not reached
      // 20 then increment it
      if (timer == ADVANCE_ONE_SEC_INTERVAL) {
        clockDisplay_advanceTimeOneSecond();
        timer = RESET_VALUE;
      } else {
        timer++;
      }
    } else {
      timer = RESET_VALUE;
    }
  }

  // Perform state update first.
  // Perform the Mealy action based on currentState
  switch (currentState) {
  case init_st:
    currentState = waiting_for_touch_st;
    break;

  case never_touched_st:
    break;

  case waiting_for_touch_st:
    // Checks if screen is touched
    // If so then call display_clearOldTouchData()
    // set the currentState to ad_timer_running_st
    // set startTime to true
    if (display_isTouched()) {
      display_clearOldTouchData();
      currentState = ad_timer_running_st;
      startTime = true;
    }
    break;

  case ad_timer_running_st:
    // Checks if screen is touched
    // If so then set the currentState to auto_timer_running_st
    // if not then call clockDisplay_performIncDec() and
    // set currentState to waiting_for_touch_st
    if (display_isTouched()) {
      currentState = auto_timer_running_st;
    } else if (!display_isTouched()) {
      clockDisplay_performIncDec();
      currentState = waiting_for_touch_st;
    }
    break;

  case auto_timer_running_st:
    // Checks if screen is still touched
    // if not then set currentState to waiting_for_touch_st
    if (!display_isTouched()) {
      clockDisplay_performIncDec();
      currentState = waiting_for_touch_st;
    }
    // If the screen is still touched and
    // autoCounter equals AUTO_COUNTER_MAX_VALUE
    // then set the currentState to auto_timer_running_st
    else if (display_isTouched() && autoCounter == AUTO_COUNTER_MAX_VALUE) {
      clockDisplay_performIncDec();
      currentState = rate_timer_running_st;
    }
    break;

  case rate_timer_running_st:
    // Checks if screen is still touched
    // if not then set currentState to waiting_for_touch_st
    if (!display_isTouched()) {
      currentState = waiting_for_touch_st;
    }
    // If the screen is still touched and
    // rateCounter equals RATE_COUNTER_MAX_VALUE
    // then call set clockDisplay_performIncDec()
    // and set currentState to rate_timer_expired_st
    else if (display_isTouched() && rateCounter == RATE_COUNTER_MAX_VALUE) {
      clockDisplay_performIncDec();
      currentState = rate_timer_expired_st;
    }
    break;

  case rate_timer_expired_st:
    // Checks if screen is still touched
    // if not then set currentState to waiting_for_touch_st
    if (!display_isTouched()) {
      currentState = waiting_for_touch_st;
    }
    // If the screen is still touched then
    // set currentState to rate_timer_running_st
    else if (display_isTouched()) {
      clockDisplay_performIncDec();
      currentState = rate_timer_running_st;
    }
    break;

  // print an error message here.
  default:
    printf(DEFAULT_ERROR_MEALY_MSG);
    break;
  }

  // Perform state action next.
  // Perform the Moore actions base on currentState
  switch (currentState) {
  case init_st:
    break;

  // Reset the counters in waiting_for_touch_st
  case waiting_for_touch_st:
    adcCounter = RESET_VALUE;
    autoCounter = RESET_VALUE;
    rateCounter = RESET_VALUE;
    break;

  // Increment adcCounter
  case ad_timer_running_st:
    adcCounter++;
    break;

  // Increment autoCounter
  case auto_timer_running_st:
    autoCounter++;
    break;

  // Increment rateCounter
  case rate_timer_running_st:
    rateCounter++;
    break;

  // Reset rateCounter
  case rate_timer_expired_st:
    rateCounter = RESET_VALUE;
    break;

  // print an error message here.
  default:
    printf(DEFAULT_ERROR_MOORE_MSG);
    break;
  }
}