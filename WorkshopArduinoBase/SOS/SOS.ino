/*
SOS
*/


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i=0;i<3;i++){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(200); 
    }
  for(int j=0;j<3;j++){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(600);                       // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(200); 
    }
  for(int k=0;k<3;k++){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(200);                       // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(200); 
  }
  delay(2000);
  
}
