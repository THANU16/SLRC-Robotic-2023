// Ultrasonic Sensor
#include <HCSR04.h>

  //Motor Left
#define ENA_L 6 // Enable/speed motor Front Left D10->ENA L298N Front Side
#define IN_L_1 52 // L298N #2 in 1 motor Front Left D8->IN1 L298N Front Side
#define IN_L_2 53 // L298N #2 in 2 motor Front Left D9->IN2 L298N Front Side

//Motor Right
#define ENA_R 5  // Enable/speed motor Back Right  D6->ENB L298N Back Side
#define IN_R_1 51 // L298N #1 in 3 motor Back Right D4->IN3 L298N Back Side
#define IN_R_2 50  // L298N #1 in 4 motor Back Right D7->IN4 L298N Back Side

// robot lenth 26cm
//wall distance 60 cm

// initialisation the ultrasonic sensors
//Left
UltraSonicDistanceSensor  hLeft(22,44); // initialize HCSR04 object with trig pin 22 and echo pin 44
//Center
UltraSonicDistanceSensor  hCenter(23,45); 
//Right
//UltraSonicDistanceSensor  hRight(24,46);
//Back
UltraSonicDistanceSensor  hBack(24,46);

int motorLeftnewSpeed;
int motorRightnewSpeed;
int speedup =50;
int motorRightSpeed = speedup; //Default 70 , 60
int motorLeftSpeed = speedup; //Default 120

int initialSpeed = 100;

const float timeFact = 5.83; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar


void setup(){
  Serial.begin(9600);
  
  pinMode(ENA_L, OUTPUT);
  pinMode(ENA_R, OUTPUT);

  pinMode(IN_L_1, OUTPUT);
  pinMode(IN_L_2, OUTPUT);

  pinMode(IN_R_1, OUTPUT);
  pinMode(IN_R_2, OUTPUT);

//  initialStartCar(30);  
}

void loop()
{ 
  int vLeft=hLeft.measureDistanceCm();
  int vCenter=hCenter.measureDistanceCm();
//  int vRight=hRight.measureDistanceCm();
int vBack=hBack.measureDistanceCm();
  Serial.print("left => ") ;
  Serial.print( vLeft );
  Serial.print( "   " ); 
   Serial.print("center => ") ;
  Serial.print( vCenter );
  Serial.print( "   "); 
//   Serial.print("Right => ") ;
//  Serial.println( vRight ); 
//  Serial.println();
  Serial.print("Back => ") ;
  Serial.println( vBack ); 
  Serial.println();


  if (vBack+vCenter >(30)){
    turnLeft();
  }
  else{
    stopM(500);
    turnRight();
    stopM(1000);
  }
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
  
  analogWrite(ENA_L, speedup); //Left Motor Speed
  analogWrite(ENA_R, speedup); //Right Motor Speed

  
  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW);

  digitalWrite(IN_R_1, HIGH);
  digitalWrite(IN_R_2, LOW);

  delay(x);

}

void reverse(){
  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  analogWrite(ENA_R, 100);

  digitalWrite(IN_L_1, LOW);
  digitalWrite(IN_L_2, HIGH); 
  analogWrite(ENA_L, 100);
  delay(500);
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
  delay(10);

// delay(80);
}

void turnLeft()
{
  digitalWrite(IN_R_1, LOW);
  digitalWrite(IN_R_2, HIGH);
  analogWrite(ENA_R, 100);

  digitalWrite(IN_L_1, HIGH);
  digitalWrite(IN_L_2, LOW); 
  analogWrite(ENA_L, 100);
  delay(10);
//  delay(80);
}
