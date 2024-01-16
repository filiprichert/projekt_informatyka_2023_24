#ifndef GRACZ
#define GRACZ

#include "Game.h"

#include "MainMenu.h"

#include "Pociski.h"
class Missile;
class Player {
public:
	Player(Texture* texture, Vector2u playerPosition);
	~Player();

	Sprite shape;
	Texture* texture;
	int HP;
	int HPMax;

	vector<Missile> missile;

	bool lastShotLeft;
};

#endif GRACZ