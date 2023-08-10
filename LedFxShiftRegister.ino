/*
 * ======================================================================
 * LED Animation Program
 * ======================================================================
 * 
 * This program is designed to control animations for a set of 11 LEDs using a shift register. 
 * The program uses the `ledFx` library to define a set of animation functions that can be used 
 * to create various lighting effects. The `setup` function initializes the pins used to control 
 * the shift register and runs an initial animation using the `fillOut` function. The `fx` function 
 * is an example of how multiple animation functions can be combined to create a more complex lighting 
 * sequence. By modifying the `fx` function or creating new animation functions, you can create custom 
 * lighting effects for your LEDs.
 */


#include "ledFx.h"

const int dataPin  = 10;      //    DS - data serial
const int latchPin = 12;      // ST_CP - storage register, latch clock pin
const int clockPin = 11;       // SH_CP - shift register clock pin

const int leftBlinkFx = 9;   //nodeMcu GIPO 04
const int rightBlinkFx = 7;   //nodeMcu GPIO 15
const int blinkFx = 8;       //nodeMcu GPIO 16
const int fadeIn = 5;         //nodeMcu GIPO 17
const int fadeOut = 6;         //nodeMcu GPIO 05

bool fadeInPressed = false;
bool fadeOutPressed = false;

bool fadeInStatus = true;

void setup() {
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);

    pinMode(leftBlinkFx, INPUT);
    pinMode(rightBlinkFx, INPUT);
    pinMode(blinkFx, INPUT);
    pinMode(fadeIn, INPUT);
    pinMode(fadeOut, INPUT);
    // ledFX(fillOut,1);
    clear();
    delay(200);
    clear();
}

void loop() {
    
  if(digitalRead(leftBlinkFx) == HIGH){
    ledFX(leftAnimation, count);
    if(!fadeInStatus) {
      ledFX(fillIn, 1);
    }
  }

  if(digitalRead(rightBlinkFx) == HIGH){
    ledFX(rightAnimation, count);
  }

  if(digitalRead(blinkFx) == HIGH){
    ledFX(fillIn, count, fillOut);
  }


  if(digitalRead(fadeIn) == HIGH && !fadeInPressed){
    ledFX(fillIn, 1);
    fadeInPressed = true;

    fadeInStatus = !fadeInStatus;
  } else if (digitalRead(fadeIn) == false){
    fadeInPressed = false;
  }

  if(digitalRead(fadeOut) == HIGH && !fadeOutPressed){
    ledFX(fillOut, 1);
    fadeOutPressed = true;
  } else if (digitalRead(fadeOut) == false){
    fadeOutPressed = false;
  }

delay(50);

}
