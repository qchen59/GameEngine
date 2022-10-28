#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "EventHandler.h"
#include "Shoot.h"

class Char : public GameObject
{
public:
	Shoot s;
	Char();
	void transform();
	void setP(float x, float y);
	void shoot(GameObject* go, sf::RenderWindow* wd);
	void update(GameObject* go, sf::RenderWindow* wd);
	void trans(float a, float b);
};


