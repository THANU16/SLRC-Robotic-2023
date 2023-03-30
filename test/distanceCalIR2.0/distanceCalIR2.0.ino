#define irPin A0  // the pin to which the IR sensor is connected

void setup() {
  Serial.begin(9600);  // initialize serial communication at 9600 bits per second
}

void loop() {
  int distance = getDistance();  // read the distance from the IR sensor
  Serial.println(distance);  // print the distance to the serial monitor
  delay(500);  // wait for half a second before measuring again
}

int getDistance() {
  int irValue = analogRead(irPin);  // read the analog value from the IR sensor
  float voltage = irValue * 5.0 / 1023.0;  // convert the analog value to voltage (assuming a 5V power supply)
  float distance = 26.5 / (voltage - 0.16);  // convert the voltage to distance (using the equation provided by the manufacturer)
  return int(distance);  // return the distance as an integer value
}
