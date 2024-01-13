#include "MainMenu.h"


int main() {
    RenderWindow window(VideoMode(1600, 1400), "Space shooter", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    Menu menu(window);
    menu.MainMenu();

    return 0;
}