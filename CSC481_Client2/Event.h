#pragma once
#include <string>
#include "GameObject.h"

class Event
{

public:
	float timestamp;
	std::string type;
	int priority;
	float time;
	GameObject* go;
	bool upflag;
	bool lrflag;
	Event(std::string type);
	std::string getType();
	void setType(std::string str);
	int getPriority();
	void setPriority(int);
	float getTime();
	void setTime(float time);
	GameObject* getGO();
	void setGo(GameObject* go);
	void setLR(bool lr);
	bool getLR();
	void setUD(bool up);
	bool getUD();
};







