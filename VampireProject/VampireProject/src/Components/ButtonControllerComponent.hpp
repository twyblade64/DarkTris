#ifndef HEX_BUTTON_CONTROLLER_COMPONENT_H_
#define HEX_BUTTON_CONTROLLER_COMPONENT_H_

#include <memory>
#include "../Core/Component.hpp"
#include "../GameObjects/GameObjectBase.hpp"

class Command;
class ButtonControllerComponent: public Component<ButtonControllerComponent> {
public:
    ButtonControllerComponent(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f size = sf::Vector2f(0,0));
    ~ButtonControllerComponent();
public:
    virtual void FixedUpdateImplementation() = 0;
    virtual void VarUpdateImplementation();
    virtual void RenderImplementation() = 0;
public:
    void SetOnMouseEnter(std::unique_ptr<Command> command);
    void SetOnMouseExit (std::unique_ptr<Command> command);
    void SetOnMouseHover(std::unique_ptr<Command> command);
    void SetOnMouseDown (std::unique_ptr<Command> command);
    void SetOnMouseUp   (std::unique_ptr<Command> command);
    void SetOnMouseClick(std::unique_ptr<Command> command);

    void SetSize(sf::Vector2f size);
    sf::Vector2f GetSize();
protected:
    virtual void OnMouseEnter();
    virtual void OnMouseExit();
    virtual void OnMouseHover();
    virtual void OnMouseDown();
    virtual void OnMouseUp();
    virtual void OnMouseClick();
protected:
    bool mPressed;
    bool mHover;

    std::unique_ptr<Command> mOnMouseEnterDelegate;
    std::unique_ptr<Command> mOnMouseExitDelegate;
    std::unique_ptr<Command> mOnMouseHoverDelegate;
    std::unique_ptr<Command> mOnMouseDownDelegate;
    std::unique_ptr<Command> mOnMouseUpDelegate;
    std::unique_ptr<Command> mOnMouseClickDelegate;
private:
    sf::Vector2f mSize;
    sf::Vector2f mPosition;
};

#endif HEX_BUTTON_CONTROLLER_COMPONENT_H_
