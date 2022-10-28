#pragma once
#include "Event.h"
#include "GameObject.h"
#include"Char.h"
#include<iostream>
class EventHandler
{
public:
	std::string type;
	GameObject* ch;
	Event* e;
	EventHandler();
	EventHandler(std::string type);
	void setCh(GameObject* ch);
	void onEvent(Event* e);
	void onChar();
};


