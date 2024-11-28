//*******01/03/2024 nuevo Logi con GSM ok 04/03/2024
#include <EEPROM.h>
#include <PubSubClient.h>
#include <stdio.h>
#include <Arduino.h>

// Select your modem:
#define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
#define RXD2 16
#define TXD2 17

// Set serial for debug console (to the Serial Monitor, default speed 115200)
//#define /*SerialMon*/Serial Serial
#define SerialAT Serial2

// Define the serial console for debug prints, if needed
//#define TINY_GSM_DEBUG SerialMon

// Uncomment this if you want to use SSL
//#define USE_SSL

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false

// set GSM PIN, if any
#define GSM_PIN ""

//#define uS_TO_S_FACTOR 1000000    //Conversion de micro a saegundos
//#define TIME_TO_SLEEP  120        // Tiempo inactivo del ESP
//RTC_DATA_ATTR int bootCount = 0;

const char apn[] = "internet.comcel.com.co";
const char gprsUser[] = "comcel";
const char gprsPass[] = "comcel";


//DATOS MQTT UBIDOTS
#define TOKEN "BBFF-sDzTuSgHbyHsLZNx1U6RfrzCTT7gB4" //
#define MQTT_CLIENT_NAME "0001" // MQTT client Name, put a Random ASCII
char mqttBroker[] = "industrial.api.ubidots.com";
char payload[300];
char topic[40];

#include <TinyGsmClient.h>

#include "Adafruit_Debounce.h"
#include <ESP32Servo.h>
#include "Ucglib.h"
#include <SPI.h>
#include <Wire.h> 

Servo servo;

#define bolsapin 18
#define seguropin 19

Adafruit_Debounce bolsa(bolsapin, LOW);
Adafruit_Debounce seguro(seguropin, LOW);
byte relepin=33;  //GPIO33
byte numbol=0;

int             impresion=27;     //Indicador de impresion
int             hall= 26;         //GPIO26 sensor hall
unsigned long   antes=0;
const long      interval=5000;    //Tiempo en milesimas

TinyGsm modem(SerialAT);
TinyGsmClient gsmclient(modem);
  const int  port = 80;

PubSubClient client(gsmclient);

void setup() {
  /*SerialMon*/Serial.begin(115200);      //Comunicación con serial
  delay(10);
//  pinMode(pinSIM,OUTPUT);
//  digitalWrite(pinSIM,HIGH);
  /*SerialMon*/Serial.println("Setup Sensores");
  while(!/*SerialMon*/Serial);   
  //Begin serial communication with Arduino and GPS & SIM800 
  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
  iniciarSIM();//iniciar modulo sim800L
  delay(1000);
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);

  servo.attach(21);
  bolsa.begin();
  seguro.begin();
  pinMode(relepin,  OUTPUT);
  pinMode(hall,     INPUT);
  pinMode(impresion,OUTPUT);
  digitalWrite(relepin, LOW);
}
 
void loop() {

  unsigned long ahora = millis();
  bolsa.update();
  seguro.update();
  byte boton=0;

//****HALL   
    uint16_t value = analogRead (hall);
    uint16_t range = get_gp2d12 (value);
     /*SerialMon*/Serial.println (value);
    //Serial.printf("Value %d\n",value); //Serial.print (value); Serial.println("\t");
    //Serial.printf("Rango mm %d\n",range);//Serial.print (range);Serial.println (" mm");
    if (value>=2500) {
         /*SerialMon*/Serial.println("Tanque lleno ");
//        ucg.setFont(ucg_font_ncenR10_hr);
//        ucg.setColor(255, 0, 55);
//        ucg.setPrintPos(2,18); 
//        ucg.print("TANQUE LLENO "); 
        delay(200);     
//        ucg.setColor(0, 0, 0);
//        ucg.drawBox(1, 7, 128, 13);
    }        
//*****HALL  FIN
  
  if (bolsa.justPressed()) {
    boton++;
     /*SerialMon*/Serial.println("Button was just pressed!");
        for (byte i=0; i<=180;i++){
        servo.write(i);
        delay(15);
        }
        //digitalWrite(relepin, HIGH);      
  }

  if (seguro.justReleased()) {
    numbol++;
    /*SerialMon*/Serial.println(numbol);
     /*SerialMon*/Serial.println("Button was just released!");
          for ( int i=180; i>=0; i--){ 
          servo.write(i);
          delay(15);
          }
          delay(2000);
          digitalWrite(relepin, HIGH);
           /*SerialMon*/Serial.println("motor on");
          delay(5000);
          digitalWrite(relepin, LOW);
           /*SerialMon*/Serial.println("motor off");
          delay(2000);
  }
//----------------------------------------------------------------------RECIBO
   /*SerialMon*/Serial.println("Otra bolsa? presione boton 1 de lo contrario espere");
  if (bolsa.justPressed())
  boton++;
   /*SerialMon*/Serial.println(boton);
  if (boton>0){
    digitalWrite(impresion, HIGH);
     /*SerialMon*/Serial.println("Lugar "+String(ahora));
     /*SerialMon*/Serial.println("Bolsas "+String(numbol));
    const String impres=("Lugar "+String(ahora));
  }
//----------------------------------------------------------------------RECIBO  
  delay(10);
  
//-------------------------------------  
//  ++bootCount;
//  SerialMon.println("Boot number: " + String(bootCount));  //Increment boot number and print it every reboot
//  print_wakeup_reason();//Print the wakeup reason for ESP32
//  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);  
//  SerialMon.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
//
//    delay(2000);
//    
////    digitalWrite(pinSIM,LOW);
//si duerme poner codigo aqui
////    digitalWrite(pinSensor,LOW);
//  
//  SerialMon.println("Going to sleep now");
//  delay(1000);
//  SerialMon.flush(); 
////  esp_deep_sleep_start();
//  SerialMon.println("This will never be printed");
//-------------------------------------
if (!client.connected()) {
    reconnect();
  }  

  float temperature = random(20, 50);
  /*SerialMon*/Serial.println(temperature);
  float volt= 3.3*(random(20, 50));
  /*SerialMon*/Serial.println(volt);
  byte hum= 20*(random(1, 5));
  /*SerialMon*/Serial.println(hum);
  
  //cabecera
  sprintf(topic, "%s", "");                                             // Cleans the topic content
  sprintf(topic, "%s%s", "/v1.6/devices/", "asador");                   //label
  //inicio
  sprintf(payload, "%s", "");                                           // Cleans the payload content
  sprintf(payload, "{\"%s\":", "sensor");                               // A la variable de ubi 1   
  sprintf(payload, "%s {\"value\": %s", payload, String(temperature));  // La variable que envio
  sprintf(payload, "%s },\"%s\":", payload, "termocupla");             // A la variable de ubi 2
  sprintf(payload, "%s {\"value\": %s", payload, String(volt));         // La variable que envio 2
  sprintf(payload, "%s },\"%s\":", payload, "puntomedio");              // A la variable de ubi 3
  sprintf(payload, "%s {\"value\": %s", payload, String(hum));          // La variable que envio
  //cierre
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic, payload);
  client.loop();
  delay(3000); 
}//FIN LOOP

void iniciarSIM()
{
    // Restart takes quite some time
  // To skip it, call init() instead of restart()
  /*SerialMon*/Serial.println(F("Initializing modem..."));
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  /*SerialMon*/Serial.print(F("Modem Info: "));
  /*SerialMon*/Serial.println(modemInfo);

  // Unlock your SIM card with a PIN if needed
  if ( GSM_PIN && modem.getSimStatus() != 3 ) {
    modem.simUnlock(GSM_PIN);
  }

  // GPRS connection parameters are usually set after network registration
    /*SerialMon*/Serial.print(F("Connecting to "));
    /*SerialMon*/Serial.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      /*SerialMon*/Serial.println(F(" fail"));
      delay(10000);
      return;
    }
    /*SerialMon*/Serial.println(F(" success"));

  if (modem.isGprsConnected()) {
    /*SerialMon*/Serial.println(F("GPRS connected"));
  }
}
//****************************************
 * Auxiliar Functions para Ubidots
 ****************************************/
void callback(char* topic, byte* payload, unsigned int length) {} 

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
  /*SerialMon*/Serial.println("Attempting MQTT connection...");
  
  /*SerialMon*/Serial.print(F("Connecting to "));
    /*SerialMon*/Serial.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      /*SerialMon*/Serial.println(F(" fail"));
      delay(10000);
      return;
    }
    /*SerialMon*/Serial.println(F(" success"));

  if (modem.isGprsConnected()) {
    /*SerialMon*/Serial.println(F("GPRS connected"));
  }

  // Attempt to connect
  if (client.connect(MQTT_CLIENT_NAME, TOKEN,"")) {
    /*SerialMon*/Serial.println("connected");
    } else {
    /*SerialMon*/Serial.print("failed, rc=");
    /*SerialMon*/Serial.print(client.state());
    /*SerialMon*/Serial.println(" try again in 2 seconds");
    // Wait 2 seconds before retrying
    delay(2000);
    }
  }
}

uint16_t get_gp2d12 (uint16_t value) {      //*************HALL
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}

//**********************************************
//*******01/03/2024 nuevo Logi con GSM ok 04/03/2024
#include <EEPROM.h>
#include <PubSubClient.h>
#include <stdio.h>
#include <Arduino.h>

// Select your modem:
#define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
#define RXD2 16
#define TXD2 17

// Set serial for debug console (to the Serial Monitor, default speed 115200)
//#define /*SerialMon*/Serial Serial
#define SerialAT Serial2

// Define the serial console for debug prints, if needed
//#define TINY_GSM_DEBUG SerialMon

// Uncomment this if you want to use SSL
//#define USE_SSL

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false

// set GSM PIN, if any
#define GSM_PIN ""

//#define uS_TO_S_FACTOR 1000000    //Conversion de micro a saegundos
//#define TIME_TO_SLEEP  120        // Tiempo inactivo del ESP
//RTC_DATA_ATTR int bootCount = 0;

const char apn[] = "internet.comcel.com.co";
const char gprsUser[] = "comcel";
const char gprsPass[] = "comcel";


//DATOS MQTT UBIDOTS
#define TOKEN "BBFF-sDzTuSgHbyHsLZNx1U6RfrzCTT7gB4" //
#define MQTT_CLIENT_NAME "0001" // MQTT client Name, put a Random ASCII
char mqttBroker[] = "industrial.api.ubidots.com";
char payload[300];
char topic[40];

#include <TinyGsmClient.h>

#include "Adafruit_Debounce.h"
#include <ESP32Servo.h>
#include "Ucglib.h"
#include <SPI.h>
#include <Wire.h> 

Servo servo;

#define bolsapin 18
#define seguropin 19

Adafruit_Debounce bolsa(bolsapin, LOW);
Adafruit_Debounce seguro(seguropin, LOW);
byte relepin=33;  //GPIO33
byte numbol=0;

int             impresion=27;     //Indicador de impresion
int             hall= 26;         //GPIO26 sensor hall
unsigned long   antes=0;
const long      interval=5000;    //Tiempo en milesimas

TinyGsm modem(SerialAT);
TinyGsmClient gsmclient(modem);
  const int  port = 80;

PubSubClient client(gsmclient);

void setup() {
  /*SerialMon*/Serial.begin(115200);      //Comunicación con serial
  delay(10);
//  pinMode(pinSIM,OUTPUT);
//  digitalWrite(pinSIM,HIGH);
  /*SerialMon*/Serial.println("Setup Sensores");
  while(!/*SerialMon*/Serial);   
  //Begin serial communication with Arduino and GPS & SIM800 
  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
//  iniciarSIM();//iniciar modulo sim800L
  delay(1000);
  client.setServer(mqttBroker, 1883);
//  client.setCallback(callback);

  servo.attach(21);
  bolsa.begin();
  seguro.begin();
  pinMode(relepin,  OUTPUT);
  pinMode(hall,     INPUT);
  pinMode(impresion,OUTPUT);
  digitalWrite(relepin, LOW);
}
 
void loop() {

  unsigned long ahora = millis();
  bolsa.update();
  seguro.update();
  byte boton=0;

//****HALL   
    uint16_t value = analogRead (hall);
    uint16_t range = get_gp2d12 (value);
     /*SerialMon*/Serial.println (value);
    //Serial.printf("Value %d\n",value); //Serial.print (value); Serial.println("\t");
    //Serial.printf("Rango mm %d\n",range);//Serial.print (range);Serial.println (" mm");
    if (value>=2500) {
         /*SerialMon*/Serial.println("Tanque lleno ");
//        ucg.setFont(ucg_font_ncenR10_hr);
//        ucg.setColor(255, 0, 55);
//        ucg.setPrintPos(2,18); 
//        ucg.print("TANQUE LLENO "); 
        delay(200);     
//        ucg.setColor(0, 0, 0);
//        ucg.drawBox(1, 7, 128, 13);
    }        
//*****HALL  FIN
  
  if (bolsa.justPressed()) {
    boton++;
     /*SerialMon*/Serial.println("Button was just pressed!");
        for (byte i=0; i<=180;i++){
        servo.write(i);
        delay(15);
        }
        //digitalWrite(relepin, HIGH);      
  }

  if (seguro.justReleased()) {
    numbol++;
    /*SerialMon*/Serial.println(numbol);
     /*SerialMon*/Serial.println("Button was just released!");
          for ( int i=180; i>=0; i--){ 
          servo.write(i);
          delay(15);
          }
          delay(2000);
          digitalWrite(relepin, HIGH);
           /*SerialMon*/Serial.println("motor on");
          delay(5000);
          digitalWrite(relepin, LOW);
           /*SerialMon*/Serial.println("motor off");
          delay(2000);
  }
//----------------------------------------------------------------------RECIBO
   /*SerialMon*/Serial.println("Otra bolsa? presione boton 1 de lo contrario espere");
  if (bolsa.justPressed())
  boton++;
   /*SerialMon*/Serial.println(boton);
  if (boton>0){
    digitalWrite(impresion, HIGH);
     /*SerialMon*/Serial.println("Lugar "+String(ahora));
     /*SerialMon*/Serial.println("Bolsas "+String(numbol));
    const String impres=("Lugar "+String(ahora));
  }
//----------------------------------------------------------------------RECIBO  
  delay(10);
  
//-------------------------------------  
//  ++bootCount;
//  SerialMon.println("Boot number: " + String(bootCount));  //Increment boot number and print it every reboot
//  print_wakeup_reason();//Print the wakeup reason for ESP32
//  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);  
//  SerialMon.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");
//
//    delay(2000);
//    
////    digitalWrite(pinSIM,LOW);
//si duerme poner codigo aqui
////    digitalWrite(pinSensor,LOW);
//  
//  SerialMon.println("Going to sleep now");
//  delay(1000);
//  SerialMon.flush(); 
////  esp_deep_sleep_start();
//  SerialMon.println("This will never be printed");
//------------------------------------- 

  float temperature = random(20, 50);
  /*SerialMon*/Serial.println(temperature);
  float volt= 3.3*(random(20, 50));
  /*SerialMon*/Serial.println(volt);
  byte hum= 20*(random(1, 5));
  /*SerialMon*/Serial.println(hum);
  
  //cabecera
  sprintf(topic, "%s", "");                                             // Cleans the topic content
  sprintf(topic, "%s%s", "/v1.6/devices/", "asador");                   //label
  //inicio
  sprintf(payload, "%s", "");                                           // Cleans the payload content
  sprintf(payload, "{\"%s\":", "sensor");                               // A la variable de ubi 1   
  sprintf(payload, "%s {\"value\": %s", payload, String(temperature));  // La variable que envio
  sprintf(payload, "%s },\"%s\":", payload, "termocupla");             // A la variable de ubi 2
  sprintf(payload, "%s {\"value\": %s", payload, String(volt));         // La variable que envio 2
  sprintf(payload, "%s },\"%s\":", payload, "puntomedio");              // A la variable de ubi 3
  sprintf(payload, "%s {\"value\": %s", payload, String(hum));          // La variable que envio
  //cierre
  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
  client.publish(topic, payload);
  client.loop();
  delay(3000); 
}//FIN LOOP



uint16_t get_gp2d12 (uint16_t value) {      //*************HALL
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}

//******************* logi Full con patnalla franja gris sin Gsm 29/10/2024
#include <ESP32Servo.h>
#include "Ucglib.h"
#include <SPI.h>
#include <Wire.h>

#include <EEPROM.h>           //sim800
#include <PubSubClient.h>
#include <stdio.h>
#include <Arduino.h>

Servo servo;
#define finalcarpin   19      //junto esp finalcar bolsa final carrera
#define bolsapin    18      //junto gsm boton inicio/otra bolsa pin

#define TINY_GSM_MODEM_SIM800     //sim800
#define RXD2 0                   // Puertos de comunicacion con ESP32 16
#define TXD2 1                   // Puertos de comunicacion con ESP32 17

#define TINY_GSM_USE_GPRS true    //sim800
#define TINY_GSM_USE_WIFI false   //sim800

#define SerialAT Serial2

Ucglib_SSD1351_18x128x128_FT_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 17, /*cd=*/ 16, /*cs=*/ 0, /*reset=*/ 2);


const char apn[] = "internet.comcel.com.co";            //Red a la cual conectar
const char gprsUser[] = "comcel";                       //sim800
const char gprsPass[] = "comcel";                       //sim800

//DATOS MQTT UBIDOTS
#define TOKEN "BBFF-sDzTuSgHbyHsLZNx1U6RfrzCTT7gB4"   //Ubidots token.
#define MQTT_CLIENT_NAME "0001"                       //Nombre MQTT Random ASCII
char mqttBroker[] = "industrial.api.ubidots.com";     //ubidots
char payload[300];                                    //ubidots
char topic[40];                                       //ubidots

byte relepin=33;  //GPIO33 pin rele3
byte numbot=0;
byte numbol=1;

int             impresion=27;       //Indicador de impresion
int             hall= 26;           //GPIO26 sensor hall
unsigned long   antes=0;
const long      interv=5000;        //Tiempo en milesimas
bool inicio=false;
bool finalcar=false;                //estado de motor final de carrera
bool ntank=false;                   // estado de nivel del tanque
bool otrabolsa=false;               // estado de boton bolsa
uint16_t value=0;
uint16_t range=0;

#include <TinyGsmClient.h>  //sim800

TinyGsm modem(SerialAT);
TinyGsmClient gsmclient(modem);
  const int  port = 80;

PubSubClient client(gsmclient);

void setup() {
  Serial.begin(9600);
  servo.attach(21);
  pinMode(relepin,      OUTPUT);
  pinMode(hall,         INPUT);
  pinMode(impresion,    OUTPUT);
  digitalWrite(relepin, LOW);
  //delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
  Serial.println("Setup Sensores");                     //sim800
//  while(!Serial);                                       //sim800
//  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);       //sim800
//  delay(1000);                                          //sim800
////  iniciarSIM();                                         //sim800
//  delay(1000);                                          //sim800
////  client.setServer(mqttBroker, 1883);                   //sim800
////  client.setCallback(callback);                         //sim800
}

void loop() {
  ucg.setColor(125, 125, 125);
  ucg.drawBox(0, 105, 125, 23);
  unsigned long ahora = millis();
//  ucg.clearScreen();
  finalcar=true;
//  finalcar=(!digitalRead(finalcarpin));//estado final de carrera
  otrabolsa=(!digitalRead(bolsapin));//estado bolsapin

//************************verificacion valores
ucg.setFont(ucg_font_fur11_hf);
ucg.setColor(255, 255, 255);
ucg.setPrintPos(0,103);
ucg.print("fncr ");ucg.print(finalcar);//finalcar
ucg.setPrintPos(45,103);
ucg.print("bol ");ucg.print(otrabolsa);//
ucg.setPrintPos(85,103);
ucg.print("tank ");ucg.print(ntank);//ntank
//************************verificacion valores  

//****HALL   
  /*uint16_t*/ value = analogRead (hall);
  /*uint16_t*/ range = get_gp2d12 (value);
  Serial.println (value);
  if (value>=2500) {
      ntank=true;
  while (millis() - ahora < 3000) {
        Serial.println("Tanque lleno ");
        ucg.setFont(ucg_font_ncenR10_hr);
        ucg.setColor(255, 0, 55);
        ucg.setPrintPos(0,125); 
        ucg.print("TANQUE LLENO ");
        }
        ucg.setColor(125, 125, 125);
        ucg.drawBox(0, 105, 132, 23);
     /*setup();*/} else {ntank=false;}        
//*****HALL  FIN

//-------------------------------------------------------------------Nivel pantalla  
  ucg.setFont(ucg_font_ncenR12_hr);
  ucg.setColor(255, 255, 255);
  ucg.setPrintPos(2, 23);
  ucg.print("Tanque ");

  ucg.setColor(0, 255, 0, 60);
  ucg.setColor(1, 255, 0, 60);
  ucg.setColor(2, 0, 255, 128);
  ucg.setColor(3, 0, 255, 128);
  ucg.drawGradientBox(90, 5, 37, 29);//-----------------------------Nivel pantalla
  ucg.setColor(255, 255, 255);
  ucg.drawFrame(90, 5, 38, 30);//x, y (posición) w, h (ancho, alto)

//----------------------------------------------------------------------Descarga de ntank  
  while (millis() - ahora < 2000) {
    descarga();
    /*uint16_t*/ value = analogRead (hall);
    /*uint16_t*/ range = get_gp2d12 (value);
//    byte y  = map(value, 1600, 2500, 3, 28);
//    byte y2 = 0;
//    if (y2!=y){
//        ucg.setColor(0, 0, 0);//negro
//        ucg.drawBox(91, 6, 36, (28-y));
//        y2=y;
//    }
  }
//----------------------------------------------------------------------Descarga de ntank  
 
//if ((finalcar)||(ntank)){ 
//  fallo();
//  /*finalcar=true;inicio=true;*/}
//  //else{
//    //while (millis() - ahora < 4000) {
//          //finalcar=true;inicio=true;
//    //}
//  //}   
    
Serial.printf("finalcar %d\t",finalcar); Serial.printf(" ntank %d\n",ntank);
if ((finalcar==true)&&(ntank==false)){finalcar=false;inicio=false;
    Serial.println("Presione boton para iniciar ...");
    ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
    ucg.setColor(255, 255, 255);
    ucg.setPrintPos(2,52);
    ucg.print("Boton para iniciar ");
    delay(20);
    ucg.setColor(125, 125, 125);
    ucg.drawBox(2, 38, 125, 20);//************texto pantalla
    
    if (otrabolsa){inicio=true;}
      while (inicio){
        switch (numbot){
        case 0:                                           //Recibir y procesar bolsas
          for (byte i=0; i<=180;i++){
            servo.write(i);
            delay(15);
            }
        while (millis() - ahora < 10000) {
            Serial.println("Ingrese bolsa");
            ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
            ucg.setColor(255, 255, 255);
            ucg.setPrintPos(2,52);
            ucg.print("Ingrese bolsa ");
          }//delay(50);
            ucg.setColor(125, 125, 125);
            ucg.drawBox(2, 38, 125, 20);//************borrar texto pantalla
          
          //delay(10000);
            Serial.println("Peligro! cerrando puerta");
            ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
            ucg.setColor(255, 255, 255);
            ucg.setPrintPos(2,52);
            ucg.print("Cerrando puerta ");
            delay(50);            
            ucg.setColor(125, 125, 125);
            ucg.drawBox(2, 38, 125, 20);//************borrar texto pantalla
            
            for (int i=0;i<=6;i++){
              Serial.println("Ingrese bolsa, la puerta se cierra en: "+String(6-i));
              ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
              ucg.setColor(255, 255, 255);
              ucg.setPrintPos(2,55);
              ucg.print("Cerrando puerta "+String(6-i));
              delay(50);
              ucg.setColor(125, 125, 125);
              ucg.drawBox(2, 38, 125, 30);//************texto pantalla
              
              delay(900);
             }
            for ( int i=180; i>=0; i--){ 
              servo.write(i);
              delay(15);
            }
              while (millis() - ahora < 2000) {
                    descarga();
                    /*uint16_t*/ value = analogRead (hall);
                    /*uint16_t*/ range = get_gp2d12 (value);
                    }
    //--------------------------------------boton recibo        
            for (int i=0;i<=5;i++){
                Serial.println("Recibo?, presione boton 1, Otra bolsa?espere "+String(5-i));
                ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
                ucg.setColor(255, 255, 255);
                ucg.setPrintPos(2,52);
                ucg.print("Recibo? boton ");
                delay(50);
                ucg.setColor(125, 125, 125);
                ucg.drawBox(2, 38, 125, 20);//************borrar texto pantalla
                ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
                ucg.setColor(255, 255, 255);
                ucg.setPrintPos(2,62);
                ucg.print("Otra bolsa?");
                ucg.setPrintPos(2,78);
                ucg.print(" espere "+String(5-i));
                delay(50);
                ucg.setColor(125, 125, 125);
                ucg.drawBox(2, 48, 130, 20); ucg.drawBox(2, 58, 130, 25);//************borrar texto pantalla
            
                unsigned long startTime = millis();
                while (millis() - startTime < 1000) {
                  if (!digitalRead(bolsapin)){
                    numbot=1; 
                    delay(50);
                    Serial.println("Generando recibo ");
                    ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
                    ucg.setColor(255, 255, 255);
                    ucg.setPrintPos(2,52);
                    ucg.print("Generando recibo ");
                    delay(50);
                    ucg.setColor(125, 125, 125);
                    ucg.drawBox(2, 38, 125, 20);//************borrar texto pantalla
                    break;}
                }
              }
     //--------------------------------------boton recibo       
    if (digitalRead(finalcarpin)){finalcar=true;}//if (!digitalRead(finalcarpin)){finalcar=true;}
      else{
        Serial.println("Seguro de motor no detectado ...");
        ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
        ucg.setColor(255, 0, 55);
        ucg.setPrintPos(15,125);
        ucg.print("FALLO MOTOR ");//************texto pantalla
        //delay(100);
        finalcar=false;inicio=0;
       /*setup();*/}
      while (inicio=1){
              digitalWrite(relepin, HIGH);
              Serial.println("motor on");
              delay(5000);
              digitalWrite(relepin, LOW);
              Serial.println("motor off");
              delay(2000);
              numbol++;//conteo de bolsas
              Serial.println(numbot);
              Serial.println(numbol);
              break;}
        break;
        case 1://--------------------------------------------------------------------Recibo
              digitalWrite(impresion, HIGH);
              Serial.println("Lugar "+String(ahora));
              Serial.println("Bolsas "+String(numbol));
              ucg.setFont(ucg_font_fur11_hf);//************texto pantalla
              ucg.setColor(255, 255, 255);
              ucg.setPrintPos(2,65);
              delay(20);
              ucg.print("Lugar "+String(ahora));
              ucg.setPrintPos(2,82);
              ucg.print("Bolsas "+String(numbol));;
              ucg.setColor(125, 125, 125);
              ucg.drawBox(2, 38, 125, 50);//************texto pantalla
              delay(70);
              const String impres=("Lugar "+String(ahora));
              numbol=0;
              numbot=0;
              inicio=false;
             if (value>=2500) {
                  ntank=true;
                  Serial.println("ntank lleno ");
                  ucg.setColor(0, 0, 0);
                  ucg.drawBox(0, 125, 125, 125);}
        break;//--------------------------------------------------------------------Recibo
             
        }//switchnumbot
      }//fin while de inicio
    delay(10);
    delay(10);}
  else{
    fallo();
    /*setup();*/}

////------------------------------------- envio a ubi
//if (!client.connected()) {reconnect();}  
//
//  float temperature = random(20, 50);
//  Serial.println(temperature);
//  float volt= 3.3*(random(20, 50));
//  Serial.println(volt);
//  byte hum= 20*(random(1, 5));
//  Serial.println(hum);
//  
//  //cabecera
//  sprintf(topic, "%s", "");                                             // Cleans the topic content
//  sprintf(topic, "%s%s", "/v1.6/devices/", "asador");                   //label
//  //inicio
//  sprintf(payload, "%s", "");                                           // Cleans the payload content
//  sprintf(payload, "{\"%s\":", "sensor");                               // A la variable de ubi 1   
//  sprintf(payload, "%s {\"value\": %s", payload, String(temperature));  // La variable que envio
//  sprintf(payload, "%s },\"%s\":", payload, "termocupla");             // A la variable de ubi 2
//  sprintf(payload, "%s {\"value\": %s", payload, String(volt));         // La variable que envio 2
//  sprintf(payload, "%s },\"%s\":", payload, "puntomedio");              // A la variable de ubi 3
//  sprintf(payload, "%s {\"value\": %s", payload, String(hum));          // La variable que envio
//  //cierre
//  sprintf(payload, "%s } }", payload); // Closes the dictionary brackets
//  client.publish(topic, payload);
//  client.loop();
//  delay(10000);
////------------------------------------- envio a ubi  
    
}//FIN LOOP


uint16_t get_gp2d12 (uint16_t value) {      //*************HALL
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}

void descarga (void){
 byte y  = map(value, 1600, 2500, 3, 28);
    byte y2 = 0;
    if (y2!=y){
        ucg.setColor(0, 0, 0);//negro
        ucg.drawBox(91, 6, 36, (28-y));
        y2=y;
    } 
 }

void fallo(void){
  unsigned long ahora = millis();
  while (millis() - ahora < 3000){
    Serial.println("Fallo 01, LLamar tecnico ...");
    ucg.setFont(ucg_font_ncenR14_hr);
    ucg.setColor(255, 0, 55);
    ucg.setPrintPos(20,125);
    ucg.print("FALLO 01 ");
  }
    ucg.setColor(125, 125, 125);
    ucg.drawBox(0, 105, 125, 23);
}

//void iniciarSIM()                                                   //sim800
//{
//  Serial.println(F("Initializing modem..."));
//  modem.restart();
//
//  String modemInfo = modem.getModemInfo();
//  Serial.print(F("Modem Info: "));
//  Serial.println(modemInfo);
//
//    Serial.print(F("Connecting to "));
//    Serial.print(apn);
//    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//      Serial.println(F(" fail"));
//      delay(10000);
//      return;
//    }
//    Serial.println(F(" success"));
//
//  if (modem.isGprsConnected()) {
//    Serial.println(F("GPRS connected"));
//  }
//}

//void callback(char* topic, byte* payload, unsigned int length) {}     //sim800
//
//void reconnect() {
//  while (!client.connected()) {
//    Serial.println("Attempting MQTT connection...");
//    Serial.print(F("Connecting to "));
//    Serial.print(apn);
//    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//      Serial.println(F(" fail"));
//      delay(10000);
//      return;
//    }
//    /*SerialMon*/Serial.println(F(" success"));
//
//  if (modem.isGprsConnected()) {
//    Serial.println(F("GPRS connected"));
//  }
//  // Attempt to connect
//  if (client.connect(MQTT_CLIENT_NAME, TOKEN,"")) {
//    Serial.println("connected");
//    } else {
//    Serial.print("failed, rc=");
//    Serial.print(client.state());
//    Serial.println(" try again in 2 seconds");
//    // Wait 2 seconds before retrying
//    delay(2000);
//    }
//  }
//}
