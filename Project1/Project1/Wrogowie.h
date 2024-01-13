#ifndef WROGOWIE
#define WROGOWIE


#include "Game.h"
#include "MainMenu.h"
class Enemy
{
public:
	Enemy(sf::Texture* texture, Vector2u windowSize);
	~Enemy();
	Sprite shape;

	int HP;
	int HPMax;
};

#endif WROGOWIE