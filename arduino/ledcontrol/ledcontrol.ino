//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       ledcontrol.ino
//  Synopsis:   Drive display devices for aphd
//

#define LEFT    10
#define RIGHT   9
#define LED_ON  128
#define LED_OFF 0

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


void setup() {
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
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
          analogWrite(LEFT, LED_ON);
        else
          analogWrite(LEFT, LED_OFF);
        break;
      case 'R':
      case 'r':
        if (Level(buffer) > 0)
          analogWrite(RIGHT, LED_ON);
        else
          analogWrite(RIGHT, LED_OFF);
        break;
    }
  }

}
