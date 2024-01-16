#ifndef GAME
#define GAME




#include "Gracz.h"
#include "Wrogowie.h"
#include "Asteroidy.h"
#include "Pociski.h"
#include "MainMenu.h"
#include "Poziom.h"
#include "Pomoc.h"


enum trudnosc
{   
    NORMAL,
    HARD
};

class Game {
public:
    Game(RenderWindow& window);
    ~Game();

    void nowa_gra(trudnosc t);
    
    bool czygra;

   
private:
    Music music;
    RenderWindow& window;
    
    void zapisz_wynik_i_czas_do_pliku(int wynik, int czas_minuty, int czas_sekundy);

};


#endif GAME