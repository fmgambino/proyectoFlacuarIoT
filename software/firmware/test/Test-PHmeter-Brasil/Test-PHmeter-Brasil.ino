const int ph_pin = 32; //This is the pin number connected to Po

void setup() {
  Serial.begin(9600);
  Serial.println("         Projeto basico");
  Serial.println("www.youtube.com/c/projetobasicos");
  }

void loop() {
  int measure = analogRead(ph_pin);
  Serial.print("Measure: ");
  Serial.print(measure);

  double voltage = 5 / 4095.0 * measure; //classic digital to voltage conversion
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 3);

  // PH_step = (voltage@PH7 - voltage@PH4) / (PH7 - PH4)
  // PH_probe = PH7 - ((voltage@PH7 - voltage@probe) / PH_step)
  float Po = 12 + ((1.5 - voltage) / 0.18);
  Serial.print("\tPH: ");
  Serial.print(Po, 3);

  Serial.println("");
  delay(2000);
}
