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

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

long valMin = 100000;
long valMax = 0;
long DMX;

void setup() {
  
/* The most common pin for DMX output is pin 3, which DmxMaster
** uses by default. If you need to change that, do it here. */
   
   DmxMaster.usePin(3);   
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin,LOW);
   //cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
   while(millis() < 10000){
    calibrate();  }
    digitalWrite(ledPin,LOW);
    DmxMaster.maxChannel(4);
    DmxMaster.write(1, 0);
    DmxMaster.write(2, 0);
    DmxMaster.write(3, 0);
    DmxMaster.write(4, 5);
   delay(500);
}

void loop() {
    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);

    //filter negatives

    DMX = map(total1,valMin,valMax,0,255);

    if(DMX > 0){

    
    Serial.println(DMX);                  // print sensor output 1
    DmxMaster.write(1, DMX);
    //DmxMaster.write(3, 255-DMX);

    }
    delay(10);                             // arbitrary delay to limit data to serial port 
}

void calibrate(){

    digitalWrite(ledPin,HIGH);
    
    long valor =  cs_4_2.capacitiveSensor(30);
    
    if(valor < valMin && valor > 0 ){

      valMin = valor;
    }

    if(valor > valMax){
      valMax = valor;
    }
    
    Serial.print("valMin:  ");
    Serial.print(valMin);  
    Serial.print("   |valMax:  ");  
    Serial.println(valMax);  
      
    delay(10);
  }
