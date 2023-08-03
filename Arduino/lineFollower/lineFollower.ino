int IR0 = 22;
int IR1 = 23;
int IR2 = 24;
int IR3 = 25;
int IR4 = 26;
int IRF = 27;
int IRB = 28;
int colour_sen = 30;

int leftForwardPin = 50;
int leftBackwardPin = 51;
int rightForwardPin = 52;
int rightBackwardPin = 53;
int motorLowPin = 54;


void setup() {
  // put your setup code here, to run once:
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IRF, INPUT);
  pinMode(IRB, INPUT);
  pinMode(colour_sen, INPUT);

  pinMode(leftForwardPin, OUTPUT);
  pinMode(leftBackwardPin, OUTPUT);
  pinMode(rightForwardPin, OUTPUT);
  pinMode(rightBackwardPin, OUTPUT);
  pinMode(motorLowPin, OUTPUT);

  digitalWrite(motorLowPin, LOW);
  
 

}

void loop() {
  // put your main code here, to run repeatedly:
//  get the value of IR sensors
  int IR0v = digitalRead(IR0);
  int IR1v = digitalRead(IR1);
  int IR2v = digitalRead(IR2);
  int IR3v = digitalRead(IR3);
  int IR4v = digitalRead(IR4);
  int IRFv = digitalRead(IRF);
  int IRBv = digitalRead(IRB);
  
  int colour_sen_value = digitalRead(colour_sen);  // get the reading of colour sensor

//forward
  if (IR0v == 1 && IR1v == 1 && IR2v == 1 && IR3v == 0 && IR4v == 0 && IRFv == 1 && IRBv == 1 ){
    forward();
  }
//  Turn Left
  else if (IR0v == 1 && IR1v == 1 && IR2v == 1 && IR3v == 1 && IR4v == 0 && IRFv == 0 && IRBv == 1 ){
    left();
  }
//  Turn right
  else if (IR0v == 1 && IR1v == 1 && IR2v == 1 && IR3v == 0 && IR4v == 1 && IRFv == 0 && IRBv == 1 ){
    right();
  }

}


void forward(){
  // Reset the wheels to go forward
  digitalWrite(leftForwardPin, HIGH);
  digitalWrite(leftBackwardPin, LOW);
  digitalWrite(rightForwardPin, HIGH);
  digitalWrite(rightBackwardPin, LOW);
}

void left(){
  // Turn the car to the left
  digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftBackwardPin, HIGH);
  digitalWrite(rightForwardPin, HIGH);
  digitalWrite(rightBackwardPin, LOW);
}

void right(){
  // Turn the car to the right
  digitalWrite(leftForwardPin, HIGH);
  digitalWrite(leftBackwardPin, LOW);
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, HIGH);
}

void stop(){
  // Stop the car
  digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftBackwardPin, LOW);
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightBackwardPin, LOW);
}
