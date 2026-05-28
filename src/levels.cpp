#include "levels.h"

#include "movement.h"
#include "objects.h"

sf::Sprite createScaledPlatform(float x, float y, float visualWidth,
                                float visualHeight, sf::Texture &tex,
                                float scale = 4.0f) {
  sf::Sprite p;
  p.setTexture(tex);
  p.setTextureRect(sf::IntRect(0, 0, static_cast<int>(visualWidth / scale),
                               static_cast<int>(visualHeight / scale)));
  p.setPosition(x, y);
  p.setScale(scale, scale);
  return p;
}

bool internalLevelLoop(sf::RenderWindow &win, sf::Vector2f spawnpoint,
                       std::vector<sf::Sprite> &platforms,
                       std::vector<sf::Sprite> &spikes, sf::Sprite &key,
                       sf::Sprite &door, sf::Texture &catTex,
                       sf::Texture &jumpTex, sf::Texture &bgTex) {
  sf::Sprite bg(bgTex);
  bg.setScale((float)win.getSize().x / bg.getLocalBounds().width,
              (float)win.getSize().y / bg.getLocalBounds().height);

  sf::Sprite cat =
      createCat(catTex, 180, 160, win.getSize().x, win.getSize().y);
  cat.setScale(0.5f, 0.5f);
  cat.setPosition(spawnpoint);

  float vy = 0, vx = 0;
  bool onGround = false, isMoving = false, keyPicked = false,
       startedFalling = false;
  sf::Clock animClock, jumpClock, fallClock;
  int frame = 0;
  sf::IntRect catRect(0, 0, 180, 160), jumpRect(0, 0, 200, 160);

  bool keyStarted = false;
  bool way = true;
  float keyFrameWidth = 100.f;
  float keySwitchTime = 0.2f;
  sf::Clock keyTimer;
  int keyFrameIdx = 11;
  sf::IntRect keyRect(1100, 0, 100, 200);

  while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;
    }

    if (!keyStarted) {
      if (keyTimer.getElapsedTime().asSeconds() > keySwitchTime) {
        keyRect.left = keyFrameIdx * static_cast<int>(keyFrameWidth);
        key.setTextureRect(keyRect);
        keyFrameIdx--;
        if (keyFrameIdx < 1) keyStarted = true;
        keyTimer.restart();
      }
    }
    if (!keyPicked && keyStarted) {
      if (keyTimer.getElapsedTime().asSeconds() > keySwitchTime) {
        keyRect.left = keyFrameIdx * static_cast<int>(keyFrameWidth);
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

    vx = 0;

    handleInput(cat, isMoving, vx, vy, onGround, -17.5f, jumpClock);
    applyPhysics(cat, vy, 0.6f);
    handlePlatformCollisions(cat, platforms, vx, vy, onGround);
    checkSpikeCollisions(cat, spikes, spawnpoint, vy);

    if (!keyPicked && getCatHitbox(cat).intersects(key.getGlobalBounds())) {
      keyPicked = true;
    }
    if (keyPicked && getCatHitbox(cat).intersects(door.getGlobalBounds())) {
      return true;
    }

    updateAnimation(cat, catTex, jumpTex, catRect, jumpRect, jumpClock,
                    fallClock, startedFalling, isMoving, animClock, 0.15f,
                    frame, 4, 180, 20, onGround, vy);

    win.clear();
    win.draw(bg);
    win.draw(door);
    if (!keyPicked) win.draw(key);
    for (auto &p : platforms) win.draw(p);
    for (auto &s : spikes) win.draw(s);
    win.draw(cat);
    win.display();
  }
  return false;
}

bool runLevel1(sf::RenderWindow &win, sf::Texture &catTex, sf::Texture &jumpTex,
               sf::Texture &keyTex, sf::Texture &bgTex, sf::Texture &obj1Tex,
               sf::Texture &obj2Tex, sf::Texture &spikeTex,
               sf::Texture &doorTex) {
  std::vector<sf::Sprite> p;
  std::vector<sf::Sprite> s;
  float screenH = (float)win.getSize().y;

  p.push_back(createScaledPlatform(0, screenH - 100, 1920, 100, obj1Tex, 5.0f));

  p.push_back(createScaledPlatform(430, screenH - 270, 256, 40, obj2Tex, 4.0f));
  p.push_back(createScaledPlatform(900, screenH - 450, 256, 40, obj2Tex, 4.0f));

  sf::Sprite sp =
      createObject(500, screenH - 164, spikeTex, sf::IntRect(0, 0, 480, 160));
  sp.setScale(0.4f, 0.4f);
  s.push_back(sp);

  sf::Sprite k =
      createObject(950, screenH - 550, keyTex, sf::IntRect(1100, 0, 100, 200));
  k.setScale(0.3f, 0.3f);

  sf::Sprite d =
      createObject(1600, screenH - 215, doorTex, sf::IntRect(0, 0, 270, 230));
  d.setScale(0.5f, 0.5f);

  return internalLevelLoop(win, {100, screenH - 200}, p, s, k, d, catTex,
                           jumpTex, bgTex);
}

bool runLevel2(sf::RenderWindow &win, sf::Texture &catTex, sf::Texture &jumpTex,
               sf::Texture &keyTex, sf::Texture &bgTex, sf::Texture &obj1Tex,
               sf::Texture &obj2Tex, sf::Texture &spikeTex,
               sf::Texture &doorTex) {
  std::vector<sf::Sprite> p;
  std::vector<sf::Sprite> s;
  float screenH = (float)win.getSize().y;

  p.push_back(createScaledPlatform(0, screenH - 100, 1920, 100, obj1Tex, 5.0f));

  p.push_back(createScaledPlatform(700, screenH - 500, 80, 400, obj1Tex, 4.0f));

  p.push_back(createScaledPlatform(300, screenH - 300, 200, 40, obj2Tex, 4.0f));
  p.push_back(createScaledPlatform(500, screenH - 500, 200, 40, obj2Tex, 4.0f));

  sf::Sprite sp = createObject(800, screenH - 164, spikeTex,
                               sf::IntRect(0, 0, 800, 160));  // Шире в 2 раза
  sp.setScale(0.4f, 0.4f);
  s.push_back(sp);

  sf::Sprite k =
      createObject(100, screenH - 400, keyTex, sf::IntRect(1100, 0, 100, 200));
  k.setScale(0.3f, 0.3f);

  sf::Sprite d =
      createObject(1500, screenH - 215, doorTex, sf::IntRect(0, 0, 270, 230));
  d.setScale(0.5f, 0.5f);

  return internalLevelLoop(win, {100, screenH - 200}, p, s, k, d, catTex,
                           jumpTex, bgTex);
}

bool runLevel3(sf::RenderWindow &win, sf::Texture &catTex, sf::Texture &jumpTex,
               sf::Texture &keyTex, sf::Texture &bgTex, sf::Texture &obj1Tex,
               sf::Texture &obj2Tex, sf::Texture &spikeTex,
               sf::Texture &doorTex) {
  std::vector<sf::Sprite> p;
  std::vector<sf::Sprite> s;
  float screenH = (float)win.getSize().y;

  p.push_back(createScaledPlatform(0, screenH - 150, 300, 50, obj1Tex, 4.0f));
  p.push_back(createScaledPlatform(450, screenH - 350, 200, 40, obj2Tex, 4.0f));
  p.push_back(createScaledPlatform(850, screenH - 550, 200, 40, obj2Tex, 4.0f));
  p.push_back(
      createScaledPlatform(1300, screenH - 300, 400, 60, obj1Tex, 4.0f));

  sf::Sprite sp =
      createObject(250, screenH - 64, spikeTex, sf::IntRect(0, 0, 2400, 160));
  sp.setScale(0.4f, 0.4f);
  s.push_back(sp);

  sf::Sprite k =
      createObject(900, screenH - 650, keyTex, sf::IntRect(1100, 0, 100, 200));
  k.setScale(0.3f, 0.3f);

  sf::Sprite d =
      createObject(1500, screenH - 415, doorTex, sf::IntRect(0, 0, 270, 230));
  d.setScale(0.5f, 0.5f);

  return internalLevelLoop(win, {50, screenH - 300}, p, s, k, d, catTex,
                           jumpTex, bgTex);
}