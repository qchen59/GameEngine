#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Platform : public sf::RectangleShape
{
public:
	sf::RectangleShape rect;
	void setShape();
};
