#pragma once
#include "Event.h"
#include "GameObject.h"
#include<iostream>

class EventHandler
{
public:
	std::string type;
	GameObject* ch;
	Event* e;
	zmq::socket_t* socket;
	EventHandler();
	EventHandler(std::string type);
	void setCh(GameObject* ch);
	void onEvent(Event* e);
	void onChar();
	void onConnect();
	void setSocket(zmq::socket_t* socket);

};


