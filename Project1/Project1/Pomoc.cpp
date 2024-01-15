#include "Pomoc.h"

Help::Help() : window(sf::VideoMode(600, 600), "Help with the game", Style::None) {}

void Help::GameHelp() {
    while (window.isOpen()) {
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

void Help::render() {
    window.clear();

    infoText.setPosition(window.getSize().x / 2.0f - infoText.getLocalBounds().width / 2, window.getSize().y / 2.0f - infoText.getLocalBounds().height - 150);
    znakiText.setPosition(window.getSize().x / 2.0f - znakiText.getLocalBounds().width / 2, window.getSize().y / 2.0f - znakiText.getLocalBounds().height + 35);
    returneText.setPosition(window.getSize().x / 2.0f - returneText.getLocalBounds().width / 2, window.getSize().y / 2.0f - returneText.getLocalBounds().height + 95);

    window.draw(infoText);
    window.draw(znakiText);
    window.draw(returneText);

    window.display();
}

void Help::handleMouseHover(int x, int y) {
    

    if (returneText.getGlobalBounds().contains(x, y)) {
        returneText.setFillColor(sf::Color::Red);
    }
    else {
        returneText.setFillColor(sf::Color::White);
    }
}

void Help::handleMouseClick(int x, int y) {

    if (returneText.getGlobalBounds().contains(x, y)) {
        window.close();
    }
}

void Help::setup() {

    font1.loadFromFile("Fonts/Stereotones.otf");
    font2.loadFromFile("Fonts/Aleo-Bold.otf");

    infoText.setFont(font2);
    infoText.setString("Pomoc z systemem sterowania statkiem:");
    infoText.setCharacterSize(30);

    znakiText.setFont(font2);
    znakiText.setString("Poruszanie sie do przodu: W\nPoruszanie sie do tylu: S\nPoruszanie siê w lewo: A\nPoruszanie sie w prawo: D\nStrzelanie rakietami: Spacja");
    znakiText.setCharacterSize(30);

    returneText.setFont(font1);
    returneText.setString("Powrot do gry");
    returneText.setCharacterSize(40);
}