// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

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
  redFrequency = pulseIn(sensorOut, LOW);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Comparing frequency values to known ranges to identify the color
  if (redFrequency > 390 && redFrequency < 700 && greenFrequency > 530 && greenFrequency < 610 && blueFrequency > 610 && blueFrequency < 670) {
    Serial.println("The color is blue");
  }
  else if (redFrequency > 390 && redFrequency < 700 && greenFrequency > 530 && greenFrequency < 610 && blueFrequency < 610) {
    Serial.println("The color is green");
  }
  else if (redFrequency > 390 && redFrequency < 700 && greenFrequency < 530 && blueFrequency < 610) {
    Serial.println("The color is red");
  }
  else {
    Serial.println("The color could not be identified");
  }
  
  // Adding a delay to avoid interference between readings
  delay(1000);
}
