#include "MovingPlatform.h"


MovingPlatform::MovingPlatform() {
	rect.setSize(sf::Vector2f(100.f, 100.f));
	collide = new Collide;
}

