#include <Arduino.h>

// inputs
const int in0 = 14;
const int in1 = 27;
const int in2 = 26;
const int in3 = 25;
/*const int in4 = 32;
const int in5 = 33;
const int in6 = 26;
const int in7 = 25;*/
// outputs
const int ot0 = 5;
const int ot1 = 17;
const int ot2 = 16;
const int ot3 = 4;
/*const int ot5 = 5;
const int ot6 = 18;
const int ot7 = 19;
const int ot8 = 23; */
void setup() {
  pinMode(in0, INPUT);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(in3, INPUT);
 /* pinMode(in4, INPUT);
  pinMode(in5, INPUT);
  pinMode(in6, INPUT);
  pinMode(in7, INPUT);
  pinMode(ot0, OUTPUT);
  pinMode(ot1, OUTPUT);
  pinMode(ot2, OUTPUT);
  pinMode(ot3, OUTPUT); */
  /*pinMode(ot4, OUTPUT);
  pinMode(ot5, OUTPUT);
  pinMode(ot6, OUTPUT);
  pinMode(ot7, OUTPUT);*/
}
void loop() {
 // simple test inputs and outputs
  if (digitalRead(in0))digitalWrite(ot0, 1);
  else digitalWrite(ot0, 0);
  if (digitalRead(in1))digitalWrite(ot1, 1);
  else digitalWrite(ot1, 0);
  if (digitalRead(in2))digitalWrite(ot2, 1);
  else digitalWrite(ot2, 0);
  if (digitalRead(in3))digitalWrite(ot3, 1);
  else digitalWrite(ot3, 0);
  /*if (digitalRead(in5))digitalWrite(ot5, 1);
  else digitalWrite(ot5, 0);
  if (digitalRead(in6))digitalWrite(ot6, 1);
  else digitalWrite(ot6, 0);
  if (digitalRead(in7))digitalWrite(ot7, 1);
  else digitalWrite(ot7, 0);
  if (digitalRead(in8))digitalWrite(ot8, 1);
  else digitalWrite(ot8, 0);*/
}