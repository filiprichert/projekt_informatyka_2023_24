#include "MainMenu.h"


int main() {
    RenderWindow window(VideoMode(1200, 1100), "Space shooter", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    Menu menu(window);
    menu.MainMenu();

    return 0;
}