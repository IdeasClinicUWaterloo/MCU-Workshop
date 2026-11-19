/**
 * Tron Days
 * Synthesizer Code
 * Ideas Clinic
 *
 * Last Updated: August 11, 2023
 */

/** Include the functions and definitions from internal.h. The libraries that are
 *  included in internal.h are also included through here
 */
#include "internal.h"

// Define analog input pins
#define KNOB1 A0     // ADSR mode: Attack; LFO mode: Waveform
#define KNOB2 A1     // ADSR mode: Decay; LFO mode: Frequency
#define KNOB3 A2     // ADSR mode: Sustain; LFO mode: Cutoff Frequency
#define KNOB4 A3     // ADSR mode: Release; LFO mode: LFO frequency
#define KNOB5 A4     // LFO mode: Resonance

// Define digital input pins
#define ADSR_NOTE_0 7         // Plays note from the current scale in ADSR mode
#define SCALE_SELECT_PIN 8    // Switch between scales in ADSR mode
#define MODE_SELECT_PIN 11    // Selects between LFO mode and ADSR mode

int pot0, pot1, pot2, pot3, pot4; // Stores the value of each potentiometer

// Variables for button debouncing
long modePinLastChangeTime = 0;
bool modePinLastState = HIGH;
bool modePinDebouncedState = HIGH;
long scalePinLastChangeTime = 0;
bool scalePinLastState = HIGH;
bool scalePinDebouncedState = HIGH;

// Global variables to track pin states
bool modePinState = HIGH;
bool scalePinState = HIGH;
bool notePinState0 = HIGH;

extern bool isLFOMode;

bool doPause = false;
long lastButtonTime = 0;

int loopiter = 0;

/** The setup function runs after the above values are defined and initialized
 *  and before the loop function.
 */
void setup() {
  Serial.begin(9600);

  startMozzi(CONTROL_RATE);
  internalSetup(); // Sets up the baseline values for ADSR and LFO modes
  setNotes(major, C_4); // Sets the starting scale to major

  pinMode(MODE_SELECT_PIN, INPUT_PULLUP);
  pinMode(SCALE_SELECT_PIN, INPUT_PULLUP);
  pinMode(ADSR_NOTE_0, INPUT_PULLUP);
}

/** Updates parameters based on the current mode:
 *  waveform, frequency, cutoff frequency, LFO frequency, and resonance in LFO
 *  Mode, or attack, decay, sustain, and release in ADSR Mode
 */
void updateControl() {
  pot0=mozziAnalogRead(A0);
  pot1=mozziAnalogRead(A1);
  pot2=mozziAnalogRead(A2);
  pot3=mozziAnalogRead(A3);
  pot4=mozziAnalogRead(A4);

  updateEnvironments(pot0, pot1, pot2, pot3, pot4);
}

/** The checkInputs function monitors the digital pins connected to each button
 *  and updates the states accordingly
 */
void checkInputs() {
  // Read Mode Select and Scale Select Pin States and check for debouncing
  modePinState = digitalRead(MODE_SELECT_PIN);
  scalePinState = digitalRead(SCALE_SELECT_PIN);
  
  // Read ADSR Note Pin State
  if (!isLFOMode){
    scalePinState = digitalRead(SCALE_SELECT_PIN);
    
    // Read ADSR Note Pin States
    switch(loopiter) {
      case 0:
        notePinState0 = digitalRead(ADSR_NOTE_0);
    }
  }
}

/** The updateEnvironments function updates the ADSR and LFO environments
 *  based on inputs
 */
void updateEnvironments() {
  // Check mode button for debouncing
  if (!doPause){
    if (modePinState == LOW) {
      soundOff();
      switchMode();
      lastButtonTime = millis();
      doPause = true;
    }
    if (scalePinState == LOW) {
      soundOff();
      nextScale();
      lastButtonTime = millis();
      doPause = true;
    }
  } else {
    if ((millis() - lastButtonTime) > 1000){
      doPause = false;
    }
  }

  // Update ADSR Note frequency based on if button is pressed and play ADSR note
  updateADSR(notePinState0);
}

/** The loop function is run repeatedly after the setup function is finished.
 */
void loop() {
  checkInputs();
  updateEnvironments();
  audioHook();
  loopiter++;

  if (loopiter > 8) {
    loopiter = 0;
  }
}