/**
 * Synth Header File
 * Ideas Clinic
 * 
 *    This header defines some functions that are used to update
 *    the audio output of the synthesizer.
 * 
 * Last Updated: August 11, 2023
 */
 
#ifndef internal_h
#define internal_h

#include <MozziGuts.h>
#include <Oscil.h>
#include <ADSR.h>
#include <Line.h>
#include <LowPassFilter.h>
#include <Smooth.h>
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/saw2048_int8.h> // saw table for oscillator
#include <tables/triangle_analogue512_int8.h> // triangle table for oscillator
#include <tables/square_analogue512_int8.h> // square table for oscillator
#include "scale.h" // The internal header file includes functions from the scale header file

#define C_4_FREQ 262
#define LFO_MODE_ATTACK_LEVEL 200
#define LFO_MODE_DECAY_LEVEL 100
#define LFO_MODE_DECAY_TIME 100
#define LFO_MODE_SUSTAIN_TIME 1000
#define CONTROL_RATE 128
#define ADSR_MODE_ATTACK_LEVEL 255
#define ADSR_MODE_DECAY_LEVEL 255

enum WAVE_NAME {sine, saw, tri, sqr};

/** Called in the setup loop of the main code to initialize the base
  *  values for the LFO and ADSR modes 
 */
void internalSetup();

/** Given the values measured from each potentiometer (knob) as parameters,
  * this function updates the corresponding values depending on the mode
 */
void updateEnvironments(int pot0, int pot1, int pot2, int pot3, int pot4);

/** Changes the environment between LFO and ADSR based on user input
 */
void switchMode();

/** Updates the audio output for LFO and ADSR Mode
 *  LFO Mode can switch between different waveforms based on user input
 */
int updateAudio();

/** Given the states of any ADSR buttons, this function sets the ADSR mode to
  * the appropriate frequency and plays the corresponding note. If less than
  * 6 button states are used, the remaining states are disabled (set to high)
 */
void updateADSR(bool State_0 = HIGH, bool State_1 = HIGH, bool State_2 = HIGH, bool State_3 = HIGH, bool State_4 = HIGH, bool State_5 = HIGH);

/** Turn off all sound
 */
void soundOff();

#endif