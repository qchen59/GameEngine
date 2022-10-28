#include "Platform.h"

void Platform::setShape()
{
	rect.setSize(sf::Vector2f(1000.f, 1000.f));
	rect.setFillColor(sf::Color(100, 100, 50));
	rect.setPosition(0, 500.f);

}
