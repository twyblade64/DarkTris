#ifndef HEX_GAME_H_
#define HEX_GAME_H_

#include <list>
#include <memory>
#include "../GameObjects/GameObjectBase.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class Game {
public:
	Game();
	void Run();
private:
	void FixedUpdate();
	void VarUpdate();
	void Render();
	void ProcessEvents();
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	std::list<std::unique_ptr<GameObjectBase>> objectList;
};

#endif // HEX_GAME_H_