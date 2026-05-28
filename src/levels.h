#ifndef LEVELS_H
#define LEVELS_H

#include <SFML/Graphics.hpp>
#include <vector>

bool executeLevel(sf::RenderWindow &win, sf::Vector2f spawnpoint,
                  std::vector<sf::Sprite> &platforms,
                  std::vector<sf::Sprite> &spikes, sf::Sprite &key,
                  sf::Sprite &door, sf::Texture &catTexture,
                  sf::Texture &jumpTexture, sf::Texture &keyTexture,
                  sf::Texture &background, sf::Texture &doorTexture);

bool runLevel1(sf::RenderWindow &win, sf::Texture &catTex, sf::Texture &jumpTex,
               sf::Texture &keyTex, sf::Texture &bgTex, sf::Texture &obj1Tex,
               sf::Texture &obj2Tex, sf::Texture &spikeTex,
               sf::Texture &doorTex);

bool runLevel2(sf::RenderWindow &win, sf::Texture &catTex, sf::Texture &jumpTex,
               sf::Texture &keyTex, sf::Texture &bgTex, sf::Texture &obj1Tex,
               sf::Texture &obj2Tex, sf::Texture &spikeTex,
               sf::Texture &doorTex);

bool runLevel3(sf::RenderWindow &win, sf::Texture &catTex, sf::Texture &jumpTex,
               sf::Texture &keyTex, sf::Texture &bgTex, sf::Texture &obj1Tex,
               sf::Texture &obj2Tex, sf::Texture &spikeTex,
               sf::Texture &doorTex);

#endif