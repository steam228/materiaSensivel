import codeanticode.syphon.*;
import processing.video.*;
import processing.serial.*;

PGraphics canvas;
SyphonServer server;

Serial myPort;

float inByte = 0; 
float valMin = 0;
float valMax = 255; 
float valor = 0;

Movie movie;

void setup() { 
  size(640,360, P3D);
  
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[5], 9600);
  myPort.bufferUntil('\n');
  
  
  canvas = createGraphics(400, 400, P3D);
  
  background(0);
  // Load and play the video in a loop
  movie = new Movie(this, "loopM.mov");
  movie.loop();
  
  // Create syhpon server to send frames out.
  server = new SyphonServer(this, "Processing Syphon");
}

void movieEvent(Movie m) {
  m.read();
}

void draw() {
  canvas.beginDraw();
  canvas.blendMode(REPLACE);
  canvas.image(movie, 0, 0, width, height);
  canvas.blendMode(MULTIPLY);
  canvas.fill(valor,0,255-valor);
  canvas.rect(0,0,width, height);
  canvas.endDraw();
  image(canvas, 0, 0);
  server.sendImage(canvas);
}

void serialEvent (Serial myPort) {
    // get the ASCII string:
    String inString = myPort.readStringUntil('\n');

    if (inString != null) {
      // trim off any whitespace:
      inString = trim(inString);
      // convert to an int and map to the screen height:
      inByte = float(inString);
      print(inByte);
      print("  -  ");
      valor = map(inByte, valMin, valMax, 0, 255);
      println(valor);
    }
  }
