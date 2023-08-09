#include "ledFx.h"

byte leds1;
byte leds2;
int t = 50;
int count = 8;

void updateShiftRegister(byte leds1, byte leds2){
  digitalWrite(latchPin, HIGH);
  shiftOut(dataPin, clockPin, LSBFIRST, leds2);
  shiftOut(dataPin, clockPin, LSBFIRST, leds1);
  digitalWrite(latchPin, LOW);
}

void ledFX(void (*fn)(), int count, void (*fn2)()){
  for(int i = 0; i < count; i++){
    fn();
    delay(100);
    if(fn2){
      fn2();
      delay(100);
    }
  }
}

void leftAnimation(){
  const byte animation[] = {0b00000000, 0b00000100, 0b00001100, 0b00011100, 0b00111100, 0b01111100, 0b11111100, 0b11111100, 0b00000000, 0b00000000};
    for (int i = 0; i < sizeof(animation)/sizeof(animation[0]); i++) {
        updateShiftRegister(animation[i], 0b00000000);
        delay(t);
    }
}

void rightAnimation(){
  const byte animation[] = {0b00000000, 0b00000100, 0b00000110, 0b00000111, 0b00000111, 0b00000111, 0b00000111, 0b00000000, 0b00000000};
  const byte animation2[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b11000000, 0b11100000, 0b00000000, 0b00000000};
    for (int i = 0; i < sizeof(animation)/sizeof(animation[0]); i++) {
        updateShiftRegister(animation[i], animation2[i]);
        delay(t);
    }
}

void fillIn(){
  const byte animation[] = {0b00000000, 0b00000100, 0b00001110, 0b00011111, 0b00111111, 0b01111111, 0b11111111, 0b11111111};
  const byte animation2[] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000000, 0b11000000, 0b11100000, 0b11110000};
    for (int i = 0; i < sizeof(animation)/sizeof(animation[0]); i++) {
        updateShiftRegister(animation[i], animation2[i]);
        delay(t);
    }
}

void fillOut(){
  const byte animation[] = {0b11111111, 0b01111111, 0b00111111, 0b00011111, 0b00001110, 0b00000100, 0b00000000};
  const byte animation2[] = {0b11110000, 0b11010000, 0b10010000, 0b10010000, 0b10010000, 0b10010000};
    for (int i = sizeof(animation)/sizeof(animation[1])-1; i >= sizeof(animation)/sizeof(animation[1])-1; i--) {
        updateShiftRegister(animation[i], animation2[i]);
        delay(t);
    }
}
