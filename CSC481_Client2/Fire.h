#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
class Fire: public GameObject
{
public:
	Fire();
	void trans(float a, float b);
};
