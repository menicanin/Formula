#include <PS4Controller.h>
#include <ESP32Servo.h>
#include <L298N.h>
#include <NewPing.h>

#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define MAX_DISTANCE 200

#define leftBlinkFx 4
#define fadeIn 17
#define fadeOut 5
#define rightBlinkFx 15
#define blinkFx 16



NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo myservo;
const byte ENA = 25;
const byte IN1 = 21;
const byte IN2 = 23;
const byte TURBO = 32; //relay switch join 2 batteries (paralel connection) in serial connection 8 to 12v
const byte TurboPlus = 33; // relay switch ‚‚+‚‚ 12v
const byte LED = 26;  // rear light
const byte LED2 = 27; //front light
bool BOOST = false;
bool ledState = true;
bool reverseOnObstacle = false;
bool touchpadPressed = false;
// bool ledStates[NUM_LEDS];

bool trianglePressed = false;
bool leftButtonPressed = false;
bool rightButtonPressed = false;
bool upButtonPressed = false;
bool downButtonPressed = false;

L298N motor(ENA, IN1, IN2);

byte r = 0;
byte g = 0;
byte b = 255;

void setup() {
    Serial.begin(115200);
    PS4.begin("1a:2b:3c:01:01:01");

    PS4.setLed(r, g, b);
    PS4.sendToController();

    Serial.println("Ready.");
    
    myservo.attach(22);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(TURBO, OUTPUT);
    pinMode(TurboPlus, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(LED2, OUTPUT);

    pinMode(leftBlinkFx, OUTPUT); 
    pinMode(rightBlinkFx, OUTPUT); 
    pinMode(fadeIn, OUTPUT); 
    pinMode(fadeOut, OUTPUT); 
    pinMode(blinkFx, OUTPUT); 

    digitalWrite(leftBlinkFx, LOW);
    digitalWrite(rightBlinkFx, LOW);
    digitalWrite(fadeIn, LOW);
    digitalWrite(fadeOut, LOW);
    digitalWrite(blinkFx, LOW);

    digitalWrite(TurboPlus, LOW);
    digitalWrite(LED, HIGH); //rear light
    digitalWrite(LED2, HIGH);  // front light
}

void loop() {
    if (PS4.isConnected()) {
        // handleTouchpadButton(); //touchpad button - shift register - battery status of the remote controller
        handleTriangleButton();
        handleTurboButton();
        handleUpButton();
        handleDownButton();
        handleBatteryLevel();
        handleRumbleAndLed();
        handleServo();
        handleDistance();
        handleR2Button();
        handleL2Button();
        handleLeftButton();
        handleRightButton();
        handleL1Button();
        handleR1Button();
        
        Serial.printf("Battery Level : %d\n", PS4.Battery());
      //  delay(15);
    }
}



// HANDLE TOUCHPAD BUTTON - Shift register //
// void handleTouchpadButton(){
//   if(PS4.Touchpad() && !touchpadPressed){
//     int value = PS4.Battery();
//     delay(200);
//     checkBattery(value);
//     touchpadPressed = true; 
//   } 
//   else if (!PS4.Touchpad()){
//     touchpadPressed = false;
//   }
// }


void handleTriangleButton() {
    if (PS4.Triangle() && !trianglePressed) {
        BOOST = !BOOST;
        if (BOOST) {
            r = 0;
            g = 255;
            b = 0;
        } else {
            r = 0;
            g = 0;
            b = 255;
        }
        trianglePressed = true;
    } else if (!PS4.Triangle()) {
        trianglePressed = false;
    }
}

void handleTurboButton() {
    digitalWrite(TURBO, BOOST);
}


void handleUpButton() {
     if(PS4.Up() && !upButtonPressed){
       ledState = !ledState;
      digitalWrite(LED, ledState);
      digitalWrite(fadeIn,!ledState);
      
      digitalWrite(fadeOut,ledState);
      upButtonPressed = true; 
      } 
    else if (!PS4.Up()){
      upButtonPressed = false;
      digitalWrite(fadeIn,LOW);
      digitalWrite(fadeOut,LOW);
      
      // delay(100);
    }
}


void handleBatteryLevel() {
    if (PS4.Battery() == 5) {
            r = 255;
            g = 0;
            b = 0;
        }
}

void handleRumbleAndLed() {
    PS4.setRumble(PS4.L2Value(), PS4.R2Value());
    PS4.setLed(r, g, b);
    PS4.sendToController();
}

void handleServo() {
    int val = map(PS4.LStickX(), -128, 255, 60, 0);
    myservo.write(val);
}

void handleDistance() {
    int distance = sonar.ping_cm();

    if (reverseOnObstacle && distance > 0 && distance <= 80 && !PS4.L2Value() && PS4.R2Value()) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        analogWrite(ENA,255);
        delay(500); // move in opposite direction for exactly 500ms
        while (PS4.R2Value() != 0) { // wait until R2 is released
          delay(15); 
        }
    } else if (PS4.R2Value()){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA,PS4.R2Value());
    } else {
      digitalWrite(IN2, LOW);
      digitalWrite(IN1, LOW);
    }
}

void handleR2Button() {
     if (PS4.R2Value()){
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          analogWrite(ENA,PS4.R2Value());
     } else {
          digitalWrite(IN2, LOW);
          digitalWrite(IN1, LOW);
     }
}

void handleL2Button() {
     if (PS4.L2Value()) {
           digitalWrite(IN1, LOW);
           digitalWrite(IN2, HIGH);
           analogWrite(ENA,PS4.L2Value());
     } else {
           digitalWrite(IN2, LOW);
     }
}

void handleDownButton() {
     if(PS4.Down() && !downButtonPressed){
      digitalWrite(blinkFx, HIGH);
      downButtonPressed = true; 
      } 
    else if (!PS4.Down()){
      downButtonPressed = false;
      digitalWrite(blinkFx, LOW);
    }
}

void handleLeftButton() {
     if(PS4.Left() && !leftButtonPressed){
      digitalWrite(leftBlinkFx, HIGH);
      leftButtonPressed = true; 
      } 
    else if (!PS4.Left()){
      leftButtonPressed = false;
      digitalWrite(leftBlinkFx, LOW);
    }
}

void handleRightButton() {
     if(PS4.Right() && !rightButtonPressed){
       digitalWrite(rightBlinkFx, HIGH);
      rightButtonPressed = true; 
      } 
    else if (!PS4.Right()){
      rightButtonPressed = false;
      digitalWrite(rightBlinkFx, LOW);
    }
}

void handleL1Button() {
     if (PS4.L1()) { // turn on reverseOnObstacle function
          reverseOnObstacle = true;
          delay(300); // prevent multiple button presses
     }
}

void handleR1Button() {
     if (PS4.R1()) { // turn off reverseOnObstacle function
          reverseOnObstacle = false;
          delay(300); // prevent multiple button presses
     }
}
