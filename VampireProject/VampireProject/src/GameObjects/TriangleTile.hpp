#ifndef HEX_TRIANGLETILE_H_
#define HEX_TRIANGLETILE_H_

#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../Components/TriangleRenderComponent.hpp"

class TriangleTile : public GameObject<TriangleTile> {
public:
	TriangleTile(sf::Vector2f position, float size, sf::Color color = sf::Color(255,255,255), float rotationAngle = 0);
	~TriangleTile();
public:
	TriangleRenderComponent& GetTriangleRenderComponent();
public:
	void FixedUpdateImplementation();
	void VarUpdateImplementation();
	void RenderImplementation();
private:
	TriangleRenderComponent mTriangleRenderComponent;
};

#endif // HEX_TRIANGLETILE_H_

