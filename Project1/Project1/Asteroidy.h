#ifndef ASTEROID
#define ASTEROID


#include "Game.h"
class Asteroid
{
public:
	Sprite shape;
	Vector2f movement;

    Asteroid(sf::Texture* texture, sf::Vector2u windowSize);
	~Asteroid();

	float rotationSpeed;
	int HP;
	int HPMax;
	int side;
	float angle;
	int size;
};

#endif ASTEROID