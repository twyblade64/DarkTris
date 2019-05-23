#include "Button.hpp"
Button::Button(sf::Vector2f position, sf::Vector2f dimension, std::unique_ptr<ButtonControllerComponent> buttonController):
    GameObject<Button>(position), 
    mButtonControllerComponent(std::move(buttonController)) {
        
}

Button::~Button() { }


void Button::FixedUpdateImplementation() {
    mButtonControllerComponent->FixedUpdate();
}

void Button::VarUpdateImplementation() {
    mButtonControllerComponent->VarUpdate();
}

void Button::RenderImplementation() {
    mButtonControllerComponent->Render();
}

ButtonControllerComponent& Button::GetButtonController() {
    return *mButtonControllerComponent;
}
