//Motor Front Left
#define ENA_F_FL 8 // Enable/speed motor Front Left D10->ENA L298N Front Side
#define IN_F_FL_1 50 // L298N #2 in 1 motor Front Left D8->IN1 L298N Front Side
#define IN_F_FL_2 48 // L298N #2 in 2 motor Front Left D9->IN2 L298N Front Side

//Motor Front Right
#define ENB_F_FR 7  // Enable/speed motor Front Right D11->ENB L298N Front Side
#define IN_F_FR_3 51 // L298N #2 in 3 motor Front Right D12->IN3 L298N Front Side
#define IN_F_FR_4 49 // L298N #2 in 4 motor Front Right D13->IN4 L298N Front Side

//Motor Back Left
#define ENA_B_BL 5  // Enable/speed motor Back Left D5->ENA L298N Back Side
#define IN_B_BL_1 52 // L298N #1 in 1 motor Back Left D2->IN1 L298N Back Side
#define IN_B_BL_2 46 // L298N #1 in 2 motor Back Left D3->IN2 L298N Back Side

//Motor Back Right
#define ENB_B_BR 6  // Enable/speed motor Back Right  D6->ENB L298N Back Side
#define IN_B_BR_3 53 // L298N #1 in 3 motor Back Right D4->IN3 L298N Back Side
#define IN_B_BR_4 47 // L298N #1 in 4 motor Back Right D7->IN4 L298N Back Side

int IRpin1 = 26;
int IRpin2 = 27;
int IRpin3 = 28;
int IRpin4 = 29;
int IRpin5 = 30;

int speedCar = 0; // 50 - 255. // calculated with potValue value 
int speed_Coeff = 3; // to use to slow down the speed of internal motors when turning 
int potValue = 0; // potentiometer reading

const float timeFact = 5.5; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar
const float DtimeFact = 50; // valid for 1 degree turn and motor Vcc=5.3V and max speedCar

void setup()
{

  pinMode(ENA_B_BL, OUTPUT);
  pinMode(ENB_B_BR, OUTPUT);
  pinMode(ENA_F_FL, OUTPUT);
  pinMode(ENB_F_FR, OUTPUT);

  pinMode(IN_B_BL_1, OUTPUT);
  pinMode(IN_B_BL_2, OUTPUT);
  pinMode(IN_B_BR_3, OUTPUT);
  pinMode(IN_B_BR_4, OUTPUT);

  pinMode(IN_F_FL_1, OUTPUT);
  pinMode(IN_F_FL_2, OUTPUT);
  pinMode(IN_F_FR_3, OUTPUT);
  pinMode(IN_F_FR_4, OUTPUT);

   //Serial.begin(115200);
   Serial.begin(9600);                             // start the serial port
  pinMode(IRpin1, INPUT);
  pinMode(IRpin2, INPUT);
  pinMode(IRpin3, INPUT);
  pinMode(IRpin4, INPUT);
  pinMode(IRpin5, INPUT);
}

void goAhead(int distance = -1)
{

  digitalWrite(IN_F_FL_1, HIGH);
  digitalWrite(IN_F_FL_2, LOW);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, HIGH);
  digitalWrite(IN_F_FR_4, LOW);
  analogWrite(ENB_F_FR, speedCar);

  digitalWrite(IN_B_BL_1, HIGH);
  digitalWrite(IN_B_BL_2, LOW);
  analogWrite(ENA_B_BL, speedCar);

  digitalWrite(IN_B_BR_3, HIGH);
  digitalWrite(IN_B_BR_4, LOW);
  analogWrite(ENB_B_BR, speedCar);

    if (distance > -1){
    delay(DtimeFact * distance);
    stopRobot();
  }
}

void goBack()
{

  digitalWrite(IN_F_FL_1, LOW);
  digitalWrite(IN_F_FL_2, HIGH);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, LOW);
  digitalWrite(IN_F_FR_4, HIGH);
  analogWrite(ENB_F_FR, speedCar);

  digitalWrite(IN_B_BL_1, LOW);
  digitalWrite(IN_B_BL_2, HIGH);
  analogWrite(ENA_B_BL, speedCar);

  digitalWrite(IN_B_BR_3, LOW);
  digitalWrite(IN_B_BR_4, HIGH);
  analogWrite(ENB_B_BR, speedCar);
}

void turnRight(int degree = -1)
{

  digitalWrite(IN_F_FL_1, HIGH);
  digitalWrite(IN_F_FL_2, LOW);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, LOW);
  digitalWrite(IN_F_FR_4, HIGH);
  analogWrite(ENB_F_FR, speedCar);

  digitalWrite(IN_B_BL_1, LOW);
  digitalWrite(IN_B_BL_2, HIGH);
  analogWrite(ENA_B_BL, speedCar);

  digitalWrite(IN_B_BR_3, HIGH);
  digitalWrite(IN_B_BR_4, LOW); 
  analogWrite(ENB_B_BR, speedCar);

  if (degree > -1){
    delay(timeFact * degree);
    stopRobot();
  }
}

void turnLeft(int degree = -1)
{

  digitalWrite(IN_F_FL_1, LOW);
  digitalWrite(IN_F_FL_2, HIGH);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, HIGH);
  digitalWrite(IN_F_FR_4, LOW);
  analogWrite(ENB_F_FR, speedCar);

  digitalWrite(IN_B_BL_1, HIGH);
  digitalWrite(IN_B_BL_2, LOW);
  analogWrite(ENA_B_BL, speedCar);

  digitalWrite(IN_B_BR_3, LOW);
  digitalWrite(IN_B_BR_4, HIGH);
  analogWrite(ENB_B_BR, speedCar);

  if (degree > -1)
  {
    delay(timeFact * degree);
    stopRobot();
  }
}

void goAheadRight()
{

  digitalWrite(IN_F_FL_1, HIGH);
  digitalWrite(IN_F_FL_2, LOW);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, HIGH);
  digitalWrite(IN_F_FR_4, LOW);
  analogWrite(ENB_F_FR, speedCar / speed_Coeff);

  digitalWrite(IN_B_BL_1, HIGH);
  digitalWrite(IN_B_BL_2, LOW);
  analogWrite(ENA_B_BL, speedCar/ speed_Coeff);

  digitalWrite(IN_B_BR_3, HIGH);
  digitalWrite(IN_B_BR_4, LOW);
  analogWrite(ENB_B_BR, speedCar);
}

void goAheadLeft()
{

  digitalWrite(IN_F_FL_1, HIGH);
  digitalWrite(IN_F_FL_2, LOW);
  analogWrite(ENA_F_FL, speedCar / speed_Coeff);

  digitalWrite(IN_F_FR_3, HIGH);
  digitalWrite(IN_F_FR_4, LOW);
  analogWrite(ENB_F_FR, speedCar);

  digitalWrite(IN_B_BL_1, HIGH);
  digitalWrite(IN_B_BL_2, LOW);
  analogWrite(ENA_B_BL, speedCar );

  digitalWrite(IN_B_BR_3, HIGH);
  digitalWrite(IN_B_BR_4, LOW);
  analogWrite(ENB_B_BR, speedCar/ speed_Coeff);
}

void goBackRight()
{

  digitalWrite(IN_F_FL_1, LOW);
  digitalWrite(IN_F_FL_2, HIGH);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, LOW);
  digitalWrite(IN_F_FR_4, HIGH);
  analogWrite(ENB_F_FR, speedCar / speed_Coeff);

  digitalWrite(IN_B_BL_1, LOW);
  digitalWrite(IN_B_BL_2, HIGH);
  analogWrite(ENA_B_BL, speedCar);

  digitalWrite(IN_B_BR_3, LOW);
  digitalWrite(IN_B_BR_4, HIGH);
  analogWrite(ENB_B_BR, speedCar / speed_Coeff);
}

void goBackLeft()
{

  digitalWrite(IN_F_FL_1, LOW);
  digitalWrite(IN_F_FL_2, HIGH);
  analogWrite(ENA_F_FL, speedCar / speed_Coeff);

  digitalWrite(IN_F_FR_3, LOW);
  digitalWrite(IN_F_FR_4, HIGH);
  analogWrite(ENB_F_FR, speedCar );

  digitalWrite(IN_B_BL_1, LOW);
  digitalWrite(IN_B_BL_2, HIGH);
  analogWrite(ENA_B_BL, speedCar / speed_Coeff);

  digitalWrite(IN_B_BR_3, LOW);
  digitalWrite(IN_B_BR_4, HIGH);
  analogWrite(ENB_B_BR, speedCar);
}

void stopRobot()
{

  digitalWrite(IN_F_FL_1, LOW);
  digitalWrite(IN_F_FL_2, LOW);
  analogWrite(ENA_F_FL, speedCar);

  digitalWrite(IN_F_FR_3, LOW);
  digitalWrite(IN_F_FR_4, LOW);
  analogWrite(ENB_F_FR, speedCar);

  digitalWrite(IN_B_BL_1, LOW);
  digitalWrite(IN_B_BL_2, LOW);
  analogWrite(ENA_B_BL, speedCar);

  digitalWrite(IN_B_BR_3, LOW);
  digitalWrite(IN_B_BR_4, LOW);
  analogWrite(ENB_B_BR, speedCar);
}

void loop()
{
  potValue = 800;
  speedCar = map(potValue, 0, 1023, 0, 255);
  if (speedCar < 50) {
    speedCar = 0;
  }

  delay(3000);
//
//    
//  goAheadLeft();
//  delay(2000);

//  turnRight(180);
//  delay(3000);
//
//  turnRight(360);
//   delay(3000);
//


  goAhead(10);
  delay(3000);

//   turnLeft(180);
//  delay(3000);
//
//   turnLeft(360);
//  delay(3000);
//
//  turnLeft(180);
//  delay(3000);
//
//  turnLeft(360);
//  delay(6000);

//  goAhead();
//  delay(1000);
//  stopRobot();
//
//  turnLeft();
//  delay(2000);
//  stopRobot();
//  
//  goBack();
//  delay(1000);
//  stopRobot();
//
//  goAhead();
//  delay(1000);
//  stopRobot();
//
//  turnRight();
//  delay(2000);
//  stopRobot();
//
//   goBack();
//  delay(1000);
//  stopRobot();
//
//  goAheadRight();
//  delay(1000);
//  stopRobot();
//
//  goAheadLeft();
//  delay(1000);
//  stopRobot();
//
//  goBackRight();
//  delay(2000);
//  stopRobot();
//
//  goBackLeft();
//  delay(2000);
//  stopRobot();
//
//  delay(6000);
}
