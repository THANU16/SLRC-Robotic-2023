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

// initialisation the ultrasonic sensors
//Left
UltraSonicDistanceSensor  hLeft(22,44); // initialize HCSR04 object with trig pin 6 and echo pin 7 
//Center
UltraSonicDistanceSensor  hCenter(23,45); // initialize another HCSR04 object with trig pin 8 and echo pin 9
//Right
UltraSonicDistanceSensor  hRight(24,46); // initialize another HCSR04 object with trig pin 10 and echo pin 11

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

  initialStartCar(30);  
}

void loop()
{ 
  int vLeft=hLeft.measureDistanceCm();
  int vCenter=hCenter.measureDistanceCm();
  int vRight=hRight.measureDistanceCm();
  Serial.print("left => ") ;
  Serial.print( vLeft );
  Serial.print( "   " ); 
   Serial.print("center => ") ;
  Serial.print( vCenter );
  Serial.print( "   "); 
   Serial.print("Right => ") ;
  Serial.println( vRight ); 
  Serial.println();

  if(vLeft<25)
  {
    turnRight();
    initialStartCar(15);
  }
  else if(vCenter<15)
  {
    reverse();
     turnLeft();
     initialStartCar(15);
  }
  else if(vRight<25)
  {
    turnLeft();
    initialStartCar(15);
  }
   else
  {
    forward(50);
  }

}//return curent distance in serial

//  void stopc()
//  {
//      Serial.println("stop");
//      digitalWrite(m1a, LOW);
//      digitalWrite(m1b, LOW);
//      digitalWrite(m2a, LOW);
//      digitalWrite(m2b, LOW); 
//  }
//
//  void goback()
//  {
//      Serial.println("back");
//      digitalWrite(m1a, HIGH);
//      digitalWrite(m1b, LOW);
//      digitalWrite(m2a, HIGH);
//      digitalWrite(m2b, LOW); 
//  }
// void goforward()
//  {
//      Serial.println("forward");
//      digitalWrite(m1a, LOW);
//      digitalWrite(m1b, HIGH);
//      digitalWrite(m2a, LOW);
//      digitalWrite(m2b, HIGH); 
//  }
// void gobackleft()
//  {
//     Serial.println("left");
//    digitalWrite(m1a, LOW);
//    digitalWrite(m1b, HIGH);
//    digitalWrite(m2a, HIGH);
//    digitalWrite(m2b, LOW); 
//  }
//void gobackright()
//  {
//     Serial.println("right");
//    digitalWrite(m1a, HIGH);
//    digitalWrite(m1b, LOW);
//    digitalWrite(m2a, LOW);
//    digitalWrite(m2b, HIGH);
//    
//  }


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
