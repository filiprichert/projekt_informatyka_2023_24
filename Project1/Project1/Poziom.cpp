#include "Poziom.h"
#include "Esc.h"
#include "MainMenu.h"
#include "Game.h"

Poziom::Poziom(sf::RenderWindow& window) : window(window) { setup();}

void Poziom::MainPoziom() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Poziom::processEvents() {
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

        //if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        //    Menu Menu(window);
        //    Menu.MainMenu();
        //}
    }
}

void Poziom::update() {
    
}

void Poziom::render() {
    window.clear();

    // Narysuj t³o
    window.draw(backgroundSprite);

    // Narysuj teksty opcji menu
    selectionText.setPosition(window.getSize().x / 2.0f - selectionText.getLocalBounds().width / 2, window.getSize().y / 2.0f - selectionText.getLocalBounds().height - 160);
    normalText.setPosition(window.getSize().x / 2.0f - normalText.getLocalBounds().width / 2, window.getSize().y / 2.0f - normalText.getLocalBounds().height - 80);
    hardText.setPosition(window.getSize().x / 2.0f - hardText.getLocalBounds().width / 2, window.getSize().y / 2.0f - hardText.getLocalBounds().height);
    returnText.setPosition(window.getSize().x / 2.0f - returnText.getLocalBounds().width / 2, window.getSize().y / 2.0f - returnText.getLocalBounds().height + 80);

    window.draw(selectionText);
    window.draw(normalText);
    window.draw(hardText);
    window.draw(returnText);

    window.display();
}

void Poziom::handleMouseHover(int x, int y) {
    if (normalText.getGlobalBounds().contains(x, y)) {
        normalText.setFillColor(Color::Red);
    }
    else {
        normalText.setFillColor(Color::White);
    }

    if (hardText.getGlobalBounds().contains(x, y)) {
        hardText.setFillColor(Color::Red);
    }
    else {
        hardText.setFillColor(Color::White);
    }

    if (returnText.getGlobalBounds().contains(x, y)) {
        returnText.setFillColor(Color::Red);
    }
    else {
        returnText.setFillColor(Color::White);
    }
}

void Poziom::handleMouseClick(int x, int y) {
    if (normalText.getGlobalBounds().contains(x, y)) {
        game = new Game(window);
        game -> nowa_gra(NORMAL);
        delete game;
    }

    if (hardText.getGlobalBounds().contains(x, y)) {
        game = new Game(window);
        game->nowa_gra(HARD);
        delete game;
        
    }

    if (returnText.getGlobalBounds().contains(x, y)) {
        Menu menu(window);
        menu.MainMenu();
    }
}


void Poziom::setup() {

    font.loadFromFile("Fonts/Stereotones.otf");

    backgroundTexture.loadFromFile("Tekstury/poziom.png");
    backgroundTexture.setRepeated(true);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);




    selectionText.setFont(font);
    selectionText.setString("Wybierz poziom gry:");
    selectionText.setCharacterSize(50);
    selectionText.setPosition(100, 100);

    normalText.setFont(font);
    normalText.setString("Normalny");
    normalText.setCharacterSize(50);
    normalText.setPosition(100, 150);

    hardText.setFont(font);
    hardText.setString("Trudny");
    hardText.setCharacterSize(50);
    hardText.setPosition(100, 200);

    returnText.setFont(font);
    returnText.setString("Powrod do menu");
    returnText.setCharacterSize(30);
    returnText.setPosition(100, 250);


}