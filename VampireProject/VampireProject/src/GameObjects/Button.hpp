#ifndef HEX_BUTTON_H_
#define HEX_BUTTON_H_

#include <memory>
#include "GameObject.hpp"
#include "../Components/ButtonControllerComponent.hpp"

class Button : public GameObject<Button> {
public:
    Button(sf::Vector2f position, sf::Vector2f dimension, std::unique_ptr<ButtonControllerComponent> buttonController);
    ~Button();
public:
    virtual void FixedUpdateImplementation();
    virtual void VarUpdateImplementation();
    virtual void RenderImplementation();
public:
    ButtonControllerComponent& GetButtonController();
private:
    std::unique_ptr<ButtonControllerComponent> mButtonControllerComponent;
};

#endif // HEX_BUTTON_H_
