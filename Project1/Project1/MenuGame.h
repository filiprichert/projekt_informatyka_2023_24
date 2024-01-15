#ifndef Menu_G
#define Menu_G
#include "MainMenu.h"
#include "Game.h"

class MenuGame
{
public:
	MenuGame(Game* game);
	void MenuG();

	
private:
	Text menuText;
	Text exetText;
	Text returnemenuText;
	Text returneText;
	RenderWindow window;
	Font font;
	Game* game;

	void setup();
	void render();
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);
	
	
	bool czymenu;
};

#endif Menu_G