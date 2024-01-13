#ifndef ESC
#define ESC

#include "MainMenu.h"

class Esc
{
public:
	Esc();
    void MainEsc();
	
	
private:
	Text questionText;
	Text yesText;
	Text noText;
	RenderWindow window;
	Font font;

	void setup();
	void render();
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);

};

#endif ESC