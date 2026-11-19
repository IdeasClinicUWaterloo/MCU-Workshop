#include "internal.h"

Oscil <2048, AUDIO_RATE> aOscil(SIN2048_DATA); // ADSR table recast when button pressed
//Oscil <2048, AUDIO_RATE> aOscil(SAW2048_DATA);
//Oscil <2048, AUDIO_RATE> aOscil(TRIANGLE2048_DATA);
//Oscil <2048, AUDIO_RATE> aOscil(SQUARE_NO_ALIAS_2048_DATA);


// LFO environment 
ADSR <CONTROL_RATE, AUDIO_RATE> lfo_env;
LowPassFilter lpf;

// ADSR environment
ADSR <CONTROL_RATE, AUDIO_RATE> adsr_env;

int wave_form, frequency, cutoff, speed_lfo, gain_lfo, attack, releas, resonance, decay;

long adsrTonePinLastPushTime = 0;
long envelopeTime = 200;
long adsrTime;
long playTime;
long timeOff = 0;
long releaseTime = 50;

bool isPlayingADSRNote = false;
bool isPushed = false;

void internalSetup() {
  aOscil.setFreq(C_4_FREQ);
  adsr_env.setADLevels(ADSR_MODE_ATTACK_LEVEL,ADSR_MODE_DECAY_LEVEL);
  adsr_env.noteOff();
}

void updateEnvironments(int pot0, int pot1, int pot2, int pot3, int pot4) {
  unsigned int attack_ms = map(pot0, 0, 1023, 20, 300);
  unsigned int decay_ms = map(pot1, 0, 1023, 20, 500);
  unsigned int sustain_ms = map(pot2, 0, 1023, 20, 16000);
  unsigned int release_ms = map(pot3, 0, 1023, 20, 500);
  releaseTime = map(pot3, 0, 1023, 20, 2000);

  envelopeTime = attack_ms + decay_ms + sustain_ms;
  adsr_env.setTimes(attack_ms,decay_ms,sustain_ms,release_ms);
  adsr_env.update();
}

int updateAudio() {
  return MonoOutput::from8Bit(((int)adsr_env.next() * aOscil.next())>>8);
}

void updateADSR(bool state = HIGH) {
  if(state == LOW && (millis() - timeOff) > releaseTime) { // When the ADSR button is pressed
    if(isPlayingADSRNote == false && isPushed == false) { // If a note is not already playing
      Serial.println("Playing ADSR Note");
      isPlayingADSRNote = true;
      isPushed = true;
      adsr_env.noteOn();
      adsrTonePinLastPushTime = millis();
    }
    else if (isPlayingADSRNote == true) {
      adsrTime = millis();
      playTime = adsrTime - adsrTonePinLastPushTime;
      if(playTime >= envelopeTime) {
        Serial.print(envelopeTime);
        adsr_env.noteOff();
        isPlayingADSRNote = false;
      }
    }
  }
  else {
    isPushed = false;
    if(isPlayingADSRNote == true) {
      adsr_env.noteOff();
      isPlayingADSRNote = false;
      timeOff = millis();
    }

  }
}

void setFrequency(int freq) {
  aOscil.setFreq(freq);
  Serial.print("Set frequency to ");
  Serial.println(freq);
}

long getReleaseTime() {
  return releaseTime;
}