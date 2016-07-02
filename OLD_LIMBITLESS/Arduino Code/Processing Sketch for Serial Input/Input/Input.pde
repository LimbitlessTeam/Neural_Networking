import processing.serial.*;
Serial mySerial;
PrintWriter output;


void setup() {
   mySerial = new Serial( this, Serial.list()[0], 9600 );
   output = createWriter( "data.txt" );
}
void draw() {
    println(mySerial.available());
    if (mySerial.available() > 0 ) { //<>//
         String value = mySerial.readString(); //<>//
         println(value);
         if ( value != null ) {
              output.println( value );
         }
    }
    
    keyPressed();
}
 //<>//
void keyPressed() {
    output.flush();  // Writes the remaining data to the file
    output.close();  // Finishes the file
    //exit();  // Stops the program
}