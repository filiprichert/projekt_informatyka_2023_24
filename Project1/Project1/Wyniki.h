#ifndef WYNIKI
#define WYNIKI

#include "MainMenu.h" 
class Ranking {
public:
    int punkty;
    int minuty;
    int sekundy;

    Ranking(int pkt, int min, int sec) : punkty(pkt), minuty(min), sekundy(sec) {}
    Ranking() : punkty(0), minuty(0), sekundy(0) {}
};

class Wyniki
{
public:

    Wyniki(RenderWindow& window);
    ~Wyniki();

    void wyswietl_najlepsze_wyniki();

private:
    Font font;
    RenderWindow& window;
    vector<Ranking> najlepszeWyniki;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Text returneText;
    Text tekst;

    void wczytaj_najlepsze_wyniki();
    void sortuj_wyniki();
    void render();
    void handleMouseHover(int x, int y);
    void handleMouseClick(int x, int y);
    void Star();
};

#endif WYNIKI
