#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Timeline.h"
#include "GameObject.h"

class MovingPlatform : public GameObject
{
public:
	sf::Texture* texture;
	MovingPlatform();
};
