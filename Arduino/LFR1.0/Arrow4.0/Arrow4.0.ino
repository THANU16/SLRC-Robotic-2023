//Motor Left
#define ENA_L 6 // Enable/speed motor Front Left D10->ENA L298N Front Side
#define IN_L_1 52 // L298N #2 in 1 motor Front Left D8->IN1 L298N Front Side
#define IN_L_2 53 // L298N #2 in 2 motor Front Left D9->IN2 L298N Front Side

//Motor Right
#define ENA_R 5  // Enable/speed motor Back Right  D6->ENB L298N Back Side
#define IN_R_1 51 // L298N #1 in 3 motor Back Right D4->IN3 L298N Back Side
#define IN_R_2 50  // L298N #1 in 4 motor Back Right D7->IN4 L298N Back Side


float pTerm, iTerm, dTerm;
int error;
int previousError;
float kp = 15; //11, 20, 10
float ki = 0;
float kd = 7; //11, 5, 3
float output;
int integral, derivative;
boolean arrowIsFound = false;
boolean arrowIsDetected = false;
  
int irSensors[] = {13,12,11,10,9,8,7,4,3}; //IR sensor pins
int irReadings[9];


int motorLeftnewSpeed;
int motorRightnewSpeed;
int speedup =45;
int motorRightSpeed = speedup; //Default 70 , 60
int motorLeftSpeed = speedup; //Default 120

int initialSpeed = 100;

int turnSpeed = 160;



const float timeFact = 5.5; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar




void setup() {
  //Declare all IR sensors as inputs
  Serial.begin(9600);
  for (int pin = 0; pin < 9; pin++) {
    int pinNum = irSensors[pin];
    pinMode(pinNum, INPUT);
  }
  
  pinMode(ENA_L, OUTPUT);
  pinMode(ENA_R, OUTPUT);

  pinMode(IN_L_1, OUTPUT);
  pinMode(IN_L_2, OUTPUT);

  pinMode(IN_R_1, OUTPUT);
  pinMode(IN_R_2, OUTPUT);

initialStartCar(35);
   
  

}

void loop() {
  //Put all of our functions here
//  delay(1000);
  readIRSensors();
  calculateError();
//  Serial.println(error);
//  
  while(error==103){
      readIRSensors();
      calculateError();
      initialStartCar(15);
      forward(30);
      arrowIsDetected == false;
  } 

//  if(irReadings[0] == 1 || irReadings[1] == 1 || irReadings[2] == 1 || irReadings[3] == 1 || irReadings[4] == 1 || irReadings[5] == 1){
//    stop(1000);
//    arrowIsDetected = true;
//  }
    if (!arrowIsDetected){
      reverse(100);
      stop(1000);
      arrowIsDetected = true;
    }


  while(!arrowIsFound){
     
      Serial.println("loop start");
//      initialStartCar(30);
      readIRSensors();
      calculateError();
      Serial.println(error);
      if((irReadings[5] == 1 && irReadings[6] == 1) && (irReadings[7] == 0 && irReadings[8] == 0) && error ==0){
        stop(1000); 
        arrowIsFound = true;
      }else{
        useFront();
      }
  }
  initialStartCar(15);
  forward(100);
}

  
//void useLine(){
//  if(error==0){
//      if((irReadings[5] == 1 && irReadings[6] == 1) && (irReadings[7] == 0 || irReadings[8] == 0)){
//        stop(1000);
//        arrowIsFound = true;
//      }else if(irReadings[7] == 1 && irReadings[8] == 1 && irReadings[5] == 1){
//        initialStartCar(15);
//      }else{
//        useFront();
//      }
//  }else{
//    useFront();
//  }
//}


void useFront(){
  if(irReadings[5] == 1){
    useBack();
  }else if(irReadings[7] == 0 && irReadings[8] == 1 && irReadings[5] == 0){
    turnRight();
  }else if(irReadings[7] == 1 && irReadings[8] == 0 && irReadings[5] == 0){
    turnLeft();
  }else{
    useBack();
  }
}


void useBack(){
   if (error<0){
      turnLeft();
      stop(80);
    }else if(error>0 && error<50){
      turnRight();
      stop(80);
    }else if(error == 0) {
//      stop(500);
      initialStartCar(30);
      forward(40);
      Serial.println("Hu 2");
    }else{
      initialStartCar(30);
    }
    
}
void readIRSensors() {
//  delay(1000);
  //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 9; pin++) {
    int pinNum = irSensors[pin];
    irReadings[pin] = digitalRead(pinNum);

    Serial.print(irReadings[pin]);
//    Serial.print(digitalRead(pinNum));
    Serial.print(" ");
  }
  Serial.println();
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
  }else if ((irReadings[0] == 0) && (irReadings[1] == 0) && (irReadings[2] == 0) && (irReadings[3] == 0) && (irReadings[4] == 0) && (irReadings[5] == 0) && (irReadings[6] == 0)&& (irReadings[7] == 0) && (irReadings[8] == 0)) {
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

void pidCalculations() {
  pTerm = kp * error;
  integral += error;
  iTerm = ki * integral;
  derivative = error - previousError;
  dTerm = kd * derivative;
  output = pTerm + iTerm + dTerm;
  previousError = error;
}

void changeMotorSpeed() {
  //Change motor speed of both motors accordingly
  motorLeftnewSpeed = motorLeftSpeed + output;
  Serial.println(motorLeftnewSpeed);
  motorRightnewSpeed = motorRightSpeed - output;
    Serial.println(motorRightnewSpeed);
  //Constrain the new speed of motors to be between the range 0-255
  constrain(motorLeftnewSpeed, 0, 255);
  constrain(motorRightnewSpeed, 0, 255);

  if(motorLeftnewSpeed<5){
    motorLeftnewSpeed=5;
  }else if(motorRightnewSpeed<5){
    motorRightnewSpeed = 5;
  }else if(motorLeftnewSpeed== speedup || motorRightnewSpeed == speedup ){  // if you change motor speed. then you must change the if condition
    initialStartCar(5);
  }
  
  //Set new speed, and run motors in forward direction
  Serial.println(motorLeftnewSpeed);
  Serial.println(motorRightnewSpeed);
  analogWrite(ENA_L, motorLeftnewSpeed); //Left Motor Speed
  analogWrite(ENA_R, motorRightnewSpeed); //Right Motor Speed

  
  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW);

  digitalWrite(IN_R_1, HIGH);
  digitalWrite(IN_R_2, LOW);

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
  
//  analogWrite(ENA_L, motorLeftnewSpeed); //Left Motor Speed
//  analogWrite(ENA_R, motorRightnewSpeed); //Right Motor Speed

  analogWrite(ENA_L, 30); //Left Motor Speed
  analogWrite(ENA_R, 30); //Right Motor Speed

  
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
  analogWrite(ENA_R, 120);

  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH); 
  analogWrite(ENA_L, 120);

  delay(80);
}

void turnLeft()
{
  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  analogWrite(ENA_R, 120);

  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW); 
  analogWrite(ENA_L, 120);
  
  delay(80);

}

void reverse(int x){
  analogWrite(ENA_L, 160); //Left Motor Speed
  analogWrite(ENA_R, 160); //Right Motor Speed

  
  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH);

  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  delay(x);
}
