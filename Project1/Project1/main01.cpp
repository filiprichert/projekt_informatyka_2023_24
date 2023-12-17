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

	Enemy(Texture* texture, Vector2u windowSize) {
		this->HPMax = rand() % 3 + 1;
		this->HP = this->HPMax;

		this->shape.setTexture(*texture);
		this->shape.setScale(0.2f, 0.2f);
		this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().width), 0.0f);
		//this->shape.setPosition(rand() % static_cast<int>(windowSize.x - this->shape.getGlobalBounds().width), 0.0f);
	}
	~Enemy(){}
};


int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(1000, 800), "Space shooter");
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
	int enemySpawnTimer = 0;
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

		if (shootTimer < 25)
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
			if (player.missile[i].shape.getPosition().x > window.getSize().x) {
				player.missile.erase(player.missile.begin() + i);
				break;
			}
			
			//kolizja wroga
			for (size_t k = 0; k < enemies.size(); k++)
			{
				if (player.missile[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds())) {
					enemies.erase(enemies.begin() + k);
					player.missile.erase(player.missile.begin() + i);
					break;
				}
			}
		};

		

		//Wrog
		if(enemySpawnTimer < 25)
			enemySpawnTimer++;

		if (enemySpawnTimer >= 25) {
			enemies.push_back(Enemy(&enemyTex, window.getSize()));
			enemySpawnTimer = 0;
		}


		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].shape.move(0.f, 4.f);

			if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width) {
				enemies.erase(enemies.begin() + i);
				break;
			}

			if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
				enemies.erase(enemies.begin() + i);
				player.HP--; //zadawanie obrarzen graczowi 
				break;
			}

		}


		//rysowanie
		window.clear();
		//gracz
		window.draw(player.shape);

		//pociski
		for (size_t i = 0; i < player.missile.size(); i++) {
			window.draw(player.missile[i].shape);
		}

		//wrog
		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i].shape);
		}

		window.display();
		
	}





	
	
}