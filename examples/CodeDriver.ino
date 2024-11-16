
///aaaaaaaaaaaaaaaa

#include "../src/DongCoPi.h"
#include <Wire.h>

// #define DEBUG_I2C
// #define DEBUG_FUNTION
// #define DEBUG_DATA

#define pinPwm1 3
#define pinDir1 2
#define pinPwm2 5
#define pinDir2 4
#define pinPwm3 7
#define pinDir3 6
#define pinPwm4 11
#define pinDir4 10
#define pinDebug 25

XMotor dongco;

void setup() {


  dongco.init(pinDir1, pinPwm1, pinDir2, pinPwm2, pinDir3, pinPwm3, pinDir4, pinPwm4);
  Serial.begin(115200);
  Serial.println("Start");
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWriteFast(LED_BUILTIN, 1);

}

void loop() {
  Serial.println("Hello");
  dongco.setSpeed(100, 100, 100, 100);
  delay(1000);
  dongco.setSpeed(0, 0, 0, 0);
  delay(1000);
  

}
