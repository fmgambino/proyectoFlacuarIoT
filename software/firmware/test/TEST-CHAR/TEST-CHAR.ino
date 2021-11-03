

void setup() {
  Serial.begin(9600);  //Iniciamos la salida serie
  Serial.println("Iniciando ejemplo");
}

void loop() {
  char buffer[20]=" ";
  char* formato="Hola Mundo";
  sprintf(buffer, formato);
  Serial.println(buffer);
  delay(1000);
}
