#include <CapacitiveSensor.h>
#include <DmxMaster.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 * 
 * steam228:
 * + DMX control strcture
 * + calibration
 */



#define ledPin 13

CapacitiveSensor   cs_4_2 = CapacitiveSensor(8,9);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(8,10);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(8,11);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil


long valMinRed = 100000;
long valMaxRed = 0;
long valMinGreen = 100000;
long valMaxGreen = 0;
long valMinBlue = 100000;
long valMaxBlue = 0;
long DMXred;
long DMXgreen;
long DMXblue;

void setup() {
  
/* The most common pin for DMX output is pin 3, which DmxMaster
** uses by default. If you need to change that, do it here. */
   
   DmxMaster.usePin(3);   
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin,LOW);
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   while(millis() < 30000){
    calibrate();  }
    digitalWrite(ledPin,LOW);
    DmxMaster.maxChannel(8);
    DmxMaster.write(1, 0);
    DmxMaster.write(2, 0);
    DmxMaster.write(3, 0);
    DmxMaster.write(4, 0);
     DmxMaster.write(5, 0);
    DmxMaster.write(6, 0);
    DmxMaster.write(7, 0);
    DmxMaster.write(8, 0);
    delay(500);
}

void loop() {
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);
    long total2 =  cs_4_6.capacitiveSensor(30);
    long total3 =  cs_4_8.capacitiveSensor(30);

    //filter negatives

    DMXred = abs(map(total1,valMinRed,valMaxRed,0,255));
    DMXgreen = abs(map(total2,valMinGreen,valMaxGreen,0,255));
    DMXblue = abs(map(total3,valMinBlue,valMaxBlue,0,255));
    Serial.print(DMXred);
    Serial.print(",");              
    DmxMaster.write(1, DMXred);
    DmxMaster.write(5, DMXred);
    Serial.print(DMXgreen);
    Serial.print(",");
    DmxMaster.write(2, DMXgreen);
    DmxMaster.write(6, DMXgreen);
    Serial.println(DMXblue);  
    DmxMaster.write(3, DMXblue);
    DmxMaster.write(7, DMXblue);
    DmxMaster.write(4, (DMXred+DMXgreen+DMXblue)/3);
    DmxMaster.write(8, (DMXred+DMXgreen+DMXblue)/3);
    delay(2);  
    }
                              // arbitrary delay to limit data to serial port 

void calibrate(){

    digitalWrite(ledPin,HIGH);
    long start = millis();
    long valor1 =  cs_4_2.capacitiveSensor(30);
    long valor2 =  cs_4_6.capacitiveSensor(30);
    long valor3 =  cs_4_8.capacitiveSensor(30);
    
    if(valor1 < valMinRed && valor1 > 0){
      valMinRed = valor1;}

    if  (valor2 < valMinGreen && valor2 > 0){
      valMinGreen = valor2;}

    if  (valor3 < valMinBlue && valor3 > 0){
      valMinBlue = valor3;}
    
    if(valor1 > valMaxRed){ 
      valMaxRed = valor1;}

    if(valor2 > valMaxGreen){   
      valMaxGreen = valor2;}

    if(valor3 > valMaxBlue){
      valMaxBlue = valor3;}
    
    
    Serial.print("mR/MR:");
    Serial.print(valMinRed);  
    Serial.print("/");  
    Serial.print(valMaxRed);
    Serial.print("    |    mG/MG:");
    Serial.print(valMinGreen);  
    Serial.print("/");  
    Serial.print(valMaxGreen);
    Serial.print("    |    mB/MB:");
    Serial.print(valMinBlue);  
    Serial.print("/");  
    Serial.println(valMaxBlue);
    Serial.println("___________________c-a-l-b-r-a-t-i-o-n----m-o-d-e_______________________");
      
    delay(2);
  }
