// Threading example code from online
// Thank you dmesser !!

boolean cycleCheck(unsigned long *lastMillis, unsigned int cycle) 
{
 unsigned long currentMillis = millis();
 if(currentMillis - *lastMillis >= cycle)
 {
   *lastMillis = currentMillis;
   return true;
 }
 else
   return false;
}

//For each event you want to deal with, set up an unsigned int for 
//how often it should trigger in ms (cycle), and an unsigned 
//long to keep track of the last millis() reading since the 
//last event (lastMillis). You call the function passing the 
//address of the lastMillis for that event and the cycle for 
//that event. The function returns a true if the event is due
//for action, and a false if the syscle time hasn't elapsed yet.

//Typical usage example (Simple blinking 2 LEDs at different rates)
//******************************************************************

#define ledPin1 11
#define ledPin2 12

#define led1Cycle 100U
#define led2Cycle 275U

unsigned long led1LastMillis = 0;
unsigned long led2LastMillis = 0;

boolean led1State = false;
boolean led2State = false;

boolean cycleCheck(unsigned long *lastMillis, unsigned int cycle) 
{
 unsigned long currentMillis = millis();
 if(currentMillis - *lastMillis >= cycle)
 {
   *lastMillis = currentMillis;
   return true;
 }
 else
   return false;
}

void setup()
{
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
}

void loop()
{
 if(cycleCheck(&led1LastMillis, led1Cycle))
 {
   digitalWrite(ledPin1, led1State);
   led1State = !led1State;
 }
 if(cycleCheck(&led2LastMillis, led2Cycle))
 {
   digitalWrite(ledPin2, led2State);
   led2State = !led2State;
 }
}
