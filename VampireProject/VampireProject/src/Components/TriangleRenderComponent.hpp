#ifndef HEX_TRIANGLE_RENDER_COMPONENT_H_
#define HEX_TRIANGLE_RENDER_COMPONENT_H_

#include "../Core/Component.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class TriangleRenderComponent: public Component<TriangleRenderComponent> {
public:
	TriangleRenderComponent(sf::Vector2f position, float size, sf::Color color = sf::Color(255,255,255), float rotationAngle = 0);
public:
    float GetRotationAngle();
	void SetRotationAngle(float angle);
	float GetSize();
	void SetSize(float size);
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	sf::Color GetColor();
	void SetColor(sf::Color color);
public:
    void FixedUpdateImplementation() {}
    void VarUpdateImplementation() {}
    void RenderImplementation();
private:
    float size;
    sf::ConvexShape shape;
    sf::ConvexShape pointer;
	sf::Sprite sprite;
};

#endif // HEX_TRIANGLE_RENDER_COMPONENT_H_
