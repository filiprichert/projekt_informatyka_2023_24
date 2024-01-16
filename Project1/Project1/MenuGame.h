#ifndef Menu_G
#define Menu_G
#include "MainMenu.h"
#include "Game.h"

enum czyporaszka
{
	KONIEC,
	INNE
	
};
class MenuGame
{
public:
	MenuGame(Game* game);
	void MenuG(czyporaszka k);

	
private:
	Text menuText;
	Text exetText;
	Text returnemenuText;
	Text returneText;
	Text gameOverText;
	RenderWindow window;
	Font font;
	Game* game;

	void setup();
	void render(czyporaszka k);
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);
	
	
	bool czymenu;
};

#endif Menu_G