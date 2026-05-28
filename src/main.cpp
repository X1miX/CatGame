#include <SFML/Graphics.hpp>
#include "game_menu.h"
#include "levels.h"

int main() {
    // Получаем параметры текущего монитора (разрешение и частоту)
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Создаем окно строго под размер рабочего стола в полноэкранном режиме
    sf::RenderWindow window(desktopMode, "Cat Game", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    // Загрузка текстур
    sf::Texture catTex, jumpTex, keyTex, bgTex, obj1Tex, obj2Tex, spikeTex, doorTex;
    // Пути теперь просто images/...
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

    // Центрируем меню динамически (относительно ширины и высоты экрана)
    float screenW = (float)desktopMode.width;
    float screenH = (float)desktopMode.height;
    
    sf::String names[] = { L"Уровень 1", L"Уровень 2", L"Уровень 3", L"Выход" };
    GameMenuData menu;
    // Меню будет примерно по центру
    initGameMenu(menu, window, screenW / 2.2f, screenH / 2.5f, 4, names, 80, 100);

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
                    
                    // После выхода из уровня сбрасываем вид, чтобы меню не уехало
                    window.setView(window.getDefaultView());
                }
            }
        }

        window.clear();
        
        // Рисуем фон, растянутый на весь экран
        sf::Sprite bgSprite(bgTex);
        bgSprite.setScale(screenW / bgSprite.getLocalBounds().width, screenH / bgSprite.getLocalBounds().height);
        
        window.draw(bgSprite);
        drawMenu(menu);
        window.display();
    }
    return 0;
}