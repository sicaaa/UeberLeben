/*

  Projekt: Ultraschall Sensor steuert den SMA Draht

  HCSR04 Sensor:
  Rot     | VCC     | +5VDC
  Gelb    | Trigger | Pin 11
  Grün    | Echo    | Pin 12
  Schwarz | GND     | GND

  SMA Aktor:
  Rot     | +5VDC
  Gelb    | Pin 13
  Schwarz | GND

*/


int trigPin = 12;    
int echoPin = 11;   
long duration, cm, inches;

int SMA = 13;


void setup () {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(SMA, OUTPUT);
}


void loop () {

  SensorRead();

  if (cm < 10) {                 // Definiere einen Abstand in Centimeter, um den SMA Draht zu aktivieren.
    digitalWrite(SMA, HIGH);     // SMA an
    Serial.println("an");
    delay(7000);                 // Definiere eine Pause (1 Sekunde = 1000)
    digitalWrite(SMA, LOW);      // SMA aus
    Serial.println("aus");
    delay(18000);                
  }

  else {
    digitalWrite(SMA, LOW);      // SMA aus
  }

  delay(100);
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
