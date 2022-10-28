#include "Event.h"
Event::Event(std::string type) {
	this->type = type;
}
std::string Event::getType() {
	return type;
}
void Event::setType(std::string str) {
	type = str;
}
int Event::getPriority() {
	return priority;
}
void Event::setPriority(int p) {
	priority = p;
}

float Event::getTime() {
	return time;
}
void Event::setTime(float time) {
	this->time = time;
}

GameObject* Event::getGO() {
	return go;
}
void Event::setGo(GameObject* go) {
	this->go = go;
}

void Event::setLR(bool lr) {
	this->lrflag = lr;
}
bool Event::getLR() {
	return lrflag;
}
void Event::setUD(bool up) {
	this->upflag = up;
}
bool Event::getUD() {
	return upflag;
}