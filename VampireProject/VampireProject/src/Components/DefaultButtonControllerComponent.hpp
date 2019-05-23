#ifndef HEX_DEFAULT_BUTTON_CONTROLLER_COMPONENT_H_
#define HEX_DEFAULT_BUTTON_CONTROLLER_COMPONENT_H_

#include <string>
#include "SFML/Graphics.hpp"
#include "../Components/ButtonControllerComponent.hpp"

namespace sf {
    class Font;
}

class DefaultButtonControllerComponent: public ButtonControllerComponent {
public:
	DefaultButtonControllerComponent(sf::Vector2f position, sf::Vector2f size, const std::string& label, const sf::Font& font, sf::Color backgroundColor = sf::Color(0xCCCCCCFF), sf::Color borderColor = sf::Color(0x000000FF), sf::Color textColor = sf::Color(0x000000FF), float borderSize = 1);
    ~DefaultButtonControllerComponent();
public:
    void FixedUpdateImplementation() override;
    void RenderImplementation() override;
protected:
    sf::Text mText;
    sf::RectangleShape mRect;
};


#endif // HEX_DEFAULT_BUTTON_CONTROLLER_COMPONENT_H_
