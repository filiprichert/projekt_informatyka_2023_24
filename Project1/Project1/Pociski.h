#ifndef POCISKI 
#define POCISKI

#include "Game.h"
#include "MainMenu.h"



class Missile {
public:
    Missile(Texture* texture, Vector2f playerPosition);
    ~Missile();

    Sprite shape;
    Missile() {};
};

#endif POCISKI