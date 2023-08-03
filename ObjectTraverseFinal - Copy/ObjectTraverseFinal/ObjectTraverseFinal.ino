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
float kp = 15; //11, 20
float ki = 0;
float kd = 2; //11, 5
float output;
int integral, derivative;

int irSensors[] = {13,12,11,10,9}; //IR sensor pins
int irReadings[5];


int motorLeftnewSpeed;
int motorRightnewSpeed;
int speedup =50;
int motorRightSpeed = speedup; //Default 70 , 60
int motorLeftSpeed = speedup; //Default 120

int initialSpeed = 100;

int turnSpeed = 160;

int mode = 1;

const float timeFact = 5.83; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar


//UltraSensorTHings
int trigPin[] = {30,36,34}; //Trig Pins
int echoPin[] = {31,37,35}; //EchoPins
int duration[3];
int distance[3];


void setup() {
  //Declare all IR sensors as inputs
  Serial.begin(9600);

  
  for (int pin = 0; pin < 3; pin++) {
    int pinNum = irSensors[pin];
    pinMode(pinNum, INPUT);
     }

  for (int pin = 0; pin < 3; pin++) {
    int pinNum = trigPin[pin];
    pinMode(pinNum, OUTPUT);
    }
    for (int pin = 0; pin < 3; pin++) {
    int pinNum = echoPin[pin];
    pinMode(pinNum, INPUT);
    }
  
  pinMode(ENA_L, OUTPUT);
  pinMode(ENA_R, OUTPUT);

  pinMode(IN_L_1, OUTPUT);
  pinMode(IN_L_2, OUTPUT);

  pinMode(IN_R_1, OUTPUT);
  pinMode(IN_R_2, OUTPUT);

//initialStartCar(30);
   
}

void loop() {
  int largestdistance = 0;
  int leastdistance= 20;
  int largestindex = 0;
  int shortindex=0;

  int loopcount;
  
  boolean isReached= false;
  for (int pin = 0; pin < 3; pin++) {
    digitalWrite (trigPin[pin], HIGH);
    delay(5);
    digitalWrite (trigPin[pin], LOW);
    duration[pin]=pulseIn(echoPin[pin],HIGH);
    distance[pin]=(duration[pin]/2)/29.1;
    Serial.println(distance[pin]);
    
    if(leastdistance > distance[pin]){
      leastdistance =distance[pin] ;
      shortindex = pin;
      isReached = true;
    }
     
    if(largestdistance < distance[pin]){
      largestindex = pin;
      largestdistance =distance[pin] ;
      
    }
  }
  
  Serial.println();
//  if(!isReached){
//    initialStartCar(30);
//  }
//  else{
//    reverse(100);
//    if(largestindex==0){
//    initialStartCar(30);
//   }
//   else if(largestindex==1){
//    turnRight();
//   }
//   else{
//    turnLeft();
//    } 
//  }

 if(!isReached){
    initialStartCar(20);
    loopcount = 0;
//    stopM(100);
  }
  else{
//    stopM(30);
    reverse(80);
//    stopM(100);
    
    if(largestindex==0 && shortindex==1){
    turnLeft(30);
    stopM(30);
    initialStartCar(30);
    loopcount++;

       if (loopcount == 6){
      stopM(2000);
      reverse(120);
      turnRight(60);
      loopcount = 0 ;
    }
    
   } else if (largestindex==0 && shortindex==2){
    turnRight(30);
    stopM(30);
    initialStartCar(30);
    loopcount++;

    if (loopcount == 6){
      stopM(2000);
      reverse(120);
      turnLeft(60);
      loopcount = 0 ;
    }
    
    }
   
   else if(largestindex==1 && (shortindex==0 || shortindex==2)){
    turnRight(30);
    stopM(30);
    initialStartCar(30);
    stopM(30);
   } else if(largestindex==2 && (shortindex==0 || shortindex==1)){
    turnLeft(30);
    stopM(30);
    initialStartCar(30);
    stopM(30);
   }
   
  }

  if ((distance[1] <20) && (distance[2] <20) && (distance[0] >20)) {
    stopM(3000);
    do {
    stopM(500);
    initialStartCar(30);
    for (int pin = 0; pin < 3; pin++) {
    digitalWrite (trigPin[pin], HIGH);
    delay(5);
    digitalWrite (trigPin[pin], LOW);
    duration[pin]=pulseIn(echoPin[pin],HIGH);
    distance[pin]=(duration[pin]/2)/29.1;
    }
    } while ((distance[0]>20) && (distance[1] >8) && (distance[2]>8)) ;
  }

//  stopM(200);
  
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

void stopM(int x) {
  
  analogWrite(ENA_L, motorLeftnewSpeed); //Left Motor Speed
  analogWrite(ENA_R, motorRightnewSpeed); //Right Motor Speed

  
  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, LOW);

  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, LOW);

  delay(x);

}

void forward(int x) {
  
  analogWrite(ENA_L, initialSpeed); //Left Motor Speed
  analogWrite(ENA_R, initialSpeed); //Right Motor Speed

  
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

void turnRight(int x)
{
  digitalWrite(IN_R_1, HIGH);
  digitalWrite(IN_R_2, LOW);
  analogWrite(ENA_R, 100);

  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH); 
  analogWrite(ENA_L, 100);

 delay(x);
}

void turnLeft(int x)
{
  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  analogWrite(ENA_R, 100);

  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW); 
  analogWrite(ENA_L, 100);
  
  delay(x);
}

void reverse(int x) {
  
  analogWrite(ENA_L, initialSpeed); //Left Motor Speed
  analogWrite(ENA_R, initialSpeed); //Right Motor Speed

  
  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH);

  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);

  delay(x);

}
