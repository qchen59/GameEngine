#include "Move.h"

void Move::move(GameObject* go) {
 if (go->getInter()) {
		// ground based movement and actions
		if (go->getFocus()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				//go->getShape().move(-150.f * go->getTime(), 0.f);
				go->updateShape(-150.f * go->getTime(), 0.f);
				go->setPre(sf::Vector2f(go->getPre().x - 150.f * go->getTime(), go->getPre().y));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				//go->getShape().move(150.f * go->getTime(), 0.f);
				go->updateShape(150.f * go->getTime(), 0.f);
				go->setPre(sf::Vector2f(go->getPre().x + 150.f * go->getTime(), go->getPre().y));
			}
			// check to see if the spacebar was pressed to jump
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				//vY = -1000;
				go->updateInter(false);
				go->updatevY(-1000);

			}
		}

	}
	else {
		// air based movement and actions
		if (go->getFocus()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				//go->getShape().move(-150.f * go->getTime(), 0.f);
				go->updateShape(-150.f * go->getTime(), 0.f);
				go->setPre(sf::Vector2f(go->getPre().x - 150.f * go->getTime(), go->getPre().y));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				//go->getShape().move(150.f * go->getTime(), 0.f);
				go->updateShape(150.f * go->getTime(), 0.f);
				go->setPre(sf::Vector2f(go->getPre().x + 150.f * go->getTime(), go->getPre().y));
			}
		}
		// apply gravity
		//vY += 2400 * time;
		go->updatevY(go->getvY() + 2400 * go->getTime());

	}
	float x = go->getShape().getPosition().x;
	float y = go->getShape().getPosition().y;
	// movement and collision work after you've figured out the x and y acceleration of the player
	if (!go->getInter()) {
		y += go->getvY() * go->getTime();
		if (y > 501) {
			y = 501;
		}
		if (go->getPre().y > 501) {
			go->setPre(sf::Vector2f(go->getPre().x, 501));
		}
		//if (y < 0) {
		//	y = 0;
		//}
		//if (go->getShape().getPosition().x < 0) {
		//	x = 0;
		//}
		//if (go->getShape().getPosition().x > 700) {
		//	x = 700;
		//}
		//go->getShape().setPosition(x, y);
		go->updatePosition(x, y);
		go->setPre(sf::Vector2f(go->getPre().x, y));
	}
}
