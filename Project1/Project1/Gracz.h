#ifndef GRACZ
#define GRACZ

#include "Game.h"

#include "MainMenu.h"

#include "Pociski.h"
class Missile;
class Player {
public:
	Player(sf::Texture* texture, sf::Vector2u playerPosition);
	~Player();

	Sprite shape;
	Texture* texture;
	int HP;
	int HPMax;

	std::vector<Missile> missile;

	bool lastShotLeft;
};

#endif GRACZ