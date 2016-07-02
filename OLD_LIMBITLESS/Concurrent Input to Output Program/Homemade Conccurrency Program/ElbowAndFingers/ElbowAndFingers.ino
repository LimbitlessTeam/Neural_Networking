#include "background.h"
#include <Servo.h>

EventHandler eventHnd;
long elapsedtime;

int servo_pin = 9;
int muscle_pin = A0;
boolean hand_opened = true;
int opened_angle = 45, closed_angle = 0;
Servo servo;
float toggle_threshold = 60.0;
int servo_timer = 0;
int timer_threshold = 500;
int millisecondDelay = 5;
int pos = 0;

class Fingers : public Event
{
public:
	Fingers(long timelastrun, long cycle) : Event(timelastrun, cycle)
	{
  
	}
        ~Fingers()
        {
        }
	void run()
	{
            Event::run();
            if(hand_opened)
            {
              pos -= 2;
              servo.write(pos);
            } else {
              pos += 2;
              servo.write(pos);
            }
            
	}
	bool terminate()
	{  
            if((pos > closed_angle*2) && (hand_opened))
            {
              servo_timer = 0;
              return true; // time to stop
            }
            if((pos < opened_angle*2) && (!hand_opened))
            {
              servo_timer = 0;
              return true;
            }
	} 
	bool input()
	{
            // Raw value of the muscle sensor reading
            float muscle_sensor_value = analogRead(muscle_pin);
            // Muscle sensor value scaled down just for easier working
            float muscle_sensor_scaled = muscle_sensor_value * (180.0 / 1023.0);
            
            servo_timer = millis() - servo_timer;
            if (muscle_sensor_scaled >= toggle_threshold && servo_timer == timer_threshold)
            {
                // Change position of hand
                hand_opened = !hand_opened;
                
                if(hand_opened)
                  pos = opened_angle*2;
                else
                  pos = closed_angle*2;
                
            }
	}

};

void setup() {
  Fingers fingers(0, millisecondDelay);
  eventHnd.AddEvent(&fingers);
  
  pinMode(muscle_pin, INPUT);
  servo.attach(servo_pin);
  servo.write(opened_angle);
}

void loop() {
  elapsedtime = millis();
  eventHnd.CheckForInputs();
  eventHnd.CheckAllEventsToRun();
  
  if(servo_timer < timer_threshold)
    servo_timer++;
  
}
