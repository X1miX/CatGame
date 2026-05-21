#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SFML/Graphics.hpp>

sf::Sprite createCat(sf::Texture &texture, int fWidth, int fHeight, int winWidth, int winHeight);
void handleInput(sf::Sprite &cat, bool &isMoving, float &velocityX, float &velocityY, bool &onGround, float jumpStrength, sf::Clock &jumpClock);
void applyPhysics(sf::Sprite &cat, float &velocityY, float gravity);
void updateAnimation(sf::Sprite &cat, sf::Texture &catTex, sf::Texture &jumpTex, sf::IntRect &rect, sf::IntRect &jumpRect, sf::Clock &jumpClock, sf::Clock &fallClock, bool &startedFalling, bool isMoving, sf::Clock &animClock, float animSpeed, int &frame, int total, int width, int pad, bool &onGround, float velocityY);

#endif