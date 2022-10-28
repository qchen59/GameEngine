#include "MovingPlatform.h"


MovingPlatform::MovingPlatform() {
    texture = new sf::Texture();
    if (!texture->loadFromFile("ufo.png"))
    {
        std::cout << "ERROR MESSAGE" << std::endl;
    }
    updateTexture(texture);
	rect.setSize(sf::Vector2f(80.f, 80.f));
	collide = new Collide;
}

