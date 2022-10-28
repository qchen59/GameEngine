#pragma once
#include <string>
#include "GameObject.h"
#include <zmq.hpp>
class Event
{

public:
	std::string type;
	int priority;
	float time;
	GameObject* go;
	bool upflag;
	bool lrflag;
	int cid;
	zmq::socket_t* socket;
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
	void setSocket(zmq::socket_t* socket);
	zmq::socket_t* getSocket();
};







