#ifndef HEX_TRIANGLETILE_H_
#define HEX_TRIANGLETILE_H_

#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class TriangleTile : public GameObject<TriangleTile> {
public:
	TriangleTile(sf::Vector2f position, float size, sf::Color color = sf::Color(255,255,255), float rotationAngle = 0);
	~TriangleTile();
public:
	float GetRotationAngle();
	void SetRotationAngle();
	float SetSize();
	void GetSize();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	sf::Color GetColor();
	void SetColor();
public:
	void UpdateImplementation(float dt);
	void DrawImplementation(sf::RenderWindow& rw);
private:
	float rotationAngle;
	float size;
	sf::Vector2f position;
	sf::Color color;
	sf::ConvexShape shape;
};

#endif // HEX_TRIANGLETILE_H_

