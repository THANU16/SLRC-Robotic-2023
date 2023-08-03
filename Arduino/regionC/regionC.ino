// Front ultra sonic sensor
int front_trigPin = 14;    // Trigger
int front_echoPin = 15;    // Echo

// Right ultra sonic sensor
int right_trigPin = 16;    // Trigger
int right_echoPin = 17;    // Echo

// Left ultra sonic sensor
int left_trigPin = 18;    // Trigger
int left_echoPin = 19;    // Echo

long cm_f, cm_r, cm_l;
long duration_f,duration_r, duration_l;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(front_trigPin, OUTPUT);
  pinMode(front_echoPin, INPUT);
  pinMode(right_trigPin, OUTPUT);
  pinMode(right_echoPin, INPUT);
  pinMode(left_trigPin, OUTPUT);
  pinMode(left_echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  create pulse
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(front_trigPin, LOW);
  digitalWrite(right_trigPin, LOW);
  digitalWrite(left_trigPin, LOW);
  delayMicroseconds(5);
  
  digitalWrite(front_trigPin, HIGH);
  digitalWrite(right_trigPin, HIGH);
  digitalWrite(left_trigPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(front_trigPin, LOW);
  digitalWrite(right_trigPin, LOW);
  digitalWrite(left_trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration_f = pulseIn(front_echoPin, HIGH);
  duration_r = pulseIn(right_echoPin, HIGH);
  duration_l = pulseIn(left_echoPin, HIGH);

  // Convert the time into a distance
  // Divide by 29.1 or multiply by 0.0343
  cm_f = (duration_f/2) / 29.1;   
  cm_r = (duration_r/2) / 29.1;
  cm_l = (duration_l/2) / 29.1;  


  Serial.print("front => ");
  Serial.print(cm_f);
  Serial.print("cm");
  Serial.print(", ");

  Serial.print("Right => ");
  Serial.print(cm_r);
  Serial.print("cm");
  Serial.print(", ");
  
  Serial.print("Left => ");
  Serial.print(cm_l);
  Serial.print("cm");
  Serial.println();

  delay(2500);

}

//createPulse(int trigPin){
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(5);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//}
