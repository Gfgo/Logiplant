//#include <Wire.h>
//#include <Adafruit_RGBLCDShield.h>
//#include <utility/Adafruit_MCP23017.h>
//#include <Adafruit_NeoPixel.h>
//#include "HX711.h"
//#include "BluetoothSerial.h"
//
//#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
//#endif
//
//#define LED_PIN   32 //GPIO32
//#define LED_COUNT 8
//
//Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
//Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
//HX711 scale;
//BluetoothSerial SerialBT;
//
//byte        rojo=0;
//byte        verde=0;
//byte        azul=0;
//byte        nump=0;
//const int DOUT_PIN = 19;
//const int SCK_PIN = 18;
////byte PAUSA=200;
//String dato = "";  
//bool findato = false;                     // si el string esta completo
//
//
//void setup() {
//
//  Serial.begin(115200); SerialBT.begin(115200);   // inicio bluetooth
//  scale.begin(DOUT_PIN, SCK_PIN);
////  scale.set_scale();
////  scale.tare();
////  Serial.println("Coloque peso 222.024 gr ");
////  Serial.println("Espere");
////  scale.get_units(10);
//  scale.set_scale(1042.f);//1050.f original 894.f
//  scale.tare();
//  SerialBT.begin("Logiplant V1");          // Nombre dispositivo
//  SerialBT.println("Conexion disponible");  //Serial.println("Conexion disponible");
//  dato.reserve(200);                      //Guardo 200 bytes para datos de llegada
//  
////  lcd.setBacklight(HIGH);
//  lcd.begin(16, 2);
//  //----------------------------------------------------------------------Saludo
//    lcd.clear();
//    lcd.print("Logiplant V1"); Serial.println("DispenM V 1.3");//blut.println("DispenM V 1.3");
//    delay(500);
//    lcd.setCursor(0,1); 
//    lcd.print("Iniciando dispositivo"); Serial.println("Iniciando dispositivo");SerialBT.println("Iniciando dispositivo");
//    delay(200);
//    for (int i=0;i<=10;i++)
//      {lcd.print(". "); SerialBT.println(". ");
//      lcd.autoscroll();
//      delay(300);}
//  lcd.noAutoscroll();
//  lcd.clear();
//  //---------------------------------------------------------------------- impresion
//  int time = millis();
//  lcd.print("lectura ");
//  time = millis() - time;
//  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
//  strip.begin();           
//  strip.show();            
//  strip.setBrightness(10);
//
//}
//
//void loop() {
////----------------------------------------------impresion de valores leidos en lcd
//if (scale.is_ready()) {
//    //long reading = scale.read();
//    float var=0;
//           
//    Serial.print("lectura \t\t"); 
//    Serial.println(scale.get_units(10), 1);
//    
//    lcd.setCursor(0, 1);
//    lcd.print(scale.get_units(10), 1);
//    var=scale.get_units(5);
//
//    nump=map(var, 0, 5000, 0, 8);
//    strip.clear();
////    Serial.println(var);
////    Serial.println(nump); 
////-------------------------------------------------Ver por bluethtoot
//    SerialBT.print("lectura \t\t");             //Visualizar pesos por bluetooth
//    SerialBT.println(scale.get_units(10), 1);
//    dato="";          //limpiar el dato
//    findato = false;
////------------------------------------------------
//    
//  for(int i=0; i<=nump; i++) {
//    if (i<=1) rojo=0;
//    if ((i>=2)&&(i<=4)) rojo=128;
//    if (i>=4) rojo=255;
//    if (i<=4) verde=255;
//    if (i==5) verde=128;
//    if (i>=6) verde=0;
//    if (i<=8) azul=0;
//    strip.setPixelColor(i, rojo, verde,  azul);//rojo,verde,azul 0-255
//    strip.show();
//    //delay(PAUSA);
//    }
//  }
//}//Fin loop

//pausa sin delay
/*
byte led=19;
int boton=5;
int lecboton=0;
  unsigned long     inicio=0;
  int               delta=0;
  byte              uso=0;
  

void setup() {
  Serial.begin(9600);
  pinMode(boton,INPUT);
  pinMode(led,OUTPUT);
}

void loop() {
  lecboton=digitalRead(boton);
  unsigned long  ahora=millis();
 if(lecboton && (uso==0)) {
    Serial.println("boton presionado");
    inicio=ahora;
    Serial.println("tiempoinicial: "+String(inicio));
    uso=1;
  }
  delta=ahora-inicio;
  
  if((delta>=5000) && (uso==1)) {
   Serial.println("dtiempo: "+String(delta));
   Serial.println("dtiemponow: "+String(ahora));
   inicio=ahora;
   uso=0;
   }
  if(ahora>=4294967293) {
    inicio=0;
  }  
}*/

//----------
//------------------------------motor con pir
//byte       motorPin=9;       //GPIO33 Motor
//const int  interval=1000;     //Tiempo
//unsigned long antes=0; 
//byte          pir =3; 
//
//void setup() {
//  Serial.begin(9600);
//  pinMode(pir,    INPUT);
//  pinMode(motorPin, OUTPUT);
//
//}
//
//void loop() {
//      byte state = digitalRead(pir);
//      unsigned long ahora = millis();
//      if(state == 0){Serial.println("Vacio "); digitalWrite(motorPin, LOW);}
//      else {antes=ahora+interval;
////      while(state == 1){
////          //if (ahora<=antes)break;
//          Serial.print(ahora); Serial.print(" ");Serial.print(antes);
//          Serial.println(" Bolsa ");
//          digitalWrite(motorPin, HIGH); }  //activar rele
////      }

//}
//--------------------------motor con delay
//const int ledPin =  9;// the number of the LED pin
//
//
//int ledState = LOW;             // ledState used to set the LED
//unsigned long previousMillis = 0;        // will store last time LED was updated
//const long interval = 5000;           // interval at which to blink (milliseconds)
//
//void setup() {
//  // set the digital pin as output:
//  Serial.begin(9600);
//  pinMode(ledPin, OUTPUT);
//}
//
//void loop() {
//
//  unsigned long currentMillis = millis();
//  Serial.println(currentMillis);
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis;
//    Serial.print(" ");Serial.println(previousMillis);
//    if (ledState == LOW) {
//      ledState = HIGH;
//    } else {
//      ledState = LOW;
//    }
//    digitalWrite(ledPin, ledState);
//  }
//}
//
////--------------------antirebote
//const byte boton1=18;
//const byte led=23;
//byte numpulso=0;
//
//bool actual  = false;
//bool anterior  = false;
//unsigned long lastDebounceTime  = 0;
//
//
//void setup() {
//  Serial.begin(9600);
//  Serial.println(F("Initialize System"));
//  pinMode(boton1, INPUT);
//  pinMode(led, OUTPUT);
//}
//
//void loop() {
//  digitalWrite(led, LOW);
//  byte cuenta=rebote(boton1);
//  if(  ((millis()-lastDebounceTime)<=100)&&(cuenta==1)) {digitalWrite(led, cuenta); Serial.println("estado "+String(cuenta));}
//  lastDebounceTime = cuenta;
//
//}
//
//byte rebote(byte boton ){
//  int lectura=digitalRead(boton);
//  if (lectura!=anterior){
//    lastDebounceTime = millis();
//  }
//  if ((millis()-lastDebounceTime)>20){ /*Tiempo de delay de estabilizacion*/
//    if (lectura!=actual){
//      actual=lectura;
//      //if (actual==1){
//        //numpulso++;
//        //Serial.println("numpulso "+String(numpulso));}
//      //Serial.println("Sensor state: "+String(actual));
//    }
//  }
//  anterior=lectura;
//  return (anterior);
//}
//----------

//**-------Nuevo prog 27/04/2023
/*1.  La persona va a ingresar las bolsas por una compuerta que se abre cuando 
    se presiona un botón.
2. El motor se activa cuando la compuerta se cierra y se bloquea, y el motor 
    sigue activo 5 segundos después de que el detector de movimiento dejo de detectar.
3. 5 segundos después de apagar el motor se permite la apertura de la escotilla.
4. Va a preguntar si tiene más bolsas por triturar en caso de tener otras, vuelve
    al paso 1 en caso de no tener más bolsas, va a preguntar si desea recibo o escanear 
    el código, en caso de quererlo va a imprimir un recibo con código el cual se rija por 
    la ubicación de la máquina, la fecha y hora, además de un código de barras con esta 
    información para el usuario, donde se visualiza la cantidad de bolsas, la ubicación de 
    la maquina y la fecha y hora.

    Serial.printf("Value %d\n",value);
    Serial.println("dtiempo: "+String(deltatiempo));
    #include <arduino-timer.h>

    ----*****-----*****---- graficas en pantalla
    */
#include "Adafruit_Debounce.h"
#include <SPI.h>
#include "Ucglib.h"
#include <ESP32Servo.h>
#include <Wire.h>  


Ucglib_SSD1351_18x128x128_FT_SWSPI ucg(/*sclk=*/ 4, /*data=*/ 17, /*cd=*/ 16, /*cs=*/ 0, /*reset=*/ 2);

const byte      servo1Pin = 21;   //GPIO21 Pin SERVO
byte            pos = 0;          //position in degrees
const byte      boton=19;         //GPIO19 Boton de puerta
byte            lecbot=0;         //Lectura estado boton
byte            numbot=0;         //Numero de veces boton pulsado
byte            numbol=0;         //Numero de bolsas
byte            conta=0;
const byte      seguro=18;        //GPIO18 Seguro puerta
byte            lecseg=0;         //Lectura estado seguro
const int       motorPin=33;      //GPIO33 Motor
unsigned long   antes=0;
const long      interval=5000;    //Tiempo en milesimas
const byte      tmol=20;          //Tiempo de molido en segundos
const int       boton2=25;        //GPIO25 Boton de recibo
int             lecbot2=0;        //Lectura estado boton
int             hall= 26;         //GPIO26 sensor hall
int             impresion=27;     //Indicador de impresion

Servo mervo;                      //datos servo en 21
Adafruit_Debounce btn   (boton, LOW);
Adafruit_Debounce btn2  (seguro, LOW);

void setup(void){
  delay(1000);
  Serial.begin(9600);
  btn.begin();
  btn2.begin();
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.setFont(ucg_font_ncenR12_hr);
  ucg.clearScreen();
//  pinMode(boton,  INPUT);
  pinMode(boton2,  INPUT); 
//  pinMode(seguro, INPUT);
  pinMode(hall,   INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(impresion,OUTPUT);
  mervo.attach(servo1Pin);
  mervo.write(0);
  attachInterrupt(digitalPinToInterrupt(boton), inter, RISING);
  ucg.clearScreen();
  //**********************Boton

}

void loop(void){
  //ucg.clearScreen();
  btn.update();
  btn2.update();
  unsigned long ahora = millis();
  Serial.printf("numbot %d\n",numbot);
  Serial.printf("pos %d\n",pos);

//****HALL   
    uint16_t value = analogRead (hall);
    uint16_t range = get_gp2d12 (value);
    Serial.println (value);
    //Serial.printf("Value %d\n",value); //Serial.print (value); Serial.println("\t");
    //Serial.printf("Rango mm %d\n",range);//Serial.print (range);Serial.println (" mm");
    if (value>=2500) {
        Serial.println("Tanque lleno ");
        ucg.setFont(ucg_font_ncenR10_hr);
        ucg.setColor(255, 0, 55);
        ucg.setPrintPos(2,18); 
        ucg.print("TANQUE LLENO "); 
        delay(200);     
        ucg.setColor(0, 0, 0);
        ucg.drawBox(1, 7, 128, 13);
    }        
//*****HALL  FIN


  lecseg= (digitalRead(seguro)); Serial.printf("lecseg %d\n",lecseg);
  lecbot= (digitalRead(boton)); Serial.printf("lecbot %d\n",lecbot);
//  ucg.setPrintPos(0,25);
//  ucg.print("lecseg "); ucg.print(lecseg);
//  ucg.setPrintPos(0,75);
//  ucg.print("lecbot "); ucg.print(lecbot);
//------------------------------------------------------------------Depositar material
  while (numbot==1){                          //pulsa boton para abrir puerta para dopositar material
  if ((lecseg==1)&&(pos==0)){                 // y cuando el seguro este desactivado, abre la puerta
      Serial.print("abro puerta ");
      ucg.setColor(255, 255, 255);
      ucg.setPrintPos(2,40); 
      ucg.print("Apertura Puerta ");
      ucg.setColor(128, 128, 0);
      ucg.drawBox(1, 28, 125, 17); 
      for (pos = 1; pos <= 179; pos++) {      //ABRE PUERTA y espero a que llegue a la posición
            mervo.write(pos);
            delay(10);                      
           }Serial.println(180); 
    }break;
  }
  if ((numbot==2)&&(pos==180)){
      Serial.print("cierro puerta ");
      ucg.setColor(255, 255, 255);
      ucg.setPrintPos(2,40); //ucg.setPrintPos(2,20); 
      ucg.print("Cierre Puerta ");
      ucg.setColor(128, 128, 0);
      ucg.drawBox(1, 28, 103, 17); //ucg.drawFrame(1, 6, 95, 19); 
      for (pos = 180; pos >= 1; pos--) {    //cierre puerta y espero a que llegue a la posición
        mervo.write(pos);
        delay(10);
       }Serial.println(0); //numbot=0;//antes=ahora+interval;
     for (int i=0;i<=tmol;i++){
      digitalWrite(motorPin, HIGH);
      ucg.setFont(ucg_font_ncenR10_hr);
      ucg.setColor(255, 255, 90);
      ucg.setPrintPos(2,18); 
      ucg.print("PROCESANDO...");     
      ucg.setColor(0, 0, 0);
      ucg.drawBox(1, 7, 128, 13);
      delay(900);}digitalWrite(motorPin, LOW);numbot=0;
     }
    lecseg=0;lecbot=0;
//------------------------------------------------------------------
//  ucg.setPrintPos(25,50);
//  ucg.print("Boton "); ucg.println(numbot); 
//  rebote(boton);
//  ucg.setColor(128, 128, 0);
//  ucg.drawBox(74, 38, 17, 12);
//-----------------------------------------------------------------Recibo
  Serial.println("Otra bolsa presione boton 1, sino boton 2 ");

  lecbot2= (digitalRead(boton2));
  Serial.print(lecbot2); Serial.print(" ");
  if(digitalRead(lecbot2)==0){
    digitalWrite(impresion, HIGH);
    Serial.println("Lugar "+String(ahora));
    numbol/=2;
    Serial.println("Bolsas "+String(numbol));
    const String impres=("Lugar "+String(ahora));
    ucg.setColor(255, 255, 255);
    ucg.setPrintPos(2,110); 
    ucg.print(impres);
    ucg.setColor(255, 255, 255);
    ucg.setPrintPos(110,110); 
    ucg.print(numbol);
    delay(500);
    ucg.setColor(128, 128, 0);
    ucg.drawFrame(1, 95, 127, 19);
//---------------------------------------------------------------recibo    
   }
 //delay(500);  
}
  
void inter(){  // Funcion que se ejecuta durante cada interrupion
  numbot ++; //Serial.println(numbot);
  numbol ++;
}

uint16_t get_gp2d12 (uint16_t value) {      //*************HALL
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}
////********************************************************88// nuevo prog 25/10 funciona14/08 
//seguros ok falta gsm pantalla 20/08 

#include <ESP32Servo.h>
#include "Ucglib.h"
#include <SPI.h>
#include <Wire.h> 

Servo servo;
#define seguropin   19      //junto esp seguro bolsa final carrera
#define bolsapin    18      //junto gsm boton pin bolsa

byte relepin=33;  //GPIO33 pin rele3
byte numbot=0;
byte numbol=1;

int             impresion=27;     //Indicador de impresion
int             hall= 26;         //GPIO26 sensor hall
unsigned long   antes=0;
const long      interv=5000;      //Tiempo en milesimas
bool inicio=false;
bool seguro=false;
bool tanque=false;

void setup() {
  Serial.begin(9600);
  servo.attach(21);
  pinMode(relepin,  OUTPUT);
  pinMode(hall,     INPUT);
  pinMode(impresion,OUTPUT);
  digitalWrite(relepin, LOW);

}

void loop() {
  unsigned long ahora = millis();


//****HALL   
    uint16_t value = analogRead (hall);
    uint16_t range = get_gp2d12 (value);
    Serial.println (value);
    //Serial.printf("Value %d\n",value); //Serial.print (value); Serial.println("\t");
    //Serial.printf("Rango mm %d\n",range);//Serial.print (range);Serial.println (" mm");
    if (value>=2500) {
        tanque=true;
        Serial.println("Tanque lleno ");
//        ucg.setFont(ucg_font_ncenR10_hr);
//        ucg.setColor(255, 0, 55);
//        ucg.setPrintPos(2,18); 
//        ucg.print("TANQUE LLENO "); 
        delay(200);     
//        ucg.setColor(0, 0, 0);
//        ucg.drawBox(1, 7, 128, 13);
          setup();}        
//*****HALL  FIN
// leer seguro de puerta antes de empezar motor y lectura de tanque lleno .... hay problemas y programar e instalar sim800

if ((digitalRead(seguropin))||(tanque=true)){seguro=false;inicio=false;}
  else{
    Serial.println("Fallo 01, LLamar tecnico ...");
    delay(15);
    setup();}
seguro=(digitalRead(seguropin));
if ((seguro==true)&&(tanque==true)){seguro=false;inicio=false;

    Serial.println("Presiones boton para iniciar ...");
    if (!digitalRead(bolsapin)){inicio=true;}
      while (inicio){
        switch (numbot){
        case 0:                                           //Recibir y procesar bolsas
            Serial.println("Ingrese bolsa");
            for (byte i=0; i<=180;i++){
            servo.write(i);
            delay(15);
            }
            delay(10000);
            Serial.println("Peligro! cerrando puerta");
            for (int i=0;i<=6;i++){
              Serial.println("La puerta se cierra en: "+String(6-i));
              delay(900);
             }
            for ( int i=180; i>=0; i--){ 
              servo.write(i);
              delay(15);
            }
    //--------------------------------------boton recibo        
            for (int i=0;i<=5;i++){
                Serial.println("Recibo?, presione boton 1, Otra bolsa?espere "+String(5-i));
                unsigned long startTime = millis();
                while (millis() - startTime < 1000) {
                  if (!digitalRead(bolsapin)){
                    numbot=1; 
                    delay(50);
                    Serial.println("Generando recibo ");
                    break;}
                }
              }
     //--------------------------------------boton recibo       
    if (!digitalRead(seguropin)){seguro=true;}
      else{
        Serial.println("Seguro de motor no detectado ...");
        delay(100);
        seguro=false;inicio=false;
        setup();}
      while (inicio=true){
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
              const String impres=("Lugar "+String(ahora));
              numbol=0;
              numbot=0;
              inicio=false;
             if (value>=2500) {
                  tanque=true;
                  Serial.println("Tanque lleno ");}
        break;//--------------------------------------------------------------------Recibo
             
        }
      }//fin while de inicio
    delay(10);
    delay(10);}
  else{
    Serial.println("Fallo 01, LLamar tecnico ...");
    delay(60);
    setup();}
}//FIN LOOP


uint16_t get_gp2d12 (uint16_t value) {      //*************HALL
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}

//////////////////////////////********************************************** gsm y pantalla falta pruebas 03/09/2024
// Todo correcto 3/12/2024 final
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
float volt;                         //medicion voltaje hall

//#include <TinyGsmClient.h>  //sim800
//
//TinyGsm modem(SerialAT);
//TinyGsmClient gsmclient(modem);
//  const int  port = 80;
//
//PubSubClient client(gsmclient);

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
//  Serial.println("Setup Sensores");                     //sim800
//  while(!Serial);                                       //sim800
//  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);       //sim800
//  delay(1000);                                          //sim800
//  iniciarSIM();                                         //sim800
//  delay(1000);                                          //sim800
//  client.setServer(mqttBroker, 1883);                   //sim800
//  client.setCallback(callback);                         //sim800
}

void loop() {
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
  uint16_t value = analogRead (hall);
  uint16_t range = get_gp2d12 (value);
//  volt=((float)value*(3.3/4096));                       //con version valores esp hall
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
    byte y  = map(value, 1300, 2500, 3, 28);
    byte y2 = 0;
    if (y2!=y){
        ucg.setColor(0, 0, 0);//negro
        ucg.drawBox(91, 6, 36, (28-y));
        y2=y;
    }
  }
//----------------------------------------------------------------------Descarga de ntank  
    
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
              Serial.println("La puerta se cierra en: "+String(6-i));
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
                while (millis() - startTime < 3000) {
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
        delay(200);
        ucg.setColor(125, 125, 125);
        ucg.drawBox(0, 105, 125, 23);
        finalcar=false;inicio=false;
       /*setup();*/}
      while (inicio=true){
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

//------------------------------------- envio a ubi
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
//------------------------------------- envio a ubi  
    
}//FIN LOOP


uint16_t get_gp2d12 (uint16_t value) {              //*************HALL
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);    //antiguo codigo hall
//      return (29.988 * (pow(volt , -1.173)));
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
//
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
