#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "movement.h"

int main()
{
    const int WIN_WIDTH = 1366;
    const int WIN_HEIGHT = 768;

    sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Cat Platformer");
    win.setFramerateLimit(60);

    sf::Texture catTexture;
    if (!catTexture.loadFromFile("kitty.png"))
        return -1;

    int frameW = 180;
    int frameH = 160;
    int padding = 20;
    int totalFrames = 4;
    int currentFrame = 0;
    float animSpeed = 0.15f;

    sf::IntRect catRect(0, 0, frameW, frameH);
    sf::Sprite cat = createCat(catTexture, frameW, frameH, WIN_WIDTH, WIN_HEIGHT);

    sf::Clock animClock;
    float velocityY = 0.0f;
    float gravity = 0.6f;
    float jumpStrength = -13.0f;
    bool isJumping = false;
    bool isMoving = false;

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }

        handleInput(cat, isMoving, velocityY, isJumping, jumpStrength);
        applyPhysics(cat, velocityY, isJumping, gravity, WIN_HEIGHT);
        updateAnimation(cat, catRect, isMoving, animClock, animSpeed, currentFrame, totalFrames, frameW, padding);

        win.clear(sf::Color(50, 50, 50));
        win.draw(cat);
        win.display();
    }

    return 0;
}
// для компиляции g++ func.cpp -o f.out -lsfml-graphics -lsfml-window -lsfml-system