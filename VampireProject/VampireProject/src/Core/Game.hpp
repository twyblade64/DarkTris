#ifndef HEX_GAME_H_
#define HEX_GAME_H_

#include <list>
#include <SFML\Graphics.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\System\Vector2.hpp>

class Game {
public :
	Game();
	void Run();
public:
	static Game* Get();
private:
	static Game* mInstance;
	void Update(sf::Time deltaTime);
	void ProcessEvents();
	void Render();
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
private:
	sf::RenderWindow window;
};

#endif // HEX_GAME_H_