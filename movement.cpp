#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "movement.h"

sf::Sprite createCat(sf::Texture &texture, int fWidth, int fHeight, int winWidth, int winHeight)
{
    sf::IntRect firstFrame(0, 0, fWidth, fHeight);
    sf::Sprite cat(texture, firstFrame);

    cat.setOrigin(fWidth / 2.0f, fHeight / 2.0f);
    cat.setScale(0.5f, 0.5f);
    cat.setPosition(winWidth / 2.0f, winHeight - 40.0f);

    return cat;
}

void handleInput(sf::Sprite &cat, bool &isMoving, float &velocityY, bool &isJumping, float jumpStrength)
{
    isMoving = false;
    float scaleX = std::abs(cat.getScale().x);
    float scaleY = cat.getScale().y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        cat.move(-5.0f, 0.0f);
        cat.setScale(-scaleX, scaleY);
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        cat.move(5.0f, 0.0f);
        cat.setScale(scaleX, scaleY);
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping)
    {
        velocityY = jumpStrength;
        isJumping = true;
    }
}

void applyPhysics(sf::Sprite &cat, float &velocityY, bool &isJumping, float gravity, int winHeight)
{
    velocityY += gravity;
    cat.move(0, velocityY);

    float floorLevel = winHeight - 40.0f;
    if (cat.getPosition().y >= floorLevel)
    {
        cat.setPosition(cat.getPosition().x, floorLevel);
        velocityY = 0.0f;
        isJumping = false;
    }
}

void updateAnimation(sf::Sprite &cat, sf::IntRect &rect, bool isMoving, sf::Clock &animClock, float animSpeed, int &frame, int total, int width, int pad)
{
    if (isMoving)
    {
        if (animClock.getElapsedTime().asSeconds() > animSpeed)
        {
            frame = (frame + 1) % total;
            rect.left = frame * (width + pad);
            cat.setTextureRect(rect);
            animClock.restart();
        }
    }
    else
    {
        frame = 0;
        rect.left = 0;
        cat.setTextureRect(rect);
    }
}