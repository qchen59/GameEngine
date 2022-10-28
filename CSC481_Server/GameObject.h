#pragma once
#include"MovePattern.h"
#include <SFML/Graphics.hpp>
class Move;
class Collide;
class MovePattern;
class GameObject
{
protected:
	// Component
	sf::RectangleShape rect;
	bool focus = true;
	MovePattern* mp;
	float vY = 0;
	float time;
	bool inter = false;
	bool Ticchanged = false;
	int lrflag = 0;
	int upflag= 0;
	sf::Vector2f pre;


public:
	// constructor
	GameObject();
	// destructor
	~GameObject();
	void setSize(int a, int b);
	void setPosition(float x, float y);
	void updateMove(float time);
	void updateOnGround(bool update);
	void updateInter(bool update);
	void updatevY(float vy);
	void updateTime(float time);
	void updateFocus(bool focus);
	float getvY();
	float getTime();
	bool getFocus();
	bool getOnGround();
	bool getInter();
	void updateShape(float x, float y);
	void updatePosition(float x, float y);
	void updateTexture(sf::Texture* t);
	void updateColor(float a, float b, float c);
	bool getTic();
	void leftRight();
	void upDown();
	void updateTic(bool change);
	bool getLR();
	bool getUD();
	void updateLR(int LR);
	void updateUD(int UD);
	void setPre(sf::Vector2f v);
	sf::Vector2f getPre();
	sf::RectangleShape getShape();
};
