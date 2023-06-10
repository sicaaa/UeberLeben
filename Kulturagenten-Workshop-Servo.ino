/*

  Project: Über Leben
  Ultrasonic Sensor with Servo Motor

  HCSR04 Ultrasonic Sensor:
  Complete Guide for Ultrasonic Sensor HC-SR04 created by Rui Santos.
  https://randomnerdtutorials.com
  
  Cabel   | Sensor  | Arduino
  Red     | VCC     | +5VDC
  Yellow  | Trigger | Pin 11
  Green   | Echo    | Pin 12
  Black   | GND     | GND

  Servo:
  Kabel   | Arduino
  Red     | +5VDC
  Yellow  | Pin 9
  Black   | GND
  
*/


int trigPin = 12;   
int echoPin = 11;    
long duration, cm, inches;

#include <Servo.h>
Servo myservo;
int pos = 0;


void setup () {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);
}


void loop () {
  SensorRead();
  
  if (cm <= 10) {                      // Define a distance between 2-40 centimetres to activate the servo motor.
    StartServoSweep();
  }
  
  delay(100);                                   
}












void StartServoSweep() {
  for (pos = 0; pos <= 180; pos += 1) {        // The servo moves between 0 and 180 degrees.
    myservo.write(pos);
    delay(10);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
}


void StartServoNoSweep() {
myservo.write(0);                              // Move to position 1 with an angle of 0°
delay(3000);                                   // 3 seconds delay
myservo.write(90);                             // Move to position 2 with an angle of 90°
delay(3000);                                   // 3 seconds delay
}


void SensorRead() {                             
  digitalWrite(trigPin, LOW);                  // Read the signal from the sensor without a library.
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;   
  Serial.println(cm);
}
