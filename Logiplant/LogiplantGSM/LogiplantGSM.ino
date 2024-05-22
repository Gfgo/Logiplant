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

//const char apn[] = "internet.movistar.com.co";
//const char gprsUser[] = "movistar";
//const char gprsPass[] = "movistar";

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

///////////////libreria sleep
//void print_wakeup_reason(){
//  esp_sleep_wakeup_cause_t wakeup_reason;
//  wakeup_reason = esp_sleep_get_wakeup_cause();
//
//  switch(wakeup_reason)
//  {
//    case ESP_SLEEP_WAKEUP_EXT0 : SerialMon.println("Wakeup caused by external signal using RTC_IO"); break;
//    case ESP_SLEEP_WAKEUP_EXT1 : SerialMon.println("Wakeup caused by external signal using RTC_CNTL"); break;
//    case ESP_SLEEP_WAKEUP_TIMER : SerialMon.println("Wakeup caused by timer"); break;
//    case ESP_SLEEP_WAKEUP_TOUCHPAD : SerialMon.println("Wakeup caused by touchpad"); break;
//    case ESP_SLEEP_WAKEUP_ULP : SerialMon.println("Wakeup caused by ULP program"); break;
//    default : SerialMon.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
//  }
//}

/****************************************
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
//*********
// Libraries for SD card
#include "FS.h"
#include "SD.h"
#include <SPI.h>

#define SCK   14//18
#define MISO  2//19
#define MOSI  15//23
#define CS    13//5

SPIClass spi = SPIClass(VSPI);

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 3000;

// Variables to hold sensor readings
String dataMessage;

// Variable to save current epoch time
unsigned long epochTime; 

// Initialize SD card
void initSDCard(){
   if (!SD.begin(CS,spi,80000000)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }
  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

// Write to the SD card
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

// Append data to the SD card
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void setup() {
  Serial.begin(115200);
  spi.begin(SCK, MISO, MOSI, CS);
  initSDCard();
  
  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.txt");
  if(!file) {
    Serial.println("File doesn't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.txt", "Epoch Time, Temperature, Voltage, Hummidity \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close();
  
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    //Get epoch time
    epochTime++;
    
    //Get sensor readings
  float temperature = random(20, 50);
  /*SerialMon*/Serial.println(temperature);
  float volt= 3.3*(random(20, 50));
  /*SerialMon*/Serial.println(volt);
  byte hum= 20*(random(1, 5));
  /*SerialMon*/Serial.println(hum);

    //Concatenate all info separated by commas
    dataMessage = String(epochTime) + ";" + String(temperature) + ";" + String(volt) + ";" + String(hum)+ "\r\n";
    Serial.print("Saving data: ");
    Serial.println(dataMessage);

    //Append the data to file
    appendFile(SD, "/data.txt", dataMessage.c_str());

    lastTime = millis();
  }
}
