#ifndef POMOC
#define POMOC

#include "MainMenu.h"

class Help
{
public:
	Help();
	void GameHelp();


private:
	Text infoText;
	Text znakiText;
	Text returneText;
	RenderWindow window;
	Font font2;
	Font font1;

	void setup();
	void render();
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);



};


#endif POMOC