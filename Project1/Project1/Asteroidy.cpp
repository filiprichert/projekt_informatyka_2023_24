#include "Asteroidy.h"

Asteroid::Asteroid(Texture* texture, Vector2u windowSize) {
	this->HPMax = 1;
	this->HP = this->HPMax;

	this->shape.setTexture(*texture);


	this->shape.setScale(0.2f, 0.2f);

	this->shape.setOrigin(this->shape.getLocalBounds().width / 2.f, this->shape.getLocalBounds().height / 2.f);

	this->side = rand() % 2;
	this->angle = (side == 0) ? rand() % 45 + 45.f : -(rand() % 45 + 45.f);
	if (side == 0) { // Lewy bok
		this->shape.setPosition(-30.0f, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
	}
	else { // Prawy bok
		this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width + 50.0f, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
	}
}
Asteroid::~Asteroid() {}
