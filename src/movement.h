#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SFML/Graphics.hpp>

sf::Sprite createCat(sf::Texture &texture, int fWidth, int fHeight, int winWidth, int winHeight);
void handleInput(sf::Sprite &cat, bool &isMoving, float &velocityX, float &velocityY, bool &onGround, float jumpStrength);
void applyPhysics(sf::Sprite &cat, float &velocityY, float gravity);
void updateAnimation(sf::Sprite &cat, sf::IntRect &rect, bool isMoving, sf::Clock &animClock, float animSpeed, int &frame, int total, int width, int pad);

#endif