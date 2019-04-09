#ifndef HEX_TRIANGLETILE_H_
#define HEX_TRIANGLETILE_H_

#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class TriangleTile : GameObject<TriangleTile> {
public:
private:
	UpdateImplementation();
	DrawImplementation();
private:
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::vect
};

#endif // HEX_TRIANGLETILE_H_

