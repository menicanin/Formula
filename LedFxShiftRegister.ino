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

const int dataPin  = 9;      //    DS - data serial
const int latchPin = 8;      // ST_CP - storage register, latch clock pin
const int clockPin = 10;       // SH_CP - shift register clock pin



void setup() {
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);
    ledFX(fillOut,1);
    delay(2000);

    fx();
}

void loop() {

}

//example function for leds animation
void fx(){
ledFX(fillIn,1);
    delay(2000);
    ledFX(fillOut,1);
    ledFX(leftAnimation, count);
    ledFX(rightAnimation, count);
    ledFX(fillIn, count, fillOut);
    ledFX(fillIn,1);
}
