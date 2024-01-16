#include "Wrogowie.h"


Enemy::Enemy(Texture* texture, Vector2u windowSize) {
  
    
   
    this->HPMax = rand() % 3 + 1;
 
    this->HP = this->HPMax;

    this->shape.setTexture(*texture);
    this->shape.setScale(0.2f, 0.2f);
    this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().width), -50.0f);
}
Enemy::~Enemy() {}
