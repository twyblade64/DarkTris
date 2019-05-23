#ifndef HEX_GRID_H_
#define HEX_GRID_H_

#include "../GameObjects/GameObject.hpp"
#include "../Components/GridControllerComponent.hpp"

class Grid : public GameObject<Grid> {
public:
	Grid(sf::Vector2f position, sf::Vector2i dimensions, float tileSize);
	~Grid();
public:
	void FixedUpdateImplementation();
	void VarUpdateImplementation();
	void RenderImplementation();
public:
	GridControllerComponent& GetGridController();
private:
	GridControllerComponent mGridControllerComponent;
};

#endif // HEX_GRID_H_