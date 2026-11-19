/**
   Notes Header File
   Ideas Clinic

      This header defines functions that are used to access and modify the scales
      played by the synthesizer in ADSR mode

   Last Updated: July 31, 2023
*/

#ifndef scale_h
#define scale_h
#include <Arduino.h>

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
                C_7, Db_7, D_7, Eb_7, E_7, F_7, Gb_7, G_7, Ab_7, A_7, Bb_7, B_7
                };

enum SCALE_NAME {major, minor, ocarina, major_7th, dominant_7th,
                  major_sharp4_1, major_sharp4_2, dominant_sharp4,
                  dominant_b2, minor_pent, min_major_7th, minor_6th,
                  minor_sharp4, half_dim, dim_7th_1, dim_7th_2, sus_b7,
                  sus_6th, blues, hirajoshi, ritsu, in_type, kon_go, custom
                };

/** Scale constructor that initializes an instance of the Scale class.
  * Defaults to major scale with middle C tonic if no parameters are given
 */
void scaleSetup(int scale_name = major, int tonic = C_4);

/** Public int function that returns the integer frequency of a note in the scale
  * when given the corresponding button number.
 */
int getNoteFreq(int requested_note);

/** Public void function that changes the advances the current scale to the next
  * scale. Loops back to major after custom.
 */
void nextScale();

/** Private void helper function that changes the button notes to a new scale based on
  * scale name and tonic.
  * Defaults to major scale with middle C tonic if no parameters are given
 */
void setNotes(int scale_name = major, int tonic = C_4);

#endif