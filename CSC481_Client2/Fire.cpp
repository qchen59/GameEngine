#include "Fire.h"


Fire::Fire() {

	rect.setSize(sf::Vector2f(10, 30));
}

void Fire::trans(float a, float b) {
	rect.setSize(sf::Vector2f(a, b));
}
