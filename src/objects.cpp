#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>
#include "objects.h"

sf::FloatRect getCatHitbox(const sf::Sprite& cat) {
    sf::FloatRect bounds = cat.getGlobalBounds();
    float width = bounds.width * 0.4f;
    float height = bounds.height * 0.8f;
    float left = cat.getPosition().x - (width / 2.0f);
    float top = cat.getPosition().y - height;
    return sf::FloatRect(left, top, width, height);
}

sf::Sprite createObject(float x, float y, const sf::Texture &texture, sf::IntRect textureRect) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(textureRect);
    sprite.setPosition(x, y);
    return sprite;
}

void handlePlatformCollisions(sf::Sprite& cat, const std::vector<sf::Sprite>& platforms, float dx, float& dy, bool& onGround) 
{
    cat.move(dx, 0);

    for (const auto& platform : platforms) {
        sf::FloatRect catBox = getCatHitbox(cat);
        sf::FloatRect platBox = platform.getGlobalBounds();

        if (catBox.intersects(platBox)) {
            if (dx > 0) {
                float overlapX = (catBox.left + catBox.width) - platBox.left;
                cat.move(-overlapX, 0);
            }
            if (dx < 0) {
                float overlapX = (platBox.left + platBox.width) - catBox.left;
                cat.move(overlapX, 0);
            }
        }
    }
    cat.move(0, dy);
    onGround = false;
    for (const auto& platform : platforms) {
        sf::FloatRect catBox = getCatHitbox(cat);
        sf::FloatRect platBox = platform.getGlobalBounds();

        if (catBox.intersects(platBox)) {
            if (dy > 0) {
                float overlapY = (catBox.top + catBox.height) - platBox.top;
                cat.move(0, -overlapY);
                dy = 0.0f;
                onGround = true;
            }
            if (dy < 0) {
                float overlapY = (platBox.top + platBox.height) - catBox.top;
                cat.move(0, overlapY);
                dy = 0.0f;
            }
        }
    }
}
void checkSpikeCollisions(sf::Sprite& cat, const std::vector<sf::Sprite>& spikes, sf::Vector2f spawnPoint, float& dy) 
{
    for (const auto& spike : spikes) {
        if (getCatHitbox(cat).intersects(spike.getGlobalBounds())) {
            cat.setPosition(spawnPoint);
            dy = 0.0f;
            break;
        }
    }
}