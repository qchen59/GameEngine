#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
class GameObject;
class Move
{
public:
	//float move(sf::Shape* s, bool onGround, bool inter, float yy, float time, bool focus);
	void move(GameObject* go);
};

