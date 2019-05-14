#ifndef HEX_GAME_H_
#define HEX_GAME_H_

#include <list>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include "../GameObjects/GameObjectBase.hpp"
#include "../States/GameState.hpp"
#include "../States/MenuState.hpp"

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
public:
	std::list<std::unique_ptr<GameObjectBase>> objectList;
private:
	State* mCurrentState;
	GameState mGameState;
	MenuState mMenuState;
};

#endif // HEX_GAME_H_