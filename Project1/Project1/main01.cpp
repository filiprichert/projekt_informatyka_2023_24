#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace sf;

class Missile {

public:
	Sprite shape;

	Missile(Texture *texture) {
		this->shape.setTexture(*texture);
		this->shape.setScale(0.3f, 0.3f);
	}

	~Missile() {}
};


class Player {

public:
	Sprite shape;
	Texture *texture;
	int HP;
	int HPMax;

	std::vector<Missile> missile;


	Player(Texture *texture) {
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(0.6f, 0.6f);
		
		
	}
	~Player() {}
};

class Enemy {

public:


};


int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "Space shooter");
	window.setFramerateLimit(60);

	/*Font font;
	font.loadFromFile();*/ // do upe³nienia 

	Texture playerTex;
	playerTex.loadFromFile("Tekstury/statek.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Tekstury/wrog.png");

	Texture missileTex;
	missileTex.loadFromFile("Tekstury/pocisk.png");

	Player player(&playerTex);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		window.draw(player.shape);

		window.display();
		
	}





	
	
}