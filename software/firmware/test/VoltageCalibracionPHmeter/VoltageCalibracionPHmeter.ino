void setup() 
{ 
  Serial.begin(9600);
  pinMode(32, INPUT); 
} 
 
void loop() 
{ 
  int val = analogRead(32);
  float volt = float(val) * 5.0 / 1024/6;
  volt=(3.5*volt)+2.0;
  Serial.println(volt); 
 // delay(500); 

 // float Po = 7 - ((2.5 - volt) / 0.18);
  //Serial.print("\tPH: ");
  //Serial.println(Po, 3);
  delay(1000);
}
