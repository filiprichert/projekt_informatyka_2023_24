#include "Game.h"
#include "MainMenu.h"
#include "Poziom.h"
#include "Asteroidy.h"
#include "Gracz.h"
#include "Wrogowie.h"
#include "Pociski.h"
#include "MenuGame.h"

Game::Game(sf::RenderWindow& window) : window(window) { czygra = true; }

Game::~Game() {}



void Game::nowa_gra(trudnosc t) {

	

	srand(time(NULL));
	Music music;
	Music music1;
	music.openFromFile("piu.mp3");
	music1.openFromFile("SC2.mp3");
	music1.getLoop();
	music1.play();

	Font font;
	Texture backgroundTex;
	Texture asteroidTex;
	Texture playerTex;
	Texture enemyTex;
	Texture missileTex;
	asteroidTex.loadFromFile("Tekstury/asteroida.png");



	if (t == NORMAL) {
		backgroundTex.loadFromFile("Tekstury/poziom.png");

	}
	else
	{
		backgroundTex.loadFromFile("Tekstury/2poziom.png");
		
	}
	
	backgroundTex.setRepeated(true);
	Sprite background;
	background.setTexture(backgroundTex);
	background.setScale(
		static_cast<float>(window.getSize().x) / backgroundTex.getSize().x,
		static_cast<float>(window.getSize().y) / backgroundTex.getSize().y);

	
	font.loadFromFile("Fonts/Stereotones.otf");

	
	playerTex.loadFromFile("Tekstury/statek.png");

	
	enemyTex.loadFromFile("Tekstury/wrog.png");

	
	missileTex.loadFromFile("Tekstury/pocisk1.png");

	

	//UI init
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::Green);
	scoreText.setPosition(10.f, 10.f);

	//koniec gry
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

	//asteroida
	int asteroidSpawnTimer = 0;
	std::vector<Asteroid> asteroids;

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
	
	while (window.isOpen() && czygra)
	{
		// Pomiar czasu gry
		elapsed = clock.getElapsedTime();


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {

			MenuGame menuG(this);
			menuG.MenuG();
		}

		if (Keyboard::isKeyPressed(Keyboard::F1)) {
			Help help;
			help.GameHelp();
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


				if (player.lastShotLeft) {
					player.missile.push_back(Missile(&missileTex, Vector2f(player.shape.getPosition().x, player.shape.getPosition().y)));
				}
				else {
					player.missile.push_back(Missile(&missileTex, Vector2f(player.shape.getPosition().x + player.shape.getGlobalBounds().width - 10.0f, player.shape.getPosition().y)));
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
			if (t == HARD) {
				// Asteroid
				if (asteroidSpawnTimer < 45)
					asteroidSpawnTimer++;

				if (asteroidSpawnTimer >= 45) {
					asteroids.push_back(Asteroid(&asteroidTex, window.getSize()));
					asteroidSpawnTimer = 0;
				}


				for (size_t i = 0; i < asteroids.size(); i++) {
					if (asteroids[i].side == 0)
					{
						asteroids[i].shape.move(4.0f, 0.0f);
					}
					else
					{
						asteroids[i].shape.move(-4.0f, 0.0f);
					}
					float speed = rand() % 3;

					// Oblicz sk³adowe x i y na podstawie k¹ta
					float deltaX = speed * cos(asteroids[i].angle * 3.14 / 180);
					float deltaY = speed * sin(asteroids[i].angle * 3.14 / 180);

					asteroids[i].shape.move(deltaX, deltaY);

					if (asteroids[i].shape.getPosition().y >= window.getSize().y) {
						asteroids.erase(asteroids.begin() + i);
						break;
					}

					// Kolizja z graczem
					if (asteroids[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
						asteroids.erase(asteroids.begin() + i);
						player.HP--; // Gracz traci jedno ¿ycie
						break;
					}

					// Kolizja z pociskiem
					for (size_t k = 0; k < player.missile.size(); k++) {
						if (player.missile[k].shape.getGlobalBounds().intersects(asteroids[i].shape.getGlobalBounds())) {
							player.missile.erase(player.missile.begin() + k);
							asteroids.erase(asteroids.begin() + i);
							score++;
							break;
						}
					}

					float rotationSpeed = 0.5f;
					asteroids[i].shape.rotate(rotationSpeed);
				}
			}

			//UI Update 
			scoreText.setString("Wynik:" + std::to_string(score));


			// Dodaj kod do aktualizacji czasu gry
			int minutes = seconds / 60;
			seconds = seconds % 60;
			timeText.setString("Czas: " + std::to_string(minutes) + "." + std::to_string(seconds));


		}


		//rysowanie
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
		if (t == HARD) {
			for (size_t i = 0; i < asteroids.size(); i++)
			{
				window.draw(asteroids[i].shape);
			}
		}
		//UI
		window.draw(scoreText);
		window.draw(hpText);
		window.draw(timeText);

		if (player.HP <= 0) {
			int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
			int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
			zapisz_wynik_i_czas_do_pliku(score, minutes, seconds);

			music1.stop();

			window.draw(gameOverText);
			MenuGame menuG(this);
			menuG.MenuG();
		}


		window.display();

	}

}

void Game::zapisz_wynik_i_czas_do_pliku(int wynik, int czas_minuty, int czas_sekundy) {
	ofstream plik("wyniki.txt", std::ios::app);  

	plik.is_open();

	
	plik << "Wynik: " << wynik << "\t Czas: " << czas_minuty << "m " << czas_sekundy << "s" << std::endl;

	
	plik.close();
}