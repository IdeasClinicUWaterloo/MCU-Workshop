/**
* Tron Days Sequencer Code
* Ideas Clinic
*
* Last Updated: August 11, 2023
**/

/** Include the functions and definitions from internal.h. The libraries included in
 *  internal.h are also included through here
 */
#include "internal.h"
// Define analog input pins
#define KNOB0 A0     // ADSR mode: Attack
#define KNOB1 A1     // ADSR mode: Decay
#define KNOB2 A2     // ADSR mode: Sustain
#define KNOB3 A3     // ADSR mode: Release
#define KNOB4 A4     // No use in this program

// Define digital input pins
#define SEQUENCE_3_PIN 6      // Plays sequence 3
#define SEQUENCE_2_PIN 7      // Plays sequence 2
#define SEQUENCE_1_PIN 8      // Plays sequence 1
#define SEQUENCE_0_PIN 11     // Plays sequence 0

int pot0, pot1, pot2, pot3, pot4; // Stores the value of each potentiometer

bool pinState0 = HIGH;
bool pinState1 = HIGH;
bool pinState2 = HIGH;
bool pinState3 = HIGH;

/*  The Note_FREQ array stores all note's associated frequency with their
  *   position in the array corresponding to the value of the note stored in
  *   the enumerated list.
**/
                    //NOTE   C     Db    D     Eb    E     F     Gb    G     Ab    A     Bb    B
const int NOTE_FREQ[85] = {   32,   35,   37,   39,   41,   44,   46,   49,   52,   55,   58,   62,    //OCTAVE 1
                              65,   69,   73,   78,   82,   87,   93,   98,   104,  110,  117,  123,   //OCTAVE 2
                              131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247,   //OCTAVE 3
                              262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,   //OCTAVE 4
                              523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988,   //OCTAVE 5
                              1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,  //OCTAVE 6
                              2093, 2217, 2349, 2490, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,  //OCTAVE 7
                              0                                                                        // Value for rest
                          };

/** The NOTE_NAME enumerated list is used to index to the desired pitch so
  * that you don't have to worry about finding what frequency corresponds
  * to each note.
 */
enum NOTE_NAME {C_1, Db_1, D_1, Eb_1, E_1, F_1, Gb_1, G_1, Ab_1, A_1, Bb_1, B_1,
                C_2, Db_2, D_2, Eb_2, E_2, F_2, Gb_2, G_2, Ab_2, A_2, Bb_2, B_2,
                C_3, Db_3, D_3, Eb_3, E_3, F_3, Gb_3, G_3, Ab_3, A_3, Bb_3, B_3,
                C_4, Db_4, D_4, Eb_4, E_4, F_4, Gb_4, G_4, Ab_4, A_4, Bb_4, B_4,
                C_5, Db_5, D_5, Eb_5, E_5, F_5, Gb_5, G_5, Ab_5, A_5, Bb_5, B_5,
                C_6, Db_6, D_6, Eb_6, E_6, F_6, Gb_6, G_6, Ab_6, A_6, Bb_6, B_6,
                C_7, Db_7, D_7, Eb_7, E_7, F_7, Gb_7, G_7, Ab_7, A_7, Bb_7, B_7,
                REST
                };

// TIMES
#define whole_note 1600
#define dotted_half_note (whole_note * 3 / 4)
#define half_note (whole_note / 2)
#define quarter_note (whole_note / 4)
#define eighth_note (whole_note / 8)
#define sixteenth_note (whole_note / 16)

/* -------------------- Sequence 0 -------------------- */
int NOTES_0[51] = { D_4, D_4, D_4, G_4, D_5, C_5, B_4, A_4, G_5, D_5, C_5, B_4,
                    A_4, G_5, D_5, C_5, B_4, C_5, A_4, D_4, D_4, G_4, D_5, C_5,
                    B_4, A_4, G_5, D_5, C_5, B_4, A_4, G_5, D_5, C_5, B_4, C_5,
                    A_4, D_4, D_4, E_4, E_4, C_5, B_4, A_4, G_4, G_4, A_4, B_4,
                    A_4, E_4, Gb_4
                  };
// Times can be written in milliseconds
int TIMES_0[51] = { 100, 100, 100, 600, 600, 100, 100, 100, 600, 300, 100, 100,
                    100, 600, 300, 100, 100, 100, 600, 200, 100, 600, 600, 100,
                    100, 100, 600, 300, 100, 100, 100, 600, 300, 100, 100, 100,
                    600, 200, 100, 450, 150, 150, 150, 150, 150, 100, 100, 100,
                    200, 100, 300
                  };

bool sequence_looping_0 = false;

/* -------------------- Sequence 1 -------------------- */
// This sequence uses rests, where the frequency is set to zero, producing no sound
int NOTES_1[43] = { E_5, G_5, A_5, REST, G_5, REST, E_5, C_5, C_5, C_5, REST, B_4,
                    C_5, E_5, G_5, A_5, REST, G_5, REST, E_5, D_5, Db_5, C_5, REST,
                    Gb_5, REST, A_5, E_5, REST, A_5, REST, Gb_5, REST, A_5, REST, F_5,
                    E_5, REST, D_5, REST, Bb_4, Bb_4, Bb_4
                  };

int TIMES_1[43] = { 400, 200, 200, 200, 200, 200, 200, 200, 200, 200, 800, 200,
                    200, 200, 200, 200, 200, 200, 200, 200, 600, 200, 400, 400,
                    200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
                    200, 200, 200, 200, 200, 200, 200
                  };

bool sequence_looping_1 = false;

/* -------------------- Sequence 2 -------------------- 
 * EXAMPLE OF A LOOPING SEQUENCE */
// When looping is set to true you must set NOTES_X[0] = REST and TIMES_X[0] = 0 for the sequence to loop properly
int NOTES_2[28] = { REST, 
                    Bb_4, REST, Bb_4, Bb_4, Bb_4, Ab_4, Bb_4,
                    Bb_4, REST, Bb_4, Bb_4, Bb_4, Ab_4, Bb_4,
                    Bb_4, REST, Db_5, Bb_4, REST, Ab_4, 
                    Gb_4, REST, Eb_4, Eb_4, F_4, Gb_4, Eb_4
                  };

// Times can also be written using the define values for different notes
int TIMES_2[28] = { 0,
                     quarter_note, quarter_note, eighth_note, sixteenth_note, sixteenth_note, sixteenth_note, eighth_note + sixteenth_note,
                     quarter_note, quarter_note, eighth_note, sixteenth_note, sixteenth_note, sixteenth_note, eighth_note + sixteenth_note,
                     quarter_note, eighth_note, quarter_note, eighth_note, eighth_note, quarter_note,
                     eighth_note, eighth_note, eighth_note, eighth_note, eighth_note, eighth_note, eighth_note
                  };

bool sequence_looping_2 = true;

/* -------------------- Sequence 3 -------------------- */
// Add your own song here
int NOTES_3[0] = {
                  };

int TIMES_3[0] = { 
                  };

bool sequence_looping_3 = false;

// Initialize variables to track current sequence
long note_start_time;
int index = 0;
int current_length = 0;
int *current_notes;
int *current_times;
bool isLooping = false;

/** The setup function runs after the above values are defined and initialized
 *  and before the loop function.
 */
void setup() {
  Serial.begin(9600);

  startMozzi(CONTROL_RATE);
  internalSetup(); // Sets up the baseline values for ADSR and LFO modes

  pinMode(SEQUENCE_0_PIN, INPUT_PULLUP);
  pinMode(SEQUENCE_1_PIN, INPUT_PULLUP);
  pinMode(SEQUENCE_2_PIN, INPUT_PULLUP);
  pinMode(SEQUENCE_3_PIN, INPUT_PULLUP);
}

/** Updates parameters based on the current mode:
 *  waveform, frequency, cutoff frequency, LFO frequency, and resonance in LFO
 *  Mode, or attack, decay, sustain, and release in ADSR Mode
 */
void updateControl() {
  pot0=mozziAnalogRead(KNOB0);
  pot1=mozziAnalogRead(KNOB1);
  pot2=mozziAnalogRead(KNOB2);
  pot3=mozziAnalogRead(KNOB3);
  pot4=mozziAnalogRead(KNOB4);

  updateEnvironments(pot0, pot1, pot2, pot3, pot4);
}

/** The checkInputs function monitors the digital pins connected to each button
 *  and updates the states accordingly
 */
void checkInputs() {
  // Read ADSR Note Pin States
  pinState0 = digitalRead(SEQUENCE_0_PIN);
  pinState1 = digitalRead(SEQUENCE_1_PIN);
  pinState2 = digitalRead(SEQUENCE_2_PIN);
  pinState3 = digitalRead(SEQUENCE_3_PIN);
}

/** The updateEnvironment function updates the ADSR environment by setting
 *  frequency and turning the note on and off based on inputs
 */
void updateEnvironment() {
  // If a pin is pressed, reset counter values
  if (pinState0 == LOW) {
    current_notes = NOTES_0;
    current_times = TIMES_0;
    current_length = sizeof(NOTES_0) / 2; // Divided by 2 since each integer is 2 bytes of data
    setFrequency(NOTE_FREQ[*(current_notes)]);
    Serial.print("current_length is ");
    Serial.print(current_length);
    note_start_time = millis();
    isLooping = sequence_looping_0;
    index = 0;
  }
  else if (pinState1 == LOW) {
    current_notes = NOTES_1;
    current_times = TIMES_1;
    current_length = sizeof(NOTES_1) / 2;
    setFrequency(NOTE_FREQ[*(current_notes)]);
    note_start_time = millis();
    isLooping = sequence_looping_1;
    index = 0;
  }
  else if (pinState2 == LOW) {
    current_notes = NOTES_2;
    current_times = TIMES_2;
    current_length = sizeof(NOTES_2) / 2;
    setFrequency(NOTE_FREQ[*(current_notes)]);
    note_start_time = millis();
    isLooping = sequence_looping_2;
    index = 0;
  }
  else if (pinState3 == LOW) {
    current_notes = NOTES_3;
    current_times = TIMES_3;
    current_length = sizeof(NOTES_3) / 2;
    setFrequency(NOTE_FREQ[*(current_notes)]);
    note_start_time = millis();
    isLooping = sequence_looping_3;
    index = 0;
  }

  bool state = HIGH;
  if (index < current_length) {
    state = LOW; // Continue playing existing note
    long note_length = millis() - note_start_time - getReleaseTime();
    if (*(current_times + index) < note_length) {
      updateADSR(HIGH); // Turn off current note
      index++;
      setFrequency(NOTE_FREQ[*(current_notes + index)]);
      note_start_time = millis();
    }
  } else if (isLooping){
    index = 0;
  }
  else {
    index = 0;
    current_length = 0;
  }
  updateADSR(state);
}

/** The loop function is run repeatedly after the setup function is finished.
 */
void loop() {
  checkInputs();
  updateEnvironment();
  audioHook();
}