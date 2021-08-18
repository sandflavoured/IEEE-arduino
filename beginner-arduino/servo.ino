#include <Servo.h>

#define potPin A0	// 
#define servoPin 9

// Declaring an instance of servo called servo9
Servo servo9;

// Declaring variables of type float (decimal)
float r, v, angle;

void setup()
{
  Serial.begin(9600);			// begin serial connection
  pinMode(servoPin, OUTPUT);	// set pin modes
  pinMode(potPin, INPUT);
  servo9.attach(servoPin);		// set pin that controls servo
}

void loop()
{
  r = analogRead(potPin);	// gives number from 0 - 1023
  							// for voltages 0 - 5V
  
  //v = r/1023*5;		// can use this code to measure voltage
  //Serial.println(v);
  
  angle = r/1023*180;		// calculates angle
  Serial.println(angle);
  
  servo9.write(angle);		// writes angle to servo
  delay(100);
}