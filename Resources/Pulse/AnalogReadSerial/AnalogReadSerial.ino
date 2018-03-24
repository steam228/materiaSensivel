/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

#define ledPin 13
#define pulsePin A0

int peak = 0;
int sensorValue = 0;
int prevVal = 0;
int threshold = 0;

int BPM = 0;
int BPMtime = 10000;
int lastMillis = 0;



// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  if (millis < 5000) {
    sensorValue = analogRead(pulsePin);
    if (sensorValue > peak){
      peak = sensorValue;
      }  

    
  }
  threshold = peak/40;
  lastMillis = millis();
  
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(pulsePin);
  // print out the value you read:
  //Serial.println(sensorValue);

  if (sensorValue > peak-threshold && prevVal < peak-threshold) {
    
    digitalWrite(ledPin,1);
    BPM++;
  
    
    }
  else {
     digitalWrite(ledPin,0);
    }

  if (millis()-lastMillis >= BPMtime) {
      Serial.print(" BPM's: -");
      Serial.print(millis());
      Serial.print("- ");
      Serial.println(BPM*6);
      BPM=0;
      lastMillis=millis();
      }  
  prevVal = sensorValue; 
  delay(1);        // delay in between reads for stability
}
