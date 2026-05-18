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
    sf::Texture keyTexture;
    if (!keyTexture.loadFromFile("../images/key.png"))
        return -1;
    sf::Texture background;
    if (!background.loadFromFile("../images/background.png"))
        return -1;
    sf::Texture objText1;
    if (!objText1.loadFromFile("../images/templ1.png"))
        return -1;
    objText1.setRepeated(true);
    sf::Texture objText2;
    if (!objText2.loadFromFile("../images/templ2.png"))
        return -1;
    sf::Texture objText3;
    if (!objText3.loadFromFile("../images/templ3.png"))
        return -1;
    sf::Texture spike;
    if (!spike.loadFromFile("../images/spikes.png"))
        return -1;
    spike.setRepeated(true);
    int frameW = 180;
    int frameH = 160;
    int padding = 20;
    int totalFrames = 4;
    int currentFrame = 0;
    float animSpeed = 0.15f;
    sf::Vector2f spawnpoint;
    spawnpoint.x = 100.f;
    spawnpoint.y = 700.f;
    sf::Sprite BackGround(background);
    sf::IntRect catRect(0, 0, frameW, frameH);
    sf::Sprite cat = createCat(catTexture, frameW, frameH, WIN_WIDTH, WIN_HEIGHT);

    sf::Clock animClock;
    float velocityX = 0.0f;
    float velocityY = 0.0f;
    float gravity = 0.6f;
    float jumpStrength = -16.0f;
    bool onGround = false;
    bool isMoving = false;
    bool keyStarted = false;
    static int keyFrameCount = 12;
    static float keyFrameWidth = 100.f;
    static float keySwitchTime = 0.15f;
    static sf::Clock keyTimer;
    static int keyFrameIdx = keyFrameCount - 1;
    std::vector<sf::Sprite> platforms;
    std::vector<sf::Sprite> spikes;
    std::vector<sf::Sprite> keys;
    sf::IntRect groundRect(0, 0, 64, 8);
    sf::IntRect spikeRect(0, 0, 480, 160);
    sf::IntRect keyRect(1100, 0, 100, 200);
    sf::Sprite key = createObject(300.0f, 450.0f, keyTexture, keyRect);
    key.setScale(0.3f, 0.3f);
    platforms.push_back(createObject(200.f, 550.f, objText1, groundRect)); // тут можно обьектов для теста добавить
    platforms.back().setScale(4.0f, 4.0f);
    platforms.push_back(createObject(800.f, 550.f, objText2, groundRect));
    platforms.back().setScale(4.0f, 4.0f);
    platforms.push_back(createObject(0.f, WIN_HEIGHT - 40.f, objText1, sf::IntRect(0, 0, WIN_WIDTH, 40)));
    platforms.back().setScale(5.0f, 5.0f);
    spikes.push_back(createObject(500.f, WIN_HEIGHT - 100, spike, spikeRect));
    spikes.back().setScale(0.4f, 0.4f);

    while (win.isOpen())
    {
        if (keyStarted == false)
        {
            if (keyTimer.getElapsedTime().asSeconds() > keySwitchTime)
            {
                keyRect.left = keyFrameIdx * keyFrameWidth;
                key.setTextureRect(keyRect);
                keyFrameIdx--;
                if (keyFrameIdx < 0)
                {
                    keyStarted = true;
                }

                keyTimer.restart();
            }
        }
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
        win.draw(BackGround);
        win.draw(key);
        win.draw(cat);
        for (const auto &platform : platforms)
        {
            win.draw(platform);
        }
        for (const auto &spike : spikes)
        {
            win.draw(spike);
        }
        win.display();
    }
    return 0;
}
// g++ func.cpp movement.cpp objects.cpp -o f.out -lsfml-graphics -lsfml-window -lsfml-system для компиляции