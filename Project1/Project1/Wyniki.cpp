//#include "Wyniki.h"
//
//Wyniki::Wyniki(sf::RenderWindow& window) : window(window) {
//    wczytaj_najlepsze_wyniki();
//    sortuj_wyniki();
//}
//
//Wyniki::~Wyniki() {}
//
//void Wyniki::wczytaj_najlepsze_wyniki() {
//    std::ifstream plik("wyniki.txt");
//
//    plik.is_open();
//
//    int punkty, minuty, sekundy;
//
//    while (plik >> punkty >> minuty >> sekundy) {
//        najlepszeWyniki.push_back(Ranking(punkty, minuty, sekundy));
//    }
//
//    plik.close();
//}
//
//void Wyniki::sortuj_wyniki() {
//    std::sort(najlepszeWyniki.begin(), najlepszeWyniki.end(), [](const Ranking& a, const Ranking& b) {
//        return a.punkty > b.punkty;
//        });
//
//    // Ograniczamy liczbê wyników do 20
//    if (najlepszeWyniki.size() > 20) {
//        najlepszeWyniki.resize(20);
//    }
//}
//
//void Wyniki::wyswietl_najlepsze_wyniki() {
//    Font font;
//    font.loadFromFile("Fonts/Stereotones.otf");
//
//    Text tekst;
//    tekst.setFont(font);
//    tekst.setCharacterSize(24);
//    tekst.setFillColor(sf::Color::White);
//
//    window.clear();
//
//    tekst.setString("Najlepsze wyniki:\n");
//
//    for (size_t i = 0; i < najlepszeWyniki.size(); ++i) {
//        tekst.setString(tekst.getString() +
//            std::to_string(i + 1) + ". " +
//            "Punkty: " + std::to_string(najlepszeWyniki[i].punkty) +
//            " Czas: " + std::to_string(najlepszeWyniki[i].minuty) + "m " + std::to_string(najlepszeWyniki[i].sekundy) + "s\n");
//    }
//
//    window.draw(tekst);
//    window.display();
//
//    sf::Event event;
//    while (window.isOpen()) {
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//    }
//}
