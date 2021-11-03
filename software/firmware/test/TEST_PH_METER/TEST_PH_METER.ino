const int PhMetroPin = 32; 
int Valor = 0; 
unsigned long int promValor; 
float b;
int buf[10],temp;
void setup() {
 Serial.begin(9600);
}
 
void loop() {
 for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(PhMetroPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 promValor=0;
 for(int i=2;i<8;i++)
 promValor+=buf[i];
 float pHVol=(float)promValor*5.0/4095/6;
 float ph = (3.5*pHVol)+1.70;
 Serial.print("Ph= ");
 Serial.println(ph);
 
 delay(1000);
}
