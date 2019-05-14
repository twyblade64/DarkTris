#include "TriangleTile.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Utils.hpp"
#include "../Core/Locator.hpp"

TriangleTile::TriangleTile(sf::Vector2f position, float size, sf::Color color, float rotationAngle) :
    mTriangleRenderComponent(position, size, color, rotationAngle) {

}

TriangleTile::~TriangleTile() {

}

void TriangleTile::FixedUpdateImplementation() {
    mTriangleRenderComponent.FixedUpdate();
}

void TriangleTile::VarUpdateImplementation() {
    mTriangleRenderComponent.VarUpdate();
}

void TriangleTile::RenderImplementation() {
    mTriangleRenderComponent.Render();
}

TriangleRenderComponent& TriangleTile::GetTriangleRenderComponent() {
    return mTriangleRenderComponent;
}
