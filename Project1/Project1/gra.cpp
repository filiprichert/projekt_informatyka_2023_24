#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "Game.h"

using namespace sf;

class Missile {

public:
	Sprite shape;

	Missile(Texture *texture, Vector2f playerPosition) {
		this->shape.setTexture(*texture);
		this->shape.setScale(0.2f, 0.2f);
		this->shape.setPosition(playerPosition.x + 0.5f * (texture->getSize().x * 0.1f - this->shape.getGlobalBounds().width), playerPosition.y);
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
	bool lastShotLeft;

	Player(Texture *texture, Vector2u windowSize) {
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture);

		this->shape.setScale(0.2f, 0.2f);
		this->shape.setPosition((windowSize.x - this->shape.getGlobalBounds().width) / 2.f, windowSize.y - this->shape.getGlobalBounds().height);

		this->lastShotLeft = true;
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


void nowa_gra()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(1400, 1200), "Space shooter");
	window.setFramerateLimit(60);


	sf::Music music;
	if (!music.openFromFile("piu.mp3")) {
		
	}

	Texture backgroundTex;
	backgroundTex.loadFromFile("Tekstury/poziom.png");
	backgroundTex.setRepeated(true);
	Sprite background;
	background.setTexture(backgroundTex);
	background.setScale(static_cast<float>(window.getSize().x) / backgroundTex.getSize().x,
		static_cast<float>(window.getSize().y) / backgroundTex.getSize().y);

	Font font;
	font.loadFromFile("Fonts/Stereotones.otf");

	Texture playerTex;
	playerTex.loadFromFile("Tekstury/statek.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Tekstury/wrog.png");

	Texture missileTex;
	missileTex.loadFromFile("Tekstury/pocisk1.png");

	//UI init
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::Green);
	scoreText.setPosition(10.f, 10.f);

	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(100.f, window.getSize().y / 2);
	gameOverText.setString("Koniec gry!!!");



	//gracz init
	int score = 0;
	Player player(&playerTex, window.getSize());
	int shootTimer = 20;

	Text hpText;
	hpText.setFont(font);
	hpText.setCharacterSize(24);
	hpText.setFillColor(Color::Green);

	//wrog init
	int enemySpawnTimer = 0;
	std::vector<Enemy> enemies;

	Text eHpText;
	eHpText.setFont(font);
	eHpText.setCharacterSize(24);
	eHpText.setFillColor(Color::Red);

	// Aktualizacja czasu gry
	Text timeText;
	timeText.setFont(font);
	timeText.setCharacterSize(20);
	timeText.setFillColor(Color::Green);
	timeText.setPosition(window.getSize().x - 200.f, 10.f);

	Clock clock;
	Time elapsed;


	while (window.isOpen())
	{
		// Pomiar czasu gry
		elapsed = clock.getElapsedTime();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (player.HP >= 0) {



			int seconds = static_cast<int>(elapsed.asSeconds());
			//Gracz 
			if (Keyboard::isKeyPressed(Keyboard::W))
				player.shape.move(0.f, -10.f);
			if (Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0.f, 10.f);
			if (Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-10.f, 0.f);
			if (Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(10.f, 0.f);

			hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
			hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

			if (shootTimer < 15)
				shootTimer++;

			if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 15) { //sprzelanie
				//player.missile.push_back(Missile(&missileTex, player.shape.getPosition()));
				//shootTimer = 0;

				if (player.lastShotLeft) {
					player.missile.push_back(Missile(&missileTex, Vector2f(player.shape.getPosition().x, player.shape.getPosition().y)));
				}
				else {
					player.missile.push_back(Missile(&missileTex, Vector2f(player.shape.getPosition().x + player.shape.getGlobalBounds().width, player.shape.getPosition().y)));
				}

				shootTimer = 0;
				player.lastShotLeft = !player.lastShotLeft;
				music.play();
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
						if (enemies[k].HP <= 1) {
							score += enemies[k].HPMax;
							enemies.erase(enemies.begin() + k);
						}
						else {
							enemies[k].HP--; //zadawanie obrarzen od wrogow
						}


						player.missile.erase(player.missile.begin() + i);
						break;
					}
				}
			};



			//Wrog
			if (enemySpawnTimer < 45)
				enemySpawnTimer++;

			if (enemySpawnTimer >= 45) {
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
			//UI Update 
			scoreText.setString("Wynik:" + std::to_string(score));


			// Dodaj kod do aktualizacji czasu gry
			int hours = seconds / 3600;
			int minutes = (seconds % 3600) / 60;
			seconds = seconds % 60;
			timeText.setString("Czas: " + std::to_string(hours) + "." + std::to_string(minutes) + "." + std::to_string(seconds));

			//rysowanie
		}

	

		window.clear();
		
		//tlo
		window.draw(background);

		//gracz
		window.draw(player.shape);

		//pociski
		for (size_t i = 0; i < player.missile.size(); i++) {
			window.draw(player.missile[i].shape);
		}

		//wrog
		for (size_t i = 0; i < enemies.size(); i++)
		{
			eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
			eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
			window.draw(eHpText);
			window.draw(enemies[i].shape);
		}

		//UI
		window.draw(scoreText);
		window.draw(hpText);
		/*timeText.setString(timeString);*/
		window.draw(timeText);


		if (player.HP <= 0) {
			window.draw(gameOverText);
		}


		window.display();

	}
}

int main() {
	nowa_gra();
	return 0;
}






