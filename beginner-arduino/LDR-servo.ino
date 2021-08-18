#include <Servo.h>

Servo servo3;

float v, pos;

void setup()
{
  servo3.attach(3);
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  v = analogRead(A0);
  Serial.println(v);
  
  
  if (v < 300) {		// the actual threshold (300) doesn't 
    servo3.write(0);	// matter as long as the servo turns
  }						// at some point via LDR control
  else {
    servo3.write(180);
  }
  delay(100);
}