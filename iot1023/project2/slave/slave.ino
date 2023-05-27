#include "SevSeg.h"
#include <Wire.h>
SevSeg sevseg; 

int segPins[] = {6, 5, 2, 3, 4, 7, 8, 9};   // a b c d e f g .

char currentKey;
bool receiveFlag = false;
byte charCodeDigits[7][8] = {
  // a  b  c  d  e  f  g  .
  { 1, 1, 1, 0, 1, 1, 1, 0},  // A
  { 0, 0, 1, 1, 1, 1, 1, 0},  // B
  { 1, 0, 0, 1, 1, 1, 0, 0},  // C
  { 0, 1, 1, 1, 1, 0, 1, 0},  // D
  { 1, 0, 0, 1, 1, 1, 1, 0},  // E
  { 1, 0, 0, 0, 1, 1, 1, 0},  // F
  { 0, 0, 0, 0, 0, 0, 0, 1},  // .
};

void displayByIndex(int index)
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(segPins[i], charCodeDigits[index][i]);
  }
}


void receiveEvent(int bytes)
{
  currentKey = Wire.read();
  Serial.print("received:");
  Serial.println(currentKey);
  receiveFlag = true;
}

void setup()
{
    byte numDigits = 1;
    byte digitPins[] = {};
    bool resistorsOnSegments = true;
    byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};   // { a b c d e f g . )
    byte hardwareConfig = COMMON_CATHODE; 
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(90);

    //set pin for displaying ch by manual
    for (int i = 0; i < 8; i++)
    {
      pinMode(segPins[i], OUTPUT);
    }
    //default display . character
    displayByIndex(6);

    Serial.begin(9600);
    Wire.begin(9);
    Wire.onReceive(receiveEvent);
    
}

void loop(){
  if (receiveFlag)
  {
    receiveFlag = false;
    if (isdigit(currentKey))
    {
      char str[2];
      str[0] = currentKey;
      str[1] = '\0';
      sevseg.setNumber(atoi(str));

      delay(1000);
      sevseg.refreshDisplay();   

    } else if(isalpha(currentKey) ||
      currentKey == '*' ||
      currentKey == '#') {
      int index = -1;
      switch(currentKey)
      {
        case 'A':
          index = 0;
          break;
        case 'B':
          index = 1;
          break;
        case 'C':
          index = 2;
          break;
        case 'D':
          index = 3;
          break;
        case '#':
          index = 4;
          break;
        case '*':
          index = 5;
          break;
      }
      
      displayByIndex(index);
    }
    else {
      Serial.print("Cannot show this character:");
      Serial.println(currentKey);
    }
  }

     
}




 