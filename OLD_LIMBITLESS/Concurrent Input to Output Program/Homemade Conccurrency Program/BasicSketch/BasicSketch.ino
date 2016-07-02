#include "background.h"

class XXX : public Event
{
public:
	XXX(long timelastrun, long cycle) : Event(timelastrun, cycle)
	{
  
	}
        ~XXX()
        {
        }
	void run()
	{
            Event::run();  // leave it
	}
	bool terminate()
	{  
            return true;
	} 
	bool input()
	{
            return true;
	}

};

EventHandler eventHnd;
long elapsedtime;

void setup() {
  XXX elbow(0, 0);
  XXX hand(0, 0);   // etc, etc
  eventHnd.AddEvent(&elbow);
}

void loop() {
  elapsedtime = millis();
  eventHnd.CheckForInputs();
  eventHnd.CheckAllEventsToRun();
}
