#ifndef ASTEROID
#define ASTEROID


#include "Game.h"
class Asteroid
{
public:
	Sprite shape;
	Vector2f movement;

    Asteroid(Texture* texture, Vector2u windowSize);
	~Asteroid();

	float rotationSpeed;
	int HP;
	int HPMax;
	int side;
	float angle;
	int size;
};

#endif ASTEROID