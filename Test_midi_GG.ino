#include "FastLED.h"
#include <MIDI.h>
#include <HardwareSerial.h>
HardwareSerial MySerial(1);

struct Serial2MIDISettings : public midi::DefaultSettings
{
  static const long BaudRate = 31250;
  static const int8_t RxPin  = 16;
  static const int8_t TxPin  = 17;
};
static const int8_t Channel = 16;

#define NUM_LEDS_PER_STRIP 60
#define NUM_LEDS_PER_STRIP_B 60
#define NUM_LEDS_PER_STRIP_C 60
#define NUM_LEDS_PER_STRIP_D 60
#define NUM_LEDS_PER_STRIP_E 60
#define NUM_LEDS_PER_STRIP_F 60
#define NUM_LEDS_PER_STRIP_G 60
#define NUM_LEDS_PER_STRIP_H 60

#define NUM_STRIPS 3

//const uint8_t pinStrip1 = 15;
//const uint8_t pinStrip2 = 22;
//const uint8_t pinStrip3 = 23;

CRGB LedsA[NUM_LEDS_PER_STRIP];
CRGB LedsB[NUM_LEDS_PER_STRIP_B];
CRGB LedsC[NUM_LEDS_PER_STRIP_C];
CRGB LedsD[NUM_LEDS_PER_STRIP_D];
CRGB LedsE[NUM_LEDS_PER_STRIP_E];
CRGB LedsF[NUM_LEDS_PER_STRIP_F];
CRGB LedsG[NUM_LEDS_PER_STRIP_G];
CRGB LedsH[NUM_LEDS_PER_STRIP_H];


CLEDController *stripControl[NUM_STRIPS];

#define numA 15    //pixels 0-4
#define numB 15    //pixels 5-7
#define numC 15   //pixels 8-23
#define numD 15    //pixels 24-31
#define numAA 20

int colorValue = 0;
int valueColor = 0;

int colorWork = 0;
bool rgbColor = false;
bool hueColor = true;

int pressValue = 0;
int velocityColor = 0;

int brightController = 0;
int valueBright = 0;

int timeController = 0;
int delayTimer = 0;

int lenValue = 0;
int stripLen = 0;

int note[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
              21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
             };

struct MidiSettings : public midi::DefaultSettings // The sketch will probably work fine without these custom settings.
{
  static const bool UseRunningStatus = true;
  static const unsigned SysExMaxSize = 2;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial2, MIDI, Serial2MIDISettings);


// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks

void handleNoteOn(byte channel, byte note, byte velocity)
{

  if (note)
  {
    switch (note) {
      case 0: //------ Octave1 ------ Octave1 ------ Octave1
        if (velocity > 120) {
          wipeForwardA();
        }
        if (velocity < 40 ) {
          wipeForwardTwoA();
        }
        if (velocity >= 40 && velocity < 80) {
          wipeForwardTrippleA();
        }
        if (velocity >= 80 && velocity <= 120 ) {
          wipeForwardFourA();
        }
        break;
      case 1:
        if (velocity > 120) {
          wipeBackwardA();
          return;
        }
        if (velocity < 40 ) {
          wipeBackwardTwoA();
        }
        if (velocity >= 40 && velocity < 80) {
          wipeBackwardTrippleA();
        }
        if (velocity >= 80 && velocity <= 120 ) {
          wipeBackwardFourA();
        }
        break;
      case 2:
        if (velocity < 60 ) {
          dualWipeCenterToOutA();
        }
        if (velocity >= 60) {
          dualWipeEndToCenterA();
        }
        break;
      case 3:
        if (velocity < 40 ) {
          onePXupA();
        }
        if (velocity >= 40 && velocity < 80) {
          onePXdwnA();
        }
        if (velocity >= 80 && velocity <= 120) {
          onePXCenterToEndA();
        }
        if (velocity > 120) {
          onePXEndToCenterA();
        }
        break;
      case 4:
        //if (velocity < 5) {
        segementsToFullStripA();
        break;
      case 5:
        if (velocity < 50) {
          firstHalfA();
        }
        if (velocity >= 50 && velocity <= 100) {
          secondHalfA();
        }
        if (velocity > 100) {
          fillStripA();
        }
        break;
      case 6:
        if (velocity < 50) {
          oneThirdA();
        }
        if (velocity >= 50 && velocity <= 110) {
          secondThirdA();
        }
        if (velocity > 110) {
          thirdThirdA();
        }
        break;
      case 7:
        if (velocity < 40) {
          firstFourA();
        }
        if (velocity >= 40 && velocity < 80) {
          secondFourA();
        }
        if (velocity >= 80 && velocity <= 120) {
          thirdFourA();
        }
        if (velocity > 120) {
          fourthFourA();
        }
        break;
      case 8:
        if (velocity < 50) {
          TheaterChaseA();
        }
        if (velocity >= 50 && velocity <= 100) {
          TheaterChaseReverseA();
        }
        if (velocity > 100) {
          TheaterChaseDoubleA();
        }
        break;
      case 9:
        if (velocity < 50 ) {
          GlitterA();
        }
        if (velocity >= 50 && velocity <= 100) {
          StrobeSlowA(15);
        }
        if (velocity > 100) {
          StrobeFastA(25);
        }
        break;
      case 10:
        pulserA();
        break;
      case 11:
        breatheA();
      case 12: //------ Octave2 ------ Octave2 ------ Octave2
        if (velocity > 120) {
          wipeForwardB();
        }
        if (velocity < 40 ) {
          wipeForwardTwoB();
        }
        if (velocity >= 40 && velocity < 80) {
          wipeForwardTrippleB();
        }
        if (velocity >= 80 && velocity <= 120 ) {
          wipeForwardFourB();
        }
        break;
      case 13:
        if (velocity > 120) {
          wipeBackwardB();
          return;
        }
        if (velocity < 40 ) {
          wipeBackwardTwoB();
        }
        if (velocity >= 40 && velocity < 80) {
          wipeBackwardTrippleB();
        }
        if (velocity >= 80 && velocity <= 120 ) {
          wipeBackwardFourB();
        }
        break;
      case 14:
        if (velocity < 60 ) {
          dualWipeCenterToOutB();
        }
        if (velocity >= 60) {
          dualWipeEndToCenterB();
        }
        break;
      case 15:
        if (velocity < 40 ) {
          onePXupB();
        }
        if (velocity >= 40 && velocity < 80) {
          onePXdwnB();
        }
        if (velocity >= 80 && velocity <= 120) {
          onePXCenterToEndB();
        }
        if (velocity > 120) {
          onePXEndToCenterB();
        }
        break;
      case 16:
        //if (velocity < 5) {
        segementsToFullStripB();
        break;
      case 17:
        if (velocity < 50) {
          firstHalfB();
        }
        if (velocity >= 50 && velocity <= 100) {
          secondHalfB();
        }
        if (velocity > 100) {
          fillStripB();
        }
        break;
      case 18:
        if (velocity < 50) {
          oneThirdB();
        }
        if (velocity >= 50 && velocity <= 110) {
          secondThirdB();
        }
        if (velocity > 110) {
          thirdThirdB();
        }
        break;
      case 19:
        if (velocity < 40) {
          firstFourB();
        }
        if (velocity >= 40 && velocity < 80) {
          secondFourB();
        }
        if (velocity >= 80 && velocity <= 120) {
          thirdFourB();
        }
        if (velocity > 120) {
          fourthFourB();
        }
        break;
      case 20:
        if (velocity < 50) {
          TheaterChaseB();
        }
        if (velocity >= 50 && velocity <= 100) {
          TheaterChaseReverseB();
        }
        if (velocity > 100) {
          TheaterChaseDoubleB();
        }
        break;
      case 21:
        if (velocity < 50 ) {
          GlitterB();
        }
        if (velocity >= 50 && velocity <= 100) {
          StrobeSlowB(15);
        }
        if (velocity > 100) {
          StrobeFastB(25);
        }
        break;
      case 22:
        pulserB();
        break;
      case 23:
        breatheB();
      case 24: //------ Octave3 ------ Octave3 ------ Octave3
        if (velocity > 120) {
          wipeForwardC();
        }
        if (velocity < 40 ) {
          wipeForwardTwoC();
        }
        if (velocity >= 40 && velocity < 80) {
          wipeForwardTrippleC();
        }
        if (velocity >= 80 && velocity <= 120 ) {
          wipeForwardFourC();
        }
        break;
      case 25:
        if (velocity > 120) {
          wipeBackwardC();
          return;
        }
        if (velocity < 40 ) {
          wipeBackwardTwoC();
        }
        if (velocity >= 40 && velocity < 80) {
          wipeBackwardTrippleC();
        }
        if (velocity >= 80 && velocity <= 120 ) {
          wipeBackwardFourC();
        }
        break;
      case 26:
        if (velocity < 60 ) {
          dualWipeCenterToOutC();
        }
        if (velocity >= 60) {
          dualWipeEndToCenterC();
        }
        break;
      case 27:
        if (velocity < 40 ) {
          onePXupC();
        }
        if (velocity >= 40 && velocity < 80) {
          onePXdwnC();
        }
        if (velocity >= 80 && velocity <= 120) {
          onePXCenterToEndC();
        }
        if (velocity > 120) {
          onePXEndToCenterC();
        }
        break;
      case 28:
        //if (velocity < 5) {
        segementsToFullStripC();
        break;
      case 29:
        if (velocity < 50) {
          firstHalfC();
        }
        if (velocity >= 50 && velocity <= 100) {
          secondHalfC();
        }
        if (velocity > 100) {
          fillStripC();
        }
        break;
      case 30:
        if (velocity < 50) {
          oneThirdC();
        }
        if (velocity >= 50 && velocity <= 110) {
          secondThirdC();
        }
        if (velocity > 110) {
          thirdThirdC();
        }
        break;
      case 31:
        if (velocity < 40) {
          firstFourC();
        }
        if (velocity >= 40 && velocity < 80) {
          secondFourC();
        }
        if (velocity >= 80 && velocity <= 120) {
          thirdFourC();
        }
        if (velocity > 120) {
          fourthFourC();
        }
        break;
      case 32:
        if (velocity < 50) {
          TheaterChaseC();
        }
        if (velocity >= 50 && velocity <= 100) {
          TheaterChaseReverseC();
        }
        if (velocity > 100) {
          TheaterChaseDoubleC();
        }
        break;
      case 33:
        if (velocity < 50 ) {
          GlitterC();
        }
        if (velocity >= 50 && velocity <= 100) {
          StrobeSlowC(15);
        }
        if (velocity > 100) {
          StrobeFastC(25);
        }
        break;
      case 34:
        pulserC();
        break;
      case 35:
        breatheC();
    }
  }
}
void handleNoteOff(byte channel, byte note, byte velocity)
{
  if (note == 0 || note == 1 || note == 2 || note == 3 || note == 4 || note == 5 ||
      note == 6 || note == 7 || note == 8 || note == 9 || note == 10 || note == 11) {
    velocity = 0;
    fill_solid(LedsA, NUM_LEDS_PER_STRIP, CRGB::Black);
    stripControl[0]->showLeds();
  }
  if (note == 12 || note == 13 || note == 14 || note == 15 || note == 16 || note == 17 ||
      note == 18 || note == 19 || note == 20 || note == 21 || note == 22 || note == 23) {
    velocity = 0;
    fill_solid(LedsA, NUM_LEDS_PER_STRIP, CRGB::Black);
    stripControl[1]->showLeds();
  }
  if (note == 24 || note == 25 || note == 26 || note == 27 || note == 28 || note == 29 ||
      note == 30 || note == 31 || note == 32 || note == 33 || note == 34 || note == 35) {
    velocity = 0;
    fill_solid(LedsC, NUM_LEDS_PER_STRIP, CRGB::Black);
    stripControl[2]->showLeds();
  }

  //blackout();
  // Do something when the note is released.
  // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}
void handleControlChange(byte channel, byte number, byte value)
{

}
// ============)  Fade PART (============ //
void fadeallA() {
  fadeToBlackBy( LedsA, NUM_LEDS_PER_STRIP, 20);
  stripControl[0]->showLeds();
}
void fadeallB() {
  fadeToBlackBy( LedsB, NUM_LEDS_PER_STRIP_B, 20);
  stripControl[1]->showLeds();
}
void fadeallC() {
  fadeToBlackBy( LedsC, NUM_LEDS_PER_STRIP_B, 20);
  stripControl[2]->showLeds();
}
// ============)  Whipe Forward  (============ // -- OCTAVE1
void wipeForwardA() {
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {

    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
    }
    if (rgbColor == true) {
      LedsA[i] = CRGB(255, 255, 255);
    }
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
  }
}
void wipeForwardTwoA() {
  for (int i = 0; i < (numA + numB); i++) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    LedsA[(numA * 2) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer * 2);
  }
}
void wipeForwardTrippleA() {
  for (int i = 0; i < (numAA); i++) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    LedsA[numAA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsA[(numAA * 2) + i] = CHSV(valueColor, 255, valueBright);
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer * 3);
  }
}
void wipeForwardFourA() {
  for (int i = 0; i < (numA); i++) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    LedsA[numA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsA[(numA * 2) + i] = CHSV(valueColor, 255, valueBright);
    LedsA[(numA * 3) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer * 4);
  }
}
// ============)  Backward  (============ // -- OCTAVE1
void wipeBackwardA() {
  for (int i = (NUM_LEDS_PER_STRIP) - 1; i >= 0; i--) {
    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[i] = CRGB(255, 255, 255);
    }
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
  }
}
void wipeBackwardTwoA() {
  for (int i = (numA + numB) - 1; i >= 0; i--) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    LedsA[(numC * 2) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer * 2);
  }
}
void wipeBackwardTrippleA() {
  for (int i = (numAA) - 1; i >= 0; i--) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    LedsA[numAA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsA[(numAA * 2) + i] = CHSV(valueColor, 255, valueBright);
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer * 3);
  }
}
void wipeBackwardFourA() {
  for (int i = (numA) - 1; i >= 0; i--) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    LedsA[numA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsA[(numA * 2) + i] = CHSV(valueColor, 255, valueBright);
    LedsA[(numA * 3) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer * 4);
  }
}
// ============)  Dual Whipe  (=============== // -- OCTAVE1
void dualWipeCenterToOutA() {
  uint16_t j = 1;
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP / 2) - 1;
  for (uint16_t i = HALFWAY; i < NUM_LEDS_PER_STRIP  ; i++)
  {
    if (hueColor == true) {
      LedsA[HALFWAY - j] = CHSV(valueColor, 255, valueBright);
      LedsA[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[HALFWAY - j] = CRGB(255, 255, 255);
      LedsA[i] = CRGB(255, 255, 255);
    }
    j++;
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
    if (j == 30) {
      j = 1;
    }
  }
}
void dualWipeEndToCenterA() {
  uint16_t j = 0;
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP / 2) - 1;
  for (int i = NUM_LEDS_PER_STRIP  ; i >= 30; i--)
  {
    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
      LedsA[j] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[i] = CRGB(255, 255, 255);
      LedsA[j] = CRGB(255, 255, 255);
    }
    j++;
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
    if (j == 30) {
      j = 0;
    }
  }
}
// ============)  OnePixel  (====================== // -- OCTAVE1
void onePXupA() {
  for (int i = 0; i < NUM_LEDS_PER_STRIP;  i++) {
    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[i] = CRGB(255, 255, 255);
    }
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = 0; i < NUM_LEDS_PER_STRIP;  i++) {
      LedsA[i] = CHSV(0, 0, 0);
    }
  }
}
void onePXdwnA() {
  for (int i = (NUM_LEDS_PER_STRIP) - 1; i >= 0; i--) {
    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[i] = CRGB(255, 255, 255);
    }
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = (NUM_LEDS_PER_STRIP) - 1; i >= 0; i--) {
      LedsA[i] = CHSV(0, 0, 0);
    }
  }
}

void onePXCenterToEndA() {
  int k = 30;
  for (int i = 30; i < NUM_LEDS_PER_STRIP;  i++) {
    k--;
    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
      LedsA[k] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[i] = CRGB(255, 255, 255);
      LedsA[k] = CRGB(255, 255, 255);
    }
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = 30; i < NUM_LEDS_PER_STRIP;  i++) {
      LedsA[i] = CHSV(0, 0, 0);
      LedsA[k] = CHSV(0, 0, 0);
    }
  }
}

void onePXEndToCenterA() {
  int k = 0;
  for (int i = (NUM_LEDS_PER_STRIP) - 1; i >= 30; i--) {
    k++;
    if (hueColor == true) {
      LedsA[i] = CHSV(valueColor, 255, valueBright);
      LedsA[k] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsA[i] = CRGB(255, 255, 255);
      LedsA[k] = CRGB(255, 255, 255);
    }
    stripControl[0]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = (NUM_LEDS_PER_STRIP) - 1; i >= 30; i--) {
      LedsA[i] = CHSV(0, 0, 0);
      LedsA[k] = CHSV(0, 0, 0);
    }
  }
}
// ============)  Segements to FullStrip  (======= // -- OCTAVE1
void segementsToFullStripA() {
  for (int i = 0; i < stripLen; i++) {
    LedsA[i] = CHSV(valueColor, 255, valueBright);
    vTaskDelay(delayTimer);
  }
  stripControl[0]->showLeds();
}
// ============)  HalfStrip PART (================ // -- OCTAVE1
void firstHalfA() {
  for (int m = 0; m < 30; m++) {
    LedsA[m]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
void secondHalfA() {
  for (int n = 30; n < 59; n++) {
    LedsA[n]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
// ============)  FillStrip PART (=============== // -- OCTAVE1
void fillStripA() {
  fill_solid(LedsA, NUM_LEDS_PER_STRIP, CHSV( valueColor, 255, valueBright));
  stripControl[0]->showLeds();
}
// ============)  TrippleStrip PART (=========== // -- OCTAVE1
void oneThirdA() {
  for (int o = 1; o < 20; o++) {
    LedsA[o]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
void secondThirdA() {
  for (int p = 20; p < 40; p++) {
    LedsA[p]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
void thirdThirdA() {
  for (int q = 40; q < 60; q++) {
    LedsA[q]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
// ============)  QuaterStrip PART (=========== //  -- OCTAVE1
void firstFourA() {
  for (int r = 1; r < 15; r++) {
    LedsA[r]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
void secondFourA() {
  for (int s = 15; s < 30; s++) {
    LedsA[s]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
void thirdFourA() {
  for (int t = 30; t < 45; t++) {
    LedsA[t]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
void fourthFourA() {
  for (int u = 45; u < 60; u++) {
    LedsA[u]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[0]->showLeds();
}
// ============)  Theater Chase PART (========= // -- OCTAVE1
void TheaterChaseA() {
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i = i + 3) {
        LedsA[i + q] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[0]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i = i + 3) {
        LedsA[i + q] = CHSV(0, 0, 0);
      }
    }
  }
}
void TheaterChaseReverseA() {
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 3; q > 0; q--) {
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i = i + 3) {
        LedsA[i + q] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[0]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < NUM_LEDS_PER_STRIP; i = i + 3) {
        LedsA[i + q] = CHSV(0, 0, 0);
      }
    }
  }
}
void TheaterChaseDoubleA() {
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP / 2) - 1;
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 3; q > 0; q--) {
      int x = q;
      x--;
      for (int i = 0; i < HALFWAY; i = i + 3) {
        LedsA[(i + q) - 1] = CHSV(valueColor, 255, valueBright);
        LedsA[(HALFWAY + 3) + (i - x)] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[0]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < HALFWAY; i = i + 3) {
        LedsA[(i + q) - 1] = CHSV(0, 0, 0);
        LedsA[(HALFWAY + 3) + (i - x)] = CHSV(0, 0, 0);
      }
    }
  }
}
// ============)  Glitter PART (=========== // -- OCTAVE1
void GlitterA() {
  for (int i = (NUM_LEDS_PER_STRIP) - 1; i >= 0; i--) {
    LedsA[i] = CHSV(0, 0, 0);
    addGlitterA(80);
    stripControl[0]->showLeds();
    fadeallA();
    vTaskDelay(30);
  }
}
void addGlitterA( fract8 chanceOfGlitter) {//glitter effect
  if ( random8() < chanceOfGlitter) {
    if (hueColor == true) {
      LedsA[ random16(NUM_LEDS_PER_STRIP) ] += CHSV( valueColor, 255, valueBright);
    }
    else {
      LedsA[ random16(NUM_LEDS_PER_STRIP) ] +=  CRGB(255, 255, 255);
    }
  }
}
// ============)  Strobe PART (=========== // -- OCTAVE1

void StrobeSlowA(int StrobeCount) {
  for (int j = 0; j < StrobeCount; j++) {
    if (hueColor == true) {
      fill_solid(LedsA, NUM_LEDS_PER_STRIP, CHSV( valueColor, 255, valueBright));
    }
    else {
      fill_solid(LedsA, NUM_LEDS_PER_STRIP, CRGB(255, 255, 255));
    }
    stripControl[0]->showLeds();
    vTaskDelay(25);
    fill_solid(LedsA, NUM_LEDS_PER_STRIP, CRGB::Black);
    stripControl[0]->showLeds();
    vTaskDelay(35);
  }
}
void StrobeFastA(int StrobeCount) {
  for (int j = 0; j < StrobeCount; j++) {
    if (hueColor == true) {
      fill_solid(LedsA, NUM_LEDS_PER_STRIP, CHSV( valueColor, 255, valueBright));
    }
    else {
      fill_solid(LedsA, NUM_LEDS_PER_STRIP, CRGB(255, 255, 255));
    }
    stripControl[0]->showLeds();
    vTaskDelay(5);
    fill_solid(LedsA, NUM_LEDS_PER_STRIP, CRGB::Black);
    stripControl[0]->showLeds();
    vTaskDelay(15);
  }
}
// ============)  Pulser PART (=========== // -- OCTAVE1
void pulserA() {
  int count = 2;
  for (int x = 0; x < count; x++) {
    int msec = millis() % 1000;
    double msecPos = msec / 1000.0 * NUM_LEDS_PER_STRIP;
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      double a = -0.2 * (i - msecPos) * (i - msecPos); // adjust the number 0.5 to change the width - smaller number = wider pulse
      double y = 255 * pow(2, a);

      if (hueColor == true) {
        LedsA[i] = CHSV(valueColor, 255, (int)y);
      }
      else {
        LedsA[i] = CRGB(y, y, y);
      }
      count++;
      stripControl[0]->showLeds();
    }
    if (count = 30) {
      count == 0;
    }
  }
}
// ============)  Breathe PART (========= // -- OCTAVE1
void breatheA() {
  const int duration = delayTimer * 60;
  for (unsigned long loopcounter = 0; loopcounter < duration; loopcounter++) {
    //beatsin16 is a function on the FastLED library generating sinwave, (5) is bpm, (0,255) is value range.
    //value range will create the breathing effect
    uint8_t gHue = valueColor;
    int pos = beatsin16(100, 10, 128); // generating the sinwave
    fill_solid(LedsA, NUM_LEDS_PER_STRIP, CHSV( gHue, 255, pos)); // CHSV (hue, saturation, value);
    stripControl[0]->showLeds();
    EVERY_N_MILLISECONDS(100) {
      gHue++;
    }
    // shifting the HUE value by incrementing every millisecond this creates the spectrum wave
  }
}
// OCTAVE2 -- ============)  Whipe Forward  (============ // -- OCTAVE2
void wipeForwardB() {
  for (int i = 0; i < NUM_LEDS_PER_STRIP_B; i++) {

    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
    }
    if (rgbColor == true) {
      LedsB[i] = CRGB(255, 255, 255);
    }
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    //FastLED.delay(delayTimer);
  }
}
void wipeForwardTwoB() {
  for (int i = 0; i < (numA + numB); i++) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    LedsB[(numA * 2) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer * 2);
  }
}
void wipeForwardTrippleB() {
  for (int i = 0; i < (numAA); i++) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    LedsB[numAA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsB[(numAA * 2) + i] = CHSV(valueColor, 255, valueBright);
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer * 3);
  }
}
void wipeForwardFourB() {
  for (int i = 0; i < (numA); i++) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    LedsB[numA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsB[(numA * 2) + i] = CHSV(valueColor, 255, valueBright);
    LedsB[(numA * 3) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer * 4);
  }
}
// OCTAVE2 -- ============)  Backward  (============ // -- OCTAVE2
void wipeBackwardB() {
  for (int i = (NUM_LEDS_PER_STRIP_B) - 1; i >= 0; i--) {
    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[i] = CRGB(255, 255, 255);
    }
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
  }
}
void wipeBackwardTwoB() {
  for (int i = (numA + numB) - 1; i >= 0; i--) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    LedsB[(numC * 2) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer * 2);
  }
}
void wipeBackwardTrippleB() {
  for (int i = (numAA) - 1; i >= 0; i--) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    LedsB[numAA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsB[(numAA * 2) + i] = CHSV(valueColor, 255, valueBright);
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer * 3);
  }
}
void wipeBackwardFourB() {
  for (int i = (numA) - 1; i >= 0; i--) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    LedsB[numA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsB[(numA * 2) + i] = CHSV(valueColor, 255, valueBright);
    LedsB[(numA * 3) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer * 4);
  }
}
// OCTAVE2 -- ============)  Dual Whipe  (=============== // -- OCTAVE2
void dualWipeCenterToOutB() {
  uint16_t j = 1;
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP_B / 2) - 1;
  for (uint16_t i = HALFWAY; i < NUM_LEDS_PER_STRIP_B  ; i++)
  {
    if (hueColor == true) {
      LedsB[HALFWAY - j] = CHSV(valueColor, 255, valueBright);
      LedsB[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[HALFWAY - j] = CRGB(255, 255, 255);
      LedsB[i] = CRGB(255, 255, 255);
    }
    j++;
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    if (j == 30) {
      j = 1;
    }
  }
}
void dualWipeEndToCenterB() {
  uint16_t j = 0;
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP_B / 2) - 1;
  for (int i = NUM_LEDS_PER_STRIP_B  ; i >= 30; i--)
  {
    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
      LedsB[j] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[i] = CRGB(255, 255, 255);
      LedsB[j] = CRGB(255, 255, 255);
    }
    j++;
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    if (j == 30) {
      j = 0;
    }
  }
}
// OCTAVE2 -- ============)  OnePixel  (====================== // -- OCTAVE2
void onePXupB() {
  for (int i = 0; i < NUM_LEDS_PER_STRIP_B;  i++) {
    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[i] = CRGB(255, 255, 255);
    }
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = 0; i < NUM_LEDS_PER_STRIP_B;  i++) {
      LedsB[i] = CHSV(0, 0, 0);
    }
  }
}
void onePXdwnB() {
  for (int i = (NUM_LEDS_PER_STRIP_B) - 1; i >= 0; i--) {
    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[i] = CRGB(255, 255, 255);
    }
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = (NUM_LEDS_PER_STRIP_B) - 1; i >= 0; i--) {
      LedsB[i] = CHSV(0, 0, 0);
    }
  }
}

void onePXCenterToEndB() {
  int k = 30;
  for (int i = 30; i < NUM_LEDS_PER_STRIP_B;  i++) {
    k--;
    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
      LedsB[k] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[i] = CRGB(255, 255, 255);
      LedsB[k] = CRGB(255, 255, 255);
    }
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = 30; i < NUM_LEDS_PER_STRIP_B;  i++) {
      LedsB[i] = CHSV(0, 0, 0);
      LedsB[k] = CHSV(0, 0, 0);
    }
  }
}

void onePXEndToCenterB() {
  int k = 0;
  for (int i = (NUM_LEDS_PER_STRIP_B) - 1; i >= 30; i--) {
    k++;
    if (hueColor == true) {
      LedsB[i] = CHSV(valueColor, 255, valueBright);
      LedsB[k] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsB[i] = CRGB(255, 255, 255);
      LedsB[k] = CRGB(255, 255, 255);
    }
    stripControl[1]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = (NUM_LEDS_PER_STRIP_B) - 1; i >= 30; i--) {
      LedsB[i] = CHSV(0, 0, 0);
      LedsB[k] = CHSV(0, 0, 0);
    }
  }
}
// OCTAVE2 -- ============)  Segements to FullStrip  (======= // -- OCTAVE2
void segementsToFullStripB() {
  for (int i = 0; i < stripLen; i++) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    vTaskDelay(delayTimer);
  }
  stripControl[1]->showLeds();
}
// OCTAVE2 -- ============)  HalfStrip PART (================ // -- OCTAVE2
void firstHalfB() {
  for (int m = 0; m < 30; m++) {
    LedsB[m]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
void secondHalfB() {
  for (int n = 30; n < 59; n++) {
    LedsB[n]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
// OCTAVE2 -- ============)  FillStrip PART (=============== // -- OCTAVE2
void fillStripB() {
  fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CHSV( valueColor, 255, valueBright));
  stripControl[1]->showLeds();
}
// OCTAVE2 -- ============)  TrippleStrip PART (=========== // -- OCTAVE2
void oneThirdB() {
  for (int o = 1; o < 20; o++) {
    LedsB[o]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
void secondThirdB() {
  for (int p = 20; p < 40; p++) {
    LedsB[p]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
void thirdThirdB() {
  for (int q = 40; q < 60; q++) {
    LedsB[q]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
// OCTAVE2 -- ============)  QuaterStrip PART (=========== //  -- OCTAVE2
void firstFourB() {
  for (int r = 1; r < 15; r++) {
    LedsB[r]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
void secondFourB() {
  for (int s = 15; s < 30; s++) {
    LedsB[s]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
void thirdFourB() {
  for (int t = 30; t < 45; t++) {
    LedsB[t]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
void fourthFourB() {
  for (int u = 45; u < 60; u++) {
    LedsB[u]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[1]->showLeds();
}
// OCTAVE2 -- ============)  Theater Chase PART (========= // -- OCTAVE2
void TheaterChaseB() {
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS_PER_STRIP_B; i = i + 3) {
        LedsB[i + q] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[1]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < NUM_LEDS_PER_STRIP_B; i = i + 3) {
        LedsB[i + q] = CHSV(0, 0, 0);
      }
    }
  }
}
void TheaterChaseReverseB() {
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 3; q > 0; q--) {
      for (int i = 0; i < NUM_LEDS_PER_STRIP_B; i = i + 3) {
        LedsB[i + q] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[1]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < NUM_LEDS_PER_STRIP_B; i = i + 3) {
        LedsB[i + q] = CHSV(0, 0, 0);
      }
    }
  }
}
void TheaterChaseDoubleB() {
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP_B / 2) - 1;
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 3; q > 0; q--) {
      int x = q;
      x--;
      for (int i = 0; i < HALFWAY; i = i + 3) {
        LedsB[(i + q) - 1] = CHSV(valueColor, 255, valueBright);
        LedsB[(HALFWAY + 3) + (i - x)] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[1]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < HALFWAY; i = i + 3) {
        LedsB[(i + q) - 1] = CHSV(0, 0, 0);
        LedsB[(HALFWAY + 3) + (i - x)] = CHSV(0, 0, 0);
      }
    }
  }
}
// OCTAVE2 -- ============)  Glitter PART (=========== // -- OCTAVE2
void GlitterB() {
  for (int i = (NUM_LEDS_PER_STRIP_B) - 1; i >= 0; i--) {
    LedsA[i] = CHSV(0, 0, 0);
    addGlitterB(80);
    stripControl[1]->showLeds();
    fadeallB();
    vTaskDelay(30);
  }
}
void addGlitterB( fract8 chanceOfGlitter) {//glitter effect
  if ( random8() < chanceOfGlitter) {
    if (hueColor == true) {
      LedsB[ random16(NUM_LEDS_PER_STRIP_B) ] += CHSV( valueColor, 255, valueBright);
    }
    else {
      LedsB[ random16(NUM_LEDS_PER_STRIP_B) ] +=  CRGB(255, 255, 255);
    }
  }
}
// OCTAVE2 -- ============)  Strobe PART (=========== // -- OCTAVE2

void StrobeSlowB(int StrobeCount) {
  for (int j = 0; j < StrobeCount; j++) {
    if (hueColor == true) {
      fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CHSV( valueColor, 255, valueBright));
    }
    else {
      fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CRGB(255, 255, 255));
    }
    stripControl[1]->showLeds();
    vTaskDelay(25);
    fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CRGB::Black);
    stripControl[1]->showLeds();
    vTaskDelay(35);
  }
}
void StrobeFastB(int StrobeCount) {
  for (int j = 0; j < StrobeCount; j++) {
    if (hueColor == true) {
      fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CHSV( valueColor, 255, valueBright));
    }
    else {
      fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CRGB(255, 255, 255));
    }
    stripControl[1]->showLeds();
    vTaskDelay(5);
    fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CRGB::Black);
    stripControl[1]->showLeds();
    vTaskDelay(15);
  }
}
// OCTAVE2 -- ============)  Pulser PART (=========== // -- OCTAVE2
void pulserB() {
  int count = 2;
  for (int x = 0; x < count; x++) {
    int msec = millis() % 1000;
    double msecPos = msec / 1000.0 * NUM_LEDS_PER_STRIP_B;
    for (int i = 0; i < NUM_LEDS_PER_STRIP_B; i++) {
      double a = -0.2 * (i - msecPos) * (i - msecPos); // adjust the number 0.5 to change the width - smaller number = wider pulse
      double y = 255 * pow(2, a);

      if (hueColor == true) {
        LedsB[i] = CHSV(valueColor, 255, (int)y);
      }
      else {
        LedsB[i] = CRGB(y, y, y);
      }
      count++;
      stripControl[1]->showLeds();
    }
    if (count = 30) {
      count == 0;
    }
  }
}
// OCTAVE2 -- ============)  Breathe PART (========= // -- OCTAVE2
void breatheB() {
  const int duration = delayTimer * 60;
  for (unsigned long loopcounter = 0; loopcounter < duration; loopcounter++) {
    //beatsin16 is a function on the FastLED library generating sinwave, (5) is bpm, (0,255) is value range.
    //value range will create the breathing effect
    uint8_t gHue = valueColor;
    int pos = beatsin16(100, 10, 128); // generating the sinwave
    fill_solid(LedsB, NUM_LEDS_PER_STRIP_B, CHSV( gHue, 255, pos)); // CHSV (hue, saturation, value);
    stripControl[1]->showLeds();
    EVERY_N_MILLISECONDS(100) {
      gHue++;
    }
    // shifting the HUE value by incrementing every millisecond this creates the spectrum wave
  }
}
// OCTAVE3 -- ============)  Whipe Forward  (============ // -- OCTAVE3 -- OCTAVE3
void wipeForwardC() {
  for (int i = 0; i < NUM_LEDS_PER_STRIP_C; i++) {

    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
    }
    if (rgbColor == true) {
      LedsC[i] = CRGB(255, 255, 255);
    }
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    //FastLED.delay(delayTimer);
  }
}
void wipeForwardTwoC() {
  for (int i = 0; i < (numA + numB); i++) {
    LedsC[i] = CHSV(valueColor, 255, valueBright);
    LedsC[(numA * 2) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer * 2);
  }
}
void wipeForwardTrippleC() {
  for (int i = 0; i < (numAA); i++) {
    LedsC[i] = CHSV(valueColor, 255, valueBright);
    LedsC[numAA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsC[(numAA * 2) + i] = CHSV(valueColor, 255, valueBright);
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer * 3);
  }
}
void wipeForwardFourC() {
  for (int i = 0; i < (numA); i++) {
    LedsC[i] = CHSV(valueColor, 255, valueBright);
    LedsC[numA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsC[(numA * 2) + i] = CHSV(valueColor, 255, valueBright);
    LedsC[(numA * 3) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer * 4);
  }
}
// OCTAVE3 -- ============)  Backward  (============ // -- OCTAVE3 -- OCTAVE3
void wipeBackwardC() {
  for (int i = (NUM_LEDS_PER_STRIP_C) - 1; i >= 0; i--) {
    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[i] = CRGB(255, 255, 255);
    }
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
  }
}
void wipeBackwardTwoC() {
  for (int i = (numA + numB) - 1; i >= 0; i--) {
    LedsC[i] = CHSV(valueColor, 255, valueBright);
    LedsC[(numC * 2) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer * 2);
  }
}
void wipeBackwardTrippleC() {
  for (int i = (numAA) - 1; i >= 0; i--) {
    LedsC[i] = CHSV(valueColor, 255, valueBright);
    LedsC[numAA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsC[(numAA * 2) + i] = CHSV(valueColor, 255, valueBright);
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer * 3);
  }
}
void wipeBackwardFourC() {
  for (int i = (numA) - 1; i >= 0; i--) {
    LedsC[i] = CHSV(valueColor, 255, valueBright);
    LedsC[numA + i] = CHSV(valueColor / 2, 255, valueBright);
    LedsC[(numA * 2) + i] = CHSV(valueColor, 255, valueBright);
    LedsC[(numA * 3) + i] = CHSV(valueColor / 2, 255, valueBright);
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer * 4);
  }
}
// OCTAVE3 -- ============)  Dual Whipe  (=============== // -- OCTAVE3 -- OCTAVE3
void dualWipeCenterToOutC() {
  uint16_t j = 1;
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP_C / 2) - 1;
  for (uint16_t i = HALFWAY; i < NUM_LEDS_PER_STRIP_C  ; i++)
  {
    if (hueColor == true) {
      LedsC[HALFWAY - j] = CHSV(valueColor, 255, valueBright);
      LedsC[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[HALFWAY - j] = CRGB(255, 255, 255);
      LedsC[i] = CRGB(255, 255, 255);
    }
    j++;
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    if (j == 30) {
      j = 1;
    }
  }
}
void dualWipeEndToCenterC() {
  uint16_t j = 0;
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP_C / 2) - 1;
  for (int i = NUM_LEDS_PER_STRIP_C  ; i >= 30; i--)
  {
    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
      LedsC[j] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[i] = CRGB(255, 255, 255);
      LedsC[j] = CRGB(255, 255, 255);
    }
    j++;
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    if (j == 30) {
      j = 0;
    }
  }
}
// OCTAVE3 -- ============)  OnePixel  (====================== // -- OCTAVE3 -- OCTAVE3
void onePXupC() {
  for (int i = 0; i < NUM_LEDS_PER_STRIP_C;  i++) {
    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[i] = CRGB(255, 255, 255);
    }
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = 0; i < NUM_LEDS_PER_STRIP_C;  i++) {
      LedsC[i] = CHSV(0, 0, 0);
    }
  }
}
void onePXdwnC() {
  for (int i = (NUM_LEDS_PER_STRIP_C) - 1; i >= 0; i--) {
    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[i] = CRGB(255, 255, 255);
    }
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = (NUM_LEDS_PER_STRIP_C) - 1; i >= 0; i--) {
      LedsC[i] = CHSV(0, 0, 0);
    }
  }
}

void onePXCenterToEndC() {
  int k = 30;
  for (int i = 30; i < NUM_LEDS_PER_STRIP_C;  i++) {
    k--;
    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
      LedsC[k] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[i] = CRGB(255, 255, 255);
      LedsC[k] = CRGB(255, 255, 255);
    }
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = 30; i < NUM_LEDS_PER_STRIP_C;  i++) {
      LedsC[i] = CHSV(0, 0, 0);
      LedsC[k] = CHSV(0, 0, 0);
    }
  }
}

void onePXEndToCenterC() {
  int k = 0;
  for (int i = (NUM_LEDS_PER_STRIP_C) - 1; i >= 30; i--) {
    k++;
    if (hueColor == true) {
      LedsC[i] = CHSV(valueColor, 255, valueBright);
      LedsC[k] = CHSV(valueColor, 255, valueBright);
    }
    else {
      LedsC[i] = CRGB(255, 255, 255);
      LedsC[k] = CRGB(255, 255, 255);
    }
    stripControl[2]->showLeds();
    vTaskDelay(delayTimer);
    for (int i = (NUM_LEDS_PER_STRIP_C) - 1; i >= 30; i--) {
      LedsC[i] = CHSV(0, 0, 0);
      LedsC[k] = CHSV(0, 0, 0);
    }
  }
}
// OCTAVE3 -- ============)  Segements to FullStrip  (======= // -- OCTAVE3 -- OCTAVE3
void segementsToFullStripC() {
  for (int i = 0; i < stripLen; i++) {
    LedsB[i] = CHSV(valueColor, 255, valueBright);
    vTaskDelay(delayTimer);
  }
  stripControl[2]->showLeds();
}
// OCTAVE3 -- ============)  HalfStrip PART (================ // -- OCTAVE3 -- OCTAVE3
void firstHalfC() {
  for (int m = 0; m < 30; m++) {
    LedsC[m]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
void secondHalfC() {
  for (int n = 30; n < 59; n++) {
    LedsC[n]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
// OCTAVE3 -- ============)  FillStrip PART (=============== // -- OCTAVE3 -- OCTAVE3
void fillStripC() {
  fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CHSV( valueColor, 255, valueBright));
  stripControl[2]->showLeds();
}
// OCTAVE3 -- ============)  TrippleStrip PART (=========== // -- OCTAVE3 -- OCTAVE3
void oneThirdC() {
  for (int o = 1; o < 20; o++) {
    LedsC[o]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
void secondThirdC() {
  for (int p = 20; p < 40; p++) {
    LedsC[p]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
void thirdThirdC() {
  for (int q = 40; q < 60; q++) {
    LedsC[q]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
// OCTAVE3 -- ============)  QuaterStrip PART (=========== //  -- OCTAVE3 -- OCTAVE3
void firstFourC() {
  for (int r = 1; r < 15; r++) {
    LedsC[r]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
void secondFourC() {
  for (int s = 15; s < 30; s++) {
    LedsC[s]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
void thirdFourC() {
  for (int t = 30; t < 45; t++) {
    LedsC[t]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
void fourthFourC() {
  for (int u = 45; u < 60; u++) {
    LedsC[u]  = CHSV(valueColor, 255, valueBright);
  }
  stripControl[2]->showLeds();
}
// OCTAVE3 -- ============)  Theater Chase PART (========= // -- OCTAVE3 -- OCTAVE3
void TheaterChaseC() {
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < NUM_LEDS_PER_STRIP_C; i = i + 3) {
        LedsC[i + q] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[2]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < NUM_LEDS_PER_STRIP_C; i = i + 3) {
        LedsC[i + q] = CHSV(0, 0, 0);
      }
    }
  }
}
void TheaterChaseReverseC() {
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 3; q > 0; q--) {
      for (int i = 0; i < NUM_LEDS_PER_STRIP_C; i = i + 3) {
        LedsC[i + q] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[2]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < NUM_LEDS_PER_STRIP_C; i = i + 3) {
        LedsC[i + q] = CHSV(0, 0, 0);
      }
    }
  }
}
void TheaterChaseDoubleC() {
  uint16_t HALFWAY = (NUM_LEDS_PER_STRIP_C / 2) - 1;
  for (int j = 0; j < 7; j++) { //do 10 cycles of chasing
    for (int q = 3; q > 0; q--) {
      int x = q;
      x--;
      for (int i = 0; i < HALFWAY; i = i + 3) {
        LedsC[(i + q) - 1] = CHSV(valueColor, 255, valueBright);
        LedsC[(HALFWAY + 3) + (i - x)] = CHSV(valueColor, 255, valueBright);
      }
      stripControl[2]->showLeds();
      vTaskDelay(delayTimer * 2);
      for (int i = 0; i < HALFWAY; i = i + 3) {
        LedsC[(i + q) - 1] = CHSV(0, 0, 0);
        LedsC[(HALFWAY + 3) + (i - x)] = CHSV(0, 0, 0);
      }
    }
  }
}
// OCTAVE3 -- ============)  Glitter PART (=========== // -- OCTAVE3 -- OCTAVE3
void GlitterC() {
  for (int i = (NUM_LEDS_PER_STRIP_C) - 1; i >= 0; i--) {
    LedsA[i] = CHSV(0, 0, 0);
    addGlitterC(80);
    stripControl[2]->showLeds();
    fadeallC();
    vTaskDelay(30);
  }
}
void addGlitterC( fract8 chanceOfGlitter) {//glitter effect
  if ( random8() < chanceOfGlitter) {
    if (hueColor == true) {
      LedsC[ random16(NUM_LEDS_PER_STRIP_C) ] += CHSV( valueColor, 255, valueBright);
    }
    else {
      LedsC[ random16(NUM_LEDS_PER_STRIP_C) ] +=  CRGB(255, 255, 255);
    }
  }
}
// OCTAVE2 -- ============)  Strobe PART (=========== // -- OCTAVE2

void StrobeSlowC(int StrobeCount) {
  for (int j = 0; j < StrobeCount; j++) {
    if (hueColor == true) {
      fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CHSV( valueColor, 255, valueBright));
    }
    else {
      fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CRGB(255, 255, 255));
    }
    stripControl[2]->showLeds();
    vTaskDelay(25);
    fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CRGB::Black);
    stripControl[2]->showLeds();
    vTaskDelay(35);
  }
}
void StrobeFastC(int StrobeCount) {
  for (int j = 0; j < StrobeCount; j++) {
    if (hueColor == true) {
      fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CHSV( valueColor, 255, valueBright));
    }
    else {
      fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CRGB(255, 255, 255));
    }
    stripControl[2]->showLeds();
    vTaskDelay(5);
    fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CRGB::Black);
    stripControl[2]->showLeds();
    vTaskDelay(15);
  }
}
// OCTAVE3 -- ============)  Pulser PART (=========== // -- OCTAVE3 -- OCTAVE3
void pulserC() {
  int count = 2;
  for (int x = 0; x < count; x++) {
    int msec = millis() % 1000;
    double msecPos = msec / 1000.0 * NUM_LEDS_PER_STRIP_C;
    for (int i = 0; i < NUM_LEDS_PER_STRIP_C; i++) {
      double a = -0.2 * (i - msecPos) * (i - msecPos); // adjust the number 0.5 to change the width - smaller number = wider pulse
      double y = 255 * pow(2, a);

      if (hueColor == true) {
        LedsC[i] = CHSV(valueColor, 255, (int)y);
      }
      else {
        LedsC[i] = CRGB(y, y, y);
      }
      count++;
      stripControl[2]->showLeds();
    }
    if (count = 30) {
      count == 0;
    }
  }
}
// OCTAVE3 -- ============)  Breathe PART (========= // -- OCTAVE3 -- OCTAVE3
void breatheC() {
  const int duration = delayTimer * 60;
  for (unsigned long loopcounter = 0; loopcounter < duration; loopcounter++) {
    //beatsin16 is a function on the FastLED library generating sinwave, (5) is bpm, (0,255) is value range.
    //value range will create the breathing effect
    uint8_t gHue = valueColor;
    int pos = beatsin16(100, 10, 128); // generating the sinwave
    fill_solid(LedsC, NUM_LEDS_PER_STRIP_C, CHSV( gHue, 255, pos)); // CHSV (hue, saturation, value);
    stripControl[2]->showLeds();
    EVERY_N_MILLISECONDS(100) {
      gHue++;
    }
    // shifting the HUE value by incrementing every millisecond this creates the spectrum wave
  }
}
void setup() {
  hueColor = true;
  rgbColor = false;

  stripControl[0] = &FastLED.addLeds<WS2812, 15>(LedsA, NUM_LEDS_PER_STRIP);
  stripControl[1] = &FastLED.addLeds<WS2812, 21>(LedsB, NUM_LEDS_PER_STRIP_B);
  //stripControl[2] = &FastLED.addLeds<WS2812, 22>(LedsC, NUM_LEDS_PER_STRIP_C);
  //stripControl[3] = &FastLED.addLeds<WS2812, 23>(LedsD, NUM_LEDS_PER_STRIP_D);
  //stripControl[4] = &FastLED.addLeds<WS2812, 32>(LedsE, NUM_LEDS_PER_STRIP_E);
  //stripControl[5] = &FastLED.addLeds<WS2812, 33>(LedsF, NUM_LEDS_PER_STRIP_F);
  //stripControl[6] = &FastLED.addLeds<WS2812, 34>(LedsG, NUM_LEDS_PER_STRIP_G);
  //stripControl[7] = &FastLED.addLeds<WS2812, 35>(LedsH, NUM_LEDS_PER_STRIP_H);


  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function
  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);

  MIDI.setHandleControlChange(handleControlChange);

  // Initiate MIDI communications, listen to all channels
  MIDI.begin(Channel);
  stripControl[0]->clearLedData();
  stripControl[1]->clearLedData();
  stripControl[2]->clearLedData();
  //Serial.begin(9600);
  Serial2.begin(31250);

  //valueColor = 20;
  //valueBright = 128;
  //delayTimer = 20;
}

void loop() {

  int note, velocity, channel, number, valueD;

  if (MIDI.read()) {
    byte type = MIDI.getType();
    switch (type) {
      case midi::NoteOn:
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        if (velocity > 0) {
          //Serial.println(String("NoteOn: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
          //pressValue = MIDI.getData2();
          velocityColor = map(pressValue, 0, 127, 0, 255);
          //Serial.println(valueColor);
          lenValue = MIDI.getData2();
          stripLen = map(lenValue, 0, 127, 0, 60);
          //Serial.println(stripLen);
        }
        else {
          //Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case midi::NoteOff:
        note = MIDI.getData1();
        channel = MIDI.getChannel();

        //Serial.println(String("NoteOff: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        break;
      case midi::ControlChange:
        number = MIDI.getData1();
        valueD = MIDI.getData2();
        channel = MIDI.getChannel();
        if (valueD > 0 && number == 23) {
          brightController = MIDI.getData2();
          valueBright = map(brightController, 0, 127, 0, 255);
          //Serial.println(String("ControlChange: ch=") + channel + ", number=" + number + ", value=" + valueD);
        }
        if (valueD > 0 && number == 22) {
          timeController = MIDI.getData2();
          delayTimer = map(timeController, 0, 127, 0, 20);
          //Serial.println(String("ControlChange: ch=") + channel + ", number=" + number + ", value=" + valueD);
        }
        if (valueD > 0 && number == 21) {
          colorValue = MIDI.getData2();
          valueColor = map(colorValue, 0, 127, 0, 255);
          if (colorValue == 127) {
            hueColor = false;
            rgbColor = true;
          }
          else {
            hueColor = true;
            rgbColor = false;
          }
          //Serial.println(String("ControlChange: ch=") + channel + ", number=" + number + ", value=" + valueColor);
        }
    }
  }
}
