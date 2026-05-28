#include "game_menu.h"

#include <SFML/Graphics.hpp>

void setInitText(sf::Text& text, sf::String str, float xpos, float ypos,
                 sf::Font& font, int size_font, sf::Color menu_text_color,
                 sf::Color border_color) {
  text.setFont(font);
  text.setFillColor(menu_text_color);
  text.setString(str);
  text.setCharacterSize(size_font);
  text.setPosition(xpos, ypos);
  text.setOutlineThickness(3);
  text.setOutlineColor(border_color);
}

void initGameMenu(GameMenuData& menu, sf::RenderWindow& window, float menux,
                  float menuy, int index, sf::String name[], int sizeFont,
                  int step) {
  menu.mywindow = &window;
  menu.menu_X = menux;
  menu.menu_Y = menuy;
  menu.size_font = sizeFont;
  menu.menu_Step = step;
  menu.max_menu = index;
  menu.menu_text_color = sf::Color::White;
  menu.chose_text_color = sf::Color(150,150,90);
  menu.border_color = sf::Color::Black;

  
  if (!menu.font.loadFromFile("fonts/troika.otf")) exit(32);

  
  menu.mainMenu = new sf::Text[menu.max_menu];

  
  for (int i = 0, ypos = menu.menu_Y; i < menu.max_menu;
       i++, ypos += menu.menu_Step) {
    setInitText(menu.mainMenu[i], name[i], menu.menu_X, ypos, menu.font,
                menu.size_font, menu.menu_text_color, menu.border_color);
  }

  menu.mainMenuSelected = 0;
  menu.mainMenu[menu.mainMenuSelected].setFillColor(menu.chose_text_color);
}

void drawMenu(GameMenuData& menu) {
  for (int i = 0; i < menu.max_menu; i++) {
    menu.mywindow->draw(menu.mainMenu[i]);
  }
}

void moveMenuUp(GameMenuData& menu) {
  menu.mainMenuSelected--;

  if (menu.mainMenuSelected >= 0) {
    menu.mainMenu[menu.mainMenuSelected].setFillColor(menu.chose_text_color);
    menu.mainMenu[menu.mainMenuSelected + 1].setFillColor(menu.menu_text_color);
  } else {
    menu.mainMenu[0].setFillColor(menu.menu_text_color);
    menu.mainMenuSelected = menu.max_menu - 1;
    menu.mainMenu[menu.mainMenuSelected].setFillColor(menu.chose_text_color);
  }
}

void moveMenuDown(GameMenuData& menu) {
  menu.mainMenuSelected++;

  if (menu.mainMenuSelected < menu.max_menu) {
    menu.mainMenu[menu.mainMenuSelected - 1].setFillColor(menu.menu_text_color);
    menu.mainMenu[menu.mainMenuSelected].setFillColor(menu.chose_text_color);
  } else {
    menu.mainMenu[menu.max_menu - 1].setFillColor(menu.menu_text_color);
    menu.mainMenuSelected = 0;
    menu.mainMenu[menu.mainMenuSelected].setFillColor(menu.chose_text_color);
  }
}

int getSelectedMenuNumber(GameMenuData& menu) { return menu.mainMenuSelected; }

void setMenuColors(GameMenuData& menu, sf::Color menColor, sf::Color ChoColor,
                   sf::Color BordColor) {
  menu.menu_text_color = menColor;
  menu.chose_text_color = ChoColor;
  menu.border_color = BordColor;

  for (int i = 0; i < menu.max_menu; i++) {
    menu.mainMenu[i].setFillColor(menu.menu_text_color);
    menu.mainMenu[i].setOutlineColor(menu.border_color);
  }

  menu.mainMenu[menu.mainMenuSelected].setFillColor(menu.chose_text_color);
}