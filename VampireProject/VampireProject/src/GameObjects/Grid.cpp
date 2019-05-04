#include <limits>
#include "Grid.hpp"
#include "../Math/Utils.hpp"
#include "../Math/Quaternion.hpp"
#include "../Core/Locator.hpp"

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

void Grid::FixedUpdateImplementation() {

}

void Grid::VarUpdateImplementation() {
    // TODO Implement

}

void Grid::RenderImplementation() {
    sf::RenderWindow& rw = Locator::GetWindow().GetRenderWindow();
    for (auto& triangleTile : triangleTileList)
		if (triangleTile != nullptr) triangleTile->Render();

    sf::CircleShape circle;
    circle.setRadius(3);
    circle.setOrigin(3,3);
    for (int y = 0; y < dimensions.y; ++y) {
        for (int x = 0; x < dimensions.x; ++x) {
            circle.setFillColor(pivotNodeList[y*dimensions.x + x] != nullptr ? sf::Color(255,0,0) : sf::Color(255,255,255));
            circle.setPosition(nodePositionList[y * dimensions.x + x] + position);
            rw.draw(circle);
        }
    }

    if (currentSelectedNode != -1) {
        sf::ConvexShape hex;
        hex.setPointCount(6);
        for (int i = 0; i < 6; ++i) hex.setPoint(i, Vector3fToVector2f(Quaternion::AngleAxis(30.f + 60.f*i, sf::Vector3f(0,0,1)) * sf::Vector3f(0,triangleBase,0)));
        hex.setFillColor(sf::Color::Transparent);
        hex.setOutlineColor(sf::Color::White);
        hex.setOutlineThickness(2.f);
        hex.setPosition(nodePositionList[currentSelectedNode] + position);
        rw.draw(hex);
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

bool Grid::SetTriangleTile(int x, int y, sf::Color color, int dir) {
    if (!(x >= 0 && y >= 0 && x < (dimensions.x - 1) * 2 && y < (dimensions.y - 1)))
        return false;
    triangleTileList[y * (dimensions.x-1)*2 + x] = std::unique_ptr<TriangleTile>(new TriangleTile(
        sf::Vector2f(triangleBase * 0.5f * (1 + x), y * triangleHeight + ((x + y) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position,
        triangleBase,
        color,
        ((x + y) % 2 == 0 ? 180 : 0) + dir * 120));
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

void Grid::OnMousePress(sf::Vector2f mousePosition) {
    // TODO IMPLEMENT
    // Find selected node
    int closestNode = -1;
    float closestNodeDistSqr = std::numeric_limits<float>::max();
    for (int i = 0; i < pivotNodeList.size(); ++i) {
        if (pivotNodeList[i] != nullptr) {
            float dist = Vector2fLengthSqr((nodePositionList[i] + position) - mousePosition);
            if (dist < closestNodeDistSqr) {
                closestNodeDistSqr = dist;
                closestNode = i;
            }
        }
    }

    if (closestNode != -1) {
        currentSelectedNode = closestNode;
        hexRotationReference = Vector2fNormalized(mousePosition - (nodePositionList[closestNode] + position));
    }

    // Store mouse position
    this->mouseDragStart = mousePosition;
    this->mousePosition = mousePosition;
    this->mousePositionPrev = mousePosition;
    this->mousePositionDelta = sf::Vector2f(0,0);
}

void Grid::OnMouseRelease(sf::Vector2f mousePosition) {
    // TODO Implement new triangle states
    currentSelectedNode = -1;
}

void Grid::OnMouseMove(sf::Vector2f mousePosition) {
    this->mousePositionPrev = this->mousePosition;
    this->mousePosition = mousePosition;
    this->mousePositionDelta = this->mousePosition - this->mousePositionPrev;

    if (currentSelectedNode != -1) {
        // check angle
        sf::Vector2f dist = mousePosition - (nodePositionList[currentSelectedNode] + position);
        if (Vector2fLengthSqr(dist) > 0) {
            sf::Vector2f dir = Vector2fNormalized(dist);
            if (Vector2fDot(dir, hexRotationReference) < 0.866025403f) {
                if (Vector2fDot(dir, Vector2fPerp(hexRotationReference)) > 0) {
                    RotateRight(currentSelectedNode);
                    hexRotationReference = Vector3fToVector2f(Quaternion::AngleAxis(60, sf::Vector3f(0,0,1)) * Vector2fToVector3f(hexRotationReference));
                } else {
                    RotateLeft(currentSelectedNode);
                    hexRotationReference = Vector3fToVector2f(Quaternion::AngleAxis(-60, sf::Vector3f(0,0,1)) * Vector2fToVector3f(hexRotationReference));
                }
            }
        }
    }
}

void Grid::RotateRight(int node) {
    printf("Rotate Right\n");
    int nx = node % dimensions.x;
    int ny = node / dimensions.x;
    int dx = (dimensions.x-1)*2;
    int dy = (dimensions.y-1);

    if (nx > 0 && ny > 0 && nx < dimensions.x - 1 && ny < dimensions.y - 1) {
        int triangleIndices[6];
        std::unique_ptr<TriangleTile> tempTiles[6];

        for (int i = 0; i < 6; ++i) {
            triangleIndices[i] = (ny - 1 + i/3)*dx + (nx-1)*2 + (i/3==0?i%3:2-i%3) + (ny%2);
            tempTiles[i] = std::move(triangleTileList[triangleIndices[i]]);
        }

        for (int i = 0; i < 6; ++i) {
            triangleTileList[triangleIndices[i]] = std::move(tempTiles[(i+6-1)%6]);
            TriangleTile& tile = *triangleTileList[triangleIndices[i]];

            int tx = triangleIndices[i] % ((dimensions.x-1)*2);
            int ty = triangleIndices[i] / ((dimensions.x-1)*2);
            tile.SetRotationAngle(tile.GetRotationAngle() + 60);
            tile.SetPosition(sf::Vector2f(triangleBase * 0.5f * (1 + tx), ty * triangleHeight + ((tx + ty) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position);
        }
    }
}

void Grid::RotateLeft(int node) {
    printf("Rotate left\n");
    int nx = node % dimensions.x;
    int ny = node / dimensions.x;
    int dx = (dimensions.x-1)*2;
    int dy = (dimensions.y-1);

    if (nx > 0 && ny > 0 && nx < dimensions.x - 1 && ny < dimensions.y - 1) {
        int triangleIndices[6];
        std::unique_ptr<TriangleTile> tempTiles[6];

        for (int i = 0; i < 6; ++i) {
            triangleIndices[i] = (ny - 1 + i/3)*dx + (nx-1)*2 + (i/3==0?i%3:2-i%3) + (ny%2);
            tempTiles[i] = std::move(triangleTileList[triangleIndices[i]]);
        }

        for (int i = 0; i < 6; ++i) {
            triangleTileList[triangleIndices[i]] = std::move(tempTiles[(i+6+1)%6]);
            TriangleTile& tile = *triangleTileList[triangleIndices[i]];

            int tx = triangleIndices[i] % ((dimensions.x-1)*2);
            int ty = triangleIndices[i] / ((dimensions.x-1)*2);
            tile.SetRotationAngle(tile.GetRotationAngle() - 60);
            tile.SetPosition(sf::Vector2f(triangleBase * 0.5f * (1 + tx), ty * triangleHeight + ((tx + ty) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position);
        }
    }
}
