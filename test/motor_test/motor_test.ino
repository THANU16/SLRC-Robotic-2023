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


void setup() {
  // put your setup code here, to run once:
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
  
  
  pinMode(LED_BUILTIN, OUTPUT);

  
}

void loop() {

//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(250);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(250);                       // wait for a second
//ENableA - 5
//ENable B - 6
  
  // put your main code here, to run repeatedly:
  forward();
  delay(1000);
  left();
  delay(500);
  forward();
  delay(1000);
  right();
  delay(500);
  stopCar();
  delay(500);
  forward();
  delay(1000);
  reverse();
  delay(1000 );
  
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
  analogWrite(leftForwardEN, 60);  
//  analogWrite(rightBackwardEN, 90); 
//  analogWrite(leftBackwardEN, 90); 
//  analogWrite(rightForwardEN, 90); 
//  analogWrite(leftForwardEN, 90);  
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
