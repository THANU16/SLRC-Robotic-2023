#include <QTRSensors.h>

#define NUM_SENSORS  8;  // Define the number of sensors in the array
#define TIMEOUT      2500;  // Define the timeout period in microseconds
#define EMITTER_PIN  2;  // Define the pin number for the IR LED (emitter)



QTRSensorsRC qtrrc((unsigned char[]) {0, 1, 2, 3, 4, 5, 6, 7}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);  // Create a QTRRC object

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize built-in LED as an output

  qtrrc.calibrate();  // Calibrate the sensors
  delay(500);  // Delay for 0.5 seconds after calibration
}

void loop() {
  unsigned int sensorValues[NUM_SENSORS];  // Define an array to store the sensor readings
  qtrrc.read(sensorValues);  // Read the sensor values into the array

  for (int i = 0; i < NUM_SENSORS; i++) {  // Loop through each sensor value
    Serial.print(sensorValues[i]);  // Print the sensor value to the serial monitor
    Serial.print('\t');  // Print a tab character to separate the values
  }

  if (sensorValues[0] < 500) {  // If the first sensor value is below 500, turn on the built-in LED
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // Otherwise, turn off the built-in LED
  }

  Serial.println();  // Print a new line to separate the readings
  delay(100);  // Delay for 0.1 seconds before the next reading
}
