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
	void FixedUpdateImplementation();
	void VarUpdateImplementation();
	void RenderImplementation();
public:
	float GetRotationAngle();
	void SetRotationAngle(float angle);
	float GetSize();
	void SetSize(float size);
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	sf::Color GetColor();
	void SetColor(sf::Color color);
private:
	float size;
	sf::ConvexShape shape;
	sf::ConvexShape pointer;
};

#endif // HEX_TRIANGLETILE_H_

