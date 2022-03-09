#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <WiFiManager.h>
#include <Separador.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#include <SPI.h>
#include <Wire.h>     // libreria para bus I2C
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306
 
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto


const unsigned char PROGMEM logo_flacuariot [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x01, 0xEF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFC, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x78, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x7F, 0xCC, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0xC3, 0x8C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x03, 0x00, 0xCC, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x02, 0x60, 0x4C, 0x06, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x06, 0x00, 0x48, 0x06, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, 0x4C, 0x04, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x03, 0x81, 0xCC, 0x04, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0xFF, 0x8C, 0x0C, 0x00, 0x18, 0xE0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x7E, 0xFC, 0x08, 0x00, 0x1E, 0x70, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x78, 0x18, 0x00, 0x07, 0x30, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x98, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x30, 0x00, 0x39, 0x98, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x60, 0x00, 0x38, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0xC0, 0x00, 0x0C, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC8, 0x1F, 0xFD, 0x80, 0x00, 0x8C, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x1F, 0xFF, 0x00, 0x01, 0xC4, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x02, 0x00, 0x01, 0xC4, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x18, 0x0E, 0x00, 0x00, 0x00, 0xCC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1F, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,
0x00, 0x03, 0xFE, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x7F, 0xF8, 0x00,
0x00, 0x03, 0xFF, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x7F, 0xF8, 0x00,
0x00, 0x03, 0xFF, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x7F, 0xF8, 0x00,
0x00, 0x03, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x38, 0x1C, 0x03, 0xC0, 0x00, 0x03, 0x80, 0x19, 0xC0, 0x70, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x38, 0x7F, 0x07, 0xE1, 0xC7, 0x8F, 0xE3, 0xF9, 0xC1, 0xFC, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x38, 0xFF, 0x0F, 0xF1, 0xC7, 0x9F, 0xF3, 0xF9, 0xC3, 0xFE, 0x07, 0x80, 0x00,
0x00, 0x03, 0xFC, 0x38, 0xE7, 0x9E, 0x71, 0xC7, 0x9C, 0xF3, 0xF9, 0xC3, 0x9E, 0x07, 0x80, 0x00,
0x00, 0x03, 0xFE, 0x38, 0x07, 0x9E, 0x79, 0xC7, 0x80, 0x73, 0xC1, 0xC7, 0x8E, 0x07, 0x80, 0x00,
0x00, 0x03, 0xFE, 0x38, 0x0F, 0x9C, 0x01, 0xC7, 0x80, 0xF3, 0xC1, 0xC7, 0x8E, 0x07, 0x80, 0x00,
0x00, 0x03, 0xC0, 0x38, 0x7F, 0x9C, 0x01, 0xC7, 0x8F, 0xF3, 0xC1, 0xC7, 0x0E, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x38, 0xFF, 0x9C, 0x01, 0xC7, 0x9F, 0xF3, 0xC1, 0xC7, 0x0E, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x39, 0xE7, 0x9C, 0x01, 0xC7, 0x9C, 0x73, 0xC1, 0xC7, 0x8E, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x39, 0xE7, 0x9C, 0x79, 0xC7, 0x3C, 0x73, 0xC1, 0xC7, 0x8E, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x39, 0xE7, 0x9E, 0x71, 0xEF, 0x3C, 0xF3, 0xC1, 0xC3, 0x9E, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x38, 0xFF, 0x8F, 0xF1, 0xFF, 0x9F, 0xF3, 0xC1, 0xC3, 0xFE, 0x07, 0x80, 0x00,
0x00, 0x03, 0x80, 0x38, 0xFF, 0x87, 0xE0, 0xFF, 0x9F, 0xF3, 0xC1, 0xC1, 0xFC, 0x07, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0x80, 0x60, 0x06, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//*********************************
//*********** CONFIG **************
//*********************************

//#define WIFI_PIN 17
#define LED 2 //On Board LED
#define bomba 17 // Rele Bomba
#define pficador 16 //Rele Purificador
#define calentador 4 // Rele Calentador de Agua

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
const int PhMetroPin = 32; 
const int ptpin=33;
const int nivpin=14;

//PH METETRO - CONFIG
int Valor = 0; 
unsigned long int promValor; //Variable para almacenar 10 muestras
float b;
int buf[10],phTemp;

//NIVEL DE AGUA CONFIG
char* estado;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8; //Resolution 8, 10, 12, 15 

const int tempchannel = 0;

//estos datos deben estar configurador también en las constantes de tu panel
// NO USES ESTOS DATOS PON LOS TUYOS!!!!
const String serial_number = "797171";
const String insert_password = "285289";
const String get_data_password = "420285";
const char*  server = "flacuariot.com";

//MQTT
const char *mqtt_server = "broker.emqx.io";
const int mqtt_port = 8883;

//no completar, el dispositivo se encargará de averiguar qué usuario y qué contraseña mqtt debe usar.
char mqtt_user[20] = "";
char mqtt_pass[20] = "";

const int expected_topic_length = 26;

WiFiManager wifiManager;
WiFiClientSecure client;
PubSubClient mqttclient(client);
WiFiClientSecure client2;

Separador s;




//************************************
//***** DECLARACION FUNCIONES ********
//************************************
bool get_topic(int length);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void send_mqtt_data();
void send_to_database();
void phMeter();
void ptTEMP();
void nivelAgua();
void myOled();
void oledWiFi();
void oledWiFiConect();



//*************************************
//********      GLOBALS         *******
//*************************************
bool topic_obteined = false;
char device_topic_subscribe [40];
char device_topic_publish [40];
char msg[25];
float temp;
float hum;
int niv;
int buffer;
float ph;
long milliseconds = 0;
byte sw1 = 0;
byte sw2 = 0;
byte slider = 0;



void setup() {

  Wire.begin();         // inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // inicializa pantalla con direccion 0x3C
  
  oled.stopscroll();
  oled.clearDisplay();
  oled.drawBitmap(0, 0, logo_flacuariot, 128, 64, WHITE);
  oled.display();
  delay(1500);
  

  pinMode(LED,OUTPUT);
  pinMode(bomba, OUTPUT);
  pinMode(pficador, OUTPUT);
  pinMode(calentador, OUTPUT);
  pinMode(nivpin, INPUT);

  // configurar funcionalidades LED PWM
  ledcSetup(ledChannel, freq, resolution);


  // adjuntar el canal al GPIO2 para ser controlado
  ledcAttachPin(LED, ledChannel);
  ledcAttachPin(calentador, tempchannel);


  Serial.begin(115200);


  //pinMode(WIFI_PIN,INPUT_PULLUP);



  wifiManager.autoConnect("FlacuarIoT Admin");
  oledWiFiConect();
  Serial.println("Conexión a WiFi exitosa!");

  //client2.setCACert(web_cert);

  while(!topic_obteined){
    topic_obteined = get_topic(expected_topic_length);
    delay(5000);
  }


  //set mqtt cert
  //client.setCACert(mqtt_cert);
  mqttclient.setServer(mqtt_server, mqtt_port);
	mqttclient.setCallback(callback);

  oledWiFi();

}

void loop() {

  

  digitalWrite(5,HIGH);

  if (!client.connected()) {
		reconnect();
	}

//si el pulsador wifi esta en low, activamos el acces point de configuración
 /* if ( digitalRead(WIFI_PIN) == LOW ) {
    WiFiManager wifiManager;
    wifiManager.startConfigPortal("FlacuarIoT Admin");
    Serial.println("Conectados a WiFi!!! :)");
  }*/

  //si estamos conectados a mqtt enviamos mensajes
  if (millis() - milliseconds > 5000){
    milliseconds = millis();

    
    

    if(mqttclient.connected()){
      //set mqtt cert
      phMeter(); // Se llama a la Funcion de Calibracion PHmetro
      ptTEMP(); // Se llama a la Funcion de Calibracion Sensor de Temperatura
      myOled(); // Se llama a la Funcion de Config Pantalla Oled 0,96"

      //ENVIO DE CADENA A PHP
      String to_send = String(temp) + "," + String(hum) + "," + String(digitalRead(nivpin)) + "," + String(sw1) + "," + String(sw2); 
      to_send.toCharArray(msg,20);
      mqttclient.publish(device_topic_publish,msg);

     // delay(5000);

      if (ph >=6.5 || ph <=7.5 ){
        send_to_database();
      }
    }

  }

  mqttclient.loop();

}



//************************************
//*********** FUNCIONES **************
//************************************

void callback(char* topic, byte* payload, unsigned int length) {
  String incoming = "";
	Serial.print("Mensaje recibido desde tópico -> ");
	Serial.print(topic);
	Serial.println("");
	for (int i = 0; i < length; i++) {
		incoming += (char)payload[i];
	}
	incoming.trim();
	Serial.println("Mensaje -> " + incoming);

  String str_topic = String(topic);
  String command = s.separa(str_topic,'/',3);
  Serial.println(command);

  if(command=="sw1"){
    Serial.println("Sw1 pasa a estado " + incoming);
      sw1 = incoming.toInt();
      Serial.print("Estado Bomba: ");
      Serial.println(sw1);
    
    if(sw1==0){
        digitalWrite(bomba, LOW);
    } else {
        digitalWrite(bomba, HIGH);
    }
  //  delay(500);
  }

  if(command=="sw2"){
    Serial.println("Estado Purificador " + incoming);
    sw2 = incoming.toInt();
          Serial.print("Estado Prurificador: ");
      Serial.println(sw2);
    
    if(sw2==0){
        digitalWrite(pficador, LOW);
    } else {
        digitalWrite(pficador, HIGH);
    }
   // delay(500);
  }


  if(command=="slider"){
    //Serial.println("Slider pasa a estado " + incoming + );
    slider = incoming.toInt();
    ledcWrite(ledChannel,slider);
  }

  if(command=="slider"){
    Serial.println("Variamos Temperatura " + incoming + "%");
    slider = incoming.toInt();
    ledcWrite(tempchannel,slider);
  }

}

void reconnect() {

	while (!mqttclient.connected()) {
		Serial.print("Intentando conexión MQTT SSL");
		// we create client id
		String clientId = "client_id_57626";
		clientId += String(random(0xffff), HEX);
		// Trying SSL MQTT connection
		if (mqttclient.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
			Serial.println("Connected!");
			// We subscribe to topic

			mqttclient.subscribe(device_topic_subscribe);

		} else {
			Serial.print(" falló :( con error -> ");
			Serial.print(mqttclient.state());
			Serial.println(" Intentamos de nuevo en 5 segundos");

			delay(5000);
		}
	}
}

//función para obtener el tópico perteneciente a este dispositivo
bool get_topic(int length){

  Serial.println("\nIniciando conexión segura para obtener tópico raíz...");

  if (!client2.connect(server, 443)) {
    Serial.println("Error... Falló conexión!");
  }else {
    Serial.println("Conectados a servidor para obtener tópico - ok");
    // Make a HTTP request:
    String data = "gdp="+get_data_password+"&sn="+serial_number+"\r\n";
    client2.print(String("POST ") + "/app/getdata/gettopics" + " HTTP/1.1\r\n" +\
                 "Host: " + server + "\r\n" +\
                 "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +\
                 "Content-Length: " + String (data.length()) + "\r\n\r\n" +\
                 data +\
                 "Connection: close\r\n\r\n");

    Serial.println("Solicitud enviada - ok");

    while (client2.connected()) {
      String line = client2.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers recibidos - ok"); 
        break;
      }
    }

    String line;
    while(client2.available()){
      line += client2.readStringUntil('\n');
    }
    Serial.println(line);
    String temporal_topic = s.separa(line,'#',1);
    String temporal_user = s.separa(line,'#',2);
    String temporal_password = s.separa(line,'#',3);



    Serial.println("El tópico es: " + temporal_topic);
    Serial.println("El user MQTT es: " + temporal_user);
    Serial.println("La pass MQTT es: " + temporal_password);
    Serial.println("La cuenta del tópico obtenido es: " + String(temporal_topic.length()));

    if (temporal_topic.length()==length){
      Serial.println("El largo del tópico es el esperado: " + String(temporal_topic.length()));

      String temporal_topic_subscribe = temporal_topic + "/actions/#";
      temporal_topic_subscribe.toCharArray(device_topic_subscribe,40);
      Serial.println(device_topic_subscribe);
      String temporal_topic_publish = temporal_topic + "/data";
      temporal_topic_publish.toCharArray(device_topic_publish,40);
      temporal_user.toCharArray(mqtt_user,20);
      temporal_password.toCharArray(mqtt_pass,20);

      client2.stop();
      return true;
    }else{
      client2.stop();
      return false;
    }

  }
}


void send_to_database(){

  Serial.println("\nIniciando conexión segura para enviar a base de datos...");

  if (!client2.connect(server, 443)) {
    Serial.println("Falló conexión!");
  }else {
    Serial.println("Conectados a servidor para insertar en db - ok");
    // Make a HTTP request:
    String data = "idp="+insert_password+"&sn="+serial_number+"&temp="+String(temp)+"&hum="+String(hum)+"\r\n";
    client2.print(String("POST ") + "/app/insertdata/insert" + " HTTP/1.1\r\n" +\
                 "Host: " + server + "\r\n" +\
                 "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +\
                 "Content-Length: " + String (data.length()) + "\r\n\r\n" +\
                 data +\
                 "Connection: close\r\n\r\n");

    Serial.println("Solicitud enviada - ok");

    while (client2.connected()) {
      String line = client2.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers recibidos - ok");
        break;
      }
    }


    String line;
    while(client2.available()){
      line += client2.readStringUntil('\n');
    }
    Serial.println(line);
    client2.stop();

    }

  }

  // PH METER FUNCION

  void phMeter()
  {
    for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(PhMetroPin); //Almacenos la lectura analogica
  //delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    phTemp=buf[i];
    buf[i]=buf[j];
    buf[j]=phTemp;
   }
  }
 }
 promValor=0;
 for(int i=2;i<8;i++)
 promValor+=buf[i];
 float pHVol=(float)promValor*5.0/4095/6;
 float ph = (3.5*pHVol)+1.70;
 hum = ph;
 Serial.print("Ph= ");
 Serial.println(hum);
 
 //delay(10);
  }

  // PT100 TEMP FUNCION

void ptTEMP(){
    int sum = 0;
    for(int i=0;i<1000;i++){
      sum = sum + analogRead(ptpin); //Almacenos la lectura analogica 
      //buf[i]=analogRead(ptpin); //Almacenos la lectura analogica
    //  delay(10);
    } 
    int promedio = sum / 1000; 
    
    int y = promedio;
    float x = (1000*( y )/9107.0)+6.5;
    temp = x;

    Serial.print("temperatura= ");
    Serial.println(temp); 
   // delay(10);
  }

  //PANTALLA OLED

  void myOled(){

    oled.clearDisplay();
  oled.setTextSize(1);             // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);        // Draw white text
  oled.setCursor(15,5);             // Columna, Fila
  oled.println(F("MENU PRINCIPAL"));
  oled.setCursor(1,20);  
  

  oled.setTextColor(SSD1306_WHITE);
  oled.print(F("1) TEMP: "));
  oled.print(temp);
  oled.println(F("C"));
  delay(5);
  
  oled.setTextColor(SSD1306_WHITE);        // Draw white text
  oled.setCursor(1,30);  
  oled.print(F("2) PH:    "));
  oled.println(hum);
  delay(5);

  if(digitalRead(nivpin)==1){

  oled.setTextColor(SSD1306_WHITE);        // Draw white text
  oled.setCursor(1,40);  
  oled.print(F("3) NIVEL: OPTIMO    "));
  
  delay(5);

  } else {
  
  oled.setTextColor(SSD1306_WHITE);        // Draw white text
  oled.setCursor(1,40);  
  oled.print(F("3) NIVEL: BAJO      "));
  
  delay(5);
  }

  
  oled.setTextColor(SSD1306_WHITE); 
  oled.setCursor(1,50);  
  oled.println(F("  by FLACUARIOT 2021"));
  delay(50); 
  oled.display();
  }

  // OLED CONECTANDO AL FI WI

  void oledWiFiConect(){

  oled.stopscroll();
  oled.clearDisplay();
  oled.setTextSize(2);             // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE);        // Draw white text
  oled.setCursor(0,10);             // Columna, Fila
  oled.println(F("Conectando"));
  oled.setCursor(0,30);
  oled.println(F("a Wi-Fi..."));
  oled.display();
  delay(5);
  }

  // OLED WI FI CONEXION EXITOSA

  void oledWiFi(){

  oled.stopscroll();
  oled.clearDisplay();
  oled.setTextSize(2);             // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE);        // Draw white text
  oled.setCursor(15,10);             // Columna, Fila
  oled.println(F("Conexion"));
  oled.setCursor(15,30);
  oled.println(F("WI-FI"));

  oled.setCursor(15,50);
  oled.println(F("EXITOSA"));

  oled.display();
  delay(1000);
  oled.clearDisplay();
  }