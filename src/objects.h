#ifndef OBJECTS_H
#define OBJECTS_H

#include <SFML/Graphics.hpp>
#include <vector>

sf::FloatRect getCatHitbox(const sf::Sprite &cat);
sf::Sprite createObject(float x, float y, const sf::Texture &texture, sf::IntRect textureRect);
void handlePlatformCollisions(sf::Sprite &cat, const std::vector<sf::Sprite> &platforms, float dx, float &dy, bool &onGround);
void checkSpikeCollisions(sf::Sprite &cat, const std::vector<sf::Sprite> &spikes, sf::Vector2f spawnPoint, float &dy);

#endif