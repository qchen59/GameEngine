#pragma once
#include "EventHandler.h"
#include <map>
#include <string>
#include <list>
#include "Event.h"
#include <queue>

class comparision {
public:
	bool operator()(Event* e, Event* e2) {
		return e->getPriority() > e2->getPriority();
	}
};
class EventManager
{
protected:
	std::map < std::string, std::list<EventHandler*>> handlers;
	std::priority_queue<Event*, std::vector<Event*>, comparision> events;
	EventHandler* eh;
public:
	EventManager();
	// use string to represent the event type
	void regist(std::string, EventHandler* eh);
	void unregist(std::string, EventHandler* eh);
	void evenh(EventHandler* eh);
	void raise(Event* e);
	void handleEvents();
	// use int to represent the priority, smaller int indicates higher priority
	void handleEvents(int p);

};

