#LedAnimationProgram

This repository contains an Arduino program that controls a shift register to drive a set of 11 LEDs. The program uses the `ledFx` library to create animations that simulate the modern turn signals found on some new cars, where the lights appear to "run" or "fill" in the direction of the turn.

## How it works

![Asset 3@1080x-100](https://github.com/menicanin/Formula/assets/101369794/4451d1d4-df5e-4d34-96a5-a0753d24135c)


The program consists of several files, including an `.ino` file that contains the main sketch, a `.cpp` file that defines the functions used by the sketch, and a `.h` file that declares the functions and variables used by the sketch.

The main sketch sets up the pins used to control the shift register and runs a series of animations using the `ledFX` function. This function takes as arguments a pointer to an animation function, the number of times to repeat the animation, and an optional second animation function to run after each repetition of the first animation.

The animation functions are defined in the `.cpp` file and use the `updateShiftRegister` function to control the state of the LEDs. This function takes as arguments two bytes representing the state of each set of LEDs and uses the `shiftOut` function to send these values to the shift register.

By modifying the animation functions or creating new ones, you can create custom lighting effects for your LEDs. The program also includes several example animations, such as `leftAnimation`, `rightAnimation`, `fillIn`, and `fillOut`, that you can use as a starting point for your own animations.

## How to use

To use this program, you will need an Arduino board, a shift register, and a set of 11 LEDs. Connect the LEDs to the outputs of the shift register and connect the shift register to your Arduino board according to its datasheet. Then, upload the sketch to your Arduino board and open the serial monitor to see the animations in action.

You can modify the values of `dataPin`, `latchPin`, and `clockPin` in the `.ino` file to match the pins you used to connect your shift register to your Arduino board. You can also modify the animation functions or create new ones in the `.cpp` file to create custom lighting effects.

We hope you enjoy using this program to create modern turn signal animations for your LEDs!
