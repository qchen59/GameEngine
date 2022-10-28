#include "GameObject.h"
#include <iostream>
GameObject::GameObject()
{
	// no component by defualt	
}

GameObject::~GameObject()
{
}

void  GameObject::setSize(int a, int b) {
	rect.setSize(sf::Vector2f(a, b));
}

void  GameObject::setPosition(float x, float y) {
	rect.setPosition(x, y);
}


void GameObject::updateShape(float x, float y) {
	rect.move(x, y);
}

void GameObject::updatePosition(float x, float y) {
	rect.setPosition(x, y);
}

void GameObject::updateTexture(sf::Texture* t) {
	rect.setTexture(t);
}

void GameObject::updateColor(float a, float b, float c) {
	rect.setFillColor(sf::Color(a, b, c));
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

void  GameObject::leftRight() {
	mp->moveLeftRight(this);
}
void  GameObject::upDown() {
	mp->moveUpDown(this);
}

void GameObject::updateTime(float time) {
	this->time = time;
}

void GameObject::updateTic(bool change) {
	Ticchanged = change;
}

bool GameObject::getTic() {
	return Ticchanged;
}

bool GameObject::getLR() {
	return lrflag;
}

bool GameObject::getUD() {
	return upflag;
}

void GameObject::updateLR(int LR) {
	lrflag = LR;
}

void GameObject::updateUD(int UD) {
	upflag = UD;
}

