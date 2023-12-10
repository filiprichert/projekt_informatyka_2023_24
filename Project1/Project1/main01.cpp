#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace sf;

class Missile {

public:
	Sprite shape;

	Missile(Texture *texture, Vector2f pos) {
		this->shape.setTexture(*texture);
		this->shape.setScale(0.1f, 0.1f);
		this->shape.setPosition(pos);
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
	Sprite shape;

	int HP;
	int HPMax;

	Enemy(Texture* texture, Vector2f pos) {
		this->HPMax = rand() % 3 + 1;
		this->HP = this->HPMax;

		this->shape.setTexture(*texture);
		this->shape.setScale(0.2f, 0.2f);
		this->shape.setPosition(pos);
	}
	~Enemy(){}
};


int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(800, 600), "Space shooter");
	window.setFramerateLimit(60);


	/*sf::Music music;
	if (!music.openFromFile("piu.mp3")) {
		return -1;
	}*/

	/*Font font;
	font.loadFromFile();*/ // do upe³nienia 

	Texture playerTex;
	playerTex.loadFromFile("Tekstury/statek.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Tekstury/wrog.png");

	Texture missileTex;
	missileTex.loadFromFile("Tekstury/pocisk1.png");
	//gracz init
	Player player(&playerTex);
	int shootTimer = 20;

	//wrog init
	std::vector<Enemy> enemies;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Gracz 
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.shape.move(0.f, -10.f);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.shape.move(0.f, 10.f);
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.shape.move(-10.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.shape.move(10.f, 0.f);

		if (shootTimer < 20)
			shootTimer++; 

		if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 20) { //sprzelanie
			player.missile.push_back(Missile(&missileTex, player.shape.getPosition()));
			shootTimer = 0;
			/*music.play();*/
		}

		//kolizja z ekranem 
		if (player.shape.getPosition().x <= 0)
			player.shape.setPosition(0.f, player.shape.getPosition().y);
		if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
			player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
		if (player.shape.getPosition().y <= 0)
			player.shape.setPosition(player.shape.getPosition().x, 0.f);
		if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
			player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);


		//pociski
		for (size_t i = 0; i < player.missile.size(); i++)
		{
			//ruch
			player.missile[i].shape.move(0.f, -20.f);


			//poza ekranem 
			if (player.missile[i].shape.getPosition().x > window.getSize().x)
				player.missile.erase(player.missile.begin() + i);
			
			//kolizja wroga

		};

		

		//wrog


		//rysowanie
		window.clear();
		window.draw(player.shape);

		for (size_t i = 0; i < player.missile.size(); i++) {
			window.draw(player.missile[i].shape);
		}

		window.display();
		
	}





	
	
}