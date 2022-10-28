#include "Eventhandler.h"
EventHandler::EventHandler() {
}
EventHandler::EventHandler(std::string type) {
	this->type = type;
}
void EventHandler::setCh(GameObject* ch) {
	this->ch = ch;
}

void EventHandler::setSocket(zmq::socket_t* socket) {
	this->socket = socket;
}

void EventHandler::onEvent(Event* e) {
	this->e = e;
	if (type.compare("connection") == 0) {
		onConnect();
	}
}

void EventHandler::onConnect() {
	//  Send the client id
	zmq::message_t message(5); snprintf((char*)message.data(), 5, "%d", e->cid);
	e->getSocket()->send(message);
}

