
#include "LimbitlessArduino.h"

// these are used to simulate how a arduino would get input
// not necessary in code that isn't being simulated on windows

bool ELBOWINPUT = false;
bool FINGERSINPUT = false;

// This is the initialization of the event handler which makes sure all code is run efficiently 
// and a time variable that is used by the program. 
EventHandler eventhandl;
double elapsedtime;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// This is an example of how to us the Event class /////////////////////////////////////////////////////////
////////////  I made two example event class. I called one elbow as if it is moving a elbow ///////////////////////////
//////////// and the other fingers as if it were mmoving fingers. /////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Elbow : public Event
{
public:
	int i; // counter used to tell when the event should stop running. 
	Elbow(double cycle) : Event(cycle)
	{
		i = 0; /// initialize the counter when the events object is created. 
	}
	void run()
	{
		// This function should always call the parent class's run() function like this
		// It sets time scheduling elements for the event
		Event::run();

		// in this example the run function simply counts to ten.
		cout << "running elbow..." << i << "\n";
		cout << "run time: " << elapsedtime << "\n";
		i += 1;
	}

	bool terminate()
	{
		// this code terminates the events process when the events counter gets over 10. 
		
		/// when you put your code in here make it return true when you want to stop your run function.
		if (i >= 10)
		{
			cout << "time to terminate elbow: " << elapsedtime << " \n";
			i = 0;
			return true;
		}
		return false;
	} 

	bool input()
	{
		// this if statement is used to simulate the code that would execute when a button is pressed or a muscle input is read.
		// on a Arduino it would look like this for a button:
		// if(digitalRead(button_pin) == HIGH)

		// make this return true when you get your input

		if (ELBOWINPUT == true) 
		{
			cout << "Got elbow input: " << elapsedtime << "\n";
			ELBOWINPUT = false;

			// input() should return true if the input it is reading in has happened. 
			return true;
		}
		return false;
	}
};

// This is another example event function. The purpose of having two events in this example
// is to show how the eventhandler can pass back and forth between run function giving each enough time
// so that two or more servos or process can run at once. 

class Fingers : public Event
{
public:
	int i;
	Fingers(double cycle) : Event(cycle)
	{
		i = 0;
	}
	void run()
	{
		Event::run();
		cout << "running fingers..." << i << "\n";
		cout << "run time: " << elapsedtime << "\n";
		i += 1;
	}
	bool terminate()
	{
		if (i >= 10)
		{
			cout << "time to terminate fingers: " << elapsedtime << " \n";
			i = 0;
			return true;
		}
		return false;
	}
	bool input()
	{
		if (FINGERSINPUT == true)
		{
			cout << "Got fingers input: " << elapsedtime << "\n";
			FINGERSINPUT = false;
			return true;
		}
		return false;
	}

};


// instantiate the two event objects
// I don't recommend changing these to be part of dynamic memory
// but its possible as long as the are deleted at the end of the programs execution and
// don't become memory leaks.

Elbow limb(10);
Fingers fingers(10);


int main()
{
	////////////////////////////////////////////////////////////////////////////////
	// this code would normally be in the setup() function of an arduino
	/////////////////////////////////////////////////////////////////////////////////
	// startCounter() wouldn't be used normally but allows me to simulate millis() function on windows
	StartCounter();

	// the two event objects must be added to the handler so it runs them
	eventhandl.AddEvent(&limb);
	eventhandl.AddEvent(&fingers);

	elapsedtime = millis();
	cout << "elapsedtime initially: " << elapsedtime << "\n";

	///////////////////////////////// end of setup()

	///////////////////////////////////////////////////////////////////////////////////////////
	// this while loop simulates the loop() function of the arduino
	// but I have it only run for 10,000 milliseconds (ten seconds) here for testing purposes
	/////////////////////////////////////////////////////////////////////////////////////////////

	while (elapsedtime <= 15000.0)
	{

		// I used these two if statements to simulate what would happen if arduino input was given
		// 2 seconds after the start of the program. Both inputs are given at the exact same time 
		// to see how the eventhandler handles two inputs at once.
		// see output picture or compile code to see!
		
		if ((elapsedtime >= 2000.000) && (elapsedtime <= 2006.00))
		{
			ELBOWINPUT = true; // simmulate elbow input. whatever input is ment for the elbow to move
			cout << "elbow should be 2000:  " << elapsedtime << "\n";
		}
		if ((elapsedtime >= 2000.0) && (elapsedtime <= 2006.00))
		{
			FINGERSINPUT = true; // simulate finger input. same as above but for fingers to move.
			cout << "fingers should be 2000: " << elapsedtime << "\n";
		}

		if ((elapsedtime >= 6000.0) && (elapsedtime <= 6006.0))
		{
			FINGERSINPUT = true;
			cout << "fingers should be 4000: " << elapsedtime << "\n";
		}
		///////////////////////////////////////////////////////////////////////////////////////////////
		// These two functions must be called for the eventhandler to work.
		// they let it check for any inputs and event processes that need to be run.
		//////////////////////////////////////////////////////////////////////////////////////////////

		eventhandl.CheckForInputs();
		eventhandl.CheckAllEventsToRun();

		// update elapsedtime variable. 
		elapsedtime = millis();
	}



	system("pause");
}