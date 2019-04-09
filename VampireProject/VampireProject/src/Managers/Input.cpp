#include "Input.hpp"

namespace Managers {
	Input& Input::GetInstance() {
		static Input input;
		return input;
	}

	void Input::KeyPress(sf::Keyboard::Key key) {
		if (!mKeyIsPressed[key]) {
			mKeyPressEventFire[key] = true;
			mOnEventFire[key] = true;
		}

		mKeyIsPressed[key] = true;
	}

	void Input::KeyRelease(sf::Keyboard::Key key) {
		if (mKeyIsPressed[key]) {
			mKeyReleaseEventFire[key] = true;
			mOnEventFire[key] = false;
		}

		mKeyIsPressed[key] = false;
	}

	void Input::KeyReset() {
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			mKeyPressEventFire[i] = false;
			mKeyReleaseEventFire[i] = false;
		}
	}

	bool Input::GetKeyPressed(sf::Keyboard::Key key) {
		return mKeyPressEventFire[key];
	}
	bool Input::GetKey(sf::Keyboard::Key key) {
		return mOnEventFire[key];
	}
	bool Input::GetKeyReleased(sf::Keyboard::Key key) {
		return mKeyReleaseEventFire[key];
	}

	Input::Input() {
		printf("Input init!\n");
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			mKeyIsPressed[i] = false;

			mKeyPressEventFire[i] = false;
			mOnEventFire[i] = false;
			mKeyReleaseEventFire[i] = false;
		}
	}
}