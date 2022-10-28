#include "MovePattern.h"
#include <iostream>
void MovePattern::moveLeftRight(GameObject* go) {
	sf::Vector2f p = go->getShape().getPosition();
	int x = p.x;
	if (go->getTic()) {
		go->updateTic(false);
	}
	else {
		// the time that to finish one turn
		if (x >= 700.f) {
			//go->getShape().setPosition(700, p.y);
			//go->updatePosition(700, p.y);
			go->updateLR(1);
			
		}
		else if (x <= 0) {
			//go->getShape().setPosition(0, p.y);
			//go->updatePosition(0, p.y);
			go->updateLR(0);
		}
		if (go->getLR() == 0) {
			//go->getShape().move(150.f * go->getTime(), 0);
			go->updateShape(150.f * go->getTime(), 0.f);
		}
		else if (go->getLR() == 1) {
			//go->getShape().move(-150.f * go->getTime(), 0);
			go->updateShape(-150.f * go->getTime(), 0.f);
		}
	}


}
void MovePattern::moveUpDown(GameObject* go) {
	sf::Vector2f p = go->getShape().getPosition();
	int y = p.y;
	if (go->getTic()) {
		go->updateTic(false);
	}
	else {
		// the time that to finish one turn
		if (y >= 400.f) {
			//go->getShape().setPosition(700, p.y);
			//go->updatePosition(p.x, 400);
			go->updateUD(1);
		}
		else if (y <= 10) {
			//go->getShape().setPosition(0, p.y);
			//go->updatePosition(p.x, 10);
			go->updateUD(0);
		}
		if (go->getUD() == 0) {
			//go->getShape().move(150.f * go->getTime(), 0);
			go->updateShape(0, 150.f * go->getTime());
		}
		else if (go->getUD() == 1) {
			//go->getShape().move(-150.f * go->getTime(), 0);
			go->updateShape(0, -150.f * go->getTime());
		}
	}
}