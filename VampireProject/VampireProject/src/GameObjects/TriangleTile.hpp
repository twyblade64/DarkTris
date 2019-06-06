#ifndef HEX_TRIANGLETILE_H_
#define HEX_TRIANGLETILE_H_

#include "GameObject.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../Components/TriangleRenderComponent.hpp"
#include "../Components/TileConfigurationComponent.hpp"

class TriangleTile : public GameObject<TriangleTile> {
public:
	TriangleTile(sf::Vector2f position, float size, sf::Color color = sf::Color(255,255,255), float rotationAngle = 0, TileConfiguration configuration = TileConfiguration());
	~TriangleTile();
public:
	TriangleRenderComponent& GetTriangleRenderComponent();
	TileConfigurationComponent& GetConfigurationComponent();
public:
	void FixedUpdateImplementation();
	void VarUpdateImplementation();
	void RenderImplementation();
private:
	TriangleRenderComponent mTriangleRenderComponent;
	TileConfigurationComponent mTileConfigurationComponent;
};

#endif // HEX_TRIANGLETILE_H_

