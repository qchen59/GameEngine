#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
class Platform : public GameObject
{
public:
	Platform();
	void trans(float a, float b);
};
