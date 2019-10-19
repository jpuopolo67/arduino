/*
SparkFun Inventor’s Kit
Circuit 1C-Photoresistor

Use a photoresistor to monitor how bright a room is, and turn an LED on when it gets dark.

This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
This code is completely free for any use.

View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <Servo.h>      // include the servo library

int photoresistor = 0;  // value based on the brightness of the ambient light
int threshold = 600;    // voltage threshold at which we turn on/off the LED
Servo myservo;          // create a servo object
int servoPosition;      // servo will move to this position


void setup()
{
  Serial.begin(9600);   // start a serial connection with the computer @ 9600 baud
  pinMode(13, OUTPUT);  // set pin 13 as an output that can be set to HIGH or LOW (for the LED)
  myservo.attach(9);    // tell the servo object that it's plugged into pin 9

}

void sweepServo(int startDegrees, int endDegrees, int step = 1)
{
  int pos = 0;

  if (startDegrees < 0 || startDegrees > 180) {
    return;
  }
  if (endDegrees < 0 || endDegrees > 180) {
    return;
  }
  if (step < 0 || step > 180) {
    return;
  }

  // servo can be told to position itself from 0 - 180 degrees. 
  // note: the SIK warns not to max it out in either direction.

  // sweep in one direction...
  for (pos = startDegrees; pos <= endDegrees; pos += step) { 
    myservo.write(pos);              
    delay(15);                       
  }

  // ...and back in opposite direction
  for (pos = endDegrees; pos >= startDegrees; pos -= step) {
    myservo.write(pos);              
    delay(15);                      
  }
}

void loop()
{
  // read the brightness of the ambient light
  photoresistor = analogRead(A0);   // the photoresistor's output should be connected to pin A0

  Serial.print("Photoresistor voltage output: ");
  Serial.println(photoresistor);  // dump value (0-1023) to computer's serial monitor

  if (photoresistor < threshold) {
    digitalWrite(13, LOW);  // it's light in room, so turn LED OFF
    Serial.println("LED OFF");
  } else {
    digitalWrite(13, HIGH); // it's dark in the room, to turn LED ON
    Serial.println("LED ON!"); 

    // since it's dark in room, move the servo motor back and forth. 
    // hmmm... if we attach a flag or something to it, we can activate the light sensor in my office :).
    sweepServo(10, 170, 2);
  }
}
