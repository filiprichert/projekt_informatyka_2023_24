#ifndef MENU
#define MENU


#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iomanip>


using namespace std;
using namespace sf;


class Menu
{

public:

	Menu(RenderWindow& window);

	void MainMenu();

	

private:
	Font font;
	RenderWindow& window;
	Text playText;
	Text scoresText;
	Text aboutText;
	Text exitText;
	Texture backgroundTexture;
	Sprite backgroundSprite;

	void setup();
	void processEvents();
	void update();
	void render();
	void handleMouseClick(int x, int y);
	void handleMouseHover(int x, int y);
	void drawWhiteStar();
	
};

#endif MENU