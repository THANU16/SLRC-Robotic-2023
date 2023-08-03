// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int frequency = 0;
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

String colour="";

void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
   // Begins serial communication 
  Serial.begin(9600);
}
void loop() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
//  redFrequency = pulseIn(sensorOut, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redFrequency = map(redFrequency, 25, 72, 255, 0);
  
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redFrequency);
  delay(2);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
//  greenFrequency = pulseIn(sensorOut, LOW);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenFrequency = map(greenFrequency, 30, 90, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenFrequency);
  delay(2);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
//  blueFrequency = pulseIn(sensorOut, LOW);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueFrequency = map(blueFrequency, 25, 70, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(blueFrequency);
  delay(2);

  if (redFrequency>50 && greenFrequency<70 && blueFrequency<70){
    colour = "red";
  } else if (redFrequency<70 && greenFrequency>40 && blueFrequency<70){
    colour = "green";
  } else if (redFrequency<70 && greenFrequency<70 && blueFrequency>50){
    colour = "blue";
  } else if (redFrequency>70 && greenFrequency>70 && blueFrequency>70){
    colour = "white";
  } else if (redFrequency<20 && greenFrequency<20 && blueFrequency<20){
    colour = "black";
  }
  Serial.println(colour);
  delay(1000);
}
