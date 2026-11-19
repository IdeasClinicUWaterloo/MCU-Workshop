#include "internal.h"

Oscil<2048, AUDIO_RATE>aSin(SIN2048_DATA);
Oscil<2048, AUDIO_RATE>aSaw(SAW2048_DATA);
Oscil<512, AUDIO_RATE>aTri(TRIANGLE_ANALOGUE512_DATA);
Oscil<512, AUDIO_RATE>aSqu(SQUARE_ANALOGUE512_DATA);

Oscil<2048, AUDIO_RATE>LFO_aSin(SIN2048_DATA);
Oscil<2048, AUDIO_RATE>LFO_aSaw(SAW2048_DATA);
Oscil<512, AUDIO_RATE>LFO_aTri(TRIANGLE_ANALOGUE512_DATA);
Oscil<512, AUDIO_RATE>LFO_aSqu(SQUARE_ANALOGUE512_DATA);

Oscil <2048, AUDIO_RATE> aOscil(SIN2048_DATA); // ADSR table recast when button pressed

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

bool isLFOMode = false; // Starts in ADSR mode
bool isPlayingADSRNote = false;
bool isPushed = false;

void internalSetup() {
  aOscil.setFreq(C_4_FREQ);
  adsr_env.setADLevels(ADSR_MODE_ATTACK_LEVEL,ADSR_MODE_DECAY_LEVEL);
  adsr_env.noteOff();

  lfo_env.setADLevels(LFO_MODE_ATTACK_LEVEL,LFO_MODE_DECAY_LEVEL);
  lfo_env.setDecayTime(LFO_MODE_DECAY_TIME);
  lfo_env.setSustainTime(LFO_MODE_SUSTAIN_TIME);
  lfo_env.noteOff();
}

void updateEnvironments(int pot0, int pot1, int pot2, int pot3, int pot4) {
  if (isLFOMode) {
    frequency = 50 + pot1;

    aSin.setFreq(frequency);
    aSaw.setFreq(frequency);
    aTri.setFreq(frequency);
    aSqu.setFreq(frequency);

    if (pot0 <= 256){
      wave_form = sine;
    } else if (pot0 <= 512 && pot0 > 256) {
      wave_form = saw;
    } else if (pot0 <= 768 && pot0 > 512) {
      wave_form = tri;
    } else if (pot0 > 768) {
      wave_form = sqr;
    }

    cutoff=map(pot2,0,1024,20,255);
    speed_lfo = map(pot3,0,1024,30,2000);

    LFO_aSin.setFreq(speed_lfo);
    LFO_aSaw.setFreq(speed_lfo);
    LFO_aTri.setFreq(speed_lfo);
    LFO_aSqu.setFreq(speed_lfo);

    gain_lfo = 128 + LFO_aSin.next();

    //If LFO potentiometer is null don't send any modulation
    if (pot3 < 5) {
      lpf.setCutoffFreq(cutoff);
    } else {
      lpf.setCutoffFreq((cutoff*gain_lfo)>>8);
    }

    if (wave_form==2) resonance=map(pot4,0,1024,0,120);
      else resonance=map(pot4,0,1024,0,170);

  } else {
    unsigned int attack_ms = map(pot0, 0, 1023, 20, 300);
    unsigned int decay_ms = map(pot1, 0, 1023, 20, 500);
    unsigned int sustain_ms = map(pot2, 0, 1023, 20, 16000);
    unsigned int release_ms = map(pot3, 0, 1023, 20, 2000);

    envelopeTime = attack_ms + decay_ms + sustain_ms;
    adsr_env.setTimes(attack_ms,decay_ms,sustain_ms,release_ms);
    adsr_env.update();
  }
}

void switchMode() {
  if(!isLFOMode){
    Serial.println("Switching to LFO environment");
    adsr_env.noteOff();
    lfo_env.noteOn();
  } else {
    Serial.println("Switching to ADSR environment");
    lfo_env.noteOff();
  }
  isLFOMode = !isLFOMode;
}

int updateAudio() {
  if (isLFOMode){
    switch (wave_form){
    case 1:
      return MonoOutput::from8Bit(((int)lfo_env.next() * (lpf.next(aSin.next())))>>8);
      break;
    case 2:
      return MonoOutput::from8Bit(((int)lfo_env.next() * (lpf.next(aSaw.next())))>>8);
      break;
    case 4:
      return MonoOutput::from8Bit(((int)lfo_env.next() * (lpf.next(aTri.next())))>>8);
      break;
    case 3:
      return MonoOutput::from8Bit(((int)lfo_env.next() * (lpf.next(aSqu.next())))>>8);
      break;
    }
  } else {
    return MonoOutput::from8Bit(((int)adsr_env.next() * aOscil.next())>>8);
  }
}

void updateADSR(bool State_0 = HIGH, bool State_1 = HIGH, bool State_2 = HIGH, bool State_3 = HIGH, bool State_4 = HIGH, bool State_5 = HIGH) {
  if(!isLFOMode){
    if(State_0 == LOW || State_1 == LOW || State_2 == LOW || State_3 == LOW || State_4 == LOW || State_5 == LOW){ // When the ADSR button is pressed
      if(isPlayingADSRNote == false && isPushed == false){ // If a note is not already playing
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
    else{
      isPushed = false;
      if(isPlayingADSRNote == true){
        adsr_env.noteOff();
        isPlayingADSRNote = false;
      }
    }
  }

  // Change ADSR frequency to corresponding note
  if(State_0 == LOW)
    aOscil.setFreq(getNoteFreq(0));
  else if(State_1 == LOW)
    aOscil.setFreq(getNoteFreq(1));
  else if(State_2 == LOW)
    aOscil.setFreq(getNoteFreq(2));
  else if(State_3 == LOW)
    aOscil.setFreq(getNoteFreq(3));
  else if(State_4 == LOW)
    aOscil.setFreq(getNoteFreq(4));
  else if(State_5 == LOW)
    aOscil.setFreq(getNoteFreq(5));
}

void soundOff() {
  adsr_env.noteOff();
  lfo_env.noteOff();
}