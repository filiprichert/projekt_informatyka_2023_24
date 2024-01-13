#pragma once

#include "Game.h"
#include "MainMenu.h"



class Missile {
public:
    Missile(sf::Texture* texture, Vector2f playerPosition);
    ~Missile();

    Sprite shape;
    Missile() {};
};

