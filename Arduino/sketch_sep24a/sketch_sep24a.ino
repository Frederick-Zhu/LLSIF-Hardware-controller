
#include <TouchScreen.h>
#include "HID_ts.h"

#define T 30

#define DATA1LINE 5000

const int x[] = {810, 553, 335, 187, 135, 187, 335, 553, 811};
const int y[] = {1571, 1519, 1372, 1155, 896, 636, 418, 272, 220};

//const int x[] = {539, 366, 220, 123, 88, 123, 220, 366, 539};
//const int y[] = {1092, 1056, 959, 813, 640, 466, 321, 224, 191};

const int pin[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

int A = 0;
int B = 0;
int a;
int b;


void setup() {

  for (int i = 0; i < 9; i++) {
    pinMode(pin[i], INPUT_PULLUP);
  }
  pinMode(13, OUTPUT);
  TouchScreen.begin();
  bl(50, 150);

}


void bl(int t, int c) {
  for (int i = 0; i < c; i++) {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(t);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(t);              // wait for a second
  }
}




void loop() {
  a = 0;
  b = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(pin[i]) == LOW) {
      a = i + 1;
      break;
    }
  }

  for (int i = 5; i < 9; i++) {
    if (digitalRead(pin[i]) == LOW) {
      b = i + 1;
      break;
    }
  }

  if (digitalRead(pin[4]) == LOW) {
    if (a == 0) {
      a = 5;
    }
    else if (b == 0) {
      b = 5;
    }
  }



  if (a != A) {
    if (a == 0) {
      TouchScreen.TouchUpA();
    }
    else {
      TouchScreen.TouchDownA(x[a - 1], y[a - 1]);
    }
    A = a;
  }

  if (b != B) {
    if (b == 0) {
      TouchScreen.TouchUpB();
    }
    else {
      TouchScreen.TouchDownB(x[b - 1], y[b - 1]);
    }
    B = b;
  }

  delay(T);
}


