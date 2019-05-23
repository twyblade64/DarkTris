#include "DefaultButtonControllerComponent.hpp"
#include "../Core/Locator.hpp"

DefaultButtonControllerComponent::DefaultButtonControllerComponent(sf::Vector2f position, sf::Vector2f size, const std::string& label, const sf::Font& font, sf::Color backgroundColor, sf::Color borderColor, sf::Color textColor, float borderSize): 
    ButtonControllerComponent(position, size) {
    mRect.setPosition(position);
    mRect.setSize(size);
    mRect.setOrigin(size*0.5f);
    mRect.setOutlineThickness(borderSize);
    mRect.setFillColor(backgroundColor);
    mRect.setOutlineColor(borderColor);
    mText.setPosition(position);
    mText.setString(label);
    mText.setFont(font);
    mText.setFillColor(textColor);
}

DefaultButtonControllerComponent::~DefaultButtonControllerComponent() { }

void DefaultButtonControllerComponent::FixedUpdateImplementation() { }

void DefaultButtonControllerComponent::RenderImplementation() {
    sf::RenderWindow& rw = Locator::GetWindow().GetRenderWindow();
    
    rw.draw(mRect);
    rw.draw(mText);

}
