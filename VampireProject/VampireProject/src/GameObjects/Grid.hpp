#ifndef HEX_GRID_H_
#define HEX_GRID_H_

#include <vector>
#include <memory>
#include "GameObject.hpp"
#include "TriangleTile.hpp"
#include "PivotNode.hpp"

class Grid : public GameObject<Grid> {
public:
	Grid(sf::Vector2i dimensions, float tileSize, sf::Vector2f position = sf::Vector2f(0,0));
	~Grid();
public:
	void UpdateImplementation(float dt);
	void DrawImplementation(sf::RenderWindow& rw);
public:
	bool SetPivotNode(int x, int y);
	bool RemovePivotNode(int x, int y);
	bool SetTriangleTile(int x, int y, sf::Color = sf::Color(255, 255, 255));
	void GenerateMissingTriangles(sf::Color = sf::Color(255,255,255));
	bool RemoveTriangleTile(int x, int y);
	bool CheckTrianglePivotNeighbour(int x, int y);
private:
	sf::Vector2f position;
	sf::Vector2i dimensions;
	float triangleBase;
	float triangleHeight;
	float triangleRad;
private:
	int currentSelectedNode;
	sf::Vector2f mouseDragStart;
	sf::Vector2f mousePrevPosition;
private:
	std::vector<sf::Vector2f> nodePositionList;
	std::vector<std::unique_ptr<TriangleTile>> triangleTileList;
	std::vector<std::unique_ptr<PivotNode>> pivotNodeList;
};

#endif // HEX_GRID_H_