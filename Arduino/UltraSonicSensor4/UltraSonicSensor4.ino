// Ultrasonic sensor
int frontTrigPin = 30;    // Trigger
int frontEchoPin = 31;    // Echo
int leftTrigPin = 36;    // Trigger
int leftEchoPin = 37;    // Echo
int rightTrigPin = 34;    // Trigger
int rightEchoPin = 35;    // Echo
int backTrigPin = 42;    // Trigger
int backEchoPin = 43;    // Echo
long durationF, cmF;
long durationL, cmL;
long durationR, cmR;
long durationB, cmB;


void setup() {
  // put your setup code here, to run once:

  Serial.begin (9600);
  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(backTrigPin, OUTPUT);
  pinMode(backEchoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(frontTrigPin, LOW);
  digitalWrite(leftTrigPin, LOW);
  digitalWrite(rightTrigPin, LOW);
  digitalWrite(backTrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(frontTrigPin, HIGH);
  digitalWrite(leftTrigPin, HIGH);
  digitalWrite(rightTrigPin, HIGH);
  digitalWrite(backTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(frontTrigPin, LOW);
  digitalWrite(leftTrigPin, LOW);
  digitalWrite(rightTrigPin, LOW);
  digitalWrite(backTrigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(frontEchoPin, INPUT);
  durationF = pulseIn(frontEchoPin, HIGH);
  cmF = (durationF/2) / 29.1; 
//  Serial.println(cm);

  pinMode(leftEchoPin, INPUT);
  durationL = pulseIn(leftEchoPin, HIGH);
  cmL = (durationL/2) / 29.1;

  pinMode(rightEchoPin, INPUT);
  durationR = pulseIn(rightEchoPin, HIGH);
  cmR = (durationR/2) / 29.1;

  pinMode(backEchoPin, INPUT);
  durationB = pulseIn(backEchoPin, HIGH);
  cmB = (durationB/2) / 29.1;

  Serial.print("f => ");
  Serial.println(cmF);
    Serial.print("l => ");
  Serial.println(cmL);
    Serial.print("r => ");
  Serial.println(cmR);
    Serial.print("b => ");
  Serial.println(cmB);
  delay(1000);

//if (cmF <= 15 && cmR < cmL){
//  left();
//}
//  
 
}
