#include "Grid.hpp"

Grid::Grid(sf::Vector2i dimensions, float tileSize, sf::Vector2f position):
    dimensions(dimensions), triangleBase(tileSize), position(position) {
	triangleHeight = tileSize * 0.866025f;
	triangleRad = tileSize * 0.5773350269f;
    nodePositionList = std::vector<sf::Vector2f>(dimensions.x * dimensions.y);
    pivotNodeList = std::vector<std::unique_ptr<PivotNode>>(dimensions.x * dimensions.y);
    triangleTileList = std::vector<std::unique_ptr<TriangleTile>>((dimensions.x-1) * (dimensions.y - 1) * 2);

    for (int i = 0; i < dimensions.x * dimensions.y; ++i) {
        int x = i%dimensions.x;
        int y = i/dimensions.x;
        nodePositionList[i] = sf::Vector2f(
            (x * tileSize) + (y%2==1?tileSize*0.5f:0) ,
            (y * triangleHeight)
        );
    }
}

Grid::~Grid() {
    // TODO Implement
}

void Grid::UpdateImplementation(float dt) {
    // TODO Implement

}

void Grid::DrawImplementation(sf::RenderWindow& rw) {
    for (auto& triangleTile : triangleTileList)
		if (triangleTile != nullptr) triangleTile->Draw(rw);

    for (int y = 0; y < dimensions.y; ++y) {
        for (int x = 0; x < dimensions.x; ++x) {
            sf::CircleShape circle;
            circle.setRadius(3);
            circle.setOrigin(3,3);
            circle.setFillColor(pivotNodeList[y*dimensions.x + x] != nullptr ? sf::Color(255,0,0) : sf::Color(255,255,255));
            circle.setPosition(nodePositionList[y * dimensions.x + x] + position);
            rw.draw(circle);
        }
    }
}

bool Grid::SetPivotNode(int x, int y) {
    if (!(x > 0 && x < dimensions.x - 1 && y > 0 && y < dimensions.y))
        return false;
    (pivotNodeList[y*dimensions.x + x]) = std::unique_ptr<PivotNode>(new PivotNode());
    return true;
}

bool Grid::RemovePivotNode(int x, int y) {
    if (!(x >= 1 && y >= 1 && x < dimensions.x - 1 && y < dimensions.y))
        return false;
    (pivotNodeList[y*dimensions.x + x]) = std::unique_ptr<PivotNode>(nullptr);
    return true;
}

bool Grid::SetTriangleTile(int x, int y, sf::Color color) {
    if (!(x >= 0 && y >= 0 && x < (dimensions.x - 1) * 2 && y < (dimensions.y - 1)))
        return false;
    triangleTileList[y * (dimensions.x-1)*2 + x] = std::unique_ptr<TriangleTile>(new TriangleTile(
        sf::Vector2f(triangleBase * 0.5f * (1 + x), y * triangleHeight + ((x + y) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position,
        triangleBase,
        color,
        (x + y) % 2 == 0 ? 180 : 0));
    return true;
}

void Grid::GenerateMissingTriangles(sf::Color color) {
    for (int y = 0; y < (dimensions.y - 1); ++y) {
        for (int x = 0; x < (dimensions.x - 1) * 2; ++x) {
            if (triangleTileList[y * (dimensions.x-1)*2 + x] == nullptr) {
                if (CheckTrianglePivotNeighbour(x, y)) {
                    SetTriangleTile(x, y, color);
                }
            }
        }
    }
}

bool Grid::RemoveTriangleTile(int x, int y) {
    if (!(x >= 0 && y >= 0 && x < (dimensions.x - 1) * 2 && y < (dimensions.y - 1)))
        return false;
    triangleTileList[y * dimensions.x + x] = std::unique_ptr<TriangleTile>(nullptr);
    return true;
}

bool Grid::CheckTrianglePivotNeighbour(int x, int y) {
    if (!(x >= 0 && y >= 0 && x < (dimensions.x - 1) * 2 && y < (dimensions.y - 1)))
        return false;

    int baseX = x/2;
    int baseY = y;
    int sector = (y%2<<1) | x%2;
    switch (sector) {
        case 0:
            return 
                pivotNodeList[(baseY + 0)*dimensions.x + (baseX + 0)] != nullptr ||
                pivotNodeList[(baseY + 0)*dimensions.x + (baseX + 1)] != nullptr ||
                pivotNodeList[(baseY + 1)*dimensions.x + (baseX + 0)] != nullptr
            ;
        break;
        case 1:
            return 
                pivotNodeList[(baseY + 0)*dimensions.x + (baseX + 1)] != nullptr ||
                pivotNodeList[(baseY + 1)*dimensions.x + (baseX + 1)] != nullptr ||
                pivotNodeList[(baseY + 1)*dimensions.x + (baseX + 0)] != nullptr
            ;
        break;
        case 2:
            return 
                pivotNodeList[(baseY + 0)*dimensions.x + (baseX + 0)] != nullptr ||
                pivotNodeList[(baseY + 1)*dimensions.x + (baseX + 1)] != nullptr ||
                pivotNodeList[(baseY + 1)*dimensions.x + (baseX + 0)] != nullptr
            ;
        break;
        case 3:
            return 
                pivotNodeList[(baseY + 0)*dimensions.x + (baseX + 0)] != nullptr ||
                pivotNodeList[(baseY + 0)*dimensions.x + (baseX + 1)] != nullptr ||
                pivotNodeList[(baseY + 1)*dimensions.x + (baseX + 1)] != nullptr
            ;
        break;
    }
    return false;
}