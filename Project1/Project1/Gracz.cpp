#include "Gracz.h"
#include "Game.h"



Player::Player(Texture* texture, Vector2u windowSize) {
	this->HPMax = 10;
	this->HP = this->HPMax;

	this->texture = texture;
	this->shape.setTexture(*texture);

	this->shape.setScale(0.2f, 0.2f);
	this->shape.setPosition((windowSize.x - this->shape.getGlobalBounds().width) / 2.f, windowSize.y - this->shape.getGlobalBounds().height);

	this->lastShotLeft = true;
}
Player::~Player() {}