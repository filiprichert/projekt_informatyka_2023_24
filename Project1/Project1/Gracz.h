#pragma once

#include "Game.h"
#include "Pociski.h"
#include "MainMenu.h"

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

