#ifndef POZIOM
#define POZIOM


#include "Esc.h"
#include "MainMenu.h"
#include "Game.h"

class Game;
class Poziom
{
public:
	Poziom(RenderWindow& window);

	void MainPoziom();
	void setup();
private:
	Font font;
	RenderWindow& window;
	Text selectionText;
	Text normalText;
	Text hardText;
	Text returnText;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	void processEvents();
	void update();
	void render();
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);
	Game* game;
	
};

#endif POZIOM