#include "Wyniki.h"
#include "Esc.h"
Wyniki::Wyniki(RenderWindow& window) : window(window) {
    wczytaj_najlepsze_wyniki();
    sortuj_wyniki();
}

Wyniki::~Wyniki() {}

void Wyniki::wczytaj_najlepsze_wyniki() {
    ifstream plik("wyniki.txt");

    plik.is_open();

    int punkty, minuty, sekundy;

    while (plik >> punkty >> minuty >> sekundy) {
        najlepszeWyniki.push_back(Ranking(punkty, minuty, sekundy));
    }

    plik.close();
}

int kryteriu_sortowania(const Ranking& a, const Ranking& b) {return a.punkty > b.punkty;
}

void Wyniki::sortuj_wyniki() {
    sort(najlepszeWyniki.begin(), najlepszeWyniki.end(), kryteriu_sortowania);

    if (najlepszeWyniki.size() > 20) {
        najlepszeWyniki.resize(20);
    }
}

void Wyniki::wyswietl_najlepsze_wyniki() {
    
    font.loadFromFile("Fonts/Stereotones.otf");

    backgroundTexture.loadFromFile("Tekstury/wynikitlo.png");
    backgroundTexture.setRepeated(true);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    tekst.setFont(font);
    tekst.setCharacterSize(25);
    

    returneText.setFont(font);
    returneText.setString("Powrot do menu");
    returneText.setCharacterSize(40);
    


    tekst.setString("Najlepsze wyniki:\n");

    for (size_t i = 0; i < najlepszeWyniki.size(); ++i) {
        tekst.setString(tekst.getString() +
            std::to_string(i + 1) + ". " +
            "Punkty: " + std::to_string(najlepszeWyniki[i].punkty) +
            "       Czas: " + std::to_string(najlepszeWyniki[i].minuty) + " m " + std::to_string(najlepszeWyniki[i].sekundy) + " s\n");
    }

    

    Event event;
    while (window.isOpen()) {
        

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
        render();
        
    }
}

void Wyniki::render() {
    window.clear();
    window.draw(backgroundSprite);
    
    returneText.setPosition(window.getSize().x / 2.0f - returneText.getLocalBounds().width / 2, window.getSize().y / 2.0f - returneText.getLocalBounds().height + 300);
    tekst.setPosition(100,100);
    
    window.draw(tekst);
    window.draw(returneText);
    Star();
    window.display();
}

void Wyniki::handleMouseHover(int x, int y) {

    if (returneText.getGlobalBounds().contains(x, y)) {
        returneText.setFillColor(Color::Red);
    }
    else {
        returneText.setFillColor(Color::White);
    }
}
void Wyniki::handleMouseClick(int x, int y) {

    if (returneText.getGlobalBounds().contains(x, y)) {
        Menu menu(window);
        menu.MainMenu();
    }
}

void Wyniki::Star() {
    sf::ConvexShape star;
    star.setPointCount(10);
    star.setPoint(0, sf::Vector2f(400, 175));
    star.setPoint(1, sf::Vector2f(450, 300));
    star.setPoint(2, sf::Vector2f(600, 300));
    star.setPoint(3, sf::Vector2f(475, 375));
    star.setPoint(4, sf::Vector2f(525, 525));
    star.setPoint(5, sf::Vector2f(400, 450));
    star.setPoint(6, sf::Vector2f(275, 525));
    star.setPoint(7, sf::Vector2f(325, 375));
    star.setPoint(8, sf::Vector2f(200, 300));
    star.setPoint(9, sf::Vector2f(350, 300));

    star.setFillColor(sf::Color::Yellow);
    star.setPosition(star.getPosition().x + 500, star.getPosition().y + 100);
    window.draw(star);
}