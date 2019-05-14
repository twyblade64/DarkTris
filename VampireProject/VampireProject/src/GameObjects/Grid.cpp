#include <limits>
#include "Grid.hpp"
#include "../Math/Utils.hpp"
#include "../Math/Quaternion.hpp"
#include "../Core/Locator.hpp"
#include "../Components/TriangleRenderComponent.hpp"

Grid::Grid(sf::Vector2i dimensions, float tileSize, sf::Vector2f position):
    mGridControllerComponent(dimensions, tileSize, position) {
}

Grid::~Grid() { }

void Grid::FixedUpdateImplementation() {
    mGridControllerComponent.FixedUpdate();
}

void Grid::VarUpdateImplementation() {
    mGridControllerComponent.VarUpdate();
}

void Grid::RenderImplementation() {
    mGridControllerComponent.Render();
}

GridControllerComponent& Grid::GetGridController() {
    return mGridControllerComponent;
}
