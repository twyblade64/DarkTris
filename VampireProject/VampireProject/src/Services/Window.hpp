#ifndef HEX_WINDOW_H_
#define HEX_WINDOW_H_

#include <SFML/Graphics.hpp>

class Window {
public:
    Window(int width, int height, const char* title): mWindow(sf::VideoMode(width, height), title) { }
    sf::RenderWindow& GetRenderWindow() { return mWindow; }
private:
    sf::RenderWindow mWindow;
};

#endif // HEX_WINDOW_H_
