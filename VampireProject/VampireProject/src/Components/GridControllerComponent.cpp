#include <limits>
#include <iostream>
#include "GridControllerComponent.hpp"
#include "../Math/Utils.hpp"
#include "../Math/Quaternion.hpp"
#include "../Core/Locator.hpp"
#include "../Components/TriangleRenderComponent.hpp"
#include "../GameObjects/TriangleTile.hpp"
#include "../GameObjects/PivotNode.hpp"

GridControllerComponent::GridControllerComponent(sf::Vector2i dimensions, float tileSize, sf::Vector2f position):
    dimensions(dimensions), triangleBase(tileSize), position(position) {
	triangleHeight = tileSize * 0.866025f;
	triangleRad = tileSize * 0.5773350269f;
    nodePositionList = std::vector<sf::Vector2f>(dimensions.x * dimensions.y);
    pivotNodeList = std::vector<std::unique_ptr<PivotNode>>(dimensions.x * dimensions.y);
    triangleTileList = std::vector<std::unique_ptr<TriangleTile>>((dimensions.x-1) * (dimensions.y - 1) * 2);
    targetConfiguration = std::vector<TileConfiguration>((dimensions.x-1) * (dimensions.y - 1) * 2);

    for (int i = 0; i < dimensions.x * dimensions.y; ++i) {
        int x = i%dimensions.x;
        int y = i/dimensions.x;
        nodePositionList[i] = sf::Vector2f(
            (x * tileSize) + (y%2==1?tileSize*0.5f:0) ,
            (y * triangleHeight)
        );
    }
}

GridControllerComponent::~GridControllerComponent() { }

void GridControllerComponent::FixedUpdateImplementation() { }

void GridControllerComponent::VarUpdateImplementation() { 
    Input& inputService = Locator::GetInput();

    if (inputService.GetMousePressed(sf::Mouse::Left)) OnMousePress();
    if (inputService.GetMouseReleased(sf::Mouse::Left)) OnMouseRelease();

    OnMouseMove(inputService.GetMousePosition());
}

void GridControllerComponent::RenderImplementation() {
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

bool GridControllerComponent::SetPivotNode(int x, int y) {
    if (!(x > 0 && x < dimensions.x - 1 && y > 0 && y < dimensions.y))
        return false;
    (pivotNodeList[y*dimensions.x + x]) = std::unique_ptr<PivotNode>(new PivotNode());
    return true;
}

bool GridControllerComponent::RemovePivotNode(int x, int y) {
    if (!(x >= 1 && y >= 1 && x < dimensions.x - 1 && y < dimensions.y))
        return false;
    (pivotNodeList[y*dimensions.x + x]) = std::unique_ptr<PivotNode>(nullptr);
    return true;
}

bool GridControllerComponent::SetTriangleTile(int x, int y, TileConfiguration configuration) {
    if (!(x >= 0 && y >= 0 && x < (dimensions.x - 1) * 2 && y < (dimensions.y - 1)))
        return false;
    targetConfiguration[y * (dimensions.x-1)*2 + x] = configuration;
}

void GridControllerComponent::GenerateTriangles() {
    int length = (dimensions.x-1) * (dimensions.y - 1) * 2;
    for (int i = 0; i < length; ++i) {
        triangleTileList[i] = nullptr;
        int x = i % ((dimensions.x-1) * 2);
        int y = i / ((dimensions.x-1) * 2);
        TileConfiguration config = targetConfiguration[i];
        triangleTileList[i] = std::unique_ptr<TriangleTile>(new TriangleTile(
            sf::Vector2f(triangleBase * 0.5f * (1 + x), y * triangleHeight + ((x + y) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position,
            triangleBase,
            sf::Color(config.GetColor()),
            ((x + y) % 2 == 0 ? 180 : 0) + config.GetNormDir() * 120, 
            config
        ));
    }
}

void GridControllerComponent::Scramble(int iterations) {
    std::vector<int> availableNodes = std::vector<int>();
    for (int i = 0; i < dimensions.x * dimensions.y; ++i) 
        if (pivotNodeList[i] != nullptr)
            availableNodes.push_back(i);
    for (int i = 0; i < iterations; ++i) {
        int rndNode = rand() % availableNodes.size();
        int rndDir = rand() % 2;

        if (rndDir == 0)
            RotateLeft(availableNodes[rndNode]);
        else
            RotateRight(availableNodes[rndNode]);
    }
}

bool GridControllerComponent::CheckTargetStatus() {
    // TODO Implement
    return false;
}


bool GridControllerComponent::RemoveTriangleTile(int x, int y) {
    if (!(x >= 0 && y >= 0 && x < (dimensions.x - 1) * 2 && y < (dimensions.y - 1)))
        return false;
    triangleTileList[y * dimensions.x + x] = std::unique_ptr<TriangleTile>(nullptr);
    return true;
}

bool GridControllerComponent::CheckTrianglePivotNeighbour(int x, int y) {
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

void GridControllerComponent::OnMousePress() {
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

void GridControllerComponent::OnMouseRelease() {
    if (currentSelectedNode != -1) ResetPosition(currentSelectedNode);
    currentSelectedNode = -1;
}

void GridControllerComponent::OnMouseMove(sf::Vector2f mousePosition) {
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

            RotateNode(currentSelectedNode);
        }
    }
}

void GridControllerComponent::RotateRight(int node) {
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
            TriangleRenderComponent& trc = triangleTileList[triangleIndices[i]]->GetTriangleRenderComponent();

            int tx = triangleIndices[i] % ((dimensions.x-1)*2);
            int ty = triangleIndices[i] / ((dimensions.x-1)*2);
            trc.SetRotationAngle(trc.GetRotationAngle() + 60);
            trc.SetPosition(sf::Vector2f(triangleBase * 0.5f * (1 + tx), ty * triangleHeight + ((tx + ty) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position);
        }
    }
}

void GridControllerComponent::RotateLeft(int node) {
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
            TriangleRenderComponent& trc = triangleTileList[triangleIndices[i]]->GetTriangleRenderComponent();

            int tx = triangleIndices[i] % ((dimensions.x-1)*2);
            int ty = triangleIndices[i] / ((dimensions.x-1)*2);
            trc.SetRotationAngle(trc.GetRotationAngle() - 60);
            trc.SetPosition(sf::Vector2f(triangleBase * 0.5f * (1 + tx), ty * triangleHeight + ((tx + ty) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position);
        }
    }
}

void GridControllerComponent::ResetPosition(int node) {
    int nx = node % dimensions.x;
    int ny = node / dimensions.x;
    int dx = (dimensions.x-1)*2;
    int dy = (dimensions.y-1);

    if (nx > 0 && ny > 0 && nx < dimensions.x - 1 && ny < dimensions.y - 1) {
        int triangleIndices[6];

        for (int i = 0; i < 6; ++i) triangleIndices[i] = (ny - 1 + i/3)*dx + (nx-1)*2 + (i/3==0?i%3:2-i%3) + (ny%2);

        for (int i = 0; i < 6; ++i) {
            TriangleRenderComponent& trc = triangleTileList[triangleIndices[i]]->GetTriangleRenderComponent();

            int tx = triangleIndices[i] % ((dimensions.x-1)*2);
            int ty = triangleIndices[i] / ((dimensions.x-1)*2);
            trc.SetRotationAngle(i * 60);
            trc.SetPosition(sf::Vector2f(triangleBase * 0.5f * (1 + tx), ty * triangleHeight + ((tx + ty) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) + position);
        }
    }
}

void GridControllerComponent::RotateNode(int node) {
    int nx = node % dimensions.x;
    int ny = node / dimensions.x;
    int dx = (dimensions.x-1)*2;
    int dy = (dimensions.y-1);
    Quaternion rotation = Quaternion::LookRotation(Vector2fToVector3f(hexRotationReference), Vector3fNormalized(Vector2fToVector3f(mousePosition - nodePositionList[currentSelectedNode] - position)));
    sf::Vector2f mouseDir = Vector2fNormalized(mousePosition - nodePositionList[currentSelectedNode] - position);
    // float rotationAngle = acos(Vector2fDot(hexRotationReference, Vector2fNormalized(mousePosition - nodePositionList[currentSelectedNode] - position))) * 180 / 3.1416;
    float rotationAngle = acos(rotation.w) * 2 * 180 / 3.1416 * (Vector2fDot(Vector2fPerp(hexRotationReference), mouseDir) > 0 ? -1 : 1);
    std::cout << rotationAngle << std::endl;
    std::cout << "Ref:  " << Vector2fToVector3f(hexRotationReference) << std::endl;
    std::cout << "Dis:  " << Vector2fNormalized(mousePosition - nodePositionList[node]) << std::endl;
    std::cout << "Mouse: " << mousePosition << std::endl;
    std::cout << "Node:  " <<  nodePositionList[node] - position << std::endl;

    if (nx > 0 && ny > 0 && nx < dimensions.x - 1 && ny < dimensions.y - 1) {
        int triangleIndices[6];

        for (int i = 0; i < 6; ++i) triangleIndices[i] = (ny - 1 + i/3)*dx + (nx-1)*2 + (i/3==0?i%3:2-i%3) + (ny%2);

        for (int i = 0; i < 6; ++i) {
            TriangleRenderComponent& trc = triangleTileList[triangleIndices[i]]->GetTriangleRenderComponent();

            int tx = triangleIndices[i] % ((dimensions.x-1)*2);
            int ty = triangleIndices[i] / ((dimensions.x-1)*2);
            trc.SetRotationAngle(i * 60 - rotationAngle);
            trc.SetPosition(
                Vector3fToVector2f(
                    rotation * Vector2fToVector3f(
                        sf::Vector2f(triangleBase * 0.5f * (1 + tx), ty * triangleHeight + ((tx + ty) % 2 == 0 ? triangleHeight - triangleRad : triangleRad)) 
                        - nodePositionList[currentSelectedNode])
                ) + nodePositionList[currentSelectedNode] + position
            );
        }
    }
}
