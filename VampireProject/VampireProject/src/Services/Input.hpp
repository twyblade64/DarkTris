#ifndef HEX_INPUT_H_
#define HEX_INPUT_H_
#include <SFML\Window.hpp>

class Input {
public:
	Input();

	void KeyPress(sf::Keyboard::Key key);
	void KeyRelease(sf::Keyboard::Key key);
	void KeyReset();

	bool GetKeyPressed(sf::Keyboard::Key key);
	bool GetKey(sf::Keyboard::Key key);
	bool GetKeyReleased(sf::Keyboard::Key key);
private:
	bool mKeyIsPressed[sf::Keyboard::KeyCount];

	bool mKeyPressEventFire[sf::Keyboard::KeyCount];
	bool mOnEventFire[sf::Keyboard::KeyCount];
	bool mKeyReleaseEventFire[sf::Keyboard::KeyCount];
};

#endif // HEX_INPUT_H_