#ifndef LEDFX_H
#define LEDFX_H

#include <Arduino.h>

// Pin declarations
extern const int dataPin;
extern const int latchPin;
extern const int clockPin;

// Other variable declarations
extern byte leds1;
extern byte leds2;
extern int t;
extern int count;

// Function declarations
void updateShiftRegister(byte leds1, byte leds2);
void ledFX(void (*fn)(), int count, void (*fn2)() = nullptr);
void leftAnimation();
void rightAnimation();
void fillIn();
void fillOut();
void checkBattery(int value);
void clear();

#endif
