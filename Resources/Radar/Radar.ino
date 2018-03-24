//Radar 1


int radarPin = 2;
int ledPin = 13;

boolean status = false;

void setup() {

pinMode(radarPin, INPUT);
pinMode(ledPin, OUTPUT);

}

void loop() {

  status = digitalRead(radarPin);
  digitalWrite(ledPin,status);
  delay(3);
}
