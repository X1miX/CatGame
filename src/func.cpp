#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "movement.h"
#include "objects.h"

int main() {
  const int WIN_WIDTH = 1366;
  const int WIN_HEIGHT = 768;

  sf::RenderWindow win(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "TEST");
  win.setFramerateLimit(60);

  sf::Texture catTexture;
  if (!catTexture.loadFromFile("../images/kitty.png")) return -1;
  sf::Texture jumpTexture;
  if (!jumpTexture.loadFromFile("../images/jump.png")) return -1;
  sf::Texture keyTexture;
  if (!keyTexture.loadFromFile("../images/key.png")) return -1;
  sf::Texture background;
  if (!background.loadFromFile("../images/background.png")) return -1;
  sf::Texture objText1;
  if (!objText1.loadFromFile("../images/templ1.png")) return -1;
  objText1.setRepeated(true);
  sf::Texture objText2;
  if (!objText2.loadFromFile("../images/templ2.png")) return -1;
  sf::Texture spike;
  if (!spike.loadFromFile("../images/spikes.png")) return -1;
  spike.setRepeated(true);

  int frameW = 180;
  int frameH = 160;
  int padding = 20;
  int totalFrames = 4;
  int currentFrame = 0;
  float animSpeed = 0.15f;
  bool way = true;

  sf::Vector2f spawnpoint(100.f, 700.f);
  sf::Sprite BackGround(background);

  sf::IntRect catRect(0, 0, frameW, frameH);
  sf::IntRect jumpRect(0, 0, 200, 160);

  sf::Sprite cat = createCat(catTexture, frameW, frameH, WIN_WIDTH, WIN_HEIGHT);

  sf::Clock animClock;
  sf::Clock jumpClock;
  sf::Clock fallClock;
  bool startedFalling = false;

  float velocityX = 0.0f;
  float velocityY = 0.0f;
  float gravity = 0.6f;
  float jumpStrength = -16.0f;
  bool onGround = false;
  bool isMoving = false;

  bool keyStarted = false;
  bool keyAlive = true;
  bool keyAnim = true;
  int keyFrameCount = 12;
  float keyFrameWidth = 100.f;
  float keySwitchTime = 0.2f;
  sf::Clock keyTimer;
  int keyFrameIdx = keyFrameCount - 1;
  sf::IntRect keyRect(1100, 0, 100, 200);

  sf::Sprite key = createObject(300.0f, 450.0f, keyTexture, keyRect);
  key.setScale(0.3f, 0.3f);

  std::vector<sf::Sprite> platforms;
  std::vector<sf::Sprite> spikes;
  sf::IntRect groundRect(0, 0, 64, 8);
  sf::IntRect spikeRect(0, 0, 480, 160);

  platforms.push_back(createObject(200.f, 550.f, objText1, groundRect));
  platforms.back().setScale(4.0f, 4.0f);
  platforms.push_back(createObject(800.f, 550.f, objText2, groundRect));
  platforms.back().setScale(4.0f, 4.0f);
  platforms.push_back(createObject(500.f, 400.f, objText2, groundRect));
  platforms.back().setScale(4.0f, 4.0f);
  platforms.push_back(createObject(0.f, WIN_HEIGHT - 40.f, objText1,
                                   sf::IntRect(0, 0, WIN_WIDTH, 40)));
  platforms.back().setScale(5.0f, 5.0f);
  spikes.push_back(createObject(530.f, WIN_HEIGHT - 100, spike, spikeRect));
  spikes.back().setScale(0.4f, 0.4f);

  while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
    }

    if (!keyStarted) {
      if (keyTimer.getElapsedTime().asSeconds() > keySwitchTime) {
        keyRect.left = keyFrameIdx * keyFrameWidth;
        key.setTextureRect(keyRect);
        keyFrameIdx--;
        if (keyFrameIdx < 1) keyStarted = true;
        keyTimer.restart();
      }
    }
    if (keyAlive && keyStarted) {
      if (keyTimer.getElapsedTime().asSeconds() > keySwitchTime) {
        keyRect.left = keyFrameIdx * keyFrameWidth;
        key.setTextureRect(keyRect);
        if (way)
          keyFrameIdx++;
        else
          keyFrameIdx--;
        if (keyFrameIdx == 0) way = true;
        if (keyFrameIdx == 3) way = false;
        keyTimer.restart();
      }
    }
    if (getCatHitbox(cat).intersects(key.getGlobalBounds())) {
      keyAlive = false;
      keyFrameIdx = -1;
      keyRect.left = keyFrameIdx * keyFrameWidth;
      key.setTextureRect(keyRect);
    }
    handleInput(cat, isMoving, velocityX, velocityY, onGround, jumpStrength,
                jumpClock);

    if (onGround) velocityY = 0.0f;
    applyPhysics(cat, velocityY, gravity);
    handlePlatformCollisions(cat, platforms, velocityX, velocityY, onGround);
    checkSpikeCollisions(cat, spikes, spawnpoint, velocityY);

    updateAnimation(cat, catTexture, jumpTexture, catRect, jumpRect, jumpClock,
                    fallClock, startedFalling, isMoving, animClock, animSpeed,
                    currentFrame, totalFrames, frameW, padding, onGround,
                    velocityY);

    win.clear(sf::Color(50, 50, 50));
    win.draw(BackGround);
    win.draw(key);
    for (const auto &p : platforms) win.draw(p);
    for (const auto &s : spikes) win.draw(s);
    win.draw(cat);
    win.display();
  }
  return 0;
}