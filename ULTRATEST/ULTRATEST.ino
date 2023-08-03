//UltraSensorTHings
int trigPin[] = {32,36,28}; //Trig Pins
int echoPin[] = {34,38,30}; //EchoPins
int duration[3];
int distance[3];


void setup()
{
for (int pin = 0; pin < 3; pin++) {
    int pinNum = trigPin[pin];
    pinMode(pinNum, OUTPUT);
}
    for (int pin = 0; pin < 3; pin++) {
    int pinNum = echoPin[pin];
    pinMode(pinNum, INPUT);
    }
 Serial.begin(9600);  
 
}



void loop(){

for (int pin = 0; pin < 3; pin++) {
  digitalWrite (trigPin[pin], HIGH);
  delay(50);
  digitalWrite (trigPin[pin], LOW);
  duration[pin]=pulseIn(echoPin[pin],HIGH);
  distance[pin]=(duration[pin]/2)/29.1;

Serial.print("Front:");
Serial.println(distance[0]);
Serial.print("Right:");
Serial.println(distance[1]);
Serial.print("Left:");
Serial.println(distance[2]);

Serial.println("");
Serial.println("");
Serial.println("");
}

delay(1000);
}
