#include "globals.h"

#define INDEX_SIZE 100
#define LOW 0

static uint8_t thisSequence[INDEX_SIZE];
static uint16_t sequenceLength;

static uint16_t iterationLength;

// This is the length of the complete sequence at maximum length.
// You must copy the contents of the sequence[] array into the global variable
// that you maintain. Do not just grab the pointer as this will fail.
void globals_setSequence(const uint8_t sequence[], uint16_t length) {

  for (uint16_t i = LOW; i < length; i++) {
    thisSequence[i] = sequence[i];
  }
  sequenceLength = length;
}

// This returns the value of the sequence at the index.
uint8_t globals_getSequenceValue(uint16_t index) { return thisSequence[index]; }

// Retrieve the sequence length.
uint16_t globals_getSequenceLength() { return sequenceLength; }

// This is the length of the sequence that you are currently working on.
void globals_setSequenceIterationLength(uint16_t length) {
  iterationLength = length;
}

// This is the length of the sequence that you are currently working on,
// not the maximum length but the interim length as
// the person playing the game works through the pattern one color at a time.
uint16_t globals_getSequenceIterationLength() { return iterationLength; }