#include "EventManager.h"
#include <iostream>
Event* event;

EventManager::EventManager() {

}

// use string to represent the event type
void EventManager::regist(std::string str, EventHandler* eh) {
	if (!handlers.count(str)) {
		std::list<EventHandler*> l;
		l.push_back(eh);
		handlers.insert_or_assign( str,l );
	}
	else {
		handlers.at(str).push_back(eh);
	}
}
void EventManager::evenh(EventHandler* eh) {
	this->eh = eh;
}
void EventManager::unregist(std::string str, EventHandler* eh) {
	// Peek event
	handlers.at(str).clear();

	// If  the queue is not empty

}
void EventManager::raise(Event* e) {
	// push based on priority
	events.push(e);
//	std::cout << events.top()->getType() << std::endl;
}
void EventManager::handleEvents() {
	//std::cout << events.size() << std::endl;
	while (!events.empty()) {
		// Peek of the queue
		event = events.top();
		events.pop();
		// Get the list of handlers
		//std::cout << event->getType() << std::endl;
		eh->onEvent(event);
		// handlers.at(event.getType()).clear();
	}
}
// use int to represent the priority, smaller int indicates higher priority
void EventManager::handleEvent() {
	// Peek of the queue
	event = events.top();
	if (event != NULL) {
		events.pop();
		// Get the list of handlers
		//std::cout << event->getType() << std::endl;
		eh->onEvent(event);
		// handlers.at(event.getType()).clear();
	}
}
