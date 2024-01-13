#ifndef GAME
#define GAME




#include "Gracz.h"
#include "Wrogowie.h"
#include "Asteroidy.h"
#include "Pociski.h"
#include "MainMenu.h"
#include "Poziom.h"

class Game {
public:
    Game(RenderWindow& window);
    ~Game();

    void nowa_gra();

private:
    Music music;
    RenderWindow& window;
};


#endif GAME