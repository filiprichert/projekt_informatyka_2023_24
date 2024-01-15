#include "OGrze.h"

OGrze::OGrze(sf::RenderWindow& window) : window(window) { setup(); }

void OGrze::MainOGrze() {
    while (window.isOpen()) {
        processEvents();
        render();

    }
}

void OGrze::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == Event::MouseButtonPressed) {
            if (event.mouseButton.button == Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        if (event.type == Event::MouseMoved) {
            handleMouseHover(event.mouseMove.x, event.mouseMove.y);
        }
    }
}



void OGrze::render() {
    window.clear();

    // Narysuj t³o
    window.draw(backgroundSprite);

    // Narysuj teksty opcji menu
    titleText.setPosition(window.getSize().x / 2.0f - titleText.getLocalBounds().width / 2, 100.0f);
    textText.setPosition(window.getSize().x / 2.0f - textText.getLocalBounds().width / 2, window.getSize().y / 2.0f - textText.getLocalBounds().height);
    returneText.setPosition(window.getSize().x / 2.0f - returneText.getLocalBounds().width / 2, window.getSize().y / 2.0f - returneText.getLocalBounds().height + 200);

    window.draw(titleText);
    window.draw(textText);
    window.draw(returneText);

    window.display();
}

void OGrze::handleMouseHover(int x, int y) {

    if (returneText.getGlobalBounds().contains(x, y)) {
        returneText.setFillColor(Color::Red);
    }
    else {
        returneText.setFillColor(Color::White);
    }
}

void OGrze::handleMouseClick(int x, int y) {

    if (returneText.getGlobalBounds().contains(x, y)) {
        Menu menu(window);
        menu.MainMenu();
    }
}


void OGrze::setup() {

    font1.loadFromFile("Fonts/Stereotones.otf");
    font2.loadFromFile("Fonts/Aleo-Bold.otf");

    backgroundTexture.loadFromFile("Tekstury/ogrze_tlo.png");
    backgroundTexture.setRepeated(true);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);




    titleText.setFont(font2);
    titleText.setString("Zagubiony Wiking: Kosmiczna Odyseja");
    titleText.setCharacterSize(50);
    titleText.setPosition(100, 100);

    textText.setFont(font2);
    textText.setString(
        "W 'Zagubiony Wiking: Kosmiczna Odyseja' wcielasz sie w role dowodcy zalogi kosmicznego statku"
        "\no nazwie Wiking,ktory zagubil sie w odleglych zakatkach kosmosu. W wyniku awarii nawigacyjnej,"
        "\nstatek znalazl siê na nieznanych koordynatach, gdzie grozi mu niebezpieczenstwo ze strony"
        "\nwrogich statkow kosmicznych oraz gromadzacych sie asteroid."

        "\n\nAby przetrwac i odnalezc droge powrotna na Ziemie, musisz stawic czola nieustannym"
        "\natakom wrogich sil oraz unikac zderzen z poteznymi asteroidami. Twój statek, Wiking,"
        "\nzostal wyposazony w zaawansowany arsenal broni kosmicznej, ktory umozliwia obrone przed"
        "\nwrogimi jednostkami. Jednakze, aby utrzymac sie w tej beznadziejnej przestrzeni, bedziesz"
        "\nmusial nie tylko skoncentrowac sie na niszczeniu wrogow, ale takze na zrecznym manewrowaniu"
        "\npomiedzy asteroidami."

        "\n\nHistoria 'Zagubionego Wikinga: Kosmicznej Odysei' rozwija sie wraz z kazdym przebytym"
        "\nsektorem, a tajemnicze komunikaty i sygnaly kosmiczne moga rzucic swiatlo na przyczyny awarii "
        "\nnawigacyjnej. Czy uda ci sie odnalezc droge powrotna do domu, pokonujac wszystkie przeszkody"
        "\ni zwyciezajac wrogie sily kosmosu? To zalezy od twoich umiejetnosci taktycznych i zrecznosci pilota!"
    );

    textText.setCharacterSize(20);
    textText.setPosition(100, 150);

    returneText.setFont(font1);
    returneText.setString("Powrot do menu");
    returneText.setCharacterSize(40);
    returneText.setPosition(100, 250);


}