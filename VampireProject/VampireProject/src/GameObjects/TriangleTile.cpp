#include "TriangleTile.hpp"
#include "../Math/Quaternion.hpp"
#include "../Math/Utils.hpp"

TriangleTile::TriangleTile(sf::Vector2f position, float size, sf::Color color, float rotationAngle) :
    position(position), size(size), color(color), rotationAngle(rotationAngle) {
    shape.setPointCount(3);
    float rad = size * 0.58;
    for (int i = 0; i < 3; ++i) {
        sf::Vector3f point = Quaternion::AngleAxis(i*120.f, sf::Vector3f(0,0,1)) * sf::Vector3f(0,-rad,0);
        shape.setPoint(i, Vector3fToVector2f(point));
    }
    shape.setFillColor(color);
    shape.setRotation(rotationAngle);
    shape.setPosition(position);

}

TriangleTile::~TriangleTile() {

}

void TriangleTile::FixedUpdateImplementation(float dt) {

}

void TriangleTile::VarUpdateImplementation(float dt) {

}

void TriangleTile::RenderImplementation(sf::RenderWindow& rw) {
    rw.draw(shape);
}


