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


void nowa_gra()
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
	gameOverText.setPosition(100.f, window.getSize().y/2);
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

			if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 15) { //sprzelanie
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
//Menu
enum MenuOption {
	Graj,
	Wczytaj,
	OGrze,
	Wyjdz
};

class GameMenu {
public:
	GameMenu(sf::RenderWindow& window) : window(window) {
		font.loadFromFile("Fonts/Stereotones.otf"); // Ustaw odpowiedni¹ œcie¿kê do pliku czcionki
		Initialize();
	}

	MenuOption Run() {
		while (window.isOpen()) {
			ProcessEvents();
			Render();
		}

		return Wyjdz; // W przypadku zamkniêcia okna
	}

private:
	static const int OptionCount = 4;
	int selectedOptionIndex = 0;
	sf::Font font;
	sf::Text text;
	sf::RenderWindow& window;
	std::vector<std::string> options;
	std::vector<sf::Text> menuTexts;

	void Initialize() {
		text.setFont(font);
		text.setCharacterSize(30);
		text.setFillColor(sf::Color::White);

		options = { "Graj", "Wczytaj", "O Grze", "Wyjdz" };

		for (int i = 0; i < OptionCount; ++i) {
			text.setString(options[i]);
			text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2, 150 + i * 60);
			menuTexts.push_back(text);
		}
	}

	void ProcessEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed) {
				HandleKeyPress(event.key.code);
			}
		}
	}

	void HandleKeyPress(sf::Keyboard::Key key) {
		if (key == sf::Keyboard::Up) {
			MoveUp();
		}
		else if (key == sf::Keyboard::Down) {
			MoveDown();
		}
		else if (key == sf::Keyboard::Enter) {
			PerformAction();
		}
	}

	void PerformAction() {
		switch (static_cast<MenuOption>(selectedOptionIndex)) {
		case Graj:
			nowa_gra(); // Tutaj mo¿esz wywo³aæ swoj¹ funkcjê Graj
			break;
		case Wczytaj:
			// Wczytaj grê - dodaj odpowiedni kod
			break;
		case OGrze:
			// Informacje o grze - dodaj odpowiedni kod
			break;
		case Wyjdz:
			window.close(); // Zamkniêcie okna - mo¿esz zast¹piæ w³aœciw¹ akcj¹
			break;
		}
	}


	void MoveUp() {
		if (selectedOptionIndex > 0) {
			selectedOptionIndex--;
		}
		else {
			selectedOptionIndex = OptionCount - 1;
		}
	}

	void MoveDown() {
		if (selectedOptionIndex < OptionCount - 1) {
			selectedOptionIndex++;
		}
		else {
			selectedOptionIndex = 0;
		}
	}

	void Render() {
		window.clear();

		for (int i = 0; i < OptionCount; ++i) {
			text = menuTexts[i];
			if (i == selectedOptionIndex) {
				text.setFillColor(sf::Color::Red);
			}
			else {
				text.setFillColor(sf::Color::White);
			}
			window.draw(text);
		}

		window.display();
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Gra 2D Menu");

	GameMenu gameMenu(window);
	MenuOption selectedOption = gameMenu.Run();

	// Tutaj mo¿esz dodaæ odpowiednie akcje dla wybranej opcji

	return 0;
}

