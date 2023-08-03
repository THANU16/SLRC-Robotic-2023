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

int irSensors[] = {13,12,11,10,9,8,7}; //IR sensor pins
int irReadings[7];


int motorLeftnewSpeed;
int motorRightnewSpeed;
int speedup =45;
int motorRightSpeed = speedup; //Default 70 , 60
int motorLeftSpeed = speedup; //Default 120

int initialSpeed = 60;

int turnSpeed = 160;



const float timeFact = 5.5; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar




void setup() {
  //Declare all IR sensors as inputs
  Serial.begin(9600);
  for (int pin = 0; pin < 7; pin++) {
    int pinNum = irSensors[pin];
    pinMode(pinNum, INPUT);
  }
  
  pinMode(ENA_L, OUTPUT);
  pinMode(ENA_R, OUTPUT);

  pinMode(IN_L_1, OUTPUT);
  pinMode(IN_L_2, OUTPUT);

  pinMode(IN_R_1, OUTPUT);
  pinMode(IN_R_2, OUTPUT);

initialStartCar(30);
   
  

}

void loop() {
  //Put all of our functions here
//  delay(1000);
  Serial.println(error);
  while(error==103){
      initialStartCar(30);
      readIRSensors();
      calculateError();
  }

  boolean arrowIsFound = false;

  while(!arrowIsFound){
    
      int count = 0;
      Serial.println("loop start");
      readIRSensors();
      calculateError();
      for(int i = 0; i <= 4; i++){
        if (irReadings[i] == 1){
          count ++;
        }
      }
    
      if (count >= 2){
        if((irReadings[5] == 1 && irReadings[6] == 1) && (error==0)){
          initialStartCar(30);
          arrowIsFound = true;
        }else if(irReadings[5] == 1 || irReadings[6] == 1){
          while(irReadings[5] == 1 || irReadings[6] == 1){
            reverse(500);
            readIRSensors();
          }
        }
      }else{
        useFront("yes");
      }

      Serial.println("Arrow is found: ");
      Serial.println(arrowIsFound);
  }

  forward(100);
//  if (irReadings[5] == 1 && irReadings[6] == 1 && error == 150) {
//    stop(2000);
//    initialStartCar(30);
//  }
//   if (-5<error<5){
//    if(irReadings[5] == 1 || irReadings[6] == 1){
//      reverse(20);
//    }else{
//    useFront("yes");
//  }
//    
//  }
//  
//  stop(1000);
  
//useFront();


 
}
  


void useFront(String isInitialStartCar){
   if (error<0){
      turnLeft();
      stop(50);
    }else if(error>0 && error<50){
      turnRight();
      stop(50);
    }
//    else if(error == 150){
//      stop(500);
//      initialStartCar(30);
//      forward(100);
//    }
    if (isInitialStartCar == "yes"){
        initialStartCar(30);
    }
    
}
void readIRSensors() {
  delay(1000);
  //Read the IR sensors and put the readings in irReadings array
  for (int pin = 0; pin < 7; pin++) {
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
