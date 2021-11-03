#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <RTClib.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>     // libreria para bus I2C
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>   // libreria para controlador SSD1306


#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4      // necesario por la libreria pero no usado
#define EEPROM_SIZE 10

Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto
RTC_DS1307 rtc;

//-----------¡¡¡IMPORTANTE!!!------------
//Logo de Electrónica Gambino - EG -
//---------------------------------------

static const unsigned char PROGMEM logo_Eg [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x9F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xF0, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1F, 0x80, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0xE0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xC0, 0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xE0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3F, 0xF0, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7F, 0xFC, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFE, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#define sw_subir 8 //Botón Subir
#define sw_aceptar 9 //Botón Seleccionar Opción
#define sw_bajar 10 //Botón Bajar
//direcciones de memoria de la eeprom
#define eeprom_temp 0
#define eeprom_ph 1
#define eeprom_horario_1_h 2
#define eeprom_horario_1_m 3
#define Nivel 7
#define valor A0
#define SensorPin 5
#define bomba 16
#define resist 17
#define dosificador 18
#define aireador 19

int contador = 1;

//--------------¡¡¡IMPORTANTE!!!---------------------------------
//Cambiar ssid y password por los valores de la red que se usara
//---------------------------------------------------------------

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//---------------------------------------------------------------

//-----------DECLARACIONES DE FUNCIONES-------------------------//


/*
====== Menu Principal =======

*/
void menu_principal(){
    contador=2;
    while(true){
        contador = contadores(contador, 2, 1, 1); //funciona con logica inversa a la numeracion del menu
                                                  //variable: contador, lim_sup: 3, lim_inf: 1, variacion del contador con cada pulso: 1
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);             // Normal 1:1 pixel scale
        oled.setTextColor(SSD1306_WHITE);        // Draw white text
        oled.setCursor(20,5);             // Columna, Fila
        oled.println(F("MENU PRINCIPAL"));
        delay(5);
        oled.drawCircle(4,23,1,WHITE);
        oled.setCursor(7,20);
        seleccion(contador,2);
        oled.println(F("Configuraciones"));
        delay(5);
        oled.drawCircle(4,33,1,WHITE);
        oled.setCursor(7,30);
        seleccion(contador,1);
        oled.println(F("Ver Estado"));
        delay(5);
        oled.display();
        if(contador == 2 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            configuraciones();
        }
         if(contador == 1 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            ver_estado();
        }
        delay(100);
    }
}

/*
======  Seleccion =======
Esta funcion es llamada por varias funciones de pantalla donde se muestre un menu.
Se utiliza para saber cual es la opcion actual en donde se encuentra el usuario,
destacandola cambiando el color de fondo y el color de texto.
*/
void seleccion(int cont,int cont_comparacion){
    if(cont == cont_comparacion)(oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE));
    else(oled.setTextColor(SSD1306_WHITE));
}

int contadores(int n, int lim_sup, int lim_inf, int variacion){
    if(digitalRead(sw_bajar) == 0){
        if(n < (lim_inf + variacion))(n = lim_sup);
        else(n = n - variacion);
    }
    if(digitalRead(sw_subir) == 0){
        if(n > (lim_sup - variacion))(n = lim_inf);
        else(n = n + variacion);
    }
    return n;
}

/*
======= Configuraciones =========
*/

void configuraciones(){
    contador=3;
    while(true){
        contador = contadores(contador, 3, 1, 1); //funciona con logica inversa a la numeracion del menu
                                                  //variable: contador, lim_sup: 3, lim_inf: 1, variacion del contador con cada pulso: 1
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);             // Normal 1:1 pixel scale
        oled.setTextColor(SSD1306_WHITE);        // Draw white text
        oled.setCursor(20,5);             // Columna, Fila
        oled.println(F("CONFIGURAIONES"));
        delay(5);
        oled.drawCircle(4,23,1,WHITE);
        oled.setCursor(7,20);
        seleccion(contador,3);
        oled.println(F("Temperatura"));
        delay(5);
        oled.drawCircle(4,33,1,WHITE);
        oled.setCursor(7,30);
        seleccion(contador,2);
        oled.println(F("NIvel de PH"));
        delay(5);
        oled.drawCircle(4,43,1,WHITE);
        oled.setCursor(7,40);
        seleccion(contador,1);
        oled.println(F("Horarios del"));
        delay(5);
        oled.setCursor(7,50);
        seleccion(contador,1);
        oled.println(F("Aireador"));
        delay(5);
        oled.display();
        if(contador == 3 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            conf_temp();
        }
        if(contador == 2 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            conf_ph();
        }
        if(contador == 1 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            conf_horarios();
        }
        delay(100);
    }
}

void conf_temp(){
    contador = EEPROM.read(eeprom_temp);
    while(true){
        contador = contadores(contador, 40, 0, 1);
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setCursor(2,5);
        oled.setTextColor(SSD1306_WHITE);
        oled.println(F("Elija la temperatura:"));
        delay(5);
        oled.setCursor(45,25);
        oled.println(contador);
        delay(5);
        oled.drawCircle(65,25,1,WHITE);
        oled.setCursor(68,25);
        oled.println(F("C"));
        delay(5);
        oled.setCursor(40,50);
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        oled.println(F("Aceptar"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            EEPROM.write(eeprom_temp,contador);
            EEPROM.commit();
            delay(4);
            configuraciones();
        }
        delay(100);
    }
}

void conf_ph(){
    contador = EEPROM.read(eeprom_ph);
    float contador_f;
    while(true){
        contador = contadores(contador, 140, 0, 1);
        contador_f = contador/10;
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setCursor(2,5);
        oled.setTextColor(SSD1306_WHITE);
        oled.println(F("Elija el nivel de ph:"));
        delay(5);
        oled.setCursor(45,25);
        oled.println(contador_f);
        delay(5);
        oled.setCursor(40,50);
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        oled.println(F("Aceptar"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            EEPROM.write(eeprom_ph,contador);
            EEPROM.commit();
            delay(700);
            configuraciones();
        }
        delay(100);
    }
}

void conf_horarios(){
    contador=4;
    while(true){
        contador = contadores(contador, 4, 0, 1); //funciona con logica inversa a la numeracion del menu
                                                  //variable: contador, lim_sup: 3, lim_inf: 1, variacion del contador con cada pulso: 1
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);             // Normal 1:1 pixel scale
        oled.drawCircle(4,13,1,WHITE);
        oled.setCursor(7,10);
        seleccion(contador,4);
        oled.println(F("ENCENDIDO 1"));
        delay(5);
        oled.drawCircle(4,23,1,WHITE);
        oled.setCursor(7,20);
        seleccion(contador,3);
        oled.println(F("APAGADO 1"));
        delay(5);
        oled.drawCircle(4,33,1,WHITE);
        oled.setCursor(7,30);
        seleccion(contador,2);
        oled.println(F("ENCENDIDO 2"));
        delay(5);
        oled.drawCircle(4,43,1,WHITE);
        oled.setCursor(7,40);
        seleccion(contador,1);
        oled.println(F("APAGADO 2"));
        delay(5);
        oled.drawCircle(4,53,1,WHITE);
        oled.setCursor(7,50);
        seleccion(contador,0);
        oled.println(F("Volver"));
        delay(5);
        oled.display();
        if(contador == 4 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(0);
        }
        if(contador == 3 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(1);
        }
        if(contador == 2 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(2);
        }
        if(contador == 1 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            introducir_horarios(3);
        }
        if(contador == 0 && digitalRead(sw_aceptar) == 0){
            delay(700); //cambiar
            configuraciones();
        }
        delay(100);
    }
}

void introducir_horarios(int k){
    int addr = eeprom_horario_1_h + 2*k;
    contador = EEPROM.read(addr);
    while(true){
        contador = contadores(contador, 23, 0, 1);
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextColor(SSD1306_WHITE);
        if(k == 0){
            oled.setCursor(15,5);
            oled.println(F("ENCENDIDO 1"));
            delay(5);
        }
        else if(k == 1){
            oled.setCursor(15,5);
            oled.println(F("APAGADO 1"));
            delay(5);
        }
        else if(k == 2){
            oled.setCursor(15,5);
            oled.println(F("ENCENDIDO 2"));
            delay(5);
        }
        else{
            oled.setCursor(15,5);
            oled.println(F("APAGADO 2"));
            delay(5);
        }
        oled.setCursor(8,15);
        oled.println(F("Introduzca la hora:"));
        delay(5);
        oled.setCursor(55,35);
        oled.println(contador);
        delay(5);
        oled.setCursor(40,50);
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        oled.println(F("ACEPTAR"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            EEPROM.write(addr,contador);
            EEPROM.commit();
            delay(4);
            addr = eeprom_horario_1_m + 2*k;
            contador = EEPROM.read(addr);
            while(true){
                contador = contadores(contador, 59, 0, 1);
                oled.clearDisplay();
                oled.drawRect(1,1,127,63,WHITE);
                oled.setTextColor(SSD1306_WHITE);
                if(k == 0){
                    oled.setCursor(15,5);
                    oled.println(F("ENCENDIDO 1"));
                    delay(5);
                }
                else if(k == 1){
                    oled.setCursor(15,5);
                    oled.println(F("APAGAD0 1"));
                    delay(5);
                }
                else if(k == 3){
                    oled.setCursor(15,5);
                    oled.println(F("ENCENDIDO 2"));
                    delay(5);
                }
                else{
                    oled.setCursor(15,5);
                    oled.println(F("APAGAD0 2"));
                    delay(5);
                }
                oled.setCursor(8,15);
                oled.println(F("Introduzca los"));
                delay(5);
                oled.setCursor(2,25);
                oled.println(F("minutos:"));
                delay(5);
                oled.setCursor(55,35);
                oled.println(contador);
                delay(5);
                oled.setCursor(40,50);
                oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
                oled.println(F("ACEPTAR"));
                delay(5);
                oled.display();
               if(digitalRead(sw_aceptar) == 0){
                    EEPROM.write(addr, contador);
                    EEPROM.commit();
                    delay(700);
                    conf_horarios();
                }
                delay(100);
            }
        }
        delay(100);
    }
}

/*
======= Ver Estado ==========
*/

void ver_estado(){
    contador = 0;
    while(true){
        int Sens = Leer_Nivel_Agua();
        float temp = Leer_Temp();
        float T = EEPROM.read(eeprom_temp);
        T = T - 2;
        if(temp < T)(digitalWrite(resist, HIGH));
        else(digitalWrite(resist, LOW));
        float ph = Leer_Ph();
        int p = EEPROM.read(eeprom_ph);
        int p_f = (p/10) + 1;
        if(ph > p_f)(digitalWrite(dosificador, HIGH));
        else(digitalWrite(dosificador, LOW));
        oled.clearDisplay();
        oled.drawRect(1,1,127,63,WHITE);
        oled.setTextSize(1);
        oled.setTextColor(SSD1306_WHITE);
        oled.setCursor(15,5);             // Columna, Fila
        oled.println(F("ESTADO ACTUAL"));
        delay(5);
        oled.setCursor(4,15);             // Columna, Fila
        oled.println(F("Temp:"));
        delay(5);
        oled.setCursor(70,15);             // Columna, Fila
        oled.println(temp);
        delay(5);
        oled.setCursor(4,25);             // Columna, Fila
        oled.println(F("N. de PH:"));
        delay(5);
        oled.setCursor(70,25);             // Columna, Fila
        oled.println(ph);
        delay(5);
        if(Sens == 0){
            digitalWrite(bomba, HIGH);
            oled.setCursor(4,35);             // Columna, Fila
            oled.println(F("B. de Agua ON"));
            delay(5);
        }
        else{
            digitalWrite(bomba, LOW);
            oled.setCursor(4,35);             // Columna, Fila
            oled.println(F("B. de Agua OFF"));
            delay(5);
        }
        int hora_1 = EEPROM.read(2);
        int min_1 = EEPROM.read(3);
        int hora_2 = EEPROM.read(4);
        int min_2 = EEPROM.read(5);
        int hora_3 = EEPROM.read(6);
        int min_3 = EEPROM.read(7);
        int hora_4 = EEPROM.read(8);
        int min_4 = EEPROM.read(9);
        DateTime h_actual = rtc.now();
        int hora_actual = h_actual.hour();
        int min_actual = h_actual.minute();
        if((hora_actual == hora_1 && min_actual == min_1)||(hora_actual == hora_3 && min_actual == min_3)){
            digitalWrite(aireador, HIGH);
            contador = 1;
        }
        else if((hora_actual == hora_2 && min_actual == min_2)||(hora_actual == hora_4 && min_actual == min_4)){
            digitalWrite(aireador, LOW);
            contador = 0;
        }
        if(contador == 1){
            oled.setCursor(4,45);             // Columna, Fila
            oled.println(F("Aireador ON"));
            delay(5);
        }
        if(contador == 0){
            oled.setCursor(4,45);             // Columna, Fila
            oled.println(F("Aireador OFF"));
            delay(5);
        }
        oled.setCursor(4,55);             // Columna, Fila
        oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        oled.println(F("VOLVER"));
        delay(5);
        oled.display();
        if(digitalRead(sw_aceptar) == 0){
            menu_principal();
        }
    }
}

int Leer_Nivel_Agua(){
    int SensorNivel = digitalRead(Nivel);
    return SensorNivel;
}
float Leer_Temp(){
       int Vo;
       float R1 = 100000;              // resistencia fija del divisor de tension
       float logR2, R2, temperatura;
       float c1 = 2.114990448e-03, c2 = 0.3832381228e-04, c3 = 5.228061052e-07;
       Vo = analogRead(valor);      // lectura de A0
       R2 = R1 * (1023.0 / (float)Vo - 1.0); // conversion de tension a resistencia
       logR2 = log(R2);      // logaritmo de R2 necesario para ecuacion
       temperatura = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));   // ecuacion S-H
       temperatura = temperatura - 273.15;   // Kelvin a Centigrados (Celsius)
       return temperatura;
}

float Leer_Ph(){
    float Offset=0.00; //deviation compensate
    unsigned long int avgValue; //Store the average value of the sensor feedback
    int buf[10]; //buffer for read analog
    for(int i=0;i<10;i++){ //Get 10 sample value from the sensor for smooth the value
        buf[i]=analogRead(SensorPin);
        delay(10);
    }
    for(int i=0;i<9;i++){ //sort the analog from small to large
       for(int j=i+1;j<10;j++){
           if(buf[i]>buf[j]){
              int temp=buf[i];
              buf[i]=buf[j];
              buf[j]=temp;
           }
       }
    }
    avgValue=0;
    for(int i=2;i<8;i++){ //take the average value of 6 center sample
          avgValue+=buf[i];
    }
    float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
    phValue=3.5*phValue+Offset; //convert the millivolt into pH value
    return phValue;
}

//------------------FUNCIONES SETUP Y LOOP---------------------------//

void setup() {
    Serial.begin(115200);
    EEPROM.begin(EEPROM_SIZE);

    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Wire.begin();         // inicializa bus I2C

    if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
        Serial.println(F("Modulo SSD1306 no encontrada"));
        for(;;); // Don't proceed, loop forever
    }
    if(!rtc.begin()) { // Address 0x3D for 128x64
        Serial.println(F("Modulo RTC no encontrado"));
        for(;;); // Don't proceed, loop forever
    }

    pinMode(sw_subir, INPUT_PULLUP);
    pinMode(sw_aceptar, INPUT_PULLUP);
    pinMode(sw_bajar, INPUT_PULLUP);
    pinMode(Nivel,INPUT);
    pinMode(valor,INPUT);
    pinMode(SensorPin,INPUT);
    pinMode(bomba,OUTPUT);
    pinMode(aireador,OUTPUT);
    pinMode(resist,OUTPUT);
    delay(100);

    //oled.stopscroll();
    oled.clearDisplay();
    oled.drawBitmap(0, 0, logo_Eg, 128, 64, SSD1306_WHITE);
    oled.display();
    delay(1000);
//    for(int k = 0; k < 10; k++){
//        if(digitalRead(aceptar)==0){
//            delay(700); //cambiar
//            config_wifi();
//        }
//        delay(100);
//    }
    menu_principal(); //funcion A
}

void loop() {
  // ** //
}
