import codeanticode.syphon.*;
import processing.video.*;
import processing.serial.*;

PGraphics canvas;
SyphonServer server;

Serial myPort;




  float redValue = 0;        // red value
  float greenValue = 0;      // green value
  float blueValue = 0;       // blue value

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
  canvas.fill(redValue,greenValue,blueValue);
  canvas.rect(0,0,width, height);
  canvas.endDraw();
  image(canvas, 0, 0);
  server.sendImage(canvas);
}

  void serialEvent(Serial myPort) {
    // get the ASCII string:
    String inString = myPort.readStringUntil('\n');

    if (inString != null) {
      // trim off any whitespace:
      inString = trim(inString);
      // split the string on the commas and convert the resulting substrings
      // into an integer array:
      float[] colors = float(split(inString, ","));
      // if the array has at least three elements, you know you got the whole
      // thing.  Put the numbers in the color variables:
      if (colors.length >= 3) {
        // map them to the range 0-255:
        redValue = colors[0];
        greenValue = colors[1]-50;
        blueValue = colors[2];
      }
    }
  }
