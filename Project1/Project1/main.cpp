//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <vector>
//
//using namespace sf;
//
//class Missile {
//public:
//    Sprite shape;
//
//    Missile(Texture* texture, Vector2f pos) {
//        this->shape.setTexture(*texture);
//        this->shape.setScale(0.1f, 0.1f);
//        this->shape.setPosition(pos);
//    }
//
//    ~Missile() {}
//};
//
//class Player {
//public:
//    Sprite shape;
//    Texture* texture;
//    int HP;
//    int HPMax;
//
//    std::vector<Missile> missile;
//
//    Player(Texture* texture, Vector2u windowSize) {
//        this->HPMax = 10;
//        this->HP = this->HPMax;
//
//        this->texture = texture;
//        this->shape.setTexture(*texture);
//
//        this->shape.setScale(0.6f, 0.6f);
//        this->shape.setPosition((windowSize.x - this->shape.getGlobalBounds().width) / 2.f, windowSize.y - this->shape.getGlobalBounds().height);
//    }
//
//    ~Player() {}
//};
//
//class Enemy {
//public:
//    Sprite shape;
//    int HP;
//    int HPMax;
//
//    Enemy(Texture* texture, Vector2u windowSize) {
//        this->HPMax = rand() % 3 + 1;
//        this->HP = this->HPMax;
//
//        this->shape.setTexture(*texture);
//        this->shape.setScale(0.2f, 0.2f);
//        this->shape.setPosition(rand() % (int)(windowSize.x - this->shape.getGlobalBounds().width), 0.0f);
//    }
//
//    ~Enemy() {}
//};
//
//enum class GameState {
//    MENU,
//    GRA,
//    GAME_OVER,
//};
//
//void gameLoop(RenderWindow& window, Texture& playerTexture, Texture& enemyTexture, Texture& missileTexture, Font& font) {
//    // Inicjalizacja gry
//    int score = 0;
//    Player player(&playerTexture, window.getSize());
//    int shootTimer = 20;
//
//    Text scoreText;
//    scoreText.setFont(font);
//    scoreText.setCharacterSize(20);
//    scoreText.setFillColor(Color::Green);
//    scoreText.setPosition(10.f, 10.f);
//
//    Text gameOverText;
//    gameOverText.setFont(font);
//    gameOverText.setCharacterSize(40);
//    gameOverText.setFillColor(Color::Red);
//    gameOverText.setPosition(100.f, window.getSize().y / 2);
//    gameOverText.setString("Koniec gry!!!");
//
//    int enemySpawnTimer = 0;
//    std::vector<Enemy> enemies;
//
//    Text eHpText;
//    eHpText.setFont(font);
//    eHpText.setCharacterSize(24);
//    eHpText.setFillColor(Color::Red);
//
//    while (window.isOpen()) {
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed)
//                window.close();
//        }
//
//        if (player.HP > 0) {
//            // Gracz
//            if (Keyboard::isKeyPressed(Keyboard::W))
//                player.shape.move(0.f, -10.f);
//            if (Keyboard::isKeyPressed(Keyboard::S))
//                player.shape.move(0.f, 10.f);
//            if (Keyboard::isKeyPressed(Keyboard::A))
//                player.shape.move(-10.f, 0.f);
//            if (Keyboard::isKeyPressed(Keyboard::D))
//                player.shape.move(10.f, 0.f);
//
//            Text hpText;
//            hpText.setFont(font);
//            hpText.setCharacterSize(24);
//            hpText.setFillColor(Color::Green);
//            hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
//            hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));
//
//            if (shootTimer < 15)
//                shootTimer++;
//
//            if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 15) { // Strzelanie
//                player.missile.push_back(Missile(&missileTexture, player.shape.getPosition()));
//                shootTimer = 0;
//            }
//
//            // Kolizja z ekranem
//            if (player.shape.getPosition().x <= 0)
//                player.shape.setPosition(0.f, player.shape.getPosition().y);
//            if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width)
//                player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
//            if (player.shape.getPosition().y <= 0)
//                player.shape.setPosition(player.shape.getPosition().x, 0.f);
//            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height)
//                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);
//
//            // Pociski
//            for (size_t i = 0; i < player.missile.size(); i++) {
//                // Ruch
//                player.missile[i].shape.move(0.f, -20.f);
//
//                // Poza ekranem
//                if (player.missile[i].shape.getPosition().x > window.getSize().x) {
//                    player.missile.erase(player.missile.begin() + i);
//                    break;
//                }
//
//                // Kolizja z wrogiem
//                for (size_t k = 0; k < enemies.size(); k++) {
//                    if (player.missile[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds())) {
//                        if (enemies[k].HP <= 1) {
//                            score += enemies[k].HPMax;
//                            enemies.erase(enemies.begin() + k);
//                        }
//                        else {
//                            enemies[k].HP--; // Zadawanie obra¿eñ od wrogów
//                        }
//
//                        player.missile.erase(player.missile.begin() + i);
//                        break;
//                    }
//                }
//            }
//
//            // Wrog
//            if (enemySpawnTimer < 25)
//                enemySpawnTimer++;
//
//            if (enemySpawnTimer >= 25) {
//                enemies.push_back(Enemy(&enemyTexture, window.getSize()));
//                enemySpawnTimer = 0;
//            }
//
//            for (size_t i = 0; i < enemies.size(); i++) {
//                enemies[i].shape.move(0.f, 4.f);
//
//                if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width) {
//                    enemies.erase(enemies.begin() + i);
//                    break;
//                }
//
//                if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
//                    enemies.erase(enemies.begin() + i);
//                    player.HP--; // Zadawanie obra¿eñ graczowi
//                    break;
//                }
//            }
//
//            // UI Update
//            scoreText.setString("Wynik:" + std::to_string(score));
//
//            // Rysowanie
//            window.clear();
//
//            // Gracz
//            window.draw(player.shape);
//
//            // Pociski
//            for (size_t i = 0; i < player.missile.size(); i++) {
//                window.draw(player.missile[i].shape);
//            }
//
//            // Wrogowie
//            for (size_t i = 0; i < enemies.size(); i++) {
//                eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
//                eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
//                window.draw(eHpText);
//                window.draw(enemies[i].shape);
//            }
//
//            // UI
//            window.draw(scoreText);
//            window.draw(hpText);
//
//            if (player.HP <= 0) {
//                window.draw(gameOverText);
//            }
//
//            window.display();
//        }
//    }
//}
//
//int main() {
//    srand(time(NULL));
//
//    RenderWindow window(VideoMode(1600, 1400), "Space shooter");
//    window.setFramerateLimit(60);
//
//    Font font;
//    font.loadFromFile("Fonts/Stereotones.otf");
//
//    Texture playerTex;
//    playerTex.loadFromFile("Tekstury/statek.png");
//
//    Texture enemyTex;
//    enemyTex.loadFromFile("Tekstury/wrog.png");
//
//    Texture missileTex;
//    missileTex.loadFromFile("Tekstury/pocisk1.png");
//
//    while (window.isOpen()) {
//        // G³ówne menu
//        GameState gameState = GameState::MENU;
//
//        while (window.isOpen()) {
//            Event event;
//            while (window.pollEvent(event)) {
//                if (event.type == Event::Closed)
//                    window.close();
//            }
//
//            window.clear();
//
//            if (gameState == GameState::MENU) {
//                // G³ówne menu
//                Text grajText, wynikiText, oGrzeText, wyjdzText;
//                grajText.setFont(font);
//                grajText.setCharacterSize(30);
//                grajText.setString("Graj");
//                grajText.setPosition(200.f, 200.f);
//
//                wynikiText.setFont(font);
//                wynikiText.setCharacterSize(30);
//                wynikiText.setString("Wyniki");
//                wynikiText.setPosition(200.f, 300.f);
//
//                oGrzeText.setFont(font);
//                oGrzeText.setCharacterSize(30);
//                oGrzeText.setString("O Grze");
//                oGrzeText.setPosition(200.f, 400.f);
//
//                wyjdzText.setFont(font);
//                wyjdzText.setCharacterSize(30);
//                wyjdzText.setString("WyjdŸ");
//                wyjdzText.setPosition(200.f, 500.f);
//
//                if (grajText.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
//                    grajText.setFillColor(Color::Red);
//                    if (Mouse::isButtonPressed(Mouse::Left)) {
//                        gameState = GameState::GRA;
//                    }
//                }
//                else {
//                    grajText.setFillColor(Color::White);
//                }
//
//                if (wynikiText.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
//                    wynikiText.setFillColor(Color::Red);
//                    if (Mouse::isButtonPressed(Mouse::Left)) {
//                        // Obs³uga opcji Wyniki
//                        // Tutaj dodaj kod do wyœwietlania wyników
//                    }
//                }
//                else {
//                    wynikiText.setFillColor(Color::White);
//                }
//
//                if (oGrzeText.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
//                    oGrzeText.setFillColor(Color::Red);
//                    if (Mouse::isButtonPressed(Mouse::Left)) {
//                        // Obs³uga opcji O Grze
//                        // Tutaj dodaj kod do wyœwietlania instrukcji
//                    }
//                }
//                else {
//                    oGrzeText.setFillColor(Color::White);
//                }
//
//                if (wyjdzText.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y)) {
//                    wyjdzText.setFillColor(Color::Red);
//                    if (Mouse::isButtonPressed(Mouse::Left)) {
//                        window.close();
//                    }
//                }
//                else {
//                    wyjdzText.setFillColor(Color::White);
//                }
//
//                window.draw(grajText);
//                window.draw(wynikiText);
//                window.draw(oGrzeText);
//                window.draw(wyjdzText);
//            }
//            else if (gameState == GameState::GRA) {
//                gameLoop(window, playerTex, enemyTex, missileTex, font);
//                gameState = GameState::MENU;  // Po zakoñczeniu gry wracamy do menu
//            }
//
//            window.display();
//        }
//
//        if (gameState == GameState::GRA) {
//            gameLoop(window, playerTex, enemyTex, missileTex, font);
//        }
//        else if (gameState == GameState::GAME_OVER) {
//            // Tutaj obs³u¿ stan po zakoñczeniu gry
//        }
//    }
//
//    return 0;
//}
