#include <SFML/Graphics.hpp>
#include "game_menu.h"
#include "levels.h"

int main() {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Cat Game", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Texture catTex, jumpTex, keyTex, bgTex, menuBgTex, obj1Tex, obj2Tex, spikeTex, doorTex;

    if (!menuBgTex.loadFromFile("images/menuBackground.png")) return -1;
    if (!catTex.loadFromFile("images/kitty.png")) return -1;
    if (!jumpTex.loadFromFile("images/jump.png")) return -1;
    if (!keyTex.loadFromFile("images/key.png")) return -1;
    if (!bgTex.loadFromFile("images/background.png")) return -1;
    if (!obj1Tex.loadFromFile("images/templ1.png")) return -1;
    if (!obj2Tex.loadFromFile("images/templ2.png")) return -1;
    if (!spikeTex.loadFromFile("images/spikes.png")) return -1;
    if (!doorTex.loadFromFile("images/door.png")) return -1;

    obj1Tex.setRepeated(true);
    obj2Tex.setRepeated(true);
    spikeTex.setRepeated(true);

    float screenW = (float)desktopMode.width;
    float screenH = (float)desktopMode.height;
    
    sf::String names[] = { L"Уровень 1", L"Уровень 2", L"Уровень 3", L"Выход" };
    GameMenuData menu;
    initGameMenu(menu, window, screenW / 2.2f, screenH / 2.5f, 4, names, 80, 100);

    sf::Sprite menuBgSprite(menuBgTex);
    menuBgSprite.setScale(screenW / menuBgSprite.getLocalBounds().width, screenH / menuBgSprite.getLocalBounds().height);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window.close();
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) moveMenuUp(menu);
                if (event.key.code == sf::Keyboard::Down) moveMenuDown(menu);
                if (event.key.code == sf::Keyboard::Return) {
                    int choice = getSelectedMenuNumber(menu);
                    if (choice == 0) runLevel1(window, catTex, jumpTex, keyTex, bgTex, obj1Tex, obj2Tex, spikeTex, doorTex);
                    if (choice == 1) runLevel2(window, catTex, jumpTex, keyTex, bgTex, obj1Tex, obj2Tex, spikeTex, doorTex);
                    if (choice == 2) runLevel3(window, catTex, jumpTex, keyTex, bgTex, obj1Tex, obj2Tex, spikeTex, doorTex);
                    if (choice == 3) window.close();
                    
                    window.setView(window.getDefaultView());
                }
            }
        }

        window.clear();
        window.draw(menuBgSprite);
        drawMenu(menu);
        window.display();
    }
    return 0;
}