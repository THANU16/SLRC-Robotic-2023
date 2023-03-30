int IRpin1 = 13;
int IRpin2 = 12;
int IRpin3 = 11;
int IRpin4 = 10;
int IRpin5 = 9;

//black => 1, white => 0
void setup() {
  Serial.begin(9600);                             // start the serial port
  pinMode(IRpin1, INPUT);
  pinMode(IRpin2, INPUT);
  pinMode(IRpin3, INPUT);
  pinMode(IRpin4, INPUT);
  pinMode(IRpin5, INPUT);
}

void loop() {
  int value1 = digitalRead(IRpin1);       
  int value2 = digitalRead(IRpin2); 
  int value3 = digitalRead(IRpin3); 
  int value4 = digitalRead(IRpin4); 
  int value5 = digitalRead(IRpin5);  
  Serial.print("1 =>"); 
  Serial.println(value1); 
  Serial.print("2 =>");   
  Serial.println(value2);
  Serial.print("3 =>"); 
  Serial.println(value3);
  Serial.print("4 =>"); 
  Serial.println(value4);
  Serial.print("5 =>"); 
  Serial.println(value5);   
  delay(1000);            
                                      
  
}
