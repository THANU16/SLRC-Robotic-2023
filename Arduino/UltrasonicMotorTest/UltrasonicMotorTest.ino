int leftForwardPin = 50;
int leftBackwardPin = 52;
int rightForwardPin = 51;
int rightBackwardPin = 53;
int leftForwardLowPin = 48;
int leftBackwardLowPin = 46;
int rightForwardLowPin = 49;
int rightBackwardLowPin = 47;
int rightBackwardEN = 6;
int leftBackwardEN = 5;
int rightForwardEN = 7;
int leftForwardEN = 8;

// Ultrasonic sensor
int frontTrigPin = 22;    // Trigger
int frontEchoPin = 23;    // Echo
int leftTrigPin = 38;    // Trigger
int leftEchoPin = 39;    // Echo
int rightTrigPin = 40;    // Trigger
int rightEchoPin = 41;    // Echo
int backTrigPin = 42;    // Trigger
int backtEchoPin = 43;    // Echo
long durationF, cmF;
long durationL, cmL;
long durationR, cmR;
long durationB, cmB;


void setup() {
  // put your setup code here, to run once:

    Serial.begin (9600);
    
  pinMode(leftForwardPin, OUTPUT);
  pinMode(leftBackwardPin, OUTPUT);
  pinMode(rightForwardPin, OUTPUT);
  pinMode(rightBackwardPin, OUTPUT);
  pinMode(leftForwardLowPin, OUTPUT);
  pinMode(leftBackwardLowPin, OUTPUT);
  pinMode(rightForwardLowPin, OUTPUT);
  pinMode(rightBackwardLowPin, OUTPUT);
  
  pinMode(rightBackwardEN, OUTPUT);
  pinMode(leftBackwardEN, OUTPUT);
  pinMode(rightForwardEN, OUTPUT);
  pinMode(leftForwardEN, OUTPUT);

  pinMode(frontTrigPin, OUTPUT);
  pinMode(frontEchoPin, INPUT);
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(backTrigPin, OUTPUT);
  pinMode(backEchoPin, INPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);

  
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
  duration = pulseIn(frontEchoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1; 
//  Serial.println(cm);
  
forward(); 
delay(500);
if (cm <= 10){
  left();
  delay(500);
  }
  
//  forward();
//  delay(1000);
//  left();
//  delay(500);
//  forward();
//  delay(1000);
//  right();
//  delay(500);
//  stopCar();
//  delay(500);
//  forward();
//  delay(1000);
//  reverse();
//  delay(1000 );
  
}


void forward(){
//   Reset the wheels to go forward
  digitalWrite(leftForwardPin, HIGH); 
  digitalWrite(rightForwardPin, HIGH);
  digitalWrite(leftBackwardPin, HIGH); 
  digitalWrite(rightBackwardPin, HIGH);

  digitalWrite(leftForwardLowPin, LOW); 
  digitalWrite(rightForwardLowPin, LOW);
  digitalWrite(leftBackwardLowPin, LOW); 
  digitalWrite(rightBackwardLowPin, LOW); 
   
  analogWrite(rightBackwardEN, 60); 
  analogWrite(leftBackwardEN, 60); 
  analogWrite(rightForwardEN, 60); 
  analogWrite(leftForwardEN, 60 );  

}



void left(){
  // Turn the car to the left
  digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftBackwardPin, HIGH);
  digitalWrite(rightForwardPin, HIGH);
  digitalWrite(rightBackwardPin, LOW);
  
  digitalWrite(leftForwardLowPin, LOW); 
  digitalWrite(rightForwardLowPin, LOW);
  digitalWrite(leftBackwardLowPin, LOW); 
  digitalWrite(rightBackwardLowPin, LOW); 
  
//  analogWrite(rightBackwardEN, 60); 
  analogWrite(leftBackwardEN, 90); 
  analogWrite(rightForwardEN, 90); 
//  analogWrite(leftForwardEN, 60);
}

void right(){
  // Turn the car to the right
  digitalWrite(leftForwardPin, HIGH);
  digitalWrite(leftBackwardPin, LOW);
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, HIGH);

  digitalWrite(leftForwardLowPin, LOW); 
  digitalWrite(rightForwardLowPin, LOW);
  digitalWrite(leftBackwardLowPin, LOW); 
  digitalWrite(rightBackwardLowPin, LOW); 
  analogWrite(rightBackwardEN, 60);
  analogWrite(leftForwardEN, 60);
}

void stopCar(){
  // Stop the car
  digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftBackwardPin, LOW);
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, LOW);
  
  digitalWrite(leftForwardLowPin, LOW); 
  digitalWrite(rightForwardLowPin, LOW);
  digitalWrite(leftBackwardLowPin, LOW); 
  digitalWrite(rightBackwardLowPin, LOW); 
}

void reverse() {
    digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftBackwardPin, LOW);
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, LOW);
  
  digitalWrite(leftForwardLowPin, HIGH); 
  digitalWrite(rightForwardLowPin, HIGH);
  digitalWrite(leftBackwardLowPin, HIGH); 
  digitalWrite(rightBackwardLowPin, HIGH); 

   analogWrite(rightBackwardEN, 60); 
  analogWrite(leftBackwardEN, 60); 
  analogWrite(rightForwardEN, 60); 
  analogWrite(leftForwardEN, 60);  
}
