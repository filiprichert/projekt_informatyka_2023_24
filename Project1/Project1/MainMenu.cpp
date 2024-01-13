#include "MainMenu.h"
#include "Esc.h"
#include "Poziom.h"

Menu::Menu(sf::RenderWindow& window) : window(window) { setup(); }

void Menu::MainMenu() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
        
    }
}

void Menu::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        if (event.type == Event::MouseMoved) {
            handleMouseHover(event.mouseMove.x, event.mouseMove.y);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            Esc Esc;
            Esc.MainEsc();
        }
    }
}

void Menu::update() {
    // Dodaj logikê aktualizacji, jeœli potrzebujesz
}

void Menu::render() {
    window.clear();

    // Narysuj t³o
    window.draw(backgroundSprite);

    // Narysuj teksty opcji menu
    playText.setPosition(window.getSize().x / 2.0f - playText.getLocalBounds().width / 2, window.getSize().y / 2.0f - playText.getLocalBounds().height - 160);
    scoresText.setPosition(window.getSize().x / 2.0f - scoresText.getLocalBounds().width / 2, window.getSize().y / 2.0f - scoresText.getLocalBounds().height - 80);
    aboutText.setPosition(window.getSize().x / 2.0f - aboutText.getLocalBounds().width / 2, window.getSize().y / 2.0f - aboutText.getLocalBounds().height);
    exitText.setPosition(window.getSize().x / 2.0f - exitText.getLocalBounds().width / 2, window.getSize().y / 2.0f - exitText.getLocalBounds().height + 80);

    window.draw(playText);
    window.draw(scoresText);
    window.draw(aboutText);
    window.draw(exitText);

    window.display();
}

void Menu::handleMouseHover(int x, int y) {
    if (playText.getGlobalBounds().contains(x, y)) {
        playText.setFillColor(Color::Red);
    }
    else {
        playText.setFillColor(Color::White);
    }

    if (scoresText.getGlobalBounds().contains(x, y)) {
        scoresText.setFillColor(Color::Red);
    }
    else {
        scoresText.setFillColor(Color::White);
    }

    if (aboutText.getGlobalBounds().contains(x, y)) {
        aboutText.setFillColor(Color::Red);
    }
    else {
        aboutText.setFillColor(Color::White);
    }

    if (exitText.getGlobalBounds().contains(x, y)) {
        exitText.setFillColor(Color::Red);
    }
    else {
        exitText.setFillColor(Color::White);
    }
}

void Menu::handleMouseClick(int x, int y) {
    if (playText.getGlobalBounds().contains(x, y)) {
        
        Poziom poziom(window);
        poziom.MainPoziom();

    }

    if (scoresText.getGlobalBounds().contains(x, y)) {
        // Obs³uga klikniêcia dla opcji "Wyniki"
        Menu menu(window);
    }

    if (aboutText.getGlobalBounds().contains(x, y)) {
        // Obs³uga klikniêcia dla opcji "O Grze"
        Menu menu(window);
    }

    if (exitText.getGlobalBounds().contains(x, y)) {
        Esc Esc;
        Esc.MainEsc();
    }
}


void Menu::setup() {

    font.loadFromFile("Fonts/Stereotones.otf");

    backgroundTexture.loadFromFile("Tekstury/menu_tlo.png");
    backgroundTexture.setRepeated(true);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);
    



    playText.setFont(font);
    playText.setString("Graj");
    playText.setCharacterSize(50);
    playText.setPosition(100, 100);

    scoresText.setFont(font);
    scoresText.setString("Wyniki");
    scoresText.setCharacterSize(50);
    scoresText.setPosition(100, 150);

    aboutText.setFont(font);
    aboutText.setString("O Grze");
    aboutText.setCharacterSize(50);
    aboutText.setPosition(100, 200);

    exitText.setFont(font);
    exitText.setString("Wyjdz");
    exitText.setCharacterSize(50);
    exitText.setPosition(100, 250);


}