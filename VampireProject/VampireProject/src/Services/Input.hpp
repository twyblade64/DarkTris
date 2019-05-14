#ifndef HEX_INPUT_H_
#define HEX_INPUT_H_
#include <SFML\Window.hpp>

class Input {
public:
	Input();

	void InputReset();

	void KeyPress(sf::Keyboard::Key key);
	void KeyRelease(sf::Keyboard::Key key);

	bool GetKeyPressed(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyReleased(sf::Keyboard::Key key);

	void MousePress(sf::Mouse::Button button);
	void MouseRelease(sf::Mouse::Button button);
	void MouseMove(sf::Vector2f position);

	bool GetMousePressed(sf::Mouse::Button button);
	bool GetMouse(sf::Mouse::Button button);
	bool GetMouseReleased(sf::Mouse::Button button);
	sf::Vector2f GetMousePosition();
	sf::Vector2f GetMousePositionDelta();

private:
	bool mKeyIsPressed[sf::Keyboard::KeyCount];
	bool mKeyPressEventFire[sf::Keyboard::KeyCount];
	bool mKeyOnEventFire[sf::Keyboard::KeyCount];
	bool mKeyReleaseEventFire[sf::Keyboard::KeyCount];

	bool mMouseIsPressed[sf::Mouse::ButtonCount];
	bool mMousePressEventFire[sf::Mouse::ButtonCount];
	bool mMouseOnEventFire[sf::Mouse::ButtonCount];
	bool mMouseReleaseEventFire[sf::Mouse::ButtonCount];

	sf::Vector2f mMousePosition;
	sf::Vector2f mMousePositionDelta;
};

#endif // HEX_INPUT_H_