#include "game_menu.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window;
    window.create(VideoMode::getDesktopMode(), L"Моя игра", Style::Fullscreen);
    window.setMouseCursorVisible(false);

    float width = VideoMode::getDesktopMode().width;
    float height = VideoMode::getDesktopMode().height;

    RectangleShape background(Vector2f(width, height));
    Texture texture_window;
    if (!texture_window.loadFromFile("images/templ1.png")) return 4;
    background.setTexture(&texture_window);

    String name_menu[]{ L"Старт", L"Выход" };

    GameMenuData mymenu;
    initGameMenu(mymenu, window, 550, 250, 2, name_menu, 100, 120);
    setMenuColors(mymenu, Color::Yellow, Color::Red, Color::Black);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up) { moveMenuUp(mymenu); }
                if (event.key.code == Keyboard::Down) { moveMenuDown(mymenu); }
                if (event.key.code == Keyboard::Return)
                {
                    switch (getSelectedMenuNumber(mymenu))
                    {
                        case 0: break;
                        case 1: window.close();     break;
                    }
                }
            }
        }
        
        window.clear();
        window.draw(background);
        drawMenu(mymenu);
        window.display();
    }

    return 0;
}