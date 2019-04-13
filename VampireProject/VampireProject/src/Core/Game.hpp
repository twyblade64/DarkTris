#ifndef HEX_GAME_H_
#define HEX_GAME_H_

#include <list>
#include <memory>
#include "../GameObjects/GameObjectBase.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class Game {
public :
	Game();
	void Run();
public:
	static Game* Get();
private:
	static Game* mInstance;
	void FixedUpdate();
	void VarUpdate();
	void Render();
	void ProcessEvents();
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow window;
	std::list<std::unique_ptr<GameObjectBase>> objectList;
};

#endif // HEX_GAME_H_