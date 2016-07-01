import processing.serial.*;

Serial myPort;

int xPos = 1;
float inByte = 0;


void setup()
{
  size(1800, 300);
  myPort = new Serial(this, "COM3", 9600);
  
  myPort.bufferUntil('\n');
  background(0);
}

void draw() {
  
  stroke(127, 34, 255);
  line(xPos, height, xPos, height - inByte);
  
  if( xPos >= width) {
    xPos = 0;
    saveFrame();
    background(0);
  } else {
    xPos++;
  }
}
  
  
void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  
  if(inString != null) {
    inString = trim(inString);
    inByte = float(inString);
    println(inByte);
    inByte = map(inByte, 0, 1023, 0, height);
  }
}