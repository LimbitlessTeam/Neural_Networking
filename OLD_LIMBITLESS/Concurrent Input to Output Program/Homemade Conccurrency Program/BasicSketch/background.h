/*
  background.h - Library that allows multiple inputs to run different processes
  at the same time without the use of Delay()
  Created by Ambrose B. Douglas, June 30, 2015
*/



#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <arduino.h>



class Event {
public:
	long timelastrun;
	long cycle;
	virtual void run() 
	{ 
		timelastrun = millis(); 
	}
	virtual bool terminate() = 0;
	virtual bool input() = 0; 
	Event(long timelastrun, long cycle)
	{
		this->cycle = cycle;
		this->timelastrun = timelastrun;
	}
	~Event()
	{
		timelastrun = 0;
		cycle = 0;
	}
};


class EventHandler {
public:
	class Node {
	public:
		Event* data;
		Node* next;
		bool active;
		Node(Event* ev, Node* pnt)
		{
			data = ev;   // eeeeeeeeeeerrrrrrrrrrrrrrrrgggggggggggg
			next = pnt;
			active = false;
		}
		~Node()
		{
			delete(data);
		}
	};

	Node* first;
	Node* last;
	Node* temp;
	int numOfElements;

	EventHandler()
	{
		first = last = temp = 0;
		numOfElements = 0;
	}
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
					temp->data->cycle = 10;
					temp->data = 0;
				}
				delete(temp);
			}
		}
		Empty();
	}
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
		numOfElements++;
	}
	void Empty()
	{
		
	}
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
		temp = first;
		for (int i = 0; i < numOfElements; i++)
		{
			if ((temp->data->input() == true) && (temp->active == false))
			{
				MakeActive(temp);
			}
		}
	}
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
		}
	}
	bool CheckToRun(Node* node)
	{
		long currenttime = millis();
		long timeelapsed = currenttime - (node->data->timelastrun);
		if (timeelapsed >= node->data->cycle)
		{
			return true;
		}
		return false;
	}

};

#endif

