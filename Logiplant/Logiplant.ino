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
//  SerialBT.begin("DispenM V 1.3");          // Nombre dispositivo
//  SerialBT.println("Conexion disponible");  //Serial.println("Conexion disponible");
//  dato.reserve(200);                      //Guardo 200 bytes para datos de llegada
//  
////  lcd.setBacklight(HIGH);
//  lcd.begin(16, 2);
//  //----------------------------------------------------------------------Saludo
//    lcd.clear();
//    lcd.print("DispenM V 1.3"); Serial.println("DispenM V 1.3");//blut.println("DispenM V 1.3");
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
//  //----------------------------------------------------------------------
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
//
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

//#define ACTION 9 // define pin 9 as for ACTION
int pin       = A0;



void setup () {
    Serial.begin (9600);
    pinMode (pin, INPUT);
}

void loop () {
    int val;
    uint16_t value = analogRead (pin);
    uint16_t range = get_gp2d12 (value);

    val=analogRead(1);//Connect the sensor to analog pin 0
    
    Serial.print (value);
    Serial.print("\t");
    Serial.print (range);
    Serial.print (" mm");
    
    Serial.print("\t");
    Serial.println(val,DEC);
    
    delay (100);
}

uint16_t get_gp2d12 (uint16_t value) {
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}
