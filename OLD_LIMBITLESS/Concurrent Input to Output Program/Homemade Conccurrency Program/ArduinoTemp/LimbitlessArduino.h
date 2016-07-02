
// all of these include statements and the using namespace statement are
// so I can work on windows. I used visual studio professional 2013 to test my code
// and make sure it runs succesfully. 

#include <iostream>
#include <Windows.h>
using namespace std;


// These two variables are for windows QueryPerformanceCounter function
// which returns the amount of time since the function QueryPerformanceFrequency was called
// I used these windows functions to simulate what the millis() function does.
// the two windows functions TimeGetTime() and GetTickCount() are actually less precise then QueryPerformanceCounter.
_int64 counterstart;
double freq = 0.0;

// initializes the counter. 
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))   // initialize the counter and give an error if it doesn't work. 
		cout << "error";
	
	freq = double(li.QuadPart) / 1000.0;  // machines frequency. used to change to milliseconds in millis() (see below)
	QueryPerformanceCounter(&li);
	counterstart = li.QuadPart;
}
double millis()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return double(time.QuadPart - counterstart) / freq;  // calculate the time in millis. 
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
// this is the background code of the eventhandler
// this allows the code to run multiple "event processes" at once
/////////////////////////////////////////////////////////////////////////////////////////////////////


// The event class 
class Event {
public:
	double timelastrun;  // the last time this events run() function was called.  
	double cycle;   // the amount of time that should be given before run() is called again. 

	// all three of these functions are declared virtual because the should be overwritten by the 
	// child object. 

	// run is the only one with code in it that the child class should run. See the child class examples in Source1.cpp
	virtual void run() 
	{ 
		timelastrun = millis(); // this updates the timelastrun variable. 
	}
	virtual bool terminate() = 0;
	virtual bool input() = 0; 

	///////////// This is the event constructor. 
	//////////// When a event is created it should be passed its cycle time. The time you want to give any hardware used in the run()
	//////////// function to catch up. 
	Event( double cycle)
	{
		this->cycle = cycle;
		this->timelastrun = 0;
	}
	~Event()
	{
		timelastrun = 0;
		cycle = 0;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////
// The eventhandler class. 
// has a lot of similarities to a linked list as well as interrupt service routine code. 
//////////////////////////////////////////////////////////////////////////////////////////


class EventHandler {
public:
	// This node class is basically the same thing as a node of a linked list but holds events only
	class Node {
	public:
		Event* data;  // pointer to a event object
		Node* next;  // pointer to the next node in the linked list
		bool active; // boolean to decide if this process is active and should be run.
		Node(Event* ev, Node* pnt)
		{
			data = ev;   
			next = pnt;
			active = false;
		}
		~Node()
		{
			delete(data);
		}
	};

	Node* first; // The first node in the eventhandlers list
	Node* last; // the last node in the eventhandlers list
	Node* temp; // a temp node used for switch nodes around , etc etc
	int numOfElements;  // holds the number of nodes in the event handler list

	// basic constructor. everything is set to null because the list is empty.
	EventHandler()
	{
		first = last = temp = 0;
		numOfElements = 0;
	}

	// The destructor
	/// This goes through each node in the list starting with the first and deletes each node
	~EventHandler()
	{
		last = 0;
		for (int i = 0; i < numOfElements; i++)
		{
			temp = first;
			first = first->next;
			if (temp != 0)
			{
				if (temp->data != 0)
				{
					// The reason the data pointer is set to 0 here is because if it is deleted then the Event object will also be deleted
					// which will case a assertion error when the program finishes. The actual event object pointed to is loaded out of memeory
					// when the program ends. 
					temp->data = 0;
					// be CAREFUl changing this code in the future. It could easily become a memory leak or bug^^
				}
				delete(temp);
			}
		}
	}

	// Adds a event object to the eventhandlrs linked list.

	void AddEvent(Event* ev)
	{
		if (numOfElements == 0)
		{
			first = new Node(ev, 0);
			last = first;
		}
		else {
			last->next = new Node(ev, 0);
			last = last->next;
		}
		numOfElements++; // keep track of how many events are in the list
	}

	// these are just to set events to active and unactive through their nodes
	void MakeActive(Node* temp)
	{
		temp->active = true;
	}
	void MakeInactive(Node* temp)
	{
		temp->active = false;
	}

	
	void CheckForInputs()
	{
		// Cycle through the linkedList structure and check each event to see if its input() has been triggered. 
		temp = first;
		for (int i = 0; i < numOfElements; i++)
		{
			if ((temp->data->input() == true) && (temp->active == false))
			{
				cout << "making active \n";
				MakeActive(temp);
			}
			temp = temp->next;
		}
	}

	// runs through all events in eventhandlers list and checks each to see it's process needs to be stoped or continue
	// and then correspondingly stops it or runs it.
	void CheckAllEventsToRun()
	{
		temp = first;
		for (int i = 0; i < numOfElements; i++)
		{
			if ((temp->data->terminate() == true) && (temp->active == true))
			{
				MakeInactive(temp);
			}
			if ((temp->active == true) && (CheckToRun(temp) == true))
			{
				temp->data->run();
			}
			temp = temp->next;
		}
	}

	// This just makes sure that enough time has passed since a events run() function was previously
	// called for it to be called again.
	// this makes sure hardware has enough time to catch up
	bool CheckToRun(Node* node)
	{
		double currenttime = millis();
		double timeelapsed = currenttime - (node->data->timelastrun);
		if (timeelapsed >= node->data->cycle)
		{
			return true;
		}
		return false;
	}

};
