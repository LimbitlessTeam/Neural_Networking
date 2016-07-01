import processing.serial.*;

Serial myPort;

int xPos = 1;
float inByte = 0;
byte[] data_f;
String[] data;
int counter = 0;

void setup()
{
  size(1800, 500);
  myPort = new Serial(this, "COM3", 9600);
  
  data = loadStrings("data.txt");
  println(data.length + " pieces of data");
  data_f = new byte[data.length];
  for(int i = 0; i < data.length; i++)
  {
    data_f[i] = byte( Float.parseFloat(data[i]));
    println(data[i]);
  }
  
  background(0);
}

void draw() {
  
  inByte = float(data_f[counter]);
  myPort.write('1');
  
  
  if(counter < data_f.length)
  {
    
    stroke(127, 34, 255);
    
    line(xPos, height, xPos, height - inByte);
    myPort.write(data_f[counter]);
    
    if( xPos >= width) {
      xPos = 0;
      background(0);
    } else {
      xPos++;
    } 
  
    
  } else {
    counter = 0;
  }
  
  counter++;

}