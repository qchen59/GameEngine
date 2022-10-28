#include "Char.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor
Char::Char()
{
	this->move = new Move;
	this->setSize(100, 100);
	this->setPosition(300, 600);
}

void Char::setP(float x, float y) {
	rect.setPosition(x, y);
}

void Char::shoot(GameObject* go, sf::RenderWindow* wd) {
	this->s.shoot(go, wd);
}
void Char::update(GameObject* go, sf::RenderWindow* wd) {
	this->s.update(go, wd);
}

void Char::trans(float a, float b) {
	rect.setSize(sf::Vector2f(a, b));
}


