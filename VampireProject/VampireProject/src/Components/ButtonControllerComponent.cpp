#include "ButtonControllerComponent.hpp"
#include "../Core/Locator.hpp"
#include "../Math/Utils.hpp"
#include "../GameObjects/GameObjectBase.hpp"
#include "../Utility/Command.hpp"

ButtonControllerComponent::ButtonControllerComponent(sf::Vector2f position, sf::Vector2f size):
    mPosition(position), mSize(size) {

}

ButtonControllerComponent::~ButtonControllerComponent() {}

void ButtonControllerComponent::VarUpdateImplementation() {
    Input& input = Locator::GetInput();
    
    sf::Vector2f delta = Vector2fAbs((input.GetMousePosition() - mPosition)) - mSize*.5f;
    
    bool prevHover = mHover;
    bool prevPressed = mPressed;

    bool mousePress = input.GetMouse(sf::Mouse::Left);
    mHover = delta.x <= 0 && delta.y <= 0;


    if (!prevHover && mHover) OnMouseEnter();
    if (mHover) OnMouseHover();
    if (prevHover && !mHover) OnMouseExit();

    if (mHover && mousePress) {
        OnMouseDown();
        mPressed = true;
    }

    if (mHover && !mousePress) {
        OnMouseUp();
    }

    if (mPressed && !mousePress) {
        mPressed = false;
        if (mHover) OnMouseClick();
    }

}

void ButtonControllerComponent::SetOnMouseEnter(std::unique_ptr<Command> command) {
    mOnMouseEnterDelegate = std::move(command);
}

void ButtonControllerComponent::SetOnMouseExit (std::unique_ptr<Command> command) {
    mOnMouseExitDelegate = std::move(command);
}

void ButtonControllerComponent::SetOnMouseHover(std::unique_ptr<Command> command) {
    mOnMouseHoverDelegate = std::move(command);
}

void ButtonControllerComponent::SetOnMouseDown (std::unique_ptr<Command> command) {
    mOnMouseDownDelegate = std::move(command);
}

void ButtonControllerComponent::SetOnMouseUp   (std::unique_ptr<Command> command) {
    mOnMouseUpDelegate = std::move(command);
}

void ButtonControllerComponent::SetOnMouseClick(std::unique_ptr<Command> command) {
    mOnMouseClickDelegate = std::move(command);
}

void ButtonControllerComponent::OnMouseEnter() {
    if (mOnMouseEnterDelegate) mOnMouseEnterDelegate->Call();
}

void ButtonControllerComponent::OnMouseExit() {
    if (mOnMouseExitDelegate) mOnMouseExitDelegate->Call();
}

void ButtonControllerComponent::OnMouseHover() {
    if (mOnMouseHoverDelegate) mOnMouseHoverDelegate->Call();
}

void ButtonControllerComponent::OnMouseDown() {
    if (mOnMouseDownDelegate) mOnMouseDownDelegate->Call();
}

void ButtonControllerComponent::OnMouseUp() {
    if (mOnMouseUpDelegate) mOnMouseUpDelegate->Call();
}

void ButtonControllerComponent::OnMouseClick() {
    if (mOnMouseClickDelegate) mOnMouseClickDelegate->Call();
}
