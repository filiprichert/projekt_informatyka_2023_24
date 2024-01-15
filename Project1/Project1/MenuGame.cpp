#include "MenuGame.h"
#include "Esc.h"
#include "Game.h"



MenuGame::MenuGame(Game* game) : window(sf::VideoMode(400, 300), "Game menu", Style::None) { this->game = game; czymenu = true; }

void MenuGame::MenuG() {
    while (window.isOpen() && czymenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                handleMouseHover(event.mouseMove.x, event.mouseMove.y);
            }

        }
        setup();
        render();
    }
}

void MenuGame::render() {
    window.clear();

    menuText.setPosition(window.getSize().x / 2.0f - menuText.getLocalBounds().width / 2, window.getSize().y / 2.0f - menuText.getLocalBounds().height - 80);
    exetText.setPosition(window.getSize().x / 2.0f - exetText.getLocalBounds().width / 2, window.getSize().y / 2.0f - exetText.getLocalBounds().height - 20);
    returnemenuText.setPosition(window.getSize().x / 2.0f - returnemenuText.getLocalBounds().width / 2, window.getSize().y / 2.0f - returnemenuText.getLocalBounds().height + 30);
    returneText.setPosition(window.getSize().x / 2.0f - returneText.getLocalBounds().width / 2, window.getSize().y / 2.0f - returneText.getLocalBounds().height + 80);

    window.draw(menuText);
    window.draw(exetText);
    window.draw(returnemenuText);
    window.draw(returneText);

    window.display();
}

void MenuGame::handleMouseHover(int x, int y) {
    if (exetText.getGlobalBounds().contains(x, y)) {
        exetText.setFillColor(sf::Color::Red);
    }
    else {
        exetText.setFillColor(sf::Color::White);
    }

    if (returnemenuText.getGlobalBounds().contains(x, y)) {
        returnemenuText.setFillColor(sf::Color::Red);
    }
    else {
        returnemenuText.setFillColor(sf::Color::White);
    }

    if (returneText.getGlobalBounds().contains(x, y)) {
        returneText.setFillColor(sf::Color::Red);
    }
    else {
        returneText.setFillColor(sf::Color::White);
    }
}

//void MenuGame::AkcjaNaDrugimOknie() {
//    drugieOkno.menu_game();
//}

void MenuGame::handleMouseClick(int x, int y) {
    if (exetText.getGlobalBounds().contains(x, y)) {
        Esc esc;
        esc.MainEsc();
    }

    if (returnemenuText.getGlobalBounds().contains(x, y)) {
        game->czygra = false;
        czymenu = false;
        window.close();
    }

    if (returneText.getGlobalBounds().contains(x, y)) {
        
        window.close();
    }
}

void MenuGame::setup() {
    font.loadFromFile("Fonts/Stereotones.otf");

    menuText.setFont(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(40);

    exetText.setFont(font);
    exetText.setString("Wyjdz z gry");
    exetText.setCharacterSize(30);

    returnemenuText.setFont(font);
    returnemenuText.setString("Powrot do menu");
    returnemenuText.setCharacterSize(30);

    returneText.setFont(font);
    returneText.setString("Wroc do gry");
    returneText.setCharacterSize(30);
}