#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

//Configuramos los datos de acceso a nuestra Red de Wi Fi.
 const char* ssid      = "JUAREZ";
 const char* password  = "CAROLINA342";

// Configuramos las credenciales de nuestro servidor MQTT
const char  *mqtt_server  = "ioticos.org";
const int    mqtt_port    = 1883;
const char  *mqtt_user    = "8Ck0VMBEt7VPXO5";
const char  *mqtt_pass    = "p4l2lTajlrbovU2";
//const char  *root_topic_suscribe   = "v3FP3BCFf6NbVK0/DZtu6y1NhM/actions/sw1";
const char  *root_topic_suscribe   = "v3FP3BCFf6NbVK0/39tIJdVg9Y";
const char  *root_topic_publish   = "v3FP3BCFf6NbVK0/salida"; 

WiFiClient espClient;
PubSubClient client(espClient); // Todas las conecciones que hagas las haras a traves de nuestro cliente wi fi del ESP8266WiFi.

long  lastMsg = 0;
char msg[50]; // array
int value = 0; // enviar dato al servidor

int relay =15; //Defino puerto del Relay Q0.0
int ldr   =A0; //Defino puerto Analógico de la LDR I0.4

// Funcion que recibe Primero a un Topico, Payload = carga util el valor topic temp = 37, tamanos del dato
void callback(char* topic, byte* payload, unsigned int length){
  String incoming = "";
  Serial.print("Mensaje recibido bajo el topico -> ");
  Serial.print(topic);
  Serial.print("\n");

  for(int i=0; i < length; i++){
    incoming += (char)payload[i];
    Serial.print((char)payload[i]);
  }

  incoming.trim();
  Serial.println(" Mensaje  -> " + incoming);

    /*if((char)payload[0] == '1'){
      digitalWrite(2, LOW);
      Serial.println("\n Led Encendido");
    } else {
      digitalWrite(2, HIGH);
      Serial.println("\n Led Apagado");
    }
     Serial.print("\n");*/

     if((char)payload[0] == '1'){
      digitalWrite(relay, LOW);
      Serial.println("\n Relay Activado");
    } else {
      digitalWrite(relay, HIGH);
      Serial.println("\n Relay Apagado");
    }
     Serial.print("\n");
}
void reconnect(){
  while (!client.connected()){ //mientras el cliente no este conectado, haremos intentos de coneccion.
  Serial.println("Intentando Conexion MQTT");
  //Creamos un cliente ID
  String clientID = "iot_1_";
  clientID += String (random(0xffff), HEX);
  //Intentamos conectar
  if (client.connect(clientID.c_str(), mqtt_user, mqtt_pass))
  {
    Serial.println("Conexion a MQTT EXITOSA !");
    //Nos suscribimos
  if (client.subscribe(root_topic_suscribe))  {
    Serial.println("Suscripcion ok");
  }else{
    Serial.println("Fallo Suscripcion");
  }

  } else{
    Serial.println("Fallo la Conexion :( con error -> ");
    Serial.print(client.state());
    Serial.print("Se intentara nuevamente en 5 segundos...");
    delay(5000);
  }

  }
}

  //****************************************************
  //*                                                  *
  //* ************** CONEXIÓN A LA RED WIFI ************
  //*                                                  *
  //* **************************************************

// Funcion creada para a Conexion a la red de Wi Fi
void setup_wifi() {
  Serial.println("");
  Serial.print("Conectando a -> ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  // Buclea mientras el wi fi no este conectado se repite el bucle.
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

// Mensaje de confirmacion de la conexion a la red de Wi Fi
  Serial.println("");
  Serial.println("Conectado a la Red WiFi! ");
  Serial.print("Direccion IP -> ");
  Serial.println(WiFi.localIP());
}

void setup() {
  pinMode(relay, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); // Le decimo al cliente que cuando el servidor nos envie info se ejecuta la funcion callback
}

void loop() {
  //Revisa si el cliente esta o no conectado
  if(client.connected()==false) {
    reconnect();
  }

  //****************************************************
  //*                                                  *
  //* ************** PUBLICAR TOPICO A MQTT ************
  //*                                                  *
  //* **************************************************

  if(client.connected()){
    String str = "El Valor es -> " + String(value);
    str.toCharArray(msg, 50);
    client.publish(root_topic_publish, msg);
    value++;
    Serial.println("Mensaje enviado -> " + String(value));
    delay(500);
  }
    client.loop(); //Mantenemos cliente atento, funcionando.

 /* if(millis() - lastMsg > 2000){
    lastMsg=millis();
    value++; // sumo 1 al entero
    String mes = "Valor -> " + String(value); //transformar value en un string para concatenar a valor. En mes esta el mensaje a enviar.
    mes.toCharArray(msg, 50); //pasar String a un char array y ponerlo adentro de msg.
    client.publish(root_topic_publish, msg);
    Serial.println("Mensaje enviado -> " + String(value));


  }*/


}
