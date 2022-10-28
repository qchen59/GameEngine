#pragma once
#include"Collide.h"
#include"Move.h"
#include <SFML/Graphics.hpp>
class Move;
class Collide;
class GameObject
{
protected:
	// Component
	sf::RectangleShape rect;
	bool focus = true;
	Collide* collide;
	Move* move;
	float vY = 0;
	float time;
	bool inter = false;
	sf::Vector2f pre;


public:
	// constructor
	GameObject();
	// destructor
	~GameObject();
	void setSize(int a, int b);
	void setPosition(float x, float y);
	void updateMove(float time);
	void updateInter(bool update);
	void updatevY(float vy);
	void updateFocus(bool focus);
	float getvY();
	float getTime();
	bool getFocus();
	bool getInter();
	void updateShape(float x, float y);
	void updatePosition(float x, float y);
	void updateTexture(sf::Texture* t);
	void updateColor(float a, float b, float c);
	bool detectCollision(GameObject* other);
	void setPre(sf::Vector2f v);
	sf::Vector2f getPre();
	sf::RectangleShape getShape();
};
