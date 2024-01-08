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


void nowa_gra(RenderWindow& window)
{
	srand(time(NULL));

	RenderWindow window(VideoMode(1600, 1400), "Space shooter");
	window.setFramerateLimit(60);


	/*sf::Music music;
	if (!music.openFromFile("piu.mp3")) {
		return -1;
	}*/

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
	Player player(&playerTex);
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




	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (player.HP >= 0) {



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
			if (enemySpawnTimer < 25)
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
			//UI Update 
			scoreText.setString("Wynik:" + std::to_string(score));
			//rysowanie
		}
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
			eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
			eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
			window.draw(eHpText);
			window.draw(enemies[i].shape);
		}

		//UI
		window.draw(scoreText);
		window.draw(hpText);

		if (player.HP <= 0) {
			window.draw(gameOverText);
		}


		window.display();

	}
}





// Funkcja do wyœwietlania menu
void wyswietl_menu(RenderWindow& window) {
	Font font;
	font.loadFromFile("Fonts/Stereotones.otf");

	Text grajText, wynikiText, oGrzeText, wyjdzText;
	grajText.setFont(font);
	grajText.setCharacterSize(40);
	grajText.setFillColor(Color::White);
	grajText.setString("Graj");
	grajText.setPosition(600.f, 300.f);

	wynikiText.setFont(font);
	wynikiText.setCharacterSize(40);
	wynikiText.setFillColor(Color::White);
	wynikiText.setString("Wyniki");
	wynikiText.setPosition(600.f, 400.f);

	oGrzeText.setFont(font);
	oGrzeText.setCharacterSize(40);
	oGrzeText.setFillColor(Color::White);
	oGrzeText.setString("O Grze");
	oGrzeText.setPosition(600.f, 500.f);

	wyjdzText.setFont(font);
	wyjdzText.setCharacterSize(40);
	wyjdzText.setFillColor(Color::White);
	wyjdzText.setString("Wyjdz");
	wyjdzText.setPosition(600.f, 600.f);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
					if (grajText.getGlobalBounds().contains(mousePos)) {
						// Opcja Graj - wybór poziomu trudnoœci
						// ... (Dodaj kod wybieraj¹cy poziom trudnoœci)
					}
					else if (wynikiText.getGlobalBounds().contains(mousePos)) {
						// Opcja Wyniki - wyœwietlanie wyników
						// ... (Dodaj kod wyœwietlaj¹cy wyniki)
					}
					else if (oGrzeText.getGlobalBounds().contains(mousePos)) {
						// Opcja O Grze - wyœwietlanie instrukcji
						// ... (Dodaj kod wyœwietlaj¹cy instrukcjê)
					}
					else if (wyjdzText.getGlobalBounds().contains(mousePos)) {
						// Opcja Wyjdz - pytanie o potwierdzenie
						return;
					}
				}
			}
		}

		window.clear();
		window.draw(grajText);
		window.draw(wynikiText);
		window.draw(oGrzeText);
		window.draw(wyjdzText);
		window.display();
	}
}

int main() {
	RenderWindow window(VideoMode(1600, 1400), "Space shooter");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::Escape) {
				// Wywo³aj menu po wciœniêciu klawisza Escape
				wyswietl_menu(window);
			}
		}

		window.clear();
		// ... (Pozosta³a czêœæ gry, np. nowa_gra())
		window.display();
	}

	return 0;
}
