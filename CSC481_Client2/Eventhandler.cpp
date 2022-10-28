#include "Eventhandler.h"
EventHandler::EventHandler() {
}
EventHandler::EventHandler(std::string type) {
	this->type = type;
}
void EventHandler::setCh(GameObject* ch) {
	this->ch = ch;
}
void EventHandler::onEvent(Event* e) {
	this->e = e;
	if (type.compare("char") == 0) {
		onChar();
	}
}


void EventHandler::onChar() {
	if (e->getType().compare("input") == 0) {
		ch->updateMove(e->getTime());
	}
	else if (e->getType().compare("death") == 0) {
		//ch->setPosition(1000, 1000);


	}
	else if (e->getType().compare("Platformcollision") == 0) {
		//			c.rect.setPosition(mp.rect.getPosition().x, mp.rect.getPosition().y - 90);
		if (ch->getShape().getPosition().y + 50 <= e->getGO()->getShape().getPosition().y - 9) {
			// ch->inter = true;
			ch->updateInter(true);
			ch->setPosition(ch->getShape().getPosition().x, ch->getShape().getPosition().y);
			ch->setPre(sf::Vector2f(ch->getPre().x, ch->getPre().y));
		}
	}
	else if (e->getType().compare("spawn") == 0) {
		ch->setPosition(10, 500);
		ch->setPre(sf::Vector2f(10, 500));
		ch->updateInter(true);
	}
	else if (e->getType().compare("MovingPlatformcollisionLR") == 0) {

		if (ch->getShape().getPosition().y + 50 <= e->getGO()->getShape().getPosition().y - 49) {
			ch->updateInter(true);
			if (e->getLR() == 0) {
				ch->setPosition(ch->getShape().getPosition().x + 150.f * e->getTime(), ch->getShape().getPosition().y);
				ch->setPre(sf::Vector2f(ch->getPre().x + 150.f * e->getTime(), ch->getPre().y));

			}
			else if (e->getLR() == 1) {
				ch->setPosition(ch->getShape().getPosition().x - 150.f * e->getTime(), ch->getShape().getPosition().y);
				ch->setPre(sf::Vector2f(ch->getPre().x - 150.f * e->getTime(), ch->getPre().y));

			}
		}
	}
	else if (e->getType().compare("MovingPlatformcollisionUD") == 0) {
		if (ch->getShape().getPosition().y + 50 <= e->getGO()->getShape().getPosition().y - 49) {
			ch->updateInter(true);
			if (e->getUD() == 0) {
				ch->setPosition(ch->getShape().getPosition().x, ch->getShape().getPosition().y + 150.f * e->getTime());
				ch->setPre(sf::Vector2f(ch->getPre().x, ch->getPre().y + 150.f * e->getTime()));
			}
			else if (e->getUD() == 1) {
				ch->setPosition(ch->getShape().getPosition().x, ch->getShape().getPosition().y - 150.f * e->getTime());
				ch->setPre(sf::Vector2f(ch->getPre().x, ch->getPre().y - 150.f * e->getTime()));
			}
		}
	}
}