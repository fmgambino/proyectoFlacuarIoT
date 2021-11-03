const int ptpin=33;

void ptTEMP();

void setup() 
{ 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  ptTEMP();
}


// PT100 TEMP FUNCION

void ptTEMP(){
    int sum = 0;
    for(int i=0;i<100;i++){
      
    int  valor = analogRead(ptpin);
      sum = sum + analogRead(ptpin); //Almacenos la lectura analogica 
    Serial.print("Lectura Analog= ");
    Serial.println(valor); 
      //buf[i]=analogRead(ptpin); //Almacenos la lectura analogica
      delay(10);
    } 
    float promedio = sum / 100; 
    
    int y = promedio;
    float x = 1000*( y )/9107.0;
    Serial.print("Promedio= ");
    Serial.println(promedio); 
    Serial.print("temperatura= ");
    Serial.println(x); 
    delay(5000);
  }
