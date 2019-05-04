#include "TriangleRenderComponent.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Utils.hpp"

TriangleRenderComponent::TriangleRenderComponent(sf::Vector2f position, float size, sf::Color color, float rotationAngle) :
    size(size) {
    shape.setPointCount(3);
    float rad = size * 0.58;
    for (int i = 0; i < 3; ++i) {
        sf::Vector3f point = Quaternion::AngleAxis(i*120.f, sf::Vector3f(0,0,1)) * sf::Vector3f(0,-rad,0);
        shape.setPoint(i, Vector3fToVector2f(point));
    }
    shape.setFillColor(color);
    shape.setRotation(rotationAngle);
    shape.setPosition(position);

    float sep = size * 0.86602 - rad;
    pointer.setPointCount(3);
    for (int i = 0; i < 3; ++i) {
        sf::Vector3f point = Quaternion::AngleAxis(i*120.f, sf::Vector3f(0,0,1)) * sf::Vector3f(0,-rad*0.25f,0);
        pointer.setPoint(i, Vector3fToVector2f(point));
    }
    pointer.setOrigin(sf::Vector2f(0,sep));
    pointer.setFillColor(sf::Color(50,50,50));
    pointer.setRotation(rotationAngle);
    pointer.setPosition(position);
}

void TriangleRenderComponent::RenderImplementation() {
    // Get RW
    //rw.draw(shape);
    //rw.draw(pointer);
}

float TriangleRenderComponent::GetRotationAngle() {
    return shape.getRotation();
}

void TriangleRenderComponent::SetRotationAngle(float angle) {
    shape.setRotation(angle);
    pointer.setRotation(angle);
}

float TriangleRenderComponent::GetSize() {
    return size;
}

void TriangleRenderComponent::SetSize(float size) {
    this->size = size;
    float rad = size * 0.58;
    for (int i = 0; i < 3; ++i) {
        sf::Vector3f point = Quaternion::AngleAxis(i*120.f, sf::Vector3f(0,0,1)) * sf::Vector3f(0,-rad,0);
        shape.setPoint(i, Vector3fToVector2f(point));
    }
}

sf::Vector2f TriangleRenderComponent::GetPosition() {
    return shape.getPosition();
}

void TriangleRenderComponent::SetPosition(sf::Vector2f position) {
    shape.setPosition(position);
    pointer.setPosition(position);
}

sf::Color TriangleRenderComponent::GetColor() {
    return shape.getFillColor();
}

void TriangleRenderComponent::SetColor(sf::Color color) {
    shape.setFillColor(color);
}