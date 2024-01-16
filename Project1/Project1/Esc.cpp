#include "Esc.h"
#include "MainMenu.h"



Esc::Esc() : window(VideoMode(800, 200), "Exit Game?", Style::None) {}

void Esc::MainEsc() {
    while (window.isOpen()) {
        Event event;
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

void Esc::render() {
    window.clear();

    questionText.setPosition(window.getSize().x / 2.0f - questionText.getLocalBounds().width / 2, window.getSize().y / 2.0f - questionText.getLocalBounds().height - 25);
    yesText.setPosition(window.getSize().x / 2.0f - yesText.getLocalBounds().width / 2 - 100, window.getSize().y / 2.0f - yesText.getLocalBounds().height + 25);
    noText.setPosition(window.getSize().x / 2.0f - noText.getLocalBounds().width / 2 + 100, window.getSize().y / 2.0f - noText.getLocalBounds().height + 25);

    window.draw(questionText);
    window.draw(yesText);
    window.draw(noText);

    window.display();
}

void Esc::handleMouseHover(int x, int y) {
    if (yesText.getGlobalBounds().contains(x, y)) {
        yesText.setFillColor(sf::Color::Red);
    }
    else {
        yesText.setFillColor(sf::Color::White);
    }

    if (noText.getGlobalBounds().contains(x, y)) {
        noText.setFillColor(sf::Color::Red);
    }
    else {
        noText.setFillColor(sf::Color::White);
    }
}

void Esc::handleMouseClick(int x, int y) {
    if (yesText.getGlobalBounds().contains(x, y)) {
        exit(EXIT_SUCCESS);
        window.close();
    }

    if (noText.getGlobalBounds().contains(x, y)) {
        window.close();
    }
}

void Esc::setup() {
    font.loadFromFile("Fonts/Stereotones.otf");

    questionText.setFont(font);
    questionText.setString("Czy na pewno chcesz wyjsc z gry?");
    questionText.setCharacterSize(30);

    yesText.setFont(font);
    yesText.setString("Tak");
    yesText.setCharacterSize(30);

    noText.setFont(font);
    noText.setString("Nie");
    noText.setCharacterSize(30);
}