#include "movement.h"
#include <cmath>

sf::Sprite createCat(sf::Texture &texture, int fWidth, int fHeight, int winWidth, int winHeight)
{
    sf::IntRect firstFrame(0, 0, fWidth, fHeight);
    sf::Sprite cat(texture, firstFrame);
    cat.setOrigin(fWidth / 2.0f, static_cast<float>(fHeight));
    cat.setScale(0.5f, 0.5f);
    cat.setPosition(winWidth / 2.0f, winHeight - 40.0f);
    return cat;
}

void handleInput(sf::Sprite &cat, bool &isMoving, float &velocityX, float &velocityY, bool &onGround, float jumpStrength, sf::Clock &jumpClock)
{
    isMoving = false;
    velocityX = 0.0f;
    float scaleX = std::abs(cat.getScale().x);
    float scaleY = cat.getScale().y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocityX = -5.0f;
        cat.setScale(-scaleX, scaleY);
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocityX = 5.0f;
        cat.setScale(scaleX, scaleY);
        isMoving = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround)
    {
        jumpClock.restart();
        velocityY = jumpStrength;
        onGround = false;
    }
}

void applyPhysics(sf::Sprite &cat, float &velocityY, float gravity)
{
    velocityY += gravity;
}

void updateAnimation(sf::Sprite &cat, sf::Texture &catTex, sf::Texture &jumpTex, sf::IntRect &rect, sf::IntRect &jumpRect, sf::Clock &jumpClock, sf::Clock &fallClock, bool &startedFalling, bool isMoving, sf::Clock &animClock, float animSpeed, int &frame, int total, int width, int pad, bool &onGround, float velocityY)
{
    if (onGround)
    {
        cat.setTexture(catTex);
        startedFalling = false;
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
    else
    {
        cat.setTexture(jumpTex);
        if (velocityY < 0)
        {
            if (jumpClock.getElapsedTime().asSeconds() < 0.3f)
                jumpRect.left = 0;
            else
                jumpRect.left = 200;
        }
        else
        {
            if (!startedFalling)
            {
                fallClock.restart();
                startedFalling = true;
            }

            if (fallClock.getElapsedTime().asSeconds() < 0.5f)
                jumpRect.left = 400;
            else
                jumpRect.left = 600;
        }
        cat.setTextureRect(jumpRect);
    }
}