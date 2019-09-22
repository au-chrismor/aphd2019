//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       ledcontrol.ino
//  Synopsis:   Drive display devices for aphd
//

#include <LedControl.h>


#define NUM_DISP 1

LedControl lc1 = LedControl(12, 11, 10, NUM_DISP);

char Channel(String buffer) {
  int idx = buffer.indexOf(":");
  if(idx > 0) {
    if(buffer.substring(0, idx) == "R")
      return 'R';
    if(buffer.substring(0, idx) == "L")
      return 'L';
  }
}

int Level(String buffer) {
  int speed = 0;
  int idx = buffer.indexOf(":");
  if(idx > 0)
    return buffer.substring(idx+1).toInt();
  else
    return -1;
}

void leftArrow() {
  lc1.clearDisplay(0);
  lc1.setRow(0, 0, B00000011);
  lc1.setRow(0, 1, B00001111);
  lc1.setRow(0, 2, B00111100);
  lc1.setRow(0, 3, B11110000);
  lc1.setRow(0, 4, B11110000);
  lc1.setRow(0, 5, B00111100);
  lc1.setRow(0, 6, B00001111);
  lc1.setRow(0, 7, B00000011);
}

void rightArrow() {
  lc1.clearDisplay(0);
  lc1.setRow(0, 0, B11000000);
  lc1.setRow(0, 1, B11110000);
  lc1.setRow(0, 2, B00111100);
  lc1.setRow(0, 3, B00001111);
  lc1.setRow(0, 4, B00001111);
  lc1.setRow(0, 5, B00111100);
  lc1.setRow(0, 6, B11110000);
  lc1.setRow(0, 7, B11000000);
}



void setup() {
  lc1.shutdown(0, false);
  lc1.setIntensity(0, 10);
  lc1.clearDisplay(0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    String buffer = Serial.readString();
    switch(Channel(buffer))
    {
      case 'L':
      case 'l':
        if (Level(buffer) > 0)
          leftArrow();
        else
          lc1.clearDisplay(0);
        break;
      case 'R':
      case 'r':
        if (Level(buffer) > 0)
          rightArrow();
        else
          lc1.clearDisplay(0);
        break;
    }
  }

}
