/*
 
  Projekt: Ultraschall Sensor steuert den Servo Motor

  HCSR04 Ultrasonic Sensor:
  Kabel   | Sensor  | Arduino
  Rot     | VCC     | +5VDC
  Gelb    | Trigger | Pin 11
  Grün    | Echo    | Pin 12
  Schwarz | GND     | GND

  Servo:
  Kabel   | Arduino
  Rot     | +5VDC
  Gelb    | Pin 9
  Schwarz | GND
  
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
  
  if (cm <= 10) {                  // Definiere einen Abstand in Centimeter, um den Servo zu aktivieren.
    StartServoSweep();
  }
  
  delay(100);                                   
}












void StartServoSweep() {
  for (pos = 0; pos <= 180; pos += 1) {       // Der Servo bewegt sich zwischen 0 und 180 Grad
    myservo.write(pos);
    delay(10);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
}


void StartServoNoSweep() {
myservo.write(0); //Position 1 ansteuern mit dem Winkel 0°
delay(1000); //Das Programm stoppt für 3 Sekunden
myservo.write(90); //Position 2 ansteuern mit dem Winkel 90°
delay(1000); //Das Programm stoppt für 3 Sekunden
}


void SensorRead() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration / 2) / 29.1;   
  Serial.println(cm);
}
