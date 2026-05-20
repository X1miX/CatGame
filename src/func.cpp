#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include "movement.h"
#include "objects.h"

int main()
{
    const int WIN_WIDTH = 1366;
    const int WIN_HEIGHT = 768;

    sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "TEST");
    win.setFramerateLimit(60);

    sf::Texture catTexture;
    if (!catTexture.loadFromFile("../images/kitty.png"))
        return -1;
    sf::Texture objText;
    if(!objText.loadFromFile("../images/objects.png"))
        return -1;
    int frameW = 180;
    int frameH = 160;
    int padding = 20;
    int totalFrames = 4;
    int currentFrame = 0;
    float animSpeed = 0.15f;
    sf::Vector2f spawnpoint;
    spawnpoint.x = 100.f;
    spawnpoint.y = 700.f;

    sf::IntRect catRect(0, 0, frameW, frameH);
    sf::Sprite cat = createCat(catTexture, frameW, frameH, WIN_WIDTH, WIN_HEIGHT);

    sf::Clock animClock;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float gravity = 0.6f;
    float jumpStrength = -16.0f;
    bool onGround = false;
    bool isMoving = false;

    std::vector<sf::Sprite> platforms;
    std::vector<sf::Sprite> spikes;
    sf::IntRect groundRect(0, 0, 128, 16); 
    sf::IntRect spikeRect(64, 0, 32, 32);

    platforms.push_back(createObject(300.f, 600.f, objText, groundRect)); // тут можно обьектов для теста добавить
    platforms.push_back(createObject(800.f, 600.f, objText, groundRect));
    platforms.push_back(createObject(0.f, WIN_HEIGHT - 40.f, objText, sf::IntRect(0, 0, WIN_WIDTH, 40)));
    spikes.push_back(createObject(500.f, WIN_HEIGHT - 70, objText, spikeRect));

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }
        
        handleInput(cat, isMoving, velocityX, velocityY, onGround, jumpStrength);
        if (onGround)
        {
            velocityY = 0.0f;
        }
        applyPhysics(cat, velocityY, gravity);
        handlePlatformCollisions(cat, platforms, velocityX, velocityY, onGround);
        checkSpikeCollisions(cat, spikes, spawnpoint, velocityY);
        updateAnimation(cat, catRect, isMoving, animClock, animSpeed, currentFrame, totalFrames, frameW, padding);
        
        win.clear(sf::Color(50, 50, 50));
        win.draw(cat);
        for (const auto& platform : platforms) {
            win.draw(platform);
        }
        for (const auto& spike : spikes) {
            win.draw(spike);
        }
        win.display();
    }
    return 0;
}
//g++ func.cpp movement.cpp objects.cpp -o f.out -lsfml-graphics -lsfml-window -lsfml-system для компиляции