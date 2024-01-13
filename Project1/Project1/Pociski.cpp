#include "Pociski.h"

Missile::Missile(Texture* texture, Vector2f playerPosition) {
	this->shape.setTexture(*texture);
	this->shape.setScale(0.2f, 0.2f);
	this->shape.setPosition(playerPosition.x + 0.5f * (texture->getSize().x * 0.1f - this->shape.getGlobalBounds().width), playerPosition.y);
}

Missile::~Missile() {}