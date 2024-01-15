#ifndef OGRZE 
#define OGRZE
#include "MainMenu.h"

class OGrze
{
public:

	OGrze(RenderWindow& window);

	void MainOGrze();



private:
	Font font1;
	Font font2;
	RenderWindow& window;
	Text titleText;
	Text textText;
	Text returneText;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	void setup();
	void processEvents();
	void render();
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);

};

#endif OGRZE