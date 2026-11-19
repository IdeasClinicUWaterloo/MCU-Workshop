#include "scale.h"

/*  The Note_FREQ array stores all note's associated frequency with their
  *   position in the array corresponding to the value of the note stored in
  *   the enumerated list.
**/
                    //NOTE   C     Db    D     Eb    E     F     Gb    G     Ab    A     Bb    B
const int NOTE_FREQ[84] = {  32,   35,   37,   39,   41,   44,   46,   49,   52,   55,   58,   62,  //OCTAVE 1
                              65,   69,   73,   78,   82,   87,   93,   98,   104,  110,  117,  123,   //OCTAVE 2
                              131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247,   //OCTAVE 3
                              262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,   //OCTAVE 4
                              523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988,   //OCTAVE 5
                              1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,  //OCTAVE 6
                              2093, 2217, 2349, 2490, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
                          }; //OCTAVE 7
int BUTTON_NOTE[6];
const int NUM_SCALES = 24;
int SCALE;

void setNotes(int scale_name = major, int tonic = C_4) {
 Serial.println("set_notes() has been entered:");
  // dummy check to ensure that the notes are all in range 
  // int tonic = C_4;

  SCALE = scale_name;

  if (tonic > A_6) {
    tonic -= 12;
   Serial.println("Selected tonic out of range, has been moved down an Octave");
    return;
  }
  
  // Maps the buttons to the appropriate scale.

  /***** Mapping Desired Notes to Buttons *****
* To create your own custom button mapping modify the last case statement in the function set_notes.
*
* To set the buttons to your custom mapping use 'custom' as the argument for set_notes(); insise of 
*   the setup function.
**/
  switch(scale_name) {
    case major:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 9];
     Serial.println("Scale: Maj.");
      break;
    case minor:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 8];
     Serial.println("Scale: minor");
      break;
    case ocarina:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 12];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 15];
     Serial.println("Scale: ocarina");
      break;
    case major_7th:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 11];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 12];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 16];
     Serial.println("Scale: Maj 7th");
      break;
    case dominant_7th:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 12];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 16];
     Serial.println("Scale: Dom 7th");
      break;
    case major_sharp4_1:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Maj #4 v1");
      break;
    case major_sharp4_2:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 11];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Maj #4 v2");
      break;
    case dominant_sharp4:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Dom #4");
      break;
    case dominant_b2:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 1];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Dom b2");
      break;
    case minor_pent:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: min pent");
      break;
    case min_major_7th:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 11];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: min Maj 7th");
      break;
    case minor_6th:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: minor 6th");
      break;
    case minor_sharp4:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: minor_sharp4");
      break;
    case half_dim:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 1];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: half_dim");
      break;
    case dim_7th_1:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 1];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: dim_7th_1");
      break;
    case dim_7th_2:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 8];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: dim_7th_2");
      break;
    case sus_b7:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: sus_b7");
      break;
    case sus_6th:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Sus_6th");
      break;
    case blues:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 6];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 10];
     Serial.println("Scale: Blues");
      break;
    case hirajoshi:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 8];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Kirajoshi");
      break;
    case ritsu:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 9];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Ritsu");
      break;
    case in_type:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 1];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 8];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: In-Type");
      break;
    case kon_go:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 1];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 5];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 7];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 10];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 12];
     Serial.println("Scale: Kon-go");
    case custom:
      BUTTON_NOTE[0] = NOTE_FREQ[tonic];
      BUTTON_NOTE[1] = NOTE_FREQ[tonic + 1];
      BUTTON_NOTE[2] = NOTE_FREQ[tonic + 2];
      BUTTON_NOTE[3] = NOTE_FREQ[tonic + 3];
      BUTTON_NOTE[4] = NOTE_FREQ[tonic + 4];
      BUTTON_NOTE[5] = NOTE_FREQ[tonic + 5];
     Serial.println("Scale: Custom");
      break;
  }
  return;
}

void nextScale() {
  if (SCALE == custom) {
    setNotes(major, C_4);\
    return;
  }
  setNotes(SCALE + 1, C_4);
  return;
}

int getNoteFreq(int requested_note) {
  return BUTTON_NOTE[requested_note];
}