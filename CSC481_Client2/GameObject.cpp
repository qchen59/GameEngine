#include "GameObject.h"
#include <iostream>
GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	delete collide;
	delete move;
}

void  GameObject::setSize(int a, int b) {
	rect.setSize(sf::Vector2f(a,b));
}

void  GameObject::setPosition(float x, float y) {
	rect.setPosition(x, y);
}

void GameObject::updateMove(float time) {
	this->time = time;
	 //move->move(&rect,onGround,inter,vY,time,focus );
	move->move(this);
}

void GameObject::updateShape(float x, float y) {
	rect.move(x,y);
}

void GameObject::updatePosition(float x, float y) {
	rect.setPosition(x, y);
}

void GameObject::updateTexture(sf::Texture* t) {
	rect.setTexture(t);
}

void GameObject::updateColor(float a, float b, float c) {
	rect.setFillColor(sf::Color(a,b,c));
}

void GameObject::updateFocus(bool focus) {
	this->focus = focus;
}

void GameObject::updateInter(bool update) {
	inter = update;
}
void GameObject::updatevY(float vy) {
	vY = vy;
}
float GameObject::getvY() {
	return vY;
}
float GameObject::getTime()
{
	return time;
}
bool GameObject::getFocus()
{
	return focus;
}


bool GameObject::getInter()
{
	return inter;
}

sf::RectangleShape GameObject::getShape() {
	return rect;
}

bool GameObject::detectCollision(GameObject* other) {
	return collide->collision(this, other);
}

void GameObject::setPre(sf::Vector2f v) {
	pre = v;
}
sf::Vector2f GameObject::getPre() {
	return pre;
}