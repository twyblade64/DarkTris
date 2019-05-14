#ifndef HEX_GRID_CONTROLLER_COMPONENT_H_
#define HEX_GRID_CONTROLLER_COMPONENT_H_

#include <vector>
#include <memory>
#include "../GameObjects/GameObject.hpp"
#include "../GameObjects/TriangleTile.hpp"
#include "../GameObjects/PivotNode.hpp"
#include "../Core/Component.hpp"

class GridControllerComponent : public Component<GridControllerComponent> {
public:
	GridControllerComponent(sf::Vector2i dimensions, float tileSize, sf::Vector2f position = sf::Vector2f(0,0));
	~GridControllerComponent();
public:
	void FixedUpdateImplementation();
	void VarUpdateImplementation();
	void RenderImplementation();
public:
	bool SetPivotNode(int x, int y);
	bool RemovePivotNode(int x, int y);
	bool SetTriangleTile(int x, int y, sf::Color = sf::Color(255, 255, 255), int dir = 0);
	void GenerateMissingTriangles(sf::Color = sf::Color(255,255,255));
	bool RemoveTriangleTile(int x, int y);
	bool CheckTrianglePivotNeighbour(int x, int y);
public:
	void OnMousePress();
	void OnMouseRelease();
	void OnMouseMove(sf::Vector2f mousePosition);
private:
	void RotateRight(int node);
	void RotateLeft(int node);
private:
	sf::Vector2f position;
	sf::Vector2i dimensions;
	float triangleBase;
	float triangleHeight;
	float triangleRad;
private:
	int currentSelectedNode = -1;
	sf::Vector2f hexRotationReference;
	sf::Vector2f mouseDragStart;
	sf::Vector2f mousePosition;
	sf::Vector2f mousePositionPrev;
	sf::Vector2f mousePositionDelta;
private:
	std::vector<sf::Vector2f> nodePositionList;
	std::vector<std::unique_ptr<TriangleTile>> triangleTileList;
	std::vector<std::unique_ptr<PivotNode>> pivotNodeList;
};

#endif // HEX_GRID_CONTROLLER_COMPONENT_H_
