//
//  Copyright (C) 2019 Christopher Moran and Phui Leng Chong
//  All Rights Reserved.
//
//  Name:       ledcontrol.ino
//  Synopsis:   Drive display devices for aphd
//

#define LEFT  10
#define RIGHT 9

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
        analogWrite(LEFT, Level(buffer));
        break;
      case 'R':
        analogWrite(RIGHT, Level(buffer));
        break;
    }
  }

}
