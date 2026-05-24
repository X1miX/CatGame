#include <SFML/Graphics.hpp>

struct GameMenuData {
    float menu_X;
    float menu_Y;
    int menu_Step;
    int max_menu;
    int size_font;
    int mainMenuSelected;
    sf::Font font;
    sf::Text* mainMenu;
    sf::Color menu_text_color;
    sf::Color chose_text_color;
    sf::Color border_color;
    sf::RenderWindow* mywindow;
};

void initGameMenu(GameMenuData& menu, sf::RenderWindow& window, float menux, float menuy,
                  int index, sf::String name[], int sizeFont = 60, int step = 80);
                  
void drawMenu(GameMenuData& menu);