#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <list>
#include "Fire.h"
#include "MovingPlatform.h"

class GameObject;
class Shoot
{
public:
	bool p = false;
	Collide cld;
	Shoot();
	std::list<GameObject> fl;
	std::list<GameObject> sl;
	void shoot(GameObject* go, sf::RenderWindow* wd);
	void update(GameObject* go, sf::RenderWindow* wd);
};

