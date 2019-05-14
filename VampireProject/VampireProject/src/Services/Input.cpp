#include "Input.hpp"

Input::Input() {
	printf("Input init!\n");
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
		mKeyIsPressed[i] = false;
		mKeyPressEventFire[i] = false;
		mKeyOnEventFire[i] = false;
		mKeyReleaseEventFire[i] = false;
	}

	for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
		mMouseIsPressed[i] = false;
		mMousePressEventFire[i] = false;
		mMouseOnEventFire[i] = false;
		mMouseReleaseEventFire[i] = false;
	}
}

void Input::InputReset() {
	for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
		mKeyPressEventFire[i] = false;
		mKeyReleaseEventFire[i] = false;
	}

	for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
		mMousePressEventFire[i] = false;
		mMouseReleaseEventFire[i] = false;
	}
}

void Input::KeyPress(sf::Keyboard::Key key) {
	if (!mKeyIsPressed[key]) {
		mKeyPressEventFire[key] = true;
		mKeyOnEventFire[key] = true;
	}

	mKeyIsPressed[key] = true;
}

void Input::KeyRelease(sf::Keyboard::Key key) {
	if (mKeyIsPressed[key]) {
		mKeyReleaseEventFire[key] = true;
		mKeyOnEventFire[key] = false;
	}

	mKeyIsPressed[key] = false;
}

bool Input::GetKeyPressed(sf::Keyboard::Key key) {
	return mKeyPressEventFire[key];
}
bool Input::GetKey(sf::Keyboard::Key key) {
	return mKeyOnEventFire[key];
}
bool Input::GetKeyReleased(sf::Keyboard::Key key) {
	return mKeyReleaseEventFire[key];
}

void Input::MousePress(sf::Mouse::Button mouse) {
	if (!mMouseIsPressed[mouse]) {
		mMousePressEventFire[mouse] = true;
		mMouseOnEventFire[mouse] = true;
	}

	mMouseIsPressed[mouse] = true;
}

void Input::MouseRelease(sf::Mouse::Button mouse) {
	if (mMouseIsPressed[mouse]) {
		mMouseReleaseEventFire[mouse] = true;
		mMouseOnEventFire[mouse] = false;
	}

	mMouseIsPressed[mouse] = false;
}

void Input::MouseMove(sf::Vector2f position) {
	mMousePositionDelta = position - mMousePosition;
	mMousePosition = position;
}

bool Input::GetMousePressed(sf::Mouse::Button mouse) {
	return mMousePressEventFire[mouse];
}
bool Input::GetMouse(sf::Mouse::Button mouse) {
	return mMouseOnEventFire[mouse];
}
bool Input::GetMouseReleased(sf::Mouse::Button mouse) {
	return mMouseReleaseEventFire[mouse];
}

sf::Vector2f Input::GetMousePosition() {
	return mMousePosition;
}

sf::Vector2f Input::GetMousePositionDelta() {
	return mMousePositionDelta;
}
