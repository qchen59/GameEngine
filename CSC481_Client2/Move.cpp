#include "Move.h"

void Move::move(GameObject* go) {

		if (go->getFocus()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				//go->getShape().move(-150.f * go->getTime(), 0.f);
				go->updateShape(-250.f * go->getTime(), 0.f);
				go->setPre(sf::Vector2f(go->getPre().x - 150.f * go->getTime(), go->getPre().y));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				//go->getShape().move(150.f * go->getTime(), 0.f);
				go->updateShape(250.f * go->getTime(), 0.f);
				go->setPre(sf::Vector2f(go->getPre().x + 150.f * go->getTime(), go->getPre().y));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				//go->getShape().move(150.f * go->getTime(), 0.f);
				go->updateShape(0.f, 250.f * go->getTime());
				go->setPre(sf::Vector2f(go->getPre().x, go->getPre().y + 150.f * go->getTime()));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				//go->getShape().move(150.f * go->getTime(), 0.f);
				go->updateShape(0.f, 250.f * go->getTime());
				go->setPre(sf::Vector2f(go->getPre().x, go->getPre().y - 150.f * go->getTime()));
			}

		}
}
