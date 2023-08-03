//Motor Left
#define ENA_L 6 // Enable/speed motor Front Left D10->ENA L298N Front Side
#define IN_L_1 52 // L298N #2 in 1 motor Front Left D8->IN1 L298N Front Side
#define IN_L_2 53 // L298N #2 in 2 motor Front Left D9->IN2 L298N Front Side

//Motor Right
#define ENA_R 5  // Enable/speed motor Back Right  D6->ENB L298N Back Side
#define IN_R_1 51 // L298N #1 in 3 motor Back Right D4->IN3 L298N Back Side
#define IN_R_2 50  // L298N #1 in 4 motor Back Right D7->IN4 L298N Back Side

// Sensor array pin definitions
#define S1 4
#define S2 2
#define S3 3
#define S4 A3
#define S5 A4
#define S6 A5
#define S7 A6
#define S8 A7



int error;
int frontError =0;
boolean arrowIsDetacted = true;
boolean arrowIsFound = false;
boolean arrowIsFinished = true;
  
int irSensors[] = {13,12,11,10,9,8}; //IR sensor pins
int FrontIrSensors[] = {4,2,3};


int frontIr = 4;
int irReadings[6];
int frontIrReadings[8];


int motorLeftnewSpeed;
int motorRightnewSpeed;
int speedup =45;
int motorRightSpeed = speedup; //Default 70 , 60
int motorLeftSpeed = speedup; //Default 120

int initialSpeed = 100;

int turnSpeed = 160;

float setPoint = 1;

const float timeFact = 5.5; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar




void setup() {
  //Declare all IR sensors as inputs
  Serial.begin(9600);
 readIRSensors();
  
  pinMode(ENA_L, OUTPUT);
  pinMode(ENA_R, OUTPUT);

  pinMode(IN_L_1, OUTPUT);
  pinMode(IN_L_2, OUTPUT);

  pinMode(IN_R_1, OUTPUT);
  pinMode(IN_R_2, OUTPUT);

  // Initialize sensor array pins
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);

initialStartCar(30);
}

void loop() {
  //Put all of our functions here
  readIRSensors();
  calculateError();
  calculateFrontError();

//  useFront();

  
  Serial.println(error);
  if (frontError==103 && error == 103 && arrowIsDetacted){
    arrowIsDetacted = false;
    arrowIsFinished = true;
  }
  while(frontError==103 && error == 103 && arrowIsFinished){
      readIRSensors();
      calculateError();
      calculateFrontError();
      initialStartCar(30);
  } 

  if(arrowIsFinished){
    for (int pin = 0; pin < 3; pin++) {
      if(irReadings[pin] == 1){
        arrowIsDetacted == true;
        arrowIsFinished == false;
        break;
      }
    }   
  }
  
  

  while(!arrowIsFound){
    readIRSensors();
    calculateError();
    calculateFrontError();
    if (error ==0 && frontError == 0){
      arrowIsFound == true;
      initialStartCar(30);
      break;
    }else{
      useFront();
    }
  }
}
  
void useFront(){
  if( error == 103){
    if (frontError == 0){
        initialStartCar(50);
    }
    else if( frontError<0){
      turnLeft();
      stop(50);
    }
    else if(frontError>0 && frontError < 50){
      turnRight();
      stop(50);
    }
  }
  else if(-5<= error && error <= 5){
    useFrontMiddle();
  }
}

void useMiddle(){
   if (error<0){
      turnLeft();
      stop(50);
    }else if(error>0 && error<50){
      turnRight();
      stop(50);
    }else if(error == 0) {
      initialStartCar(30);
    }
}

void useFrontMiddle() {
  if(frontError == 0){
    if (error<0){
      turnLeft();
      stop(50);
    }
    else if(error>0 && error<50){
      turnRight();
      stop(50);
    }
    else if(error == 0) {
      initialStartCar(30);
    }   
  }
  else if (frontError<0) {
    if (error<0){
      turnRight();
      stop(50);
      turnRight();
      stop(50);
    }
    else if(error>0 && error<50){
      turnLeft();
      stop(50);
      turnLeft();
      stop(50);
    }
    else if(error == 0) {
      turnRight();
      stop(50);
    }   
  }
  else if (frontError>0) {
    if (error<0){
      turnLeft();
      stop(50);
      turnLeft();
      stop(50);
    }
    else if(error>0 && error<50){
      turnRight();
      stop(50);
      turnRight();
      stop(50);
    }
    else if(error == 0) {
      turnLeft();
      stop(50);
    }   
  }
}

void readIRSensors() {
  //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 6; pin++) {
    int pinNum = irSensors[pin];
    irReadings[pin] = digitalRead(pinNum);
    Serial.print(irReadings[pin]);
    Serial.print(" ");
  }

  Serial.println();

//  delay(1000);

  for (int pin = 0; pin < 3; pin++) {
    int pinNum = FrontIrSensors[pin];
    frontIrReadings[pin] = digitalRead(pinNum);
    Serial.print(frontIrReadings[pin]);
    Serial.print(" ");
  }
//  
//  Serial.println();
//  frontIrReadings[0] = digitalRead(S1);
//  Serial.print(frontIrReadings[0]);
//  Serial.print(" ");
//  
//  frontIrReadings[1] = digitalRead(S2);
//  Serial.print(frontIrReadings[1]);
//  Serial.print(" ");
//  
//  frontIrReadings[2] = digitalRead(S3);
//  Serial.print(frontIrReadings[2]);
//  Serial.print(" ");
//  
//  frontIrReadings[3] = digitalRead(S4);
//  Serial.print(frontIrReadings[3]);
//  Serial.print(" ");
//  
//  frontIrReadings[4] = digitalRead(S5);
//  Serial.print(frontIrReadings[4]);
//  Serial.print(" ");
//  
//  frontIrReadings[5] = digitalRead(S6);
//  Serial.print(frontIrReadings[5]);
//  Serial.print(" ");
//  
//  frontIrReadings[6] = digitalRead(S7);
//  Serial.print(frontIrReadings[6]);
//  Serial.print(" ");
//  
//  frontIrReadings[7] = digitalRead(S8);
//  Serial.print(frontIrReadings[7]);
//  Serial.print(" ");
//  Serial.println();
//delay(1000);
}


void calculateError() {
  //Determine an error based on the readings
  if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 1)) {   //turn right
    error = 4;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 1) && (irReadings[4] == 1)) {   //turn right
    error = 3;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 1) && (irReadings[4] == 0)) {    //turn right
    error = 2;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 1) && (irReadings[3] == 1) && (irReadings[4] == 0)) {
    error = 1;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 1) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = 0;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 1) && (irReadings[2] == 1) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -1;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 1) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -2;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -3;
  } else if ((irReadings[0] == 1) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = -4;
  }else if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 1) && (irReadings[3] == 0) && (irReadings[4] == 0)) { //SHarp LEFT
    error = 100;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 1) && (irReadings[3] == 1) && (irReadings[4] == 1)) { //SHarp Right
    error = 101;
  }else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0)) {
    error = 103;
//    error = 0;
//    if (previousError <0) {
//      error = -5;
//    } else {
//      error = 5;
//    }
  } else if ((irReadings[0] == 1) && (irReadings[1] == 1) && (irReadings[2] == 1) && (irReadings[3] == 1) && (irReadings[4] == 1)) {
    error = 104;
  } else if ((irReadings[0] == 0) && (irReadings[1] == 1) && (irReadings[2] == 1) && (irReadings[3] == 1) && (irReadings[4] == 0)) {   //arrow head
    error = 150;
  }
  Serial.print("error =>");
  Serial.println(error);
}

void calculateFrontError(){
  frontError =0;
   // Calculate error (difference between line position and setpoint)
  for (int i = 0; i < 3; i++) {
    if (frontIrReadings[i] == 1) {
      frontError += (i - setPoint);
    }
  }
  if ( frontIrReadings[0] == 0 && frontIrReadings[1] == 0 && frontIrReadings[2] == 0 ){
    frontError = 103;
  }
  Serial.print("frontError =>");
  Serial.println(frontError);
}


void stop(int x) {
  
  analogWrite(ENA_L, motorLeftnewSpeed); //Left Motor Speed
  analogWrite(ENA_R, motorRightnewSpeed); //Right Motor Speed

  
  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, LOW);

  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, LOW);

  delay(x);

}

void forward(int x) {
  
  analogWrite(ENA_L, motorLeftnewSpeed); //Left Motor Speed
  analogWrite(ENA_R, motorRightnewSpeed); //Right Motor Speed

  
  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW);

  digitalWrite(IN_R_1, HIGH);
  digitalWrite(IN_R_2, LOW);

  delay(x);

}

void initialStartCar(int delayTime){
  analogWrite(ENA_L, initialSpeed); //Left Motor Speed
  analogWrite(ENA_R, initialSpeed); //Right Motor Speed

  
  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW);

  digitalWrite(IN_R_1, HIGH);
  digitalWrite(IN_R_2, LOW);
  delay(delayTime);
}

void turnRight()
{
  digitalWrite(IN_R_1, HIGH);
  digitalWrite(IN_R_2, LOW);
  analogWrite(ENA_R, 100);

  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH); 
  analogWrite(ENA_L, 100);

  delay(80);
}

void turnLeft()
{
  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  analogWrite(ENA_R, 100);

  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW); 
  analogWrite(ENA_L, 100);
  
  delay(80);

}

void reverse(int x){
  analogWrite(ENA_L, 100); //Left Motor Speed
  analogWrite(ENA_R, 100); //Right Motor Speed

  
  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH);

  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  delay(x);
}
