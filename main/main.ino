#include "header.h"
LedString String1 (0, 7, 8, 9);          //setup string 1 running on channel 0


void setup() {
  Serial.begin(9600);
  Serial.println("Reset");
}


void loop() {
  readSerial();					    //read serial buffer & change mode
  runInstructions();				//run the corresponding mode
  delay(20);
}




void runInstructions()
{
  if (fading)
  {
    String1.fade();
    Serial.print(String1.colorIncriment[0]);
    Serial.print(" ");
    Serial.print(String1.colorIncriment[1]);
    Serial.print(" ");
    Serial.print(String1.colorIncriment[2]);
    Serial.print("       ");
    Serial.print(String1.pinData[0][1]);
    Serial.print(" ");
    Serial.print(String1.pinData[1][1]);
    Serial.print(" ");
    Serial.print(String1.pinData[2][1]);
    Serial.print(" ");
    Serial.print("\n");
  }
  else if (shutDown && newInstructions)                                  //only run shutdown if there are new instructions
  {
    String1.shutDown();
    Serial.println("Shutting down string 1");
    newInstructions = false;
  }
  else if (not(shutDown) && newInstructions)                             //only run dim if there are new instructions
  {
    String1.dim();
    Serial.print(String1.pinData[0][2]);
    Serial.print(" ");
    Serial.print(String1.pinData[1][2]);
    Serial.print(" ");
    Serial.print(String1.pinData[2][2]);
    Serial.print(" ");
    Serial.println("Setting string to dim");
    newInstructions = false;
  }
}
