// LDR conectado a GPIO 33
const int temp = 33;
const int ph = 32;
// Almacenamiento del valor de puerto (Rango de 0-4095)
int tValor = 0;
int phValor = 0;
void setup() {
  Serial.begin(115200);
  delay(1000);
}
void loop() {
  // Lectura del valor en cada vuelta del bucle
  tValor = analogRead(temp);
  phValor = analogRead(temp);
  Serial.print("Temp: ");  //Envío del valor al puerto serie
  Serial.println(tValor);
  Serial.print("Ph: ");  //Envío del valor al puerto serie
  Serial.println(phValor);
  delay(3000);
}
